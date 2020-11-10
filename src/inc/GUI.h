#ifndef GUI_H_
#define GUI_H_
#include "inc/settings.h"
#include "inc/AudioManager.h"
#include "inc/Oscilloscope.h"
#include <SPI.h>
#include <ILI9341_t3n.h>

namespace Paavo
{
    class GUI
    {
    public:
        GUI(AudioManager *ptrAudioManager)
        {
            am = ptrAudioManager;
        }
        ~GUI(){
            tft.freeFrameBuffer();
        }
        void init();
        void update();
        bool updateDisplay = false;
        inline void clearDisplay() { tft.fillScreen(ILI9341_BLACK); }
        inline void drawPixel(uint16_t x, uint16_t y, uint16_t color) { tft.drawPixel(x, y, color); }

    private:
        ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST);
        uint16_t *tftFrameBuffer;
        AudioManager *am;
        Oscilloscope *osc[4];
        elapsedMillis lastScreenUpdate;
    };

} // namespace Paavo
#endif