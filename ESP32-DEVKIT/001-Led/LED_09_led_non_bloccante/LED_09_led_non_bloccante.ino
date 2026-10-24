/*
 * Importato da filippo-bilardo/ROBOTICA, Led/LED_09_led_non_bloccante.ino.
 * Revisione locale di riferimento: be14c4db788f02186c714e241a8c2fa19b975b7d.
 * Adattamento ESP32 WROOM-32 del 24/10/2026; dettagli in ../PROVENIENZA.md.
 * Licenza del sorgente: GNU AGPLv3, vedi LICENSE nella radice del repository.
 */
#include <Arduino.h>

/*
 * LED_09_led_non_bloccante.ino
 *
 * Il periodo del LED e gestito con millis(), senza lunghe attese.
 * Il ciclo mantiene una pausa cooperativa di 1 ms e legge la seriale.
 *
 * Circuito:
 * - LED collegato al GPIO 18 e GND attraverso una resistenza da 220 ohm
 *
 * Creato il: 2023
 */

const int LED_PIN = 18;        // Pin a cui è collegato il LED

// Variabili per il controllo del lampeggio non bloccante
unsigned long previousMillis = 0;  // Memorizza l'ultimo momento in cui il LED è stato aggiornato
const unsigned long interval = 1000;        // Intervallo di lampeggio (millisecondi)
int ledState = LOW;                // Stato attuale del LED

void setup() {
  // Inizializza il pin digitale come output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  previousMillis = millis();

  // Inizializza la comunicazione seriale
  Serial.begin(115200);
  Serial.println("LED non bloccante - premi qualsiasi tasto per inviare un messaggio");
}

void loop() {
  // Controlla se sono disponibili dati sulla porta seriale
  if (Serial.available() > 0) {
    // Leggi il byte in arrivo
    char incomingByte = Serial.read();

    // Stampa il carattere ricevuto
    Serial.print("Ho ricevuto: ");
    Serial.println(incomingByte);
  }

  // Controlla se è trascorso abbastanza tempo dall'ultimo aggiornamento
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Salva l'ultimo momento in cui hai aggiornato il LED
    previousMillis = currentMillis;

    // Inverte lo stato del LED
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // Imposta il LED con il nuovo stato
    digitalWrite(LED_PIN, ledState);

    // Stampa un messaggio quando il LED cambia stato
    Serial.print("LED cambiato a: ");
    Serial.println(ledState == HIGH ? "ACCESO" : "SPENTO");
  }

  // Qui puoi inserire altro codice che verrà eseguito continuamente
  // senza attendere il prossimo cambio del LED.
  delay(1);
}
