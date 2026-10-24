/*
 * Importato da filippo-bilardo/ROBOTICA, Led/LED_01_lampeggio_semplice.ino.
 * Revisione locale di riferimento: be14c4db788f02186c714e241a8c2fa19b975b7d.
 * Adattamento ESP32 WROOM-32 del 24/10/2026; dettagli in ../PROVENIENZA.md.
 * Licenza del sorgente: GNU AGPLv3, vedi LICENSE nella radice del repository.
 */
#include <Arduino.h>

/*
 * LED_01_lampeggio_semplice.ino
 *
 * Questo sketch fa lampeggiare un LED collegato al GPIO 18 dell’ESP32.
 * Qui si usa un LED esterno sul GPIO 18, con resistenza da 220 ohm.
 *
 * Circuito:
 * - LED collegato al GPIO 18 e GND attraverso una resistenza da 220 ohm
 *
 * Creato il: 2023
 */

const int LED_PIN = 18;  // Pin a cui è collegato il LED

void setup() {
  // Inizializza il pin digitale come output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);   // Accende il LED (HIGH è il livello di tensione)
  delay(1000);                   // Attende un secondo
  digitalWrite(LED_PIN, LOW);    // Spegne il LED rendendo il pin LOW
  delay(1000);                   // Attende un secondo
}
