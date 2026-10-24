#include <Arduino.h>

/**
 * \Servo_07_controllo_seriale
 *
 * Sketch per il controllo di un servo motore tramite comandi seriali
 * L'utente può inviare valori da 0 a 180 tramite il monitor seriale per posizionare il servo.
 *
 *
 * @author Filippo Bilardo
 * @version 1.0  20/03/25 - Versione iniziale
 */

#include <ESP32Servo.h>
Servo myServo;
bool ready = false;
char line[5];
int length = 0;
bool overflow = false;
void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);
  myServo.attach(18, 1000, 2000);
  ready = myServo.attached();
  if (!ready) { Serial.println("ERR SERVO"); return; }
  myServo.write(90);
  Serial.println("Invia un angolo 0..180 seguito da LF");
}
void loop() {
  int budget = 32;
  while (ready && budget-- > 0 && Serial.available() > 0) {
    const char ch = char(Serial.read());
    if (ch == '\n') {
      if (length > 0 && line[length-1] == '\r') length--;
      bool valid = !overflow && length > 0 && length <= 3;
      int angle = 0;
      for (int i=0; i<length && valid; i++) {
        if (line[i] < '0' || line[i] > '9') valid = false;
        else angle = angle*10 + line[i]-'0';
      }
      if (valid && angle <= 180) { myServo.write(angle); Serial.print("ANGOLO="); Serial.println(angle); }
      else Serial.println("ERR ANGOLO");
      length=0; overflow=false;
    } else if (!overflow) {
      if (length < 4) line[length++]=ch;
      else overflow=true;
    }
  }
  delay(1);
}
