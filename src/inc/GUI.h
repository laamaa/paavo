#ifndef GUI_H_
#define GUI_H_
#include "inc/settings.h"
#include "inc/AudioManager.h"
#include "inc/AudioEffect.h"
#include "inc/Oscilloscope.h"
#include <SPI.h>
#include <ILI9341_t3n.h>

namespace Paavo
{
    namespace GUI
    {
        class QuickFxSettingsMenu
        {
        public:
            QuickFxSettingsMenu(ILI9341_t3n *ptrDisplay, Audio::Manager *ptrAudioManager)
            {
                display = ptrDisplay;
                am = ptrAudioManager;
            }
            void setFx();
            void update();
            void drawMenuGrid();
            void drawLabels(uint8_t fxslot);
            void drawValues(uint8_t fxslot, uint8_t numQfx = 255);
            inline void setActiveFx(uint8_t activeFx) { _activeFx = activeFx; }
            uint8_t getActiveFx() { return _activeFx; }

        private:
            ILI9341_t3n *display;
            Audio::Manager *am;
            uint8_t _activeFx = 0;
        };

        class Manager
        {
        public:
            Manager(Audio::Manager *ptrAudioManager)
            {
                am = ptrAudioManager;
            }
            ~Manager()
            {
                tft.freeFrameBuffer();
            }
            void init();
            void update();
            bool updateDisplay = false;
            inline void clearDisplay() { tft.fillScreen(ILI9341_BLACK); }
            inline GUI::QuickFxSettingsMenu *getQuickFxMenu() { return qm; }
            
        private:
            ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST);
            uint16_t *tftFrameBuffer;
            Audio::Manager *am;
            GUI::QuickFxSettingsMenu *qm;

            Oscilloscope *osc[4];
            elapsedMillis lastScreenUpdate;
        };

    } // namespace GUI

} // namespace Paavo
#endif