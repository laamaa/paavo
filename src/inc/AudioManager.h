#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <Audio.h>
#include <OpenAudio_ArduinoLibrary.h>
#include "dsp/effect_zitareverb_f32.h"

namespace Paavo
{
    class AudioManager
    {
    public:
        ~AudioManager();
        void init();
        void update();
        ::AudioStream &getMaster(uint8_t num);
        inline void bypassFx() {
            Serial.println(zita.getParamValue("Dry/Wet Mix"));
            if (zita.getParamValue("Dry/Wet Mix") == 1.0f){
                zita.setParamValue("Dry/Wet Mix",-0.0f);
            } else {
                zita.setParamValue("Dry/Wet Mix",1.0f);
            }
        }
        inline void bypassShimmer() {
            Serial.println(zita.getParamValue("shimmer"));
            if (zita.getParamValue("shimmer") == -1.0f){
                zita.setParamValue("shimmer",0.0f);
            } else {
                zita.setParamValue("shimmer",-1.0f);
            }            
        }

    private:
        ::AudioOutputI2SQuad audioOutput;
        ::AudioConvert_F32toI16 float2Int[4];
        ::AudioConvert_I16toF32 int2Float[2];
        ::AudioInputUSB usb1;
        ::AudioEffectZitaShimmerReverb_F32 zita;
        ::AudioConnection *patchUsbToFloat[2];
        ::AudioConnection *patchFloatToOut[4];
        ::AudioConnection_F32 *patch[6];
    };
} // namespace Paavo

#endif