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
            Paavo::Audio::EffectBase *getFx(uint8_t fxSlot) { return fx[fxSlot]; }

        private:
            ::AudioOutputI2SQuad audioOutput;
            ::AudioConvert_F32toI16 float2Int[4];
            ::AudioConvert_I16toF32 int2Float[2];
            ::AudioInputUSB usb1;
            ::AudioConnection *patchUsbToFloat[2];
            ::AudioConnection *patchFloatToOut[4];
            ::AudioConnection_F32 *patch[6];
            Paavo::Audio::EffectBase *fx[4];
            uint8_t _activeFx = 0;
        };

    } // namespace Audio
} // namespace Paavo

#endif