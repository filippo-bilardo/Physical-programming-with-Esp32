#include <Arduino.h>

/**
 * \Servo_02_rotazione_continua
 *
 * Sketch per il controllo di un servo a rotazione continua con Arduino
 * Il servo ruota in senso orario, si ferma, ruota in senso antiorario e si ferma nuovamente.
 *
 *
 * @author Filippo Bilardo
 * @version 1.0  20/03/25 - Versione iniziale
 */
#include <ESP32Servo.h>

const int SERVO_PIN = 18;  // Pin a cui è collegato il servo
Servo continuousServo;    // Crea un oggetto servo

bool ready = false;

void setup() {
  Serial.begin(115200);
  continuousServo.setPeriodHertz(50);
  continuousServo.attach(SERVO_PIN, 1000, 2000);
  ready = continuousServo.attached();
  if (!ready) { continuousServo.detach(); Serial.println("ERR SERVO"); return; }  // Collega il servo al pin specificato
}

void loop() {
  if (!ready) { delay(10); return; }
  continuousServo.writeMicroseconds(1400);    // Rotazione in senso orario a comando moderato
  delay(2000);                 // Mantieni per 2 secondi

  continuousServo.writeMicroseconds(1500);   // Neutro nominale: da calibrare
  delay(1000);                 // Mantieni fermo per 1 secondo

  continuousServo.writeMicroseconds(1600);  // Rotazione in senso antiorario a comando moderato
  delay(2000);                 // Mantieni per 2 secondi

  continuousServo.writeMicroseconds(1500);   // Neutro nominale: da calibrare
  delay(1000);                 // Mantieni fermo per 1 secondo
}
