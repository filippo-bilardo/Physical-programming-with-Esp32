#include <Arduino.h>

const int ADC_PIN = 34;  // ADC1 sull'ESP32 classico.
const unsigned long SAMPLE_MS = 200;
unsigned long lastSample;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // Codici da 0 a 4095.
  analogSetPinAttenuation(ADC_PIN, ADC_11db);
  lastSample = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastSample >= SAMPLE_MS) {
    lastSample = now;
    const int raw = analogRead(ADC_PIN);
    Serial.println(raw);
  }
  delay(1);
}
