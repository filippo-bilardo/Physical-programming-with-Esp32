#include <Arduino.h>

const int ADC_PIN = 34;
const int ADC_MAX = 4095;
const unsigned long SAMPLE_MS = 200;
unsigned long lastSample;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);
  Serial.println("raw12,percento");
  lastSample = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastSample >= SAMPLE_MS) {
    lastSample = now;
    const int raw = analogRead(ADC_PIN);
    const int percent = raw * 100L / ADC_MAX;  // Divisione intera, per difetto.
    Serial.print(raw);
    Serial.print(",");
    Serial.println(percent);
  }
  delay(1);
}
