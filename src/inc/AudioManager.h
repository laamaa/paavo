#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <Audio.h>
#include <OpenAudio_ArduinoLibrary.h>
#include "dsp/FaustZitaHeavy.h"

namespace Paavo
{
    class AudioManager
    {
    public:
        ~AudioManager();
        void init();
        void update();
        ::AudioStream &getMaster(uint8_t num);

    private:
        ::AudioOutputI2SQuad audioOutput;
        ::AudioConvert_F32toI16 float2Int[4];
        ::AudioConvert_I16toF32 int2Float[2];
        ::AudioInputUSB usb1;
        ::AudioConnection *patchUsbToFloat[2];
        ::AudioConnection *patchFloatToOut[4];
        ::AudioConnection_F32 *patch[4];
    };
} // namespace Paavo

#endif