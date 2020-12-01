#ifndef OADEBUG_H_
#define OADEBUG_H_
#include <Audio.h>
#include <OpenAudio_ArduinoLibrary.h>
#include "inc/AudioManager.h"

class OADebug
{
public:
    OADebug(Paavo::Audio::Manager *ptrAm) {
        am=ptrAm;
    }
    void update();

private:
    void printResources(float cpu, uint8_t memF32, uint8_t memI16);
    void performanceCheck();
    void selectCommand(char c);

    float statsCpu = 0;
    uint8_t statsMemI16 = 0;
    uint8_t statsMemF32 = 0;
    Paavo::Audio::Manager *am;
};
#endif