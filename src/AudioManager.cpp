#include "inc/AudioManager.h"

#include <Audio.h>
#include <OpenAudio_ArduinoLibrary.h>
#include "inc/AudioEffect.h"
#include "dsp/effect_zitareverb_f32.h"

namespace Paavo
{
    namespace Audio
    {
        Manager::~Manager()
        {
            for (AudioConnection *ac : patchUsbToFloat)
                delete ac;
            for (AudioConnection_F32 *ac : patch)
                delete ac;
            for (AudioConnection *ac : patchFloatToOut)
                delete ac;
        }

        void Manager::init()
        {
            AudioMemory(30);
            AudioMemory_F32(20);

            fx[0] = new Paavo::Audio::Effect<AudioEffectZitaShimmerReverb_F32>("Reverb");

            patchUsbToFloat[0] = new AudioConnection(usb1, 0, int2Float[0], 0);
            patchUsbToFloat[1] = new AudioConnection(usb1, 1, int2Float[1], 0);

            patch[0] = new AudioConnection_F32(int2Float[0], 0, *fx[0]->getFx(), 0);
            patch[1] = new AudioConnection_F32(int2Float[1], 0, *fx[0]->getFx(), 1);
            patch[2] = new AudioConnection_F32(*fx[0]->getFx(), 0, float2Int[0], 0);
            patch[3] = new AudioConnection_F32(*fx[0]->getFx(), 1, float2Int[1], 0);
            patch[4] = new AudioConnection_F32(*fx[0]->getFx(), 0, float2Int[2], 0);
            patch[5] = new AudioConnection_F32(*fx[0]->getFx(), 1, float2Int[3], 0);
     
            patchFloatToOut[0] = new AudioConnection(float2Int[0], 0, audioOutput, 0);
            patchFloatToOut[1] = new AudioConnection(float2Int[1], 0, audioOutput, 1);
            patchFloatToOut[2] = new AudioConnection(float2Int[2], 0, audioOutput, 2);
            patchFloatToOut[3] = new AudioConnection(float2Int[3], 0, audioOutput, 3);
        }

        void Manager::update()
        {
        }

        AudioStream &Manager::getMaster(uint8_t num)
        {
            if (num < 4)
                return float2Int[num];
            else
                return float2Int[0];
        }
        
        AudioStream_F32 &Manager::getF32Master(uint8_t num)
        {
            if (num < 4)
                return float2Int[num];
            else
                return float2Int[0];
        }
    } // namespace Audio
} // namespace Paavo