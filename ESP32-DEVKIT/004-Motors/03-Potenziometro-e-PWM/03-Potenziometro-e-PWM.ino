#include "MyMotors.h"

MyMotors motors(IN1, IN2, ENA, PWM_CHA, IN3, IN4, ENB, PWM_CHB, true);
bool ready = false;

bool active = false;
int lastPercent = -1;
unsigned long lastSample;

void setup() {
  Serial.begin(115200);
  pinMode(ENABLE_BUTTON, INPUT_PULLUP);
  analogReadResolution(12);
  analogSetPinAttenuation(34, ADC_11db);
  ready = motors.begin();
  lastSample = millis();
  Serial.println(ready ? "PRONTO: tieni premuto GPIO23" : "ERR PWM");
}

void loop() {
  const unsigned long now = millis();
  if (ready) {
    if (digitalRead(ENABLE_BUTTON) == HIGH) {
      if (active) { motors.stop(3); Serial.println("STOP"); }
      active = false;
      lastPercent = -1;
    } else if (!active || now - lastSample >= 100) {
      active = true;
      lastSample = now;
      const int raw = analogRead(34);
      // Piccola zona di arresto all'inizio della scala ADC.
      const int percent = raw <= 100 ? 0 : (raw - 100) * 100L / (4095 - 100);
      if (percent != lastPercent) {
        ready = motors.run(1, percent);
        Serial.print("ADC="); Serial.print(raw);
        Serial.print(" CMD="); Serial.println(percent);
        lastPercent = percent;
      }
    }
    if (!motors.isReady()) ready = false;
    if (!ready) { motors.stop(3); Serial.println("ERR PWM"); }
  }
  delay(1);
}
