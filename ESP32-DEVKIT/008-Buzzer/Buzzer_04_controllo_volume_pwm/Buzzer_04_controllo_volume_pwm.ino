#include <Arduino.h>

// Esperimento sul duty: non e un controllo calibrato del volume.
const int BUZZER_PIN = 27;  // Uscita PWM ESP32

void setup() {
  analogWriteResolution(BUZZER_PIN,8);
  analogWriteFrequency(BUZZER_PIN,1000);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Duty crescente
  for (int duty = 0; duty <= 255; duty += 5) {
    analogWrite(BUZZER_PIN, duty);  // Imposta il duty, non una percentuale calibrata di volume
    delay(30);
  }

  // Duty decrescente
  for (int duty = 255; duty >= 0; duty -= 5) {
    analogWrite(BUZZER_PIN, duty);
    delay(30);
  }

  delay(1000);  // Pausa prima di ripetere
}
