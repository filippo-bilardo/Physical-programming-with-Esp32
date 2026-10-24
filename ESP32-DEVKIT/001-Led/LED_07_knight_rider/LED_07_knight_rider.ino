/*
 * Importato da filippo-bilardo/ROBOTICA, Led/LED_07_knight_rider.ino.
 * Revisione locale di riferimento: be14c4db788f02186c714e241a8c2fa19b975b7d.
 * Adattamento ESP32 WROOM-32 del 24/10/2026; dettagli in ../PROVENIENZA.md.
 * Licenza del sorgente: GNU AGPLv3, vedi LICENSE nella radice del repository.
 */
#include <Arduino.h>

/*
 * LED_07_knight_rider.ino
 *
 * Questo sketch crea un effetto "Knight Rider" (come la serie TV Supercar)
 * con una serie di LED che si accendono e si spengono in sequenza.
 *
 * Circuito:
 * - 6 LED collegati ai GPIO 18, 19, 21, 22, 25 e 26 e GND attraverso resistenze da 220 ohm
 *
 * Creato il: 2023
 */

// Definizione dei pin per i LED
const int LED_PINS[] = {18, 19, 21, 22, 25, 26};
const int NUM_LEDS = 6;       // Numero di LED utilizzati

// Variabili per il controllo dell'animazione
int currentLed = 0;           // LED attualmente acceso
int direction = 1;            // Direzione dell'animazione (1 = avanti, -1 = indietro)

void setup() {
  // Inizializza tutti i pin dei LED come output
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void loop() {
  // Spegni tutti i LED
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }

  // Accendi il LED corrente
  digitalWrite(LED_PINS[currentLed], HIGH);

  // Attendi un po' prima di passare al LED successivo
  delay(100);

  // Aggiorna la posizione per il prossimo ciclo
  currentLed += direction;

  // Cambia direzione quando raggiungi la fine della sequenza
  if (currentLed == NUM_LEDS - 1 || currentLed == 0) {
    direction = -direction;
  }
}
