#include <Arduino.h>

const int LED_PINS[] = {18, 19, 21};
const int LED_COUNT = 3;
const unsigned long STEP_MS = 300;

void showOnly(int selected) {
  // Prima spegne tutti: evita sovrapposizioni nel cambio di fase.
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  digitalWrite(LED_PINS[selected], HIGH);
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < LED_COUNT; i++) {
    showOnly(i);
    Serial.println(i);
    delay(STEP_MS);
  }
}
