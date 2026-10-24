#include <Arduino.h>

/*
 * @file Ultrasuoni_02_media_mobile
 * @brief Misurazione con media mobile per ridurre il rumore
 *
 * @description
 * Questo sketch è un esempio avanzato per utilizzare il sensore a ultrasuoni HC-SR04 con Arduino,
 * implementando una media mobile per ridurre il rumore nelle misurazioni.
 * La media mobile aiuta a stabilizzare le letture della distanza, specialmente in ambienti con
 * molte interferenze o quando il sensore è soggetto a vibrazioni.
 * Il risultato viene visualizzato in centimetri sul monitor seriale, mostrando sia la lettura
 * attuale che la media delle ultime letture.
 *
 * @author Filippo Bilardo
 * @date 09/03/2026
 * @version 1.0
 */

 // Misurazione con media mobile per ridurre il rumore
const int TRIG_PIN = 25;
const int ECHO_PIN = 26;

// Parametri per la media mobile
const int NUM_READINGS = 5;  // Numero di letture da mediare
int readings[NUM_READINGS];  // Array per memorizzare le letture
int samples = 0;
int readIndex = 0;           // Indice della lettura corrente
long total = 0;              // Totale corrente

int measureDistance();

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(115200);
  Serial.println("Sensore a ultrasuoni con media mobile attivo");

  // Inizializza l'array delle letture a 0
  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = 0;
  }
}

void loop() {
  const int measured = measureDistance();
  if (measured < 0) {
    // Non lasciare una vecchia media come misura attuale dopo un guasto.
    total=0; samples=0; readIndex=0;
    for (int i=0;i<NUM_READINGS;i++) readings[i]=0;
    Serial.println("ERR ECO"); delay(100); return;
  }
  total -= readings[readIndex];
  readings[readIndex] = measured;
  total += measured;
  if (samples < NUM_READINGS) samples++;

  // Avanza all'indice successivo
  readIndex = (readIndex + 1) % NUM_READINGS;

  // Calcola la media
  int averageDistance = total / samples;

  // Visualizza sia la lettura corrente che la media
  Serial.print("Distanza attuale: ");
  Serial.print(readings[(readIndex - 1 + NUM_READINGS) % NUM_READINGS]);
  Serial.print(" cm | Media: ");
  Serial.print(averageDistance);
  Serial.println(" cm");

  delay(100);  // Breve ritardo tra le misurazioni
}

// Funzione per misurare la distanza
int measureDistance() {
  long duration;

  // Invia impulso ultrasonico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Misura il tempo di ritorno dell'eco
  duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  // Calcola e restituisci la distanza in cm
  return duration == 0 ? -1 : int(duration / 58);
}
