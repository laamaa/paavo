#include "inc/OADebug.h"
#include "inc/AudioManager.h"

void OADebug::printResources(float cpu, uint8_t memF32, uint8_t memI16)
{
    Serial.printf("CPU: %.2f%%, Mem: %d F32 %d I16\n", cpu, memF32, memI16);
}

void OADebug::performanceCheck()
{
    static unsigned long last = 0;
    unsigned long now = millis();
    if ((now - last) > 1000)
    {
        last = now;
        float cpu = AudioProcessorUsageMax();
        uint8_t memI16 = AudioMemoryUsageMax();
        uint8_t memF32 = AudioMemoryUsageMax_F32();
        if ((statsMemF32 != memF32) || (statsMemI16 != memI16) || fabs(statsCpu - cpu) > 1)
        {
            printResources(cpu, memF32, memI16);
        }
        AudioProcessorUsageMaxReset();
        AudioMemoryUsageMaxReset();
        AudioMemoryUsageMaxReset_F32();
        last = now;
        statsCpu = 0;
        statsMemF32 = memF32;
        statsMemI16 = memI16;
    }
}

void OADebug::selectCommand(char c)
{
    switch (c)
    {
    case '\r':
        Serial.println();
        break;
    case 's':
        // print cpu and mem usage
        printResources(statsCpu, statsMemF32, statsMemI16);
        break;
    case '\t':
        // reboot Teensy
        *(uint32_t *)0xE000ED0C = 0x5FA0004;
        break;
    case 'b':
        am->bypassFx();
        break;
    case 'i':
        am->bypassShimmer();
        break;
    default:
        break;
    }
}

void OADebug::update()
{
    performanceCheck();
    while (Serial.available())
        selectCommand(Serial.read());
}
