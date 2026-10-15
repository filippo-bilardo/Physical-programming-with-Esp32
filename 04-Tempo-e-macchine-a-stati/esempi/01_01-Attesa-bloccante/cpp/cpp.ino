#include <Arduino.h>

const int RED_PIN = 18;
const int YELLOW_PIN = 19;
const int BUTTON_PIN = 23;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
}

void loop() {
  // Si legge soltanto qui: una pressione tra due letture puo' andare persa.
  digitalWrite(YELLOW_PIN, digitalRead(BUTTON_PIN) == LOW ? HIGH : LOW);
  digitalWrite(RED_PIN, HIGH);
  delay(1000);
  digitalWrite(RED_PIN, LOW);
  delay(1000);
}
