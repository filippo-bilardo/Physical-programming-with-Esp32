#include <Arduino.h>

/**
 * \Servo_04_movimento_fluido
 *
 * Sketch per il movimento fluido di un servo motore con Arduino
 * Il servo si muove gradualmente da 0° a 180° e viceversa.
 *
 *
 * @author Filippo Bilardo
 * @version 1.0  20/03/25 - Versione iniziale
 */
#include <ESP32Servo.h>

const int SERVO_PIN = 18;  // Pin a cui è collegato il servo
Servo myServo;           // Crea un oggetto servo

bool ready = false;

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 1000, 2000);
  ready = myServo.attached();
  if (!ready) { myServo.detach(); Serial.println("ERR SERVO"); return; }  // Collega il servo al pin specificato
}

void loop() {
  if (!ready) { delay(10); return; }
  // Movimento da 0 a 180 gradi
  for (int pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos);  // Imposta la posizione del servo
    delay(15);           // Attende 15ms per permettere al servo di raggiungere la posizione
  }

  // Movimento da 180 a 0 gradi
  for (int pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos);  // Imposta la posizione del servo
    delay(15);           // Attende 15ms per permettere al servo di raggiungere la posizione
  }
}
