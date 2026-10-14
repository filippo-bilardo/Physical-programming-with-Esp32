#include <Arduino.h>

const int LED_PIN = 18;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  // Mantiene il livello senza riscriverlo.
  Serial.println("LED acceso in modo continuo");
}

void loop() {
  delay(1000);                 // Il GPIO conserva il suo stato.
}
