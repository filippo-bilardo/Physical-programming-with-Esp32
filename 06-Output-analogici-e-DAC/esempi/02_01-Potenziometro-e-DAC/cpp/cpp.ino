#include <Arduino.h>

unsigned long lastSample;
unsigned long lastPrint;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(34, ADC_11db);
  dacWrite(25, 0);
  lastSample = millis();
  lastPrint = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastSample >= 20) {
    lastSample = now;
    const int raw = analogRead(34);
    const int code = raw * 255L / 4095;
    dacWrite(25, code);
    if (now - lastPrint >= 200) {
      lastPrint = now;
      Serial.print("ADC="); Serial.print(raw);
      Serial.print(" DAC="); Serial.println(code);
    }
  }
  delay(1);
}
