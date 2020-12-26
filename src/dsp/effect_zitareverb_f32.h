/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************/

#ifndef faust_AudioEffectZitaShimmerReverb_F32_h_
#define faust_AudioEffectZitaShimmerReverb_F32_h_

#include "Arduino.h"
#include "AudioStream_F32.h"
#include "Audio.h"
#include "dsp/faust_architecture.h"

class AudioEffectZitaShimmerReverb_F32 : public AudioStream_F32
{
public:
    AudioEffectZitaShimmerReverb_F32();
    ~AudioEffectZitaShimmerReverb_F32();

    virtual void update(void);
    mydsp *getMydsp() { return fDSP; }

private:
    void updateImp(void);

    float **fInChannel;
    float **fOutChannel;
    mydsp *fDSP;
};

#endif
