/*
 * Importato da filippo-bilardo/ROBOTICA, Led/LED_04_effetto_respiro.ino.
 * Revisione locale di riferimento: be14c4db788f02186c714e241a8c2fa19b975b7d.
 * Adattamento ESP32 WROOM-32 del 24/10/2026; dettagli in ../PROVENIENZA.md.
 * Licenza del sorgente: GNU AGPLv3, vedi LICENSE nella radice del repository.
 */
#include <Arduino.h>

/*
 * LED_04_effetto_respiro.ino
 *
 * Questo sketch crea un effetto di "respiro" (breathing effect) con un LED,
 * simulando un'accensione e uno spegnimento graduali con un andamento sinusoidale.
 *
 * Circuito:
 * - LED collegato al GPIO 18 (uscita PWM) e GND attraverso una resistenza da 220 ohm
 *
 * Creato il: 2023
 */

const int LED_PIN = 18;  // Pin PWM a cui è collegato il LED

void setup() {
  pinMode(LED_PIN, OUTPUT);
  analogWriteResolution(LED_PIN, 8);
  analogWriteFrequency(LED_PIN, 5000);
}

void loop() {
  // Utilizza la funzione seno per creare un effetto di respiro più naturale
  for (int i = 0; i < 360; i++) {
    // Converte l'angolo in radianti e calcola il seno
    float rad = i * (PI / 180.0);
    float sinVal = sin(rad);

    // Trasforma il valore del seno (che va da -1 a 1) in un valore da 0 a 255
    int brightness = int((sinVal + 1.0) * 127.5);

    // Imposta la luminosità del LED
    analogWrite(LED_PIN, brightness);

    // Piccolo ritardo per rendere l'effetto visibile
    delay(5);
  }
}
