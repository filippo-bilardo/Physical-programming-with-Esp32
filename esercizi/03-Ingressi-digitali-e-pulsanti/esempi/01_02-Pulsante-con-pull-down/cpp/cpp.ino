#include <Arduino.h>

const int LED_PIN = 18;
const int BUTTON_PIN = 23;
int previousReading = -1;    // Forza la stampa della prima lettura.

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  const int reading = digitalRead(BUTTON_PIN);
  const bool pressed = (reading == HIGH); // Pulsante attivo alto.
  digitalWrite(LED_PIN, pressed ? HIGH : LOW);
  if (reading != previousReading) {
    Serial.println(pressed ? "Premuto" : "Rilasciato");
    previousReading = reading;
  }
  delay(10);                 // Lettura periodica; non e' un debounce.
}
