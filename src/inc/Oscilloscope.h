#ifndef OSCILLOSCOPE_H_
#define OSCILLOSCOPE_H_
#include "inc/AudioManager.h"
#include "AudioStream.h"
#include <ILI9341_t3n.h>

#define SCOPE_UPDATE_INTERVAL 17

namespace Paavo
{
    class Oscilloscope : public AudioStream
    {
    public:
        Oscilloscope(AudioStream &as, ILI9341_t3n *ptrDisplay, uint16_t width, uint16_t height) : AudioStream(1, inputQueueArray)
        {
            display = ptrDisplay;
            _width = width;
            _height = height;
            _offset_x = 0;
            _offset_y = 0;
            mapMaxY = height / 2;
            oldPixelValue = new uint16_t[width]{};
            patchConverterOscilloscope = new AudioConnection(as, 0, *this, 0);
        }
        Oscilloscope(AudioStream &as, ILI9341_t3n *ptrDisplay, uint16_t width, uint16_t height, uint16_t offset_x, uint16_t offset_y) : AudioStream(1, inputQueueArray)
        {
            display = ptrDisplay;
            _width = width;
            _height = height;
            _offset_x = offset_x;
            _offset_y = offset_y;
            mapMaxY = height / 2;
            oldPixelValue = new uint16_t[width]{};
            patchConverterOscilloscope = new AudioConnection(as, 0, *this, 0);
        }
        ~Oscilloscope()
        {
            delete patchConverterOscilloscope;
        }
        virtual void update(void);
        void init();

    private:
        void AudioToPixel(int16_t *);
        AudioConnection *patchConverterOscilloscope;
        audio_block_t *inputQueueArray[1];
        ILI9341_t3n *display;
        int16_t _width;
        int16_t _height;
        uint16_t _offset_x;
        uint16_t _offset_y;
        uint8_t mapMaxY;
        uint16_t *oldPixelValue;
        bool updateInProgress = false;
        elapsedMillis lastUpdate;
    };
} // namespace Paavo
#endif