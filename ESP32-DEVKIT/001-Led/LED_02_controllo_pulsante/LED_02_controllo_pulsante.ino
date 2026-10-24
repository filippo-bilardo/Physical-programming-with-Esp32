/*
 * Importato da filippo-bilardo/ROBOTICA, Led/LED_02_controllo_pulsante.ino.
 * Revisione locale di riferimento: be14c4db788f02186c714e241a8c2fa19b975b7d.
 * Adattamento ESP32 WROOM-32 del 24/10/2026; dettagli in ../PROVENIENZA.md.
 * Licenza del sorgente: GNU AGPLv3, vedi LICENSE nella radice del repository.
 */
#include <Arduino.h>

/*
 * LED_02_controllo_pulsante.ino
 *
 * Questo sketch controlla un LED tramite un pulsante.
 * Quando il pulsante è premuto, il LED si accende.
 *
 * Circuito:
 * - LED collegato al GPIO 18 e GND attraverso una resistenza da 220 ohm
 * - Pulsante collegato al GPIO 23 e GND
 *
 * Creato il: 2023
 */

const int LED_PIN = 18;     // Pin a cui è collegato il LED
const int BUTTON_PIN = 23;   // Pin a cui è collegato il pulsante

void setup() {
  pinMode(LED_PIN, OUTPUT);           // Imposta il pin del LED come output
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Imposta il pin del pulsante come input con resistenza pull-up
}

void loop() {
  // Leggi lo stato del pulsante
  int buttonState = digitalRead(BUTTON_PIN);

  // Controlla se il pulsante è premuto
  // Se utilizziamo INPUT_PULLUP, il pulsante restituisce LOW quando è premuto
  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH);  // Accendi il LED
  } else {
    digitalWrite(LED_PIN, LOW);   // Spegni il LED
  }
}
