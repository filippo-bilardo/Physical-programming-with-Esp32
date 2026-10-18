#include <Arduino.h>

bool ready = false;
bool sounding = true;
unsigned long lastChange;

void setup() {
  Serial.begin(115200);
  ready = ledcAttach(18, 440, 8);
  if (ready) ready = ledcWriteTone(18, 440) != 0;
  if (!ready) {
    ledcWriteTone(18, 0);
    Serial.println("ERR PWM");
  } else Serial.println("TONE=440");
  lastChange = millis();
}

void loop() {
  const unsigned long now = millis();
  if (ready && now - lastChange >= 1000) {
    lastChange = now;
    sounding = !sounding;
    if (sounding) {
      if (ledcWriteTone(18, 440) == 0) {
        ready = false;
        ledcWriteTone(18, 0);
        Serial.println("ERR PWM");
      } else Serial.println("TONE=440");
    } else {
      ledcWriteTone(18, 0);  // Duty zero: silenzio, non freq(0) MicroPython.
      Serial.println("TONE=0");
    }
  }
  delay(1);
}
