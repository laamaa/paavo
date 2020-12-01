#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <Audio.h>
#include <OpenAudio_ArduinoLibrary.h>
#include "dsp/effect_zitareverb_f32.h"
#include "AudioEffect.h"

namespace Paavo
{
    namespace Audio
    {
        class Manager
        {
        public:
            ~Manager();
            void init();
            void update();
            ::AudioStream &getMaster(uint8_t num);
            ::AudioStream_F32 &getF32Master(uint8_t num);
            EffectMeta *getFx(int fxSlot){ return fxMeta[fxSlot]; }

        private:
            ::AudioOutputI2SQuad audioOutput;
            ::AudioConvert_F32toI16 float2Int[4];
            ::AudioConvert_I16toF32 int2Float[2];
            ::AudioInputUSB usb1;
            ::AudioConnection *patchUsbToFloat[2];
            ::AudioConnection *patchFloatToOut[4];
            ::AudioConnection_F32 *patch[6];
            //AudioEffectZitaShimmerReverb_F32 zita;
            ::AudioStream_F32 *fx[4];
            Paavo::Audio::EffectMeta *fxMeta[4];
            //Effect fx[4] = {Effect(&zita,"Reverb",true),Effect(&zita,"Reverb",true),Effect(&zita,"Reverb",true),Effect(&zita,"Reverb",true)};
            //AudioEffectZitaShimmerReverb_F32 zita;
        };

    } // namespace Audio
} // namespace Paavo

#endif