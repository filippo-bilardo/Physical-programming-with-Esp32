#include <Arduino.h>

// Classe Pulsante: update() una volta per giro, poi interroga gli eventi.
class Pulsante {
  int pin;
  int raw = HIGH, stable = HIGH;
  unsigned long changed = 0, debounce;
  bool pressedEvent = false, clickEvent = false, cycleStarted = false;
 public:
  explicit Pulsante(int p, unsigned long wait = 50) : pin(p), debounce(wait) {}
  void begin() {
    pinMode(pin, INPUT_PULLUP);
    raw = stable = digitalRead(pin);
    changed = millis();
    cycleStarted = pressedEvent = clickEvent = false;
  }
  void update() {
    pressedEvent = clickEvent = false;
    const unsigned long now = millis();
    const int reading = digitalRead(pin);
    if (reading != raw) { raw = reading; changed = now; }
    if (now - changed >= debounce && raw != stable) {
      stable = raw;
      if (stable == LOW) { pressedEvent = true; cycleStarted = true; }
      else if (cycleStarted) { clickEvent = true; cycleStarted = false; }
    }
  }
  bool press() const { return stable == LOW; }
  bool pressDebounce() const { return pressedEvent; }
  bool click() const { return clickEvent; }
};
const int BUTTON_PIN = 23;
const int LED_PIN = 18;
Pulsante pulsante(BUTTON_PIN);
int ledState = LOW;
void setup() {
  Serial.begin(115200);
  pulsante.begin();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}
void loop() {
  pulsante.update();
  if (pulsante.pressDebounce()) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.println(ledState ? "LED acceso" : "LED spento");
  }
  delay(1);
}
