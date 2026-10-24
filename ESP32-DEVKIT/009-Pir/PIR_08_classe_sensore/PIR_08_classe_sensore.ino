#include <Arduino.h>

/*
 * PIR_08_classe_sensore.ino
 *
 * Utilizzo della classe SensorePIR per una gestione orientata agli oggetti
 * del sensore PIR. La classe incapsula tutte le funzionalità necessarie
 * per gestire il sensore in modo efficiente e strutturato.
 *
 * Componenti necessari:
 * - ESP32 WROOM-32
 * - Sensore PIR HC-SR501
 * - LED
 * - Resistore 220Ω
 * - Cavi di collegamento
 *
 * Collegamento:
 * PIR VCC  -> 5V del modulo, uscita OUT compatibile 3.3V
 * PIR GND  -> GND comune
 * PIR OUT  -> GPIO 23
 * LED (+)  -> GPIO 18 -> Resistore 220Ω -> LED (-) -> GND
 *
 * Autore: Filippo Bilardo
 * Data: 29/11/2025
 */


class SensorePIR {
  int pin;
  bool state = false, started = false, ended = false;
  unsigned long changed = 0, began = 0, duration = 0, count = 0;
 public:
  explicit SensorePIR(int p) : pin(p) {}
  void inizializza(unsigned long wait = 60000) {
    pinMode(pin, INPUT);
    delay(wait);
    state = started = ended = false;
    changed = began = millis(); duration = count = 0;
  }
  void update() {
    started = ended = false;
    const bool current = digitalRead(pin) == HIGH;
    if (current != state) {
      state = current; changed = millis();
      if (state) { began = changed; count++; started = true; }
      else { duration = changed - began; ended = true; }
    }
  }
  bool leggiStato() const { return state; }
  bool movimentoRilevato() const { return started; }
  bool movimentoTerminato() const { return ended; }
  unsigned long getContatore() const { return count; }
  void resetContatore() { count = 0; }
  unsigned long getTempoDallUltimoCambio() const { return millis() - changed; }
  unsigned long getDurataUltimoMovimento() const { return duration; }
};
const int PIR_PIN = 23, LED_PIN = 18;
SensorePIR sensore(PIR_PIN);
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); digitalWrite(LED_PIN, LOW);
  Serial.println("Attendi 60 s per la stabilizzazione del PIR");
  sensore.inizializza();
  Serial.println("Sensore pronto!");
}
void loop() {
  sensore.update();
  digitalWrite(LED_PIN, sensore.leggiStato() ? HIGH : LOW);
  if (sensore.movimentoRilevato()) {
    Serial.print("Movimento rilevato! Totale="); Serial.println(sensore.getContatore());
  }
  if (sensore.movimentoTerminato()) {
    Serial.print("Durata HIGH ms="); Serial.println(sensore.getDurataUltimoMovimento());
  }
  delay(100);
}
