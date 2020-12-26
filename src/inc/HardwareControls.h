#ifndef HARDWARECONTROLS_H_
#define HARDWARECONTROLS_H_

#include "inc/GUI.h"
#include <Encoder.h>
#include <Bounce2.h>
namespace Paavo
{
    namespace Controls
    {
        class HardwareControls
        {
        public:
            HardwareControls(Paavo::GUI::Manager *ptrGui, Paavo::Audio::Manager *ptrAm)
            {
                gui = ptrGui;
                am = ptrAm;
                
            }

            void init();
            inline void update() { readEncoders(); };
        private:
            Paavo::GUI::Manager *gui;
            GUI::QuickFxSettingsMenu *qm;
            Paavo::Audio::Manager *am;

            //Pins where the encoders are connected
            const uint8_t encoderPin[5][3] = {{24, 25, 26}, {27, 28, 29}, {34, 35, 36}, {37, 40, 41}, {14, 15, 16}};
            
            Encoder *encoder[5];
            Bounce *button[5];
            int encValue[5];

            void readEncoders();
            void onButtonPress(uint8_t button);
            void onEncoderIncrease(uint8_t encoder);
            void onEncoderDecrease(uint8_t encoder);
        };
    } // namespace Controls
} // namespace Paavo

#endif