#include <Arduino.h>

/**
 * \Servo_05_inseguimento_solare
 *
 * Sketch per un sistema di inseguimento solare con Arduino
 * Il servo ruota in base alla differenza di luce rilevata da due sensori LDR.
 *
 *
 * @author Filippo Bilardo
 * @version 1.0  20/03/25 - Versione iniziale
 */
#include <ESP32Servo.h>

const int SERVO_PIN = 18;    // Pin a cui è collegato il servo
const int LDR_LEFT = 34;    // Pin analogico per il sensore di luce sinistro
const int LDR_RIGHT = 35;   // Pin analogico per il sensore di luce destro
const int THRESHOLD = 200;   // Soglia di differenza per il movimento

Servo trackingServo;        // Crea un oggetto servo
int currentPosition = 90;   // Posizione iniziale del servo (centro)

bool ready = false;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(34, ADC_11db);
  analogSetPinAttenuation(35, ADC_11db);

  trackingServo.setPeriodHertz(50);
  trackingServo.attach(SERVO_PIN, 1000, 2000);
  ready = trackingServo.attached();
  if (!ready) { trackingServo.detach(); Serial.println("ERR SERVO"); return; }  // Collega il servo al pin specificato
  trackingServo.write(currentPosition);  // Imposta la posizione iniziale
}

void loop() {
  if (!ready) { delay(10); return; }
  // Legge i valori dei sensori di luce
  int leftLight = analogRead(LDR_LEFT);
  int rightLight = analogRead(LDR_RIGHT);

  // Calcola la differenza tra i due sensori
  int diff = rightLight - leftLight; // Modulo LDR: AO diminuisce aumentando la luce.

  Serial.print("Sinistra: ");
  Serial.print(leftLight);
  Serial.print(" | Destra: ");
  Serial.print(rightLight);
  Serial.print(" | Differenza: ");
  Serial.print(diff);
  Serial.print(" | Posizione: ");
  Serial.println(currentPosition);

  // Muove il servo in base alla differenza di luce
  if (abs(diff) > THRESHOLD) {  // Se la differenza supera la soglia
    if (diff > 0) {  // Se c'è più luce a sinistra
      currentPosition = constrain(currentPosition - 1, 0, 180);  // Muove verso sinistra
    } else {         // Se c'è più luce a destra
      currentPosition = constrain(currentPosition + 1, 0, 180);  // Muove verso destra
    }
    trackingServo.write(currentPosition);  // Aggiorna la posizione del servo
  }

  delay(50);  // Piccolo ritardo per stabilità
}
