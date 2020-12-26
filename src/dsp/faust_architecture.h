/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale &
 Aalborg University (Copenhagen, Denmark)
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

/**
 * DSP memory manager.
 */

struct dsp_memory_manager
{

    virtual ~dsp_memory_manager() {}

    virtual void *allocate(size_t size) = 0;
    virtual void destroy(void *ptr) = 0;
};

/**
* Signal processor definition.
*/

class dsp
{

public:
    dsp() {}
    virtual ~dsp() {}

    /* Return instance number of audio inputs */
    virtual int getNumInputs() = 0;

    /* Return instance number of audio outputs */
    virtual int getNumOutputs() = 0;

    /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
    //virtual void buildUserInterface(UI* ui_interface) = 0;

    /* Returns the sample rate currently used by the instance */
    virtual int getSampleRate() = 0;

    /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hertz
         */
    virtual void init(int sample_rate) = 0;

    /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
    virtual void instanceInit(int sample_rate) = 0;

    /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
    virtual void instanceConstants(int sample_rate) = 0;

    /* Init default control parameters values */
    virtual void instanceResetUserInterface() = 0;

    /* Init instance state (delay lines...) */
    virtual void instanceClear() = 0;

    /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
    virtual dsp *clone() = 0;

    /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
    //virtual void metadata(Meta* m) = 0;

    /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved float samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved float samples (eiher float, double or quad)
         *
         */
    virtual void compute(int count, float **inputs, float **outputs) = 0;

    /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved float samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved float samples (either float, double or quad)
         *
         */
    virtual void compute(double /*date_usec*/, int count, float **inputs, float **outputs) { compute(count, inputs, outputs); }
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp
{

protected:
    dsp *fDSP;

public:
    decorator_dsp(dsp *dsp = nullptr) : fDSP(dsp) {}
    virtual ~decorator_dsp() { delete fDSP; }

    virtual int getNumInputs() { return fDSP->getNumInputs(); }
    virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
    //virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
    virtual int getSampleRate() { return fDSP->getSampleRate(); }
    virtual void init(int sample_rate) { fDSP->init(sample_rate); }
    virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
    virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
    virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
    virtual void instanceClear() { fDSP->instanceClear(); }
    virtual decorator_dsp *clone() { return new decorator_dsp(fDSP->clone()); }
    //virtual void metadata(Meta* m) { fDSP->metadata(m); }
    // Beware: subclasses usually have to overload the two 'compute' methods
    virtual void compute(int count, float **inputs, float **outputs) { fDSP->compute(count, inputs, outputs); }
    virtual void compute(double date_usec, int count, float **inputs, float **outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
};

/**
 * DSP factory class.
 */

class dsp_factory
{

protected:
    // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
    virtual ~dsp_factory() {}

public:
    virtual String getName() = 0;
    virtual String getSHAKey() = 0;
    virtual String getDSPCode() = 0;
    virtual String getCompileOptions() = 0;

    virtual dsp *createDSPInstance() = 0;

    virtual void setMemoryManager(dsp_memory_manager *manager) = 0;
    virtual dsp_memory_manager *getMemoryManager() = 0;
};

class mydspSIG0
{
public:
    int iRec33[2];
    int getNumInputsmydspSIG0();
    int getNumOutputsmydspSIG0();
    int getInputRatemydspSIG0(int channel);
    int getOutputRatemydspSIG0(int channel);
    void instanceInitmydspSIG0(int sample_rate);
    void fillmydspSIG0(int count, float *table);
};

static EXTMEM float ftbl0mydspSIG0[65536];

class mydsp : public dsp
{
public:
    ~mydsp();
    float fVslider0;
    float fRec0[2];
    int IOTA;
    float *fVec0;
    float fVslider1;
    float fRec1[2];
    int fSampleRate;
    float fConst0;
    float fConst1;
    float fVslider2;
    float fVslider3;
    float fVslider4;
    float fVslider5;
    float fConst2;
    float fConst3;
    float fVslider6;
    float fVslider7;
    float fVslider8;
    float fConst4;
    float fVslider9;
    float fRec15[2];
    float fRec14[2];
    float *fVec1;
    float fConst5;
    int iConst6;
    float *fVec2;
    float fConst7;
    float fVslider10;
    float fVec3[2048];
    int iConst8;
    float fRec12[2];
    float fConst9;
    float fConst10;
    float fRec19[2];
    float fRec18[2];
    float *fVec4;
    float fConst11;
    int iConst12;
    float *fVec5;
    int iConst13;
    float fRec16[2];
    float fConst14;
    float fConst15;
    float fRec23[2];
    float fRec22[2];
    float *fVec6;
    float fConst16;
    int iConst17;
    float *fVec7;
    int iConst18;
    float fRec20[2];
    float fConst19;
    float fConst20;
    float fRec27[2];
    float fRec26[2];
    float *fVec8;
    float fConst21;
    int iConst22;
    float fVec9[4096];
    int iConst23;
    float fRec24[2];
    float fVslider11;
    float fConst24;
    float fConst25;
    float fRec31[2];
    float fRec30[2];
    float *fVec10;
    float fConst26;
    float fRec35[2];
    float fRec34[2];
    float fRec32[2];
    float *fVec11;
    float fConst27;
    int iConst28;
    float fVec12[2048];
    int iConst29;
    float fRec28[2];
    float fConst30;
    float fConst31;
    float fRec39[2];
    float fRec38[2];
    float *fVec13;
    float fConst32;
    int iConst33;
    float fVec14[4096];
    int iConst34;
    float fRec36[2];
    float fConst35;
    float fConst36;
    float fRec43[2];
    float fRec42[2];
    float *fVec15;
    float fConst37;
    int iConst38;
    float fVec16[4096];
    int iConst39;
    float fRec40[2];
    float fConst40;
    float fConst41;
    float fRec47[2];
    float fRec46[2];
    float *fVec17;
    float fConst42;
    int iConst43;
    float fVec18[2048];
    int iConst44;
    float fRec44[2];
    float fRec4[3];
    float fRec5[3];
    float fRec6[3];
    float fRec7[3];
    float fRec8[3];
    float fRec9[3];
    float fRec10[3];
    float fRec11[3];
    float fRec3[3];
    float fRec2[3];
    float fRec49[3];
    float fRec48[3];

    float tone = 0.5;

    virtual int getNumInputs()
    {
        return 2;
    }
    virtual int getNumOutputs()
    {
        return 2;
    }
    virtual int getInputRate(int channel)
    {
        int rate;
        switch ((channel))
        {
        case 0:
        {
            rate = 1;
            break;
        }
        case 1:
        {
            rate = 1;
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
    virtual int getOutputRate(int channel)
    {
        int rate;
        switch ((channel))
        {
        case 0:
        {
            rate = 1;
            break;
        }
        case 1:
        {
            rate = 1;
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

    static void classInit(int sample_rate);

    virtual void instanceConstants(int sample_rate)
    {
        fSampleRate = sample_rate;
        fConst0 = min<float>(192000.0f, max<float>(1.0f, float(fSampleRate)));
        fConst1 = (6.28318548f / fConst0);
        fConst2 = floor(((0.219990999f * fConst0) + 0.5f));
        fConst3 = ((0.0f - (6.90775537f * fConst2)) / fConst0);
        fConst4 = (3.14159274f / fConst0);
        fConst5 = floor(((0.0191229992f * fConst0) + 0.5f));
        iConst6 = int(min<float>(16384.0f, max<float>(0.0f, (fConst2 - fConst5))));
        fConst7 = (0.00100000005f * fConst0);
        iConst8 = int(min<float>(1024.0f, max<float>(0.0f, (fConst5 + -1.0f))));
        fConst9 = floor(((0.256891012f * fConst0) + 0.5f));
        fConst10 = ((0.0f - (6.90775537f * fConst9)) / fConst0);
        fConst11 = floor(((0.0273330007f * fConst0) + 0.5f));
        iConst12 = int(min<float>(16384.0f, max<float>(0.0f, (fConst9 - fConst11))));
        iConst13 = int(min<float>(2048.0f, max<float>(0.0f, (fConst11 + -1.0f))));
        fConst14 = floor(((0.192303002f * fConst0) + 0.5f));
        fConst15 = ((0.0f - (6.90775537f * fConst14)) / fConst0);
        fConst16 = floor(((0.0292910002f * fConst0) + 0.5f));
        iConst17 = int(min<float>(8192.0f, max<float>(0.0f, (fConst14 - fConst16))));
        iConst18 = int(min<float>(2048.0f, max<float>(0.0f, (fConst16 + -1.0f))));
        fConst19 = floor(((0.210389003f * fConst0) + 0.5f));
        fConst20 = ((0.0f - (6.90775537f * fConst19)) / fConst0);
        fConst21 = floor(((0.0244210009f * fConst0) + 0.5f));
        iConst22 = int(min<float>(16384.0f, max<float>(0.0f, (fConst19 - fConst21))));
        iConst23 = int(min<float>(2048.0f, max<float>(0.0f, (fConst21 + -1.0f))));
        fConst24 = floor(((0.125f * fConst0) + 0.5f));
        fConst25 = ((0.0f - (6.90775537f * fConst24)) / fConst0);
        fConst26 = (1.0f / fConst0);
        fConst27 = floor(((0.0134579996f * fConst0) + 0.5f));
        iConst28 = int(min<float>(8192.0f, max<float>(0.0f, (fConst24 - fConst27))));
        iConst29 = int(min<float>(1024.0f, max<float>(0.0f, (fConst27 + -1.0f))));
        fConst30 = floor(((0.127837002f * fConst0) + 0.5f));
        fConst31 = ((0.0f - (6.90775537f * fConst30)) / fConst0);
        fConst32 = floor(((0.0316039994f * fConst0) + 0.5f));
        iConst33 = int(min<float>(8192.0f, max<float>(0.0f, (fConst30 - fConst32))));
        iConst34 = int(min<float>(2048.0f, max<float>(0.0f, (fConst32 + -1.0f))));
        fConst35 = floor(((0.174713001f * fConst0) + 0.5f));
        fConst36 = ((0.0f - (6.90775537f * fConst35)) / fConst0);
        fConst37 = floor(((0.0229039993f * fConst0) + 0.5f));
        iConst38 = int(min<float>(8192.0f, max<float>(0.0f, (fConst35 - fConst37))));
        iConst39 = int(min<float>(2048.0f, max<float>(0.0f, (fConst37 + -1.0f))));
        fConst40 = floor(((0.153128996f * fConst0) + 0.5f));
        fConst41 = ((0.0f - (6.90775537f * fConst40)) / fConst0);
        fConst42 = floor(((0.0203460008f * fConst0) + 0.5f));
        iConst43 = int(min<float>(8192.0f, max<float>(0.0f, (fConst40 - fConst42))));
        iConst44 = int(min<float>(1024.0f, max<float>(0.0f, (fConst42 + -1.0f))));
    }

    virtual void instanceResetUserInterface()
    {
        fVslider0 = float(0.0f);
        fVslider1 = float(0.0f);
        fVslider2 = float(1500.0f);
        fVslider3 = float(-2.0f);
        fVslider4 = float(315.0f);
        fVslider5 = float(-2.0f);
        fVslider6 = float(8.0f);
        fVslider7 = float(6000.0f);
        fVslider8 = float(3.0f);
        fVslider9 = float(200.0f);
        fVslider10 = float(60.0f);
        fVslider11 = float(0.0f);
    }

    virtual void instanceClear()
    {
        for (int l0 = 0; (l0 < 2); l0 = (l0 + 1))
        {
            fRec0[l0] = 0.0f;
        }
        IOTA = 0;
        for (int l1 = 0; (l1 < 4096); l1 = (l1 + 1))
        {
            fVec0[l1] = 0.0f;
        }
        for (int l2 = 0; (l2 < 2); l2 = (l2 + 1))
        {
            fRec1[l2] = 0.0f;
        }
        for (int l3 = 0; (l3 < 2); l3 = (l3 + 1))
        {
            fRec15[l3] = 0.0f;
        }
        for (int l4 = 0; (l4 < 2); l4 = (l4 + 1))
        {
            fRec14[l4] = 0.0f;
        }
        for (int l5 = 0; (l5 < 32768); l5 = (l5 + 1))
        {
            fVec1[l5] = 0.0f;
        }
        for (int l6 = 0; (l6 < 4096); l6 = (l6 + 1))
        {
            fVec2[l6] = 0.0f;
        }
        for (int l7 = 0; (l7 < 2048); l7 = (l7 + 1))
        {
            fVec3[l7] = 0.0f;
        }
        for (int l8 = 0; (l8 < 2); l8 = (l8 + 1))
        {
            fRec12[l8] = 0.0f;
        }
        for (int l9 = 0; (l9 < 2); l9 = (l9 + 1))
        {
            fRec19[l9] = 0.0f;
        }
        for (int l10 = 0; (l10 < 2); l10 = (l10 + 1))
        {
            fRec18[l10] = 0.0f;
        }
        for (int l11 = 0; (l11 < 32768); l11 = (l11 + 1))
        {
            fVec4[l11] = 0.0f;
        }
        for (int l12 = 0; (l12 < 4096); l12 = (l12 + 1))
        {
            fVec5[l12] = 0.0f;
        }
        for (int l13 = 0; (l13 < 2); l13 = (l13 + 1))
        {
            fRec16[l13] = 0.0f;
        }
        for (int l14 = 0; (l14 < 2); l14 = (l14 + 1))
        {
            fRec23[l14] = 0.0f;
        }
        for (int l15 = 0; (l15 < 2); l15 = (l15 + 1))
        {
            fRec22[l15] = 0.0f;
        }
        for (int l16 = 0; (l16 < 16384); l16 = (l16 + 1))
        {
            fVec6[l16] = 0.0f;
        }
        for (int l17 = 0; (l17 < 4096); l17 = (l17 + 1))
        {
            fVec7[l17] = 0.0f;
        }
        for (int l18 = 0; (l18 < 2); l18 = (l18 + 1))
        {
            fRec20[l18] = 0.0f;
        }
        for (int l19 = 0; (l19 < 2); l19 = (l19 + 1))
        {
            fRec27[l19] = 0.0f;
        }
        for (int l20 = 0; (l20 < 2); l20 = (l20 + 1))
        {
            fRec26[l20] = 0.0f;
        }
        for (int l21 = 0; (l21 < 32768); l21 = (l21 + 1))
        {
            fVec8[l21] = 0.0f;
        }
        for (int l22 = 0; (l22 < 4096); l22 = (l22 + 1))
        {
            fVec9[l22] = 0.0f;
        }
        for (int l23 = 0; (l23 < 2); l23 = (l23 + 1))
        {
            fRec24[l23] = 0.0f;
        }
        for (int l24 = 0; (l24 < 2); l24 = (l24 + 1))
        {
            fRec31[l24] = 0.0f;
        }
        for (int l25 = 0; (l25 < 2); l25 = (l25 + 1))
        {
            fRec30[l25] = 0.0f;
        }
        for (int l26 = 0; (l26 < 8192); l26 = (l26 + 1))
        {
            fVec10[l26] = 0.0f;
        }
        for (int l28 = 0; (l28 < 2); l28 = (l28 + 1))
        {
            fRec35[l28] = 0.0f;
        }
        for (int l29 = 0; (l29 < 2); l29 = (l29 + 1))
        {
            fRec34[l29] = 0.0f;
        }
        for (int l30 = 0; (l30 < 2); l30 = (l30 + 1))
        {
            fRec32[l30] = 0.0f;
        }
        for (int l31 = 0; (l31 < 16384); l31 = (l31 + 1))
        {
            fVec11[l31] = 0.0f;
        }
        for (int l32 = 0; (l32 < 2048); l32 = (l32 + 1))
        {
            fVec12[l32] = 0.0f;
        }
        for (int l33 = 0; (l33 < 2); l33 = (l33 + 1))
        {
            fRec28[l33] = 0.0f;
        }
        for (int l34 = 0; (l34 < 2); l34 = (l34 + 1))
        {
            fRec39[l34] = 0.0f;
        }
        for (int l35 = 0; (l35 < 2); l35 = (l35 + 1))
        {
            fRec38[l35] = 0.0f;
        }
        for (int l36 = 0; (l36 < 16384); l36 = (l36 + 1))
        {
            fVec13[l36] = 0.0f;
        }
        for (int l37 = 0; (l37 < 4096); l37 = (l37 + 1))
        {
            fVec14[l37] = 0.0f;
        }
        for (int l38 = 0; (l38 < 2); l38 = (l38 + 1))
        {
            fRec36[l38] = 0.0f;
        }
        for (int l39 = 0; (l39 < 2); l39 = (l39 + 1))
        {
            fRec43[l39] = 0.0f;
        }
        for (int l40 = 0; (l40 < 2); l40 = (l40 + 1))
        {
            fRec42[l40] = 0.0f;
        }
        for (int l41 = 0; (l41 < 16384); l41 = (l41 + 1))
        {
            fVec15[l41] = 0.0f;
        }
        for (int l42 = 0; (l42 < 4096); l42 = (l42 + 1))
        {
            fVec16[l42] = 0.0f;
        }
        for (int l43 = 0; (l43 < 2); l43 = (l43 + 1))
        {
            fRec40[l43] = 0.0f;
        }
        for (int l44 = 0; (l44 < 2); l44 = (l44 + 1))
        {
            fRec47[l44] = 0.0f;
        }
        for (int l45 = 0; (l45 < 2); l45 = (l45 + 1))
        {
            fRec46[l45] = 0.0f;
        }
        for (int l46 = 0; (l46 < 16384); l46 = (l46 + 1))
        {
            fVec17[l46] = 0.0f;
        }
        for (int l47 = 0; (l47 < 2048); l47 = (l47 + 1))
        {
            fVec18[l47] = 0.0f;
        }
        for (int l48 = 0; (l48 < 2); l48 = (l48 + 1))
        {
            fRec44[l48] = 0.0f;
        }
        for (int l49 = 0; (l49 < 3); l49 = (l49 + 1))
        {
            fRec4[l49] = 0.0f;
        }
        for (int l50 = 0; (l50 < 3); l50 = (l50 + 1))
        {
            fRec5[l50] = 0.0f;
        }
        for (int l51 = 0; (l51 < 3); l51 = (l51 + 1))
        {
            fRec6[l51] = 0.0f;
        }
        for (int l52 = 0; (l52 < 3); l52 = (l52 + 1))
        {
            fRec7[l52] = 0.0f;
        }
        for (int l53 = 0; (l53 < 3); l53 = (l53 + 1))
        {
            fRec8[l53] = 0.0f;
        }
        for (int l54 = 0; (l54 < 3); l54 = (l54 + 1))
        {
            fRec9[l54] = 0.0f;
        }
        for (int l55 = 0; (l55 < 3); l55 = (l55 + 1))
        {
            fRec10[l55] = 0.0f;
        }
        for (int l56 = 0; (l56 < 3); l56 = (l56 + 1))
        {
            fRec11[l56] = 0.0f;
        }
        for (int l57 = 0; (l57 < 3); l57 = (l57 + 1))
        {
            fRec3[l57] = 0.0f;
        }
        for (int l58 = 0; (l58 < 3); l58 = (l58 + 1))
        {
            fRec2[l58] = 0.0f;
        }
        for (int l59 = 0; (l59 < 3); l59 = (l59 + 1))
        {
            fRec49[l59] = 0.0f;
        }
        for (int l60 = 0; (l60 < 3); l60 = (l60 + 1))
        {
            fRec48[l60] = 0.0f;
        }
    }

    virtual void init(int sample_rate)
    {
        classInit(sample_rate);
        instanceInit(sample_rate);
    }

    void allocateExternalMemory();
    void freeExternalMemory();

    virtual void instanceInit(int sample_rate)
    {
        allocateExternalMemory();
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }

    virtual mydsp *clone()
    {
        return new mydsp();
    }

    virtual int getSampleRate()
    {
        return fSampleRate;
    }

    static float mydsp_faustpower2_f(float value)
    {
        return (value * value);
    }

    virtual void compute(int count, float **inputs, float **outputs)
    {
        float *input0 = inputs[0];
        float *input1 = inputs[1];
        float *output0 = outputs[0];
        float *output1 = outputs[1];
        float fSlow0 = (0.00100000005f * pow(10.0f, (0.0500000007f * float(fVslider0))));
        float fSlow1 = (0.00100000005f * float(fVslider1));
        float fSlow2 = float(fVslider2);
        float fSlow3 = pow(10.0f, (0.0500000007f * float(fVslider3)));
        float fSlow4 = (fConst1 * (fSlow2 / sqrt(max<float>(0.0f, fSlow3))));
        float fSlow5 = ((1.0f - fSlow4) / (fSlow4 + 1.0f));
        float fSlow6 = float(fVslider4);
        float fSlow7 = pow(10.0f, (0.0500000007f * float(fVslider5)));
        float fSlow8 = (fConst1 * (fSlow6 / sqrt(max<float>(0.0f, fSlow7))));
        float fSlow9 = ((1.0f - fSlow8) / (fSlow8 + 1.0f));
        float fSlow10 = float(fVslider6);
        float fSlow11 = exp((fConst3 / fSlow10));
        float fSlow12 = mydsp_faustpower2_f(fSlow11);
        float fSlow13 = cos((fConst1 * float(fVslider7)));
        float fSlow14 = (1.0f - (fSlow12 * fSlow13));
        float fSlow15 = (1.0f - fSlow12);
        float fSlow16 = (fSlow14 / fSlow15);
        float fSlow17 = sqrt(max<float>(0.0f, ((mydsp_faustpower2_f(fSlow14) / mydsp_faustpower2_f(fSlow15)) + -1.0f)));
        float fSlow18 = (fSlow16 - fSlow17);
        float fSlow19 = (fSlow11 * (fSlow17 + (1.0f - fSlow16)));
        float fSlow20 = float(fVslider8);
        float fSlow21 = ((exp((fConst3 / fSlow20)) / fSlow11) + -1.0f);
        float fSlow22 = (1.0f / tan((fConst4 * float(fVslider9))));
        float fSlow23 = (1.0f / (fSlow22 + 1.0f));
        float fSlow24 = (1.0f - fSlow22);
        int iSlow25 = int(min<float>(2700.0f, max<float>(0.0f, (fConst7 * float(fVslider10)))));
        float fSlow26 = exp((fConst10 / fSlow10));
        float fSlow27 = mydsp_faustpower2_f(fSlow26);
        float fSlow28 = (1.0f - (fSlow27 * fSlow13));
        float fSlow29 = (1.0f - fSlow27);
        float fSlow30 = (fSlow28 / fSlow29);
        float fSlow31 = sqrt(max<float>(0.0f, ((mydsp_faustpower2_f(fSlow28) / mydsp_faustpower2_f(fSlow29)) + -1.0f)));
        float fSlow32 = (fSlow30 - fSlow31);
        float fSlow33 = (fSlow26 * (fSlow31 + (1.0f - fSlow30)));
        float fSlow34 = ((exp((fConst10 / fSlow20)) / fSlow26) + -1.0f);
        float fSlow35 = exp((fConst15 / fSlow10));
        float fSlow36 = mydsp_faustpower2_f(fSlow35);
        float fSlow37 = (1.0f - (fSlow36 * fSlow13));
        float fSlow38 = (1.0f - fSlow36);
        float fSlow39 = (fSlow37 / fSlow38);
        float fSlow40 = sqrt(max<float>(0.0f, ((mydsp_faustpower2_f(fSlow37) / mydsp_faustpower2_f(fSlow38)) + -1.0f)));
        float fSlow41 = (fSlow39 - fSlow40);
        float fSlow42 = (fSlow35 * (fSlow40 + (1.0f - fSlow39)));
        float fSlow43 = ((exp((fConst15 / fSlow20)) / fSlow35) + -1.0f);
        float fSlow44 = exp((fConst20 / fSlow10));
        float fSlow45 = mydsp_faustpower2_f(fSlow44);
        float fSlow46 = (1.0f - (fSlow45 * fSlow13));
        float fSlow47 = (1.0f - fSlow45);
        float fSlow48 = (fSlow46 / fSlow47);
        float fSlow49 = sqrt(max<float>(0.0f, ((mydsp_faustpower2_f(fSlow46) / mydsp_faustpower2_f(fSlow47)) + -1.0f)));
        float fSlow50 = (fSlow48 - fSlow49);
        float fSlow51 = (fSlow44 * (fSlow49 + (1.0f - fSlow48)));
        float fSlow52 = ((exp((fConst20 / fSlow20)) / fSlow44) + -1.0f);
        float fSlow53 = (0.5f * (float(fVslider11) + 1.0f));
        float fSlow54 = exp((fConst25 / fSlow10));
        float fSlow55 = mydsp_faustpower2_f(fSlow54);
        float fSlow56 = (1.0f - (fSlow55 * fSlow13));
        float fSlow57 = (1.0f - fSlow55);
        float fSlow58 = (fSlow56 / fSlow57);
        float fSlow59 = sqrt(max<float>(0.0f, ((mydsp_faustpower2_f(fSlow56) / mydsp_faustpower2_f(fSlow57)) + -1.0f)));
        float fSlow60 = (fSlow58 - fSlow59);
        float fSlow61 = (fSlow54 * (fSlow59 + (1.0f - fSlow58)));
        float fSlow62 = ((exp((fConst25 / fSlow20)) / fSlow54) + -1.0f);
        float fSlow63 = (1.0f - fSlow53);
        float fSlow64 = exp((fConst31 / fSlow10));
        float fSlow65 = mydsp_faustpower2_f(fSlow64);
        float fSlow66 = (1.0f - (fSlow65 * fSlow13));
        float fSlow67 = (1.0f - fSlow65);
        float fSlow68 = (fSlow66 / fSlow67);
        float fSlow69 = sqrt(max<float>(0.0f, ((mydsp_faustpower2_f(fSlow66) / mydsp_faustpower2_f(fSlow67)) + -1.0f)));
        float fSlow70 = (fSlow68 - fSlow69);
        float fSlow71 = (fSlow64 * (fSlow69 + (1.0f - fSlow68)));
        float fSlow72 = ((exp((fConst31 / fSlow20)) / fSlow64) + -1.0f);
        float fSlow73 = exp((fConst36 / fSlow10));
        float fSlow74 = mydsp_faustpower2_f(fSlow73);
        float fSlow75 = (1.0f - (fSlow74 * fSlow13));
        float fSlow76 = (1.0f - fSlow74);
        float fSlow77 = (fSlow75 / fSlow76);
        float fSlow78 = sqrt(max<float>(0.0f, ((mydsp_faustpower2_f(fSlow75) / mydsp_faustpower2_f(fSlow76)) + -1.0f)));
        float fSlow79 = (fSlow77 - fSlow78);
        float fSlow80 = (fSlow73 * (fSlow78 + (1.0f - fSlow77)));
        float fSlow81 = ((exp((fConst36 / fSlow20)) / fSlow73) + -1.0f);
        float fSlow82 = exp((fConst41 / fSlow10));
        float fSlow83 = mydsp_faustpower2_f(fSlow82);
        float fSlow84 = (1.0f - (fSlow83 * fSlow13));
        float fSlow85 = (1.0f - fSlow83);
        float fSlow86 = (fSlow84 / fSlow85);
        float fSlow87 = sqrt(max<float>(0.0f, ((mydsp_faustpower2_f(fSlow84) / mydsp_faustpower2_f(fSlow85)) + -1.0f)));
        float fSlow88 = (fSlow86 - fSlow87);
        float fSlow89 = (fSlow82 * (fSlow87 + (1.0f - fSlow86)));
        float fSlow90 = ((exp((fConst41 / fSlow20)) / fSlow82) + -1.0f);
        float fSlow91 = (0.0f - (cos((fConst1 * fSlow6)) * (fSlow9 + 1.0f)));
        float fSlow92 = (0.0f - (cos((fConst1 * fSlow2)) * (fSlow5 + 1.0f)));
        for (int i = 0; (i < count); i = (i + 1))
        {
            fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
            float fTemp0 = float(input0[i]);
            fVec0[(IOTA & 4095)] = fTemp0;
            fRec1[0] = (fSlow1 + (0.999000013f * fRec1[1]));
            float fTemp1 = (fRec1[0] + 1.0f);
            float fTemp2 = (1.0f - (0.5f * fTemp1));
            fRec15[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec15[1]) - (fRec11[1] + fRec11[2]))));
            fRec14[0] = ((fSlow18 * fRec14[1]) + (fSlow19 * (fRec11[1] + (fSlow21 * fRec15[0]))));
            fVec1[(IOTA & 32767)] = ((0.353553385f * fRec14[0]) + 9.99999968e-21f);
            float fTemp3 = float(input1[i]);
            fVec2[(IOTA & 4095)] = fTemp3;
            float fTemp4 = (0.300000012f * fVec2[((IOTA - iSlow25) & 4095)]);
            float fTemp5 = (((0.600000024f * fRec12[1]) + fVec1[((IOTA - iConst6) & 32767)]) - fTemp4);
            fVec3[(IOTA & 2047)] = fTemp5;
            fRec12[0] = fVec3[((IOTA - iConst8) & 2047)];
            float fRec13 = (0.0f - (0.600000024f * fTemp5));
            fRec19[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec19[1]) - (fRec7[1] + fRec7[2]))));
            fRec18[0] = ((fSlow32 * fRec18[1]) + (fSlow33 * (fRec7[1] + (fSlow34 * fRec19[0]))));
            fVec4[(IOTA & 32767)] = ((0.353553385f * fRec18[0]) + 9.99999968e-21f);
            float fTemp6 = (((0.600000024f * fRec16[1]) + fVec4[((IOTA - iConst12) & 32767)]) - fTemp4);
            fVec5[(IOTA & 4095)] = fTemp6;
            fRec16[0] = fVec5[((IOTA - iConst13) & 4095)];
            float fRec17 = (0.0f - (0.600000024f * fTemp6));
            fRec23[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec23[1]) - (fRec9[1] + fRec9[2]))));
            fRec22[0] = ((fSlow41 * fRec22[1]) + (fSlow42 * (fRec9[1] + (fSlow43 * fRec23[0]))));
            fVec6[(IOTA & 16383)] = ((0.353553385f * fRec22[0]) + 9.99999968e-21f);
            float fTemp7 = (fVec6[((IOTA - iConst17) & 16383)] + (fTemp4 + (0.600000024f * fRec20[1])));
            fVec7[(IOTA & 4095)] = fTemp7;
            fRec20[0] = fVec7[((IOTA - iConst18) & 4095)];
            float fRec21 = (0.0f - (0.600000024f * fTemp7));
            fRec27[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec27[1]) - (fRec5[1] + fRec5[2]))));
            fRec26[0] = ((fSlow50 * fRec26[1]) + (fSlow51 * (fRec5[1] + (fSlow52 * fRec27[0]))));
            fVec8[(IOTA & 32767)] = ((0.353553385f * fRec26[0]) + 9.99999968e-21f);
            float fTemp8 = (fTemp4 + ((0.600000024f * fRec24[1]) + fVec8[((IOTA - iConst22) & 32767)]));
            fVec9[(IOTA & 4095)] = fTemp8;
            fRec24[0] = fVec9[((IOTA - iConst23) & 4095)];
            float fRec25 = (0.0f - (0.600000024f * fTemp8));
            fRec31[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec31[1]) - (fRec10[1] + fRec10[2]))));
            fRec30[0] = ((fSlow60 * fRec30[1]) + (fSlow61 * (fRec10[1] + (fSlow62 * fRec31[0]))));
            float fTemp9 = ((0.353553385f * fRec30[0]) + 9.99999968e-21f);
            fVec10[(IOTA & 8191)] = fTemp9;
            fRec35[0] = (0.5f * (fRec35[1] + 1.0f));
            float fTemp10 = (fRec34[1] + (fConst26 * fRec35[0]));
            fRec34[0] = (fTemp10 - floor(fTemp10));
            fRec32[0] = fmod((fRec32[1] + (4097.0f - pow(2.0f, (0.0833333358f * ((0.0500000007f * ftbl0mydspSIG0[int((65536.0f * fRec34[0]))]) + 12.0f))))), 4096.0f);
            int iTemp11 = int(fRec32[0]);
            float fTemp12 = floor(fRec32[0]);
            float fTemp13 = min<float>((0.001953125f * fRec32[0]), 1.0f);
            float fTemp14 = (fRec32[0] + 4096.0f);
            int iTemp15 = int(fTemp14);
            float fTemp16 = floor(fTemp14);
            fVec11[(IOTA & 16383)] = ((fSlow53 * fTemp9) + (fSlow63 * ((((fVec10[((IOTA - min<int>(4097, max<int>(0, iTemp11))) & 8191)] * (fTemp12 + (1.0f - fRec32[0]))) + ((fRec32[0] - fTemp12) * fVec10[((IOTA - min<int>(4097, max<int>(0, (iTemp11 + 1)))) & 8191)])) * fTemp13) + (((fVec10[((IOTA - min<int>(4097, max<int>(0, iTemp15))) & 8191)] * (fTemp16 + (-4095.0f - fRec32[0]))) + ((fRec32[0] + (4096.0f - fTemp16)) * fVec10[((IOTA - min<int>(4097, max<int>(0, (iTemp15 + 1)))) & 8191)])) * (1.0f - fTemp13)))));
            float fTemp17 = (0.300000012f * fVec0[((IOTA - iSlow25) & 4095)]);
            float fTemp18 = (fVec11[((IOTA - iConst28) & 16383)] - (fTemp17 + (0.600000024f * fRec28[1])));
            fVec12[(IOTA & 2047)] = fTemp18;
            fRec28[0] = fVec12[((IOTA - iConst29) & 2047)];
            float fRec29 = (0.600000024f * fTemp18);
            fRec39[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec39[1]) - (fRec6[1] + fRec6[2]))));
            fRec38[0] = ((fSlow70 * fRec38[1]) + (fSlow71 * (fRec6[1] + (fSlow72 * fRec39[0]))));
            fVec13[(IOTA & 16383)] = ((0.353553385f * fRec38[0]) + 9.99999968e-21f);
            float fTemp19 = (fVec13[((IOTA - iConst33) & 16383)] - (fTemp17 + (0.600000024f * fRec36[1])));
            fVec14[(IOTA & 4095)] = fTemp19;
            fRec36[0] = fVec14[((IOTA - iConst34) & 4095)];
            float fRec37 = (0.600000024f * fTemp19);
            fRec43[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec43[1]) - (fRec8[1] + fRec8[2]))));
            fRec42[0] = ((fSlow79 * fRec42[1]) + (fSlow80 * (fRec8[1] + (fSlow81 * fRec43[0]))));
            fVec15[(IOTA & 16383)] = ((0.353553385f * fRec42[0]) + 9.99999968e-21f);
            float fTemp20 = ((fTemp17 + fVec15[((IOTA - iConst38) & 16383)]) - (0.600000024f * fRec40[1]));
            fVec16[(IOTA & 4095)] = fTemp20;
            fRec40[0] = fVec16[((IOTA - iConst39) & 4095)];
            float fRec41 = (0.600000024f * fTemp20);
            fRec47[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec47[1]) - (fRec4[1] + fRec4[2]))));
            fRec46[0] = ((fSlow88 * fRec46[1]) + (fSlow89 * (fRec4[1] + (fSlow90 * fRec47[0]))));
            fVec17[(IOTA & 16383)] = ((0.353553385f * fRec46[0]) + 9.99999968e-21f);
            float fTemp21 = ((fVec17[((IOTA - iConst43) & 16383)] + fTemp17) - (0.600000024f * fRec44[1]));
            fVec18[(IOTA & 2047)] = fTemp21;
            fRec44[0] = fVec18[((IOTA - iConst44) & 2047)];
            float fRec45 = (0.600000024f * fTemp21);
            float fTemp22 = (fRec45 + fRec41);
            float fTemp23 = (fRec29 + (fRec37 + fTemp22));
            fRec4[0] = (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec36[1] + (fRec40[1] + (fRec44[1] + (fRec13 + (fRec17 + (fRec21 + (fRec25 + fTemp23))))))))))));
            fRec5[0] = ((fRec28[1] + (fRec36[1] + (fRec40[1] + (fRec44[1] + fTemp23)))) - (fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec13 + (fRec17 + (fRec25 + fRec21))))))));
            float fTemp24 = (fRec37 + fRec29);
            fRec6[0] = ((fRec20[1] + (fRec24[1] + (fRec40[1] + (fRec44[1] + (fRec21 + (fRec25 + fTemp22)))))) - (fRec12[1] + (fRec16[1] + (fRec28[1] + (fRec36[1] + (fRec13 + (fRec17 + fTemp24)))))));
            fRec7[0] = ((fRec12[1] + (fRec16[1] + (fRec40[1] + (fRec44[1] + (fRec13 + (fRec17 + fTemp22)))))) - (fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec36[1] + (fRec21 + (fRec25 + fTemp24)))))));
            float fTemp25 = (fRec45 + fRec37);
            float fTemp26 = (fRec41 + fRec29);
            fRec8[0] = ((fRec16[1] + (fRec24[1] + (fRec36[1] + (fRec44[1] + (fRec17 + (fRec25 + fTemp25)))))) - (fRec12[1] + (fRec20[1] + (fRec28[1] + (fRec40[1] + (fRec13 + (fRec21 + fTemp26)))))));
            fRec9[0] = ((fRec12[1] + (fRec20[1] + (fRec36[1] + (fRec44[1] + (fRec13 + (fRec21 + fTemp25)))))) - (fRec16[1] + (fRec24[1] + (fRec28[1] + (fRec40[1] + (fRec17 + (fRec25 + fTemp26)))))));
            float fTemp27 = (fRec45 + fRec29);
            float fTemp28 = (fRec41 + fRec37);
            fRec10[0] = ((fRec12[1] + (fRec24[1] + (fRec28[1] + (fRec44[1] + (fRec13 + (fRec25 + fTemp27)))))) - (fRec16[1] + (fRec20[1] + (fRec36[1] + (fRec40[1] + (fRec17 + (fRec21 + fTemp28)))))));
            fRec11[0] = ((fRec16[1] + (fRec20[1] + (fRec28[1] + (fRec44[1] + (fRec17 + (fRec21 + fTemp27)))))) - (fRec12[1] + (fRec24[1] + (fRec36[1] + (fRec40[1] + (fRec13 + (fRec25 + fTemp28)))))));
            float fTemp29 = (0.370000005f * (fRec5[0] + fRec6[0]));
            float fTemp30 = (fSlow91 * fRec3[1]);
            fRec3[0] = (fTemp29 - (fTemp30 + (fSlow9 * fRec3[2])));
            float fTemp31 = (fSlow9 * fRec3[0]);
            float fTemp32 = (0.5f * ((fTemp31 + (fRec3[2] + (fTemp29 + fTemp30))) + (fSlow7 * ((fTemp31 + (fTemp30 + fRec3[2])) - fTemp29))));
            float fTemp33 = (fSlow92 * fRec2[1]);
            fRec2[0] = (fTemp32 - (fTemp33 + (fSlow5 * fRec2[2])));
            float fTemp34 = (fSlow5 * fRec2[0]);
            output0[i] = float((0.5f * (fRec0[0] * ((fTemp0 * fTemp1) + (fTemp2 * ((fTemp34 + (fRec2[2] + (fTemp32 + fTemp33))) + (fSlow3 * ((fTemp34 + (fTemp33 + fRec2[2])) - fTemp32))))))));
            float fTemp35 = (0.370000005f * (fRec5[0] - fRec6[0]));
            float fTemp36 = (fSlow91 * fRec49[1]);
            fRec49[0] = (fTemp35 - (fTemp36 + (fSlow9 * fRec49[2])));
            float fTemp37 = (fSlow9 * fRec49[0]);
            float fTemp38 = (0.5f * ((fTemp37 + (fRec49[2] + (fTemp35 + fTemp36))) + (fSlow7 * ((fTemp37 + (fTemp36 + fRec49[2])) - fTemp35))));
            float fTemp39 = (fSlow92 * fRec48[1]);
            fRec48[0] = (fTemp38 - (fTemp39 + (fSlow5 * fRec48[2])));
            float fTemp40 = (fSlow5 * fRec48[0]);
            output1[i] = float((0.5f * (fRec0[0] * ((fTemp3 * fTemp1) + (fTemp2 * ((fTemp40 + (fRec48[2] + (fTemp38 + fTemp39))) + (fSlow3 * ((fTemp40 + (fTemp39 + fRec48[2])) - fTemp38))))))));
            fRec0[1] = fRec0[0];
            IOTA = (IOTA + 1);
            fRec1[1] = fRec1[0];
            fRec15[1] = fRec15[0];
            fRec14[1] = fRec14[0];
            fRec12[1] = fRec12[0];
            fRec19[1] = fRec19[0];
            fRec18[1] = fRec18[0];
            fRec16[1] = fRec16[0];
            fRec23[1] = fRec23[0];
            fRec22[1] = fRec22[0];
            fRec20[1] = fRec20[0];
            fRec27[1] = fRec27[0];
            fRec26[1] = fRec26[0];
            fRec24[1] = fRec24[0];
            fRec31[1] = fRec31[0];
            fRec30[1] = fRec30[0];
            fRec35[1] = fRec35[0];
            fRec34[1] = fRec34[0];
            fRec32[1] = fRec32[0];
            fRec28[1] = fRec28[0];
            fRec39[1] = fRec39[0];
            fRec38[1] = fRec38[0];
            fRec36[1] = fRec36[0];
            fRec43[1] = fRec43[0];
            fRec42[1] = fRec42[0];
            fRec40[1] = fRec40[0];
            fRec47[1] = fRec47[0];
            fRec46[1] = fRec46[0];
            fRec44[1] = fRec44[0];
            fRec4[2] = fRec4[1];
            fRec4[1] = fRec4[0];
            fRec5[2] = fRec5[1];
            fRec5[1] = fRec5[0];
            fRec6[2] = fRec6[1];
            fRec6[1] = fRec6[0];
            fRec7[2] = fRec7[1];
            fRec7[1] = fRec7[0];
            fRec8[2] = fRec8[1];
            fRec8[1] = fRec8[0];
            fRec9[2] = fRec9[1];
            fRec9[1] = fRec9[0];
            fRec10[2] = fRec10[1];
            fRec10[1] = fRec10[0];
            fRec11[2] = fRec11[1];
            fRec11[1] = fRec11[0];
            fRec3[2] = fRec3[1];
            fRec3[1] = fRec3[0];
            fRec2[2] = fRec2[1];
            fRec2[1] = fRec2[0];
            fRec49[2] = fRec49[1];
            fRec49[1] = fRec49[0];
            fRec48[2] = fRec48[1];
            fRec48[1] = fRec48[0];
        }
    }
};

#endif
