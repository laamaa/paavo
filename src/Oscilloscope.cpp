#include "inc/oscilloscope.h"

namespace Paavo
{
    void Oscilloscope::AudioToPixel(int16_t *audio)
    {
        if (!display || lastUpdate < SCOPE_UPDATE_INTERVAL)
            return;
        //const int16_t *begin = audio;
        const int16_t *end = audio + AUDIO_BLOCK_SAMPLES;
        static uint16_t pixel_x = 0;
        __disable_irq();
        do
        {
            int16_t pixel_y;
            int16_t wave_data = *audio;
            if (wave_data < -30000)
                pixel_y = 0;
            else if (wave_data > 30000)
                pixel_y = _height;
            else
                pixel_y = map(wave_data, -30000, 30000, -mapMaxY, mapMaxY) + mapMaxY;
            pixel_y += _offset_y;
            pixel_x += _offset_x;
            display->drawPixel(pixel_x, blankPixelValue[pixel_x], ILI9341_BLACK);
            display->drawPixel(pixel_x, oldPixelValue[pixel_x], ILI9341_DARKGREY);
            blankPixelValue[pixel_x] = oldPixelValue[pixel_x];
            display->drawPixel(pixel_x, pixel_y, ILI9341_WHITE);
            oldPixelValue[pixel_x] = pixel_y;
            audio++;
            pixel_x++;
            if (pixel_x == _width)
                pixel_x = 0;
        } while (audio < end);
        lastUpdate = 0;
        __enable_irq();
        return;
    }

    void Oscilloscope::init()
    {
    }

    void Oscilloscope::update(void)
    {
        if (!display)
            return;
        audio_block_t *block = NULL;

        block = receiveReadOnly(0);
        if (!block)
            return;
        AudioToPixel(block->data);
        release(block);
    }
} // namespace Paavo