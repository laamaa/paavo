#include "inc/HardwareControls.h"
#include "inc/settings.h"

void Paavo::Controls::HardwareControls::init()
{
    //Setup button pins for bounce library
    for (int i = 0; i < 5; i++)    
    {
        button[i] = new Bounce();
        button[i]->attach(encoderPin[i][0], INPUT_PULLUP);
        button[i]->interval(100);
        encoder[i] = new Encoder(encoderPin[i][1], encoderPin[i][2]);
    }
}

void Paavo::Controls::HardwareControls::onEncoderIncrease(uint8_t encoder)
{
#if SYNTH_DEBUG > 1
    Serial.printf(F("Encoder %d value increase\n"), encoder);
#endif
    am->getFx(0)->increaseQuicksettingValue(encoder);
    gui->getQuickFxMenu()->drawValues(gui->getQuickFxMenu()->getActiveFx(),encoder);
}

void Paavo::Controls::HardwareControls::onEncoderDecrease(uint8_t encoder)
{
#if SYNTH_DEBUG > 1
    Serial.printf(F("Encoder %d value decrease\n"), encoder);
#endif
    am->getFx(0)->decreaseQuicksettingValue(encoder);
    gui->getQuickFxMenu()->drawValues(gui->getQuickFxMenu()->getActiveFx(),encoder);
}

void Paavo::Controls::HardwareControls::onButtonPress(uint8_t button)
{
#if SYNTH_DEBUG > 1
    Serial.printf(F("Button %d pressed\n"), button);
#endif
}

void Paavo::Controls::HardwareControls::readEncoders()
{
    int8_t i, ctlValue;

    for (i = 0; i < 5; i++)
    {
        //Read encoder button presses
        button[i]->update();
        if (button[i]->rose())
        {
            onButtonPress(i);
        }

        //Read the current encoder turning direction
        ctlValue = encoder[i]->readAndReset();
        //The crappy encoders that I bought from Aliexpress seem to be like 1 click = 2 value increments.. trying to work around that
        if (ctlValue < 0)
        {
            //If the encoder has switched directions before reaching 4 value increments, reset the value
            if (encValue[i] > 0)
            {
                encValue[i] = 0;
            }
            encValue[i]--;
            if (encValue[i] % 2 == 0)
            {
                onEncoderDecrease(i);
            }
        }
        else if (ctlValue > 0)
        {
            if (encValue[i] < 0)
            {
                encValue[i] = 0;
            }
            encValue[i]++;
            if (encValue[i] % 2 == 0)
            {
                onEncoderIncrease(i);
            }
        }
    }
}