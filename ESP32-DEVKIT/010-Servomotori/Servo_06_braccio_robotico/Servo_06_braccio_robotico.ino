#include <Arduino.h>

/**
 * \Servo_06_braccio_robotico
 *
 * Sketch per il controllo di un braccio robotico semplice con Arduino
 * Due servo motori controllano la base e il braccio tramite un joystick.
 *
 *
 * @author Filippo Bilardo
 * @version 1.0  20/03/25 - Versione iniziale
 */
#include <ESP32Servo.h>

const int BASE_SERVO_PIN = 18;    // Pin per il servo della base
const int ARM_SERVO_PIN = 19;    // Pin per il servo del braccio
const int JOYSTICK_X_PIN = 34;   // Pin analogico per l'asse X del joystick
const int JOYSTICK_Y_PIN = 35;   // Pin analogico per l'asse Y del joystick

Servo baseServo;                 // Servo per la rotazione della base
Servo armServo;                  // Servo per il movimento del braccio

int basePosition = 90;           // Posizione iniziale della base
int armPosition = 90;            // Posizione iniziale del braccio

bool ready = false;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(34, ADC_11db);
  analogSetPinAttenuation(35, ADC_11db);

  baseServo.setPeriodHertz(50);
  baseServo.attach(BASE_SERVO_PIN, 1000, 2000);  // Collega il servo della base
  armServo.setPeriodHertz(50);
  armServo.attach(ARM_SERVO_PIN, 1000, 2000);
  ready = baseServo.attached() && armServo.attached();
  if (!ready) { baseServo.detach(); armServo.detach(); Serial.println("ERR SERVO"); return; }    // Collega il servo del braccio

  // Imposta le posizioni iniziali
  baseServo.write(basePosition);
  armServo.write(armPosition);

}

void loop() {
  if (!ready) { delay(10); return; }
  // Legge i valori del joystick
  int joystickX = analogRead(JOYSTICK_X_PIN);
  int joystickY = analogRead(JOYSTICK_Y_PIN);

  // Mappa i valori del joystick per il movimento dei servo
  // Aggiunge una zona morta centrale per evitare movimenti indesiderati
  if (abs(joystickX - 2048) > 200) {  // Se il joystick è spostato sull'asse X
    int xMovement = (joystickX > 2048 ? 1 : -1) * (abs(joystickX - 2048) > 1200 ? 2 : 1);  // Converte in incrementi di movimento
    basePosition = constrain(basePosition + xMovement, 0, 180);  // Aggiorna la posizione
    baseServo.write(basePosition);  // Muove il servo della base
  }

  if (abs(joystickY - 2048) > 200) {  // Se il joystick è spostato sull'asse Y
    int yMovement = (joystickY > 2048 ? 1 : -1) * (abs(joystickY - 2048) > 1200 ? 2 : 1);  // Converte in incrementi di movimento
    armPosition = constrain(armPosition + yMovement, 0, 180);  // Aggiorna la posizione
    armServo.write(armPosition);  // Muove il servo del braccio
  }

  // Visualizza i valori sulla console seriale
  Serial.print("Joystick X: ");
  Serial.print(joystickX);
  Serial.print(" | Base: ");
  Serial.print(basePosition);
  Serial.print(" | Joystick Y: ");
  Serial.print(joystickY);
  Serial.print(" | Braccio: ");
  Serial.println(armPosition);

  delay(15);  // Piccolo ritardo per stabilità
}
