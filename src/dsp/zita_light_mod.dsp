import("stdfaust.lib");

zita_rev_fdn(f1,f2,t60dc,t60m,fsmax) =
  ((si.bus(2*N) :> allpass_combs(N) : feedbackmatrix(N)) ~
   (delayfilters(N,freqs,durs) : fbdelaylines(N)))
with {
  N = 8;

  // Delay-line lengths in seconds:
  apdelays = (0.020346, 0.024421, 0.031604, 0.027333, 0.022904,
              0.029291, 0.013458, 0.019123); // feedforward delays in seconds
  tdelays = (0.153129, 0.210389, 0.127837, 0.256891, 0.174713,
             0.192303, 0.125000, 0.219991); // total delays in seconds
  tdelay(i) = floor(0.5 + ma.SR*ba.take(i+1,tdelays)); // samples
  apdelay(i) = floor(0.5 + ma.SR*ba.take(i+1,apdelays));
  fbdelay(i) = tdelay(i) - apdelay(i);
  // NOTE: Since SR is not bounded at compile time, we can't use it to
  // allocate delay lines; hence, the fsmax parameter:
  tdelaymaxfs(i) = floor(0.5 + fsmax*ba.take(i+1,tdelays));
  apdelaymaxfs(i) = floor(0.5 + fsmax*ba.take(i+1,apdelays));
  fbdelaymaxfs(i) = tdelaymaxfs(i) - apdelaymaxfs(i);
  nextpow2(x) = ceil(log(x)/log(2.0));
  maxapdelay(i) = int(2.0^max(1.0,nextpow2(apdelaymaxfs(i))));
  maxfbdelay(i) = int(2.0^max(1.0,nextpow2(fbdelaymaxfs(i)))) / 2;

  apcoeff(i) = select2(i&1,0.6,-0.6);  // allpass comb-filter coefficient
  allpass_combs(N) =
    par(i,N,(fi.allpass_comb(maxapdelay(i),apdelay(i),apcoeff(i)))); // filters.lib
  fbdelaylines(N) = par(i,N,(de.delay(maxfbdelay(i),(fbdelay(i)))));
  freqs = (f1,f2); durs = (t60dc,t60m);
  delayfilters(N,freqs,durs) = par(i,N,filter(i,freqs,durs));
  feedbackmatrix(N) = ro.hadamard(N);

  staynormal = 10.0^(-20); // let signals decay well below LSB, but not to zero

  special_lowpass(g,f) = si.smooth(p) with {
    // unity-dc-gain lowpass needs gain g at frequency f => quadratic formula:
    p = mbo2 - sqrt(max(0,mbo2*mbo2 - 1.0)); // other solution is unstable
    mbo2 = (1.0 - gs*c)/(1.0 - gs); // NOTE: must ensure |g|<1 (t60m finite)
    gs = g*g;
    c = cos(2.0*ma.PI*f/float(ma.SR));
  };

  filter(i,freqs,durs) = lowshelf_lowpass(i)/sqrt(float(N))+staynormal
  with {
    lowshelf_lowpass(i) = gM*low_shelf1_l(g0/gM,f(1)):special_lowpass(gM,f(2));
    low_shelf1_l(G0,fx,x) = x + (G0-1)*fi.lowpass(1,fx,x); // filters.lib
    g0 = g(0,i);
    gM = g(1,i);
    f(k) = ba.take(k,freqs);
    dur(j) = ba.take(j+1,durs);
    n60(j) = dur(j)*ma.SR; // decay time in samples
    g(j,i) = exp(-3.0*log(10.0)*tdelay(i)/n60(j));
  };
};

// Stereo input delay used by zita_rev1 in both stereo and ambisonics mode:
zita_in_delay(rdel) = zita_delay_mono(rdel), zita_delay_mono(rdel) with {
  zita_delay_mono(rdel) = de.delay(2700,ma.SR*rdel*0.001) * 0.3;
};

// Stereo input mapping used by zita_rev1 in both stereo and ambisonics mode:
zita_distrib2(N) = _,_ <: fanflip(N) with {
   fanflip(4) = _,_,*(-1),*(-1);
   fanflip(N) = fanflip(N/2),fanflip(N/2);
};


//----------------------------`(re.)zita_rev1_stereo`---------------------------
// Extend `zita_rev_fdn` to include `zita_rev1` input/output mapping in stereo mode.
// `zita_rev1_stereo` is a standard Faust function.
//
// #### Usage
//
// ```
// _,_ : zita_rev1_stereo(rdel,f1,f2,t60dc,t60m,fsmax) : _,_
// ```
//
// Where:
//
// `rdel`  = delay (in ms) before reverberation begins (e.g., 0 to ~100 ms)
// (remaining args and refs as for `zita_rev_fdn` above)
//------------------------------------------------------------
zita_rev1_stereo(rdel,f1,f2,t60dc,t60m,fsmax) =
   zita_in_delay(rdel)
 : zita_distrib2(N)
 : zita_rev_fdn(f1,f2,t60dc,t60m,fsmax)
 : output2(N)
with {
 N = 8;
 output2(N) = outmix(N) : *(t1),*(t1);
 t1 = 0.37; // zita-rev1 linearly ramps from 0 to t1 over one buffer
 outmix(4) = !,ro.butterfly(2),!; // probably the result of some experimenting!
 outmix(N) = outmix(N/2),par(i,N/2,!);
};


zita_rev1 = _,_ <: zita_rev1_stereo(rdel,f1,f2,t60dc,t60m,fsmax),_,_ : out_eq,_,_ :
	dry_wet : out_level
with{
	fsmax = 48000.0;  // highest sampling rate that will be used

	fdn_group(x) = hgroup(
	"", x);

	in_group(x) = fdn_group(hgroup("[1] Input", x));

	rdel = 60;
	freq_group(x) = fdn_group(hgroup("[2] Decay Times in Bands (see tooltips)", x));

	f1 = freq_group(vslider("[1] LF X [unit:Hz] [style:knob] [scale:log] [tooltip:
		Crossover frequency (Hz) separating low and middle frequencies]", 200, 50, 1000, 1));

	t60dc = freq_group(vslider("[2] Low RT60 [unit:s] [style:knob] [scale:log]
	[style:knob] [tooltip: T60 = time (in seconds) to decay 60dB in low-frequency band]",
	3, 1, 8, 0.1));

	t60m = freq_group(vslider("[3] Mid RT60 [unit:s] [style:knob] [scale:log] [tooltip:
		T60 = time (in seconds) to decay 60dB in middle band]",8, 1, 8, 0.1));

	f2 = freq_group(vslider("[4] HF Damping [unit:Hz] [style:knob] [scale:log]
	[tooltip: Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60]",
	6000, 1500, 0.49*fsmax, 1));

	out_eq = pareq_stereo(eq1f,eq1l,eq1q) : pareq_stereo(eq2f,eq2l,eq2q);
	// Zolzer style peaking eq (not used in zita-rev1) (filters.lib):
	// pareq_stereo(eqf,eql,Q) = peak_eq(eql,eqf,eqf/Q), peak_eq(eql,eqf,eqf/Q);
	// Regalia-Mitra peaking eq with "Q" hard-wired near sqrt(g)/2 (filters.lib):
	pareq_stereo(eqf,eql,Q) = fi.peak_eq_rm(eql,eqf,tpbt), fi.peak_eq_rm(eql,eqf,tpbt)
	with {
		tpbt = wcT/sqrt(max(0,g)); // tan(PI*B/SR), B bw in Hz (Q^2 ~ g/4)
		wcT = 2*ma.PI*eqf/ma.SR;  // peak frequency in rad/sample
		g = ba.db2linear(eql); // peak gain
	};

	eq1_group(x) = fdn_group(hgroup("[3] RM Peaking Equalizer 1", x));

	eq1f = eq1_group(vslider("[1] Eq1 Freq [unit:Hz] [style:knob] [scale:log] [tooltip:
		Center-frequency of second-order Regalia-Mitra peaking equalizer section 1]",
	315, 40, 2500, 1));

	eq1l = eq1_group(vslider("[2] Eq1 Level [unit:dB] [style:knob] [tooltip: Peak level
		in dB of second-order Regalia-Mitra peaking equalizer section 1]", -2, -15, 15, 0.1));

	eq1q = eq1_group(vslider("[3] Eq1 Q [style:knob] [tooltip: Q = centerFrequency/bandwidth
		of second-order peaking equalizer section 1]", 3, 0.1, 10, 0.1));

	eq2_group(x) = fdn_group(hgroup("[4] RM Peaking Equalizer 2", x));

	eq2f = eq2_group(vslider("[1] Eq2 Freq [unit:Hz] [style:knob] [scale:log] [tooltip:
		Center-frequency of second-order Regalia-Mitra peaking equalizer section 2]",
	1500, 160, 10000, 1));

	eq2l = eq2_group(vslider("[2] Eq2 Level [unit:dB] [style:knob] [tooltip: Peak level
		in dB of second-order Regalia-Mitra peaking equalizer section 2]", -2, -15, 15, 0.1));

	eq2q = eq2_group(vslider("[3] Eq2 Q [style:knob] [tooltip: Q = centerFrequency/bandwidth
		of second-order peaking equalizer section 2]", 3, 0.1, 10, 0.1));

	out_group(x)  = fdn_group(hgroup("[5] Output", x));

	dry_wet(x,y) = *(wet) + dry*x, *(wet) + dry*y with {
		wet = 0.5*(drywet+1.0);
		dry = 1.0-wet;
	};

	drywet = out_group(vslider("[1] Dry/Wet Mix [style:knob] [tooltip: -1 = dry, 1 = wet]",
	0, -1.0, 1.0, 0.01)) : si.smoo;

	out_level = *(gain),*(gain);

	gain = out_group(vslider("[2] Level [unit:dB] [style:knob] [tooltip: Output scale
		factor]", 0, -70, 40, 0.1)) : ba.db2linear : si.smoo;


};

process = zita_rev1;