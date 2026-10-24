// @author Filippo Bilardo
#include <Arduino.h>

#include "RtttlPlayer.h"
#include "Melodie.h"

Buzzer buzzer(27);
void setup() {
  Serial.begin(115200); buzzer.begin();
  buzzer.play(mTetris); delay(1000);
  buzzer.play(mMission); delay(1000);
  buzzer.play(mSuperMario);
}
void loop() { delay(1); }
