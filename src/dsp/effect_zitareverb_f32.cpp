/* ------------------------------------------------------------
name: "AudioEffectZitaShimmerReverb_F32"
Code generated with Faust 2.28.6 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef __mydsp_H__
#define __mydsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

#include "effect_zitareverb_f32.h"
#include "faust_architecture.h"

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

int mydspSIG0::getNumInputsmydspSIG0()
{
	return 0;
}
int mydspSIG0::getNumOutputsmydspSIG0()
{
	return 1;
}
int mydspSIG0::getInputRatemydspSIG0(int channel)
{
	int rate;
	switch ((channel))
	{
	default:
	{
		rate = -1;
		break;
	}
	}
	return rate;
}
int mydspSIG0::getOutputRatemydspSIG0(int channel)
{
	int rate;
	switch ((channel))
	{
	case 0:
	{
		rate = 0;
		break;
	}
	default:
	{
		rate = -1;
		break;
	}
	}
	return rate;
}

void mydspSIG0::instanceInitmydspSIG0(int sample_rate)
{
	for (int l27 = 0; (l27 < 2); l27 = (l27 + 1))
	{
		iRec33[l27] = 0;
	}
}

void mydspSIG0::fillmydspSIG0(int count, float *table)
{
	for (int i = 0; (i < count); i = (i + 1))
	{
		iRec33[0] = (iRec33[1] + 1);
		table[i] = sin((9.58738019e-05f * float((iRec33[0] + -1))));
		iRec33[1] = iRec33[0];
	}
}

#ifndef FAUSTCLASS
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif

mydsp::~mydsp()
{
	freeExternalMemory();
}

/* FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[1] Input/predelay", fVslider10, 60.0f, 20.0f, 100.0f, 1.0f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[2] Reverb/LF X", fVslider9, 200.0f, 50.0f, 1000.0f, 1.0f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[2] Reverb/Low RT60", fVslider8, 3.0f, 1.0f, 8.0f, 0.10000000000000001f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[2] Reverb/Mid RT60", fVslider6, 8.0f, 1.0f, 8.0f, 0.10000000000000001f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[2] Reverb/HF Damping", fVslider7, 6000.0f, 1500.0f, 23520.0f, 1.0f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[3] EQ1/EQ1 freq", fVslider4, 315.0f, 40.0f, 2500.0f, 1.0f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[3] EQ1/EQ1 lvl", fVslider5, -2.0f, -15.0f, 15.0f, 0.10000000000000001f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[4] EQ2/Eq2 Freq", fVslider2, 1500.0f, 160.0f, 10000.0f, 1.0f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[4] EQ2/Eq2 Level", fVslider3, -2.0f, -15.0f, 15.0f, 0.10000000000000001f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[5] Output/Dry/Wet Mix", fVslider1, 0.0f, -1.0f, 1.0f, 0.01f);
FAUST_ADDVERTICALSLIDER("[0] AudioEffectZitaShimmerReverb/[5] Output/Level", fVslider0, 0.0f, -70.0f, 40.0f, 0.10000000000000001f);
FAUST_ADDVERTICALSLIDER("shimmer", fVslider11, 0.0f, -1.0f, 1.0f, 0.10000000000000001f); */

static mydspSIG0 *newmydspSIG0() { return (mydspSIG0 *)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0 *dsp) { delete dsp; }

void mydsp::classInit(int sample_rate)
{
	mydspSIG0 *sig0 = newmydspSIG0();
	sig0->instanceInitmydspSIG0(sample_rate);
	sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
}

void mydsp::allocateExternalMemory()
{
	fVec1 = (float *)extmem_malloc(sizeof(float) * 32768);
	fVec4 = (float *)extmem_malloc(sizeof(float) * 32768);
	fVec8 = (float *)extmem_malloc(sizeof(float) * 32768);
	fVec6 = (float *)extmem_malloc(sizeof(float) * 16384);
	fVec11 = (float *)extmem_malloc(sizeof(float) * 16384);
	fVec13 = (float *)extmem_malloc(sizeof(float) * 16384);
	fVec15 = (float *)extmem_malloc(sizeof(float) * 16384);
	fVec17 = (float *)extmem_malloc(sizeof(float) * 16384);
	fVec10 = (float *)malloc(sizeof(float) * 8192);
	fVec0 = (float *)malloc(sizeof(float) * 4096);
	fVec2 = (float *)malloc(sizeof(float) * 4096);
	fVec5 = (float *)malloc(sizeof(float) * 4096);
	fVec7 = (float *)malloc(sizeof(float) * 4096);
}

void mydsp::freeExternalMemory()
{
	extmem_free(fVec1);
	extmem_free(fVec4);
	extmem_free(fVec8);
	extmem_free(fVec6);
	extmem_free(fVec11);
	extmem_free(fVec13);
	extmem_free(fVec15);
	extmem_free(fVec17);
	free(fVec10);
	free(fVec0);
	free(fVec2);
	free(fVec5);
	free(fVec7);
}

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

#define MULT_16 2147483647
#define DIV_16 4.6566129e-10

unsigned __exidx_start;
unsigned __exidx_end;

AudioEffectZitaShimmerReverb_F32::AudioEffectZitaShimmerReverb_F32() : AudioStream_F32(2, new audio_block_f32_t *[2])
{
#ifdef NVOICES
	int nvoices = NVOICES;
	mydsp_poly *dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, true);
	fDSP = dsp_poly;
#else
	fDSP = new mydsp();
#endif

	fDSP->init(AUDIO_SAMPLE_RATE_EXACT);

	// allocating Faust inputs
	if (fDSP->getNumInputs() > 0)
	{
		fInChannel = new float *[fDSP->getNumInputs()];
		for (int i = 0; i < fDSP->getNumInputs(); i++)
		{
			fInChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
		}
	}
	else
	{
		fInChannel = NULL;
	}

	// allocating Faust outputs
	if (fDSP->getNumOutputs() > 0)
	{
		fOutChannel = new float *[fDSP->getNumOutputs()];
		for (int i = 0; i < fDSP->getNumOutputs(); i++)
		{
			fOutChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
		}
	}
	else
	{
		fOutChannel = NULL;
	}
}

AudioEffectZitaShimmerReverb_F32::~AudioEffectZitaShimmerReverb_F32()
{
	delete fDSP;
	//delete fUI;
	for (int i = 0; i < fDSP->getNumInputs(); i++)
	{
		delete[] fInChannel[i];
	}
	delete[] fInChannel;
	for (int i = 0; i < fDSP->getNumOutputs(); i++)
	{
		delete[] fOutChannel[i];
	}
	delete[] fOutChannel;
#if MIDICTRL
	delete fMIDIInterface;
	delete fMIDIHandler;
#endif
}

void AudioEffectZitaShimmerReverb_F32::updateImp(void)
{
#if MIDICTRL
	// Process the MIDI messages received by the Teensy
	fMIDIHandler->processMidi();
	// Synchronize all GUI controllers
	GUI::updateAllGuis();
#endif

	audio_block_f32_t *inBlock[2];
	for (int channel = 0; channel < 2; channel++)
	{
		inBlock[channel] = receiveReadOnly_f32(channel);
		if (!inBlock[channel])
			return;
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
		{
			fInChannel[channel][i] = inBlock[channel]->data[i];
		}
		release(inBlock[channel]);
	}

	fDSP->compute(AUDIO_BLOCK_SAMPLES, fInChannel, fOutChannel);

	for (int channel = 0; channel < 2; channel++)
	{
		audio_block_f32_t *outBlock[2];
		outBlock[channel] = allocate_f32();
		if (outBlock[channel])
		{
			for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			{
				outBlock[channel]->data[i] = fOutChannel[channel][i];
			}
			transmit(outBlock[channel], channel);
			release(outBlock[channel]);
		}
	}
}

void AudioEffectZitaShimmerReverb_F32::update(void) { updateImp(); }

#endif
