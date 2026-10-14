#include <Arduino.h>

const int LED_PIN = 18;
const int BUTTON_PIN = 23;
int previousReading;
bool ledOn = false;
unsigned long presses = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  previousReading = digitalRead(BUTTON_PIN);
}

void loop() {
  const int reading = digitalRead(BUTTON_PIN);
  // Riconosce il fronte di discesa; NON filtra i rimbalzi.
  if (previousReading == HIGH && reading == LOW) {
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    presses++;
    Serial.println(presses);
  }
  previousReading = reading;
  delay(1);
}
