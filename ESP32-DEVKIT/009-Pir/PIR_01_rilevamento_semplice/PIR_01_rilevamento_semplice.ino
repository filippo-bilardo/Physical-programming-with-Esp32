#include <Arduino.h>

/*
 * PIR_01_rilevamento_semplice.ino
 *
 * Sketch base per il rilevamento di movimento con sensore PIR
 *
 * Componenti necessari:
 * - ESP32 WROOM-32
 * - Sensore PIR HC-SR501
 * - Cavi di collegamento
 *
 * Collegamento:
 * PIR VCC  -> 5V del modulo, uscita OUT compatibile 3.3V
 * PIR GND  -> GND comune
 * PIR OUT  -> GPIO 23
 *
 * Autore: Filippo Bilardo
 * Data: 29/11/2025
 */

const int PIR_PIN = 23;  // Pin a cui è collegato il sensore PIR

void setup() {
  Serial.begin(115200);       // Inizializza la comunicazione seriale
  pinMode(PIR_PIN, INPUT);  // Imposta il pin del PIR come input

  Serial.println("Inizializzazione sensore PIR...");
  Serial.println("Attendere 60 secondi per la stabilizzazione...");
  delay(60000);  // Attendi 60 secondi per permettere al sensore di calibrarsi
  Serial.println("Sensore pronto!");
}

void loop() {
  int pirState = digitalRead(PIR_PIN);  // Leggi lo stato del sensore PIR

  if (pirState == HIGH) {  // Se viene rilevato movimento
    Serial.println("Movimento rilevato!");
  } else {
    Serial.println("Nessun movimento");
  }

  delay(500);  // Piccolo ritardo per evitare letture eccessive
}
