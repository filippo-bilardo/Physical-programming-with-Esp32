#include <Arduino.h>

const int RED_PIN = 18;
const int YELLOW_PIN = 19;
const int BUTTON_PIN = 23;
const unsigned long INTERVAL_MS = 1000;
unsigned long lastToggle;
bool redOn = false;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  lastToggle = millis();
}

void loop() {
  const unsigned long now = millis();
  // La lettura continua anche durante le fasi del lampeggio.
  digitalWrite(YELLOW_PIN, digitalRead(BUTTON_PIN) == LOW ? HIGH : LOW);
  if (now - lastToggle >= INTERVAL_MS) {
    lastToggle = now;
    redOn = !redOn;
    digitalWrite(RED_PIN, redOn ? HIGH : LOW);
  }
  delay(1);  // Breve pausa per giro, non un'attesa di 1000 ms.
}
