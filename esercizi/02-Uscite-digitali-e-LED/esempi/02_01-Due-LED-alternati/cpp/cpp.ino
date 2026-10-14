#include <Arduino.h>

const int LED_A = 18;
const int LED_B = 19;
const unsigned long STEP_MS = 500;

void setup() {
  Serial.begin(115200);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
}

void loop() {
  digitalWrite(LED_B, LOW);   // Spegne prima di accendere l'altro LED.
  digitalWrite(LED_A, HIGH);
  Serial.println("A");
  delay(STEP_MS);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, HIGH);
  Serial.println("B");
  delay(STEP_MS);
}
