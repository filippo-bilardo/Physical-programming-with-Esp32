#include <Arduino.h>

const int SIGNAL_PIN = 34;
const int THRESHOLD_PIN = 35;
const int LED_PIN = 18;
const int ADC_MAX = 4095;
const int HYSTERESIS = 100;  // Semibanda in codici ADC: usare valori da 1 a 2047.
const unsigned long SAMPLE_MS = 20;
const unsigned long REPORT_MS = 200;
unsigned long lastSample;
unsigned long lastReport;
bool alarmOn = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Stato iniziale, prima della prima lettura.
  analogReadResolution(12);
  analogSetPinAttenuation(SIGNAL_PIN, ADC_11db);
  analogSetPinAttenuation(THRESHOLD_PIN, ADC_11db);
  Serial.println("segnale,soglia,bassa,alta,allarme");
  lastSample = millis();
  lastReport = lastSample;
}

void loop() {
  const unsigned long now = millis();
  if (now - lastSample >= SAMPLE_MS) {
    lastSample = now;
    const int signal = analogRead(SIGNAL_PIN);
    const int setting = analogRead(THRESHOLD_PIN);
    // Mantieni entrambe le soglie raggiungibili, anche agli estremi del potenziometro.
    const int threshold = HYSTERESIS + setting * (long)(ADC_MAX - 2 * HYSTERESIS) / ADC_MAX;
    const int lower = threshold - HYSTERESIS;
    const int upper = threshold + HYSTERESIS;

    if (!alarmOn && signal >= upper) {
      alarmOn = true;
    } else if (alarmOn && signal <= lower) {
      alarmOn = false;
    }
    digitalWrite(LED_PIN, alarmOn ? HIGH : LOW);

    if (now - lastReport >= REPORT_MS) {
      lastReport = now;
      Serial.print(signal);
      Serial.print(",");
      Serial.print(threshold);
      Serial.print(",");
      Serial.print(lower);
      Serial.print(",");
      Serial.print(upper);
      Serial.print(",");
      Serial.println(alarmOn ? 1 : 0);
    }
  }
  delay(1);
}
