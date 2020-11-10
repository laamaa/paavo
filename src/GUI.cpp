#include "inc/GUI.h"

void Paavo::GUI::init()
{
    tftFrameBuffer = new uint16_t[ILI9341_TFTHEIGHT * ILI9341_TFTWIDTH];
    tft.begin(26000000);
    //tft.setRotation(1);
    tft.setFrameBuffer(tftFrameBuffer);
    tft.useFrameBuffer(true);
    delay(10);
    tft.fillScreen(ILI9341_BLACK);
    tft.updateScreen();
    osc[0] = new Oscilloscope(am->getMaster(0), &tft, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.25);
    osc[1] = new Oscilloscope(am->getMaster(1), &tft, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.25, 0, ILI9341_TFTWIDTH * 0.25);
    osc[2] = new Oscilloscope(am->getMaster(2), &tft, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.25, 0, ILI9341_TFTWIDTH * 0.5);
    osc[3] = new Oscilloscope(am->getMaster(3), &tft, ILI9341_TFTHEIGHT, ILI9341_TFTWIDTH * 0.25, 0, ILI9341_TFTWIDTH * 0.75);
    osc[0]->init();
    osc[1]->init();
    osc[2]->init();
    osc[3]->init();
}

void Paavo::GUI::update()
{
    if (lastScreenUpdate > 17 && !tft.asyncUpdateActive()) //50fps
        tft.updateScreenAsync();
}