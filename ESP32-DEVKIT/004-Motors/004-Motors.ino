/** 
 * L298N_2M driver motor library test
 * by Filippo Bilardo
 * v1.0 - 02/01/21
 */
#include "MyMotors.h"

MyMotors motors(IN1, IN2, ENA, PWM_CHA, IN3, IN4, ENB, PWM_CHB, true);

void setup() {
  Serial.begin(115200); 
  
  motors.begin();
  //motors.demo();
  motors.test('2');
}

void loop() {
}
