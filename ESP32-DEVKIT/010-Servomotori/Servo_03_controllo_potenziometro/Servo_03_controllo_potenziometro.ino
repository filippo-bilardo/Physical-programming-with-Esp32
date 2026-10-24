#include <Arduino.h>

/**
 * \Servo_03_controllo_potenziometro
 *
 * Sketch per il controllo di un servo motore tramite potenziometro
 * La posizione del servo viene determinata dal valore letto dal potenziometro.
 *
 *
 * @author Filippo Bilardo
 * @version 1.0  20/03/25 - Versione iniziale
 */
#include <ESP32Servo.h>

const int SERVO_PIN = 18;       // Pin a cui è collegato il servo
const int POT_PIN = 34;        // Pin analogico per il potenziometro
Servo myServo;                 // Crea un oggetto servo

int potValue;                  // Valore letto dal potenziometro
int servoPosition;             // Posizione del servo

bool ready = false;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(34, ADC_11db);

  myServo.setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 1000, 2000);
  ready = myServo.attached();
  if (!ready) { myServo.detach(); Serial.println("ERR SERVO"); return; }  // Collega il servo al pin specificato
}

void loop() {
  if (!ready) { delay(10); return; }
  potValue = analogRead(POT_PIN);                // Legge il valore del potenziometro (0-4095)
  servoPosition = map(potValue, 0, 4095, 0, 180); // Converte il valore in gradi (0-180)
  myServo.write(servoPosition);                  // Imposta la posizione del servo

  // Visualizza i valori sulla console seriale
  Serial.print("Potenziometro: ");
  Serial.print(potValue);
  Serial.print(" | Posizione servo: ");
  Serial.println(servoPosition);

  delay(15);  // Piccolo ritardo per stabilità
}
