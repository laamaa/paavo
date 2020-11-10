#ifndef OADEBUG_H_
#define OADEBUG_H_
#include <Audio.h>
#include <OpenAudio_ArduinoLibrary.h>

class OADebug
{
public:
    void update();

private:
    void printResources(float cpu, uint8_t memF32, uint8_t memI16);
    void performanceCheck();
    void selectCommand(char c);

    float statsCpu = 0;
    uint8_t statsMemI16 = 0;
    uint8_t statsMemF32 = 0;
};
#endif