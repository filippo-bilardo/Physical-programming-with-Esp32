#include <Arduino.h>

const int LED_PIN = 18;
const unsigned long ON_MS = 200;
const unsigned long OFF_MS = 800;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Stato iniziale noto.
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED acceso");
  delay(ON_MS);               // Attesa in millisecondi.
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED spento");
  delay(OFF_MS);
}
