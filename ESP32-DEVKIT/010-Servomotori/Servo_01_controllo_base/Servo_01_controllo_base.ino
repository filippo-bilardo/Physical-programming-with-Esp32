#include <Arduino.h>

/**
 * \Servo_01_controllo_base
 *
 * Sketch base per il controllo di un servo motore con Arduino
 * Il servo viene posizionato a 0°, 90° e 180° in sequenza.
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
  myServo.write(0);    // Muove il servo a 0 gradi
  delay(1000);         // Attende 1 secondo
  myServo.write(90);   // Muove il servo a 90 gradi
  delay(1000);         // Attende 1 secondo
  myServo.write(180);  // Muove il servo a 180 gradi
  delay(1000);         // Attende 1 secondo
}
