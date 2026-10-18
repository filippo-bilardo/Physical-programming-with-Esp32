#include <Arduino.h>

const int levels[] = {0, 64, 128, 192, 255};
int indexLevel = 0;
unsigned long lastChange;

void showLevel() {
  const int code = levels[indexLevel];
  dacWrite(25, code);
  Serial.print("DAC="); Serial.println(code);  // Codice, non tensione misurata.
}

void setup() {
  Serial.begin(115200);
  showLevel();
  lastChange = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastChange >= 2000) {
    lastChange = now;
    indexLevel = (indexLevel + 1) % 5;
    showLevel();
  }
  delay(1);
}
