#include <Audio.h>
#include <OpenAudio_ArduinoLibrary.h>
#include "inc/settings.h"
#include "inc/AudioManager.h"
#include "inc/GUI.h"
#include "inc/Oscilloscope.h"

#if SYNTH_DEBUG > 0
#include "inc/OADebug.h"
OADebug debug;
#endif

Paavo::AudioManager am;
Paavo::GUI gui(&am);

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