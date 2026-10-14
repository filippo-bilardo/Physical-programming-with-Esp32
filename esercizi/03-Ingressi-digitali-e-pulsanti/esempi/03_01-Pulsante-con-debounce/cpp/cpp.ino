#include <Arduino.h>

const int LED_PIN = 18;
const int BUTTON_PIN = 23;
const unsigned long DEBOUNCE_MS = 30;
int lastRaw;
int stableState;
unsigned long lastChange;
bool ledOn = false;
unsigned long presses = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastRaw = digitalRead(BUTTON_PIN);
  stableState = lastRaw;      // Il livello iniziale non e' una pressione.
  lastChange = millis();
}

void loop() {
  const int raw = digitalRead(BUTTON_PIN);
  const unsigned long now = millis();
  if (raw != lastRaw) {
    lastRaw = raw;
    lastChange = now;         // Ogni cambiamento riavvia la finestra.
  }
  // Sottrazione unsigned: gestisce il ritorno a zero di millis().
  if (raw != stableState && now - lastChange >= DEBOUNCE_MS) {
    stableState = raw;
    if (stableState == LOW) { // Agisce solo sulla pressione stabilizzata.
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
      presses++;
      Serial.println(presses);
    }
  }
  delay(1);                  // Breve pausa; nessuna attesa bloccante di 30 ms.
}
