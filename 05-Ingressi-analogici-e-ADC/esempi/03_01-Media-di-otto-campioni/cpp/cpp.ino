#include <Arduino.h>

const int ADC_PIN = 34;
const int SAMPLES = 8;
const unsigned long SAMPLE_MS = 20;
unsigned long lastSample;
long total = 0;
int count = 0;
int minimum;
int maximum;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);
  Serial.println("ultimo,media8,minimo,massimo");
  lastSample = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastSample >= SAMPLE_MS) {
    lastSample = now;
    const int raw = analogRead(ADC_PIN);
    if (count == 0) {
      minimum = raw;
      maximum = raw;
    }
    if (raw < minimum) minimum = raw;
    if (raw > maximum) maximum = raw;
    total += raw;
    count++;

    if (count == SAMPLES) {
      const int average = total / SAMPLES;
      Serial.print(raw);
      Serial.print(",");
      Serial.print(average);
      Serial.print(",");
      Serial.print(minimum);
      Serial.print(",");
      Serial.println(maximum);
      total = 0;
      count = 0;  // Il prossimo blocco parte dal campione successivo.
    }
  }
  delay(1);
}
