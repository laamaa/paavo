#include <Audio.h>
#include <OpenAudio_ArduinoLibrary.h>
#include "inc/settings.h"
#include "inc/AudioManager.h"
#include "inc/GUI.h"
#include "inc/Oscilloscope.h"

Paavo::Audio::Manager am;
Paavo::GUI::Manager gui(&am);

#if SYNTH_DEBUG > 0
#include "inc/OADebug.h"
OADebug debug(&am);
#endif


void setup(void)
{
  Serial.begin(1);
  delay(1000);
  Serial.println(F("Paavo starttaileepi"));
  am.init();
  gui.init();
}

void loop(void)
{
#if SYNTH_DEBUG > 0
  debug.update();
#endif
gui.update();

}