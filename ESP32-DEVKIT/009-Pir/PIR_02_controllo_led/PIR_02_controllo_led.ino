#include <Arduino.h>

/*
 * PIR_02_controllo_led.ino
 *
 * Sketch per controllare un LED con un sensore PIR
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

const int PIR_PIN = 23;     // Pin a cui è collegato il sensore PIR
const int LED_PIN = 18;    // Pin a cui è collegato il LED

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);      // Imposta il pin del PIR come input
  pinMode(LED_PIN, OUTPUT); digitalWrite(LED_PIN, LOW);     // Imposta il pin del LED come output

  Serial.println("Inizializzazione sensore PIR...");
  Serial.println("Attendere 60 secondi per la stabilizzazione...");
  delay(60000);  // Attendi 60 secondi per permettere al sensore di calibrarsi
  Serial.println("Sensore pronto!");
}

void loop() {
  int pirState = digitalRead(PIR_PIN);  // Leggi lo stato del sensore PIR

  if (pirState == HIGH) {  // Se viene rilevato movimento
    digitalWrite(LED_PIN, HIGH);  // Accendi il LED
    Serial.println("Movimento rilevato! LED acceso");
  } else {
    digitalWrite(LED_PIN, LOW);   // Spegni il LED
  }

  delay(100);  // Piccolo ritardo
}
