#include <Arduino.h>

/*
 * @file Ultrasuoni_01_misurazione_base.ino
 * @brief Misurazione base con sensore a ultrasuoni HC-SR04
 *
 * @description
 * Questo sketch è un esempio base per utilizzare il sensore a ultrasuoni HC-SR04 con Arduino.
 * Il sensore misura la distanza da un oggetto riflettente inviando un impulso ultrasonico e misurando il tempo di ritorno dell'eco.
 * Il risultato viene visualizzato in centimetri sul monitor seriale.
 *
 * @author Filippo Bilardo
 * @date 09/03/2026
 * @version 1.0
 */

 // Sketch base per sensore a ultrasuoni HC-SR04
const int TRIG_PIN = 25;  // Pin Trigger del sensore
const int ECHO_PIN = 26; // Pin Echo del sensore

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(115200);
  Serial.println("Sensore a ultrasuoni HC-SR04 attivo");
}

void loop() {
  // Variabili per la durata dell'impulso e la distanza risultante
  long duration, distance;

  // Invia impulso ultrasonico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Misura il tempo di ritorno dell'eco
  duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  // Calcola la distanza (in cm)
  // La velocità del suono è 343 m/s o 34300 cm/s
  // Il tempo misurato è di andata e ritorno, quindi dividiamo per 2
  // Quindi: distanza = (tempo × 34300) / 2 / 1000000 = tempo / 58
  if (duration == 0) { Serial.println("ERR ECO"); delay(500); return; }
  distance = duration / 58;

  // Visualizza la distanza sul monitor seriale
  Serial.print("Distanza: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);  // Attendi mezzo secondo prima della prossima misurazione
}
