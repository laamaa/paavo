#include "inc/GUI.h"
#include "inc/AudioManager.h"
#include "inc/AudioEffect.h"
#include <ili9341_t3n_font_OpenSans.h>

void Paavo::GUI::Manager::init()
{
    tftFrameBuffer = new uint16_t[ILI9341_TFTHEIGHT * ILI9341_TFTWIDTH];
    tft.begin(26000000);
    tft.setRotation(3);
    tft.setFrameBuffer(tftFrameBuffer);
    tft.useFrameBuffer(true);
    delay(10);
    tft.fillScreen(ILI9341_BLACK);
    tft.updateScreen();
    osc[0] = new Oscilloscope(am->getMaster(0), &tft, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.15);
    osc[1] = new Oscilloscope(am->getMaster(1), &tft, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.15, 0, ILI9341_TFTWIDTH * 0.15);
    osc[2] = new Oscilloscope(am->getMaster(2), &tft, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.15, 0, ILI9341_TFTWIDTH * 0.30);
    osc[3] = new Oscilloscope(am->getMaster(3), &tft, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.15, 0, ILI9341_TFTWIDTH * 0.45);
    osc[0]->init();
    osc[1]->init();
    osc[2]->init();
    osc[3]->init();
    qm = new GUI::QuickFxSettingsMenu(&tft, am);
    qm->drawMenuGrid();
    qm->drawLabels(0);
}

void Paavo::GUI::Manager::update()
{
    if (lastScreenUpdate > 16 && !tft.asyncUpdateActive()) //50fps
        tft.updateScreenAsync();
}

void Paavo::GUI::QuickFxSettingsMenu::drawMenuGrid()
{
    display->drawLine(0, ILI9341_TFTWIDTH * 0.8, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.8, ILI9341_WHITE);
    for (int i = 1; i < 5; i++)
        display->drawLine(ILI9341_TFTHEIGHT * 0.2 * i, ILI9341_TFTWIDTH * 0.8, ILI9341_TFTHEIGHT * 0.2 * i, ILI9341_TFTWIDTH, ILI9341_WHITE);
}

void Paavo::GUI::QuickFxSettingsMenu::drawLabels(uint8_t fxslot)
{
    display->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    display->setCursor(ILI9341_t3n::CENTER, (ILI9341_TFTWIDTH * 0.8) - 16, true);
    display->setFont(OpenSans14);
    display->println(am->getFx(fxslot)->getTitle());
    display->setFont(OpenSans8);
        
    for (int i = 0; i < 5; i++)
    {
        display->setCursor((ILI9341_TFTHEIGHT * 0.2 * i) + ILI9341_TFTHEIGHT * 0.1, (ILI9341_TFTWIDTH * 0.8), true);
        display->println(am->getFx(fxslot)->getQuickSetting(i).getLabel());
        display->setCursor((ILI9341_TFTHEIGHT * 0.2 * i) + ILI9341_TFTHEIGHT * 0.1, (ILI9341_TFTWIDTH * 0.9)+14, true);
        display->println(am->getFx(fxslot)->getQuickSetting(i).getUnit());
    }
    drawValues(0);
}

void Paavo::GUI::QuickFxSettingsMenu::drawValues(uint8_t fxslot, uint8_t qfxNum)
{

    display->setTextColor(ILI9341_WHITE);
    display->setFont(OpenSans14);
    if (qfxNum == 255)
    {
        //Draw all values
        for (int i = 0; i < 5; i++)
        {
            display->setCursor((ILI9341_TFTHEIGHT * 0.2 * i) + ILI9341_TFTHEIGHT * 0.1, (ILI9341_TFTWIDTH * 0.9), true);
            display->printf("%.1f",am->getFx(fxslot)->getQuickSetting(i).getValue());
        }
    }
}