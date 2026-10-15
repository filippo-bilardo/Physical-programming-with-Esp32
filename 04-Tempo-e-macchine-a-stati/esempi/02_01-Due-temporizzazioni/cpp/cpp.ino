#include <Arduino.h>

const int RED_PIN = 18;
const int YELLOW_PIN = 19;
const unsigned long RED_INTERVAL_MS = 250;
const unsigned long YELLOW_INTERVAL_MS = 700;
unsigned long lastRed;
unsigned long lastYellow;
bool redOn = false;
bool yellowOn = false;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  lastRed = millis();
  lastYellow = lastRed;
}

void loop() {
  const unsigned long now = millis();
  if (now - lastRed >= RED_INTERVAL_MS) {
    lastRed = now;
    redOn = !redOn;
    digitalWrite(RED_PIN, redOn ? HIGH : LOW);
  }
  // Un altro if: entrambe le attivita' possono essere pronte nello stesso giro.
  if (now - lastYellow >= YELLOW_INTERVAL_MS) {
    lastYellow = now;
    yellowOn = !yellowOn;
    digitalWrite(YELLOW_PIN, yellowOn ? HIGH : LOW);
  }
  delay(1);
}
