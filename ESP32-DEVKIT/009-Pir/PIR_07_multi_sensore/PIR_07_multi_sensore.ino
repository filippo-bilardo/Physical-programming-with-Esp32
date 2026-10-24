#include <Arduino.h>

/*
 * PIR_07_multi_sensore.ino
 *
 * Sistema multi-sensore PIR che monitora tre zone diverse
 * e tiene traccia dei movimenti rilevati in ciascuna zona
 *
 * Componenti necessari:
 * - ESP32 WROOM-32
 * - 3x Sensore PIR HC-SR501
 * - 3x LED
 * - 3x Resistore 220Ω
 * - Cavi di collegamento
 *
 * Collegamento:
 * PIR1 VCC -> 5V del modulo, uscita OUT compatibile 3.3V
 * PIR1 GND -> GND comune
 * PIR1 OUT -> GPIO 23
 * LED1 (+) -> GPIO 18 -> Resistore 220Ω -> LED (-) -> GND
 *
 * PIR2 VCC -> 5V del modulo, uscita OUT compatibile 3.3V
 * PIR2 GND -> GND comune
 * PIR2 OUT -> GPIO 22
 * LED2 (+) -> GPIO 19 -> Resistore 220Ω -> LED (-) -> GND
 *
 * PIR3 VCC -> 5V del modulo, uscita OUT compatibile 3.3V
 * PIR3 GND -> GND comune
 * PIR3 OUT -> GPIO 21
 * LED3 (+) -> GPIO 27 -> Resistore 220Ω -> LED (-) -> GND
 *
 * Autore: Filippo Bilardo
 * Data: 29/11/2025
 */

const int PIR_PIN_1 = 23;   // Pin del primo sensore PIR (zona 1)
const int PIR_PIN_2 = 22;   // Pin del secondo sensore PIR (zona 2)
const int PIR_PIN_3 = 21;   // Pin del terzo sensore PIR (zona 3)
const int LED_1 = 18;       // LED zona 1
const int LED_2 = 19;      // LED zona 2
const int LED_3 = 25;      // LED zona 3

// Stati dei sensori
int pirState1 = LOW;
int lastPirState1 = LOW;
int pirState2 = LOW;
int lastPirState2 = LOW;
int pirState3 = LOW;
int lastPirState3 = LOW;

// Contatori per ogni zona
unsigned long counter1 = 0;
unsigned long counter2 = 0;
unsigned long counter3 = 0;

void setup() {
  Serial.begin(115200);

  // Configura i pin dei sensori PIR
  pinMode(PIR_PIN_1, INPUT);
  pinMode(PIR_PIN_2, INPUT);
  pinMode(PIR_PIN_3, INPUT);

  // Configura i pin dei LED
  pinMode(LED_1, OUTPUT); digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT); digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT); digitalWrite(LED_3, LOW);

  Serial.println("Sistema multi-sensore PIR");
  Serial.println("Inizializzazione sensori PIR...");
  Serial.println("Attendere 60 secondi per la stabilizzazione...");
  delay(60000);
  Serial.println("Sistema pronto!");
  Serial.println("Monitoraggio zone attivo:");
  Serial.println("- Zona 1 (Nord)");
  Serial.println("- Zona 2 (Est)");
  Serial.println("- Zona 3 (Sud)");
}

void loop() {
  // Leggi lo stato di tutti i sensori
  pirState1 = digitalRead(PIR_PIN_1);
  pirState2 = digitalRead(PIR_PIN_2);
  pirState3 = digitalRead(PIR_PIN_3);

  // Gestione Zona 1
  if (pirState1 == HIGH && lastPirState1 == LOW) {
    counter1++;
    digitalWrite(LED_1, HIGH);
    Serial.print("Zona 1 (Nord): Movimento rilevato! [Totale: ");
    Serial.print(counter1);
    Serial.println("]");
  }
  if (pirState1 == LOW && lastPirState1 == HIGH) {
    digitalWrite(LED_1, LOW);
  }
  lastPirState1 = pirState1;

  // Gestione Zona 2
  if (pirState2 == HIGH && lastPirState2 == LOW) {
    counter2++;
    digitalWrite(LED_2, HIGH);
    Serial.print("Zona 2 (Est): Movimento rilevato! [Totale: ");
    Serial.print(counter2);
    Serial.println("]");
  }
  if (pirState2 == LOW && lastPirState2 == HIGH) {
    digitalWrite(LED_2, LOW);
  }
  lastPirState2 = pirState2;

  // Gestione Zona 3
  if (pirState3 == HIGH && lastPirState3 == LOW) {
    counter3++;
    digitalWrite(LED_3, HIGH);
    Serial.print("Zona 3 (Sud): Movimento rilevato! [Totale: ");
    Serial.print(counter3);
    Serial.println("]");
  }
  if (pirState3 == LOW && lastPirState3 == HIGH) {
    digitalWrite(LED_3, LOW);
  }
  lastPirState3 = pirState3;

  delay(100);
}
