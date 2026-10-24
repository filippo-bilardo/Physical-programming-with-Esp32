// @author Filippo Bilardo
#include <Arduino.h>

#include "RtttlPlayer.h"
#include "Melodie.h"

NonBlockingBuzzer buzzer(27);
const char* melodies[]={mTetris,mMission,mSuperMario};
int indexMelody=0;
bool paused=false, finished=false;
unsigned long pausedAt=0, ledChanged=0;
bool ledState=false;
void setup() {
  Serial.begin(115200); buzzer.begin();
  pinMode(18,OUTPUT); digitalWrite(18,LOW);
  ledChanged=millis(); buzzer.startPlay(melodies[0]);
}
void loop() {
  const unsigned long now=millis();
  buzzer.update();
  if (now-ledChanged>=250) { ledChanged=now; ledState=!ledState; digitalWrite(18,ledState); }
  if (!finished && !buzzer.isPlayingMelody()) {
    if (!paused) { paused=true; pausedAt=now; }
    else if (now-pausedAt>=1000) {
      if (++indexMelody<3) { paused=false; buzzer.startPlay(melodies[indexMelody]); }
      else { finished=true; Serial.println("FINE MELODIE"); }
    }
  }
  delay(1);
}
