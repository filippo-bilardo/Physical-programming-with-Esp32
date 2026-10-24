#include "MyMotors.h"

MyMotors motors(IN1, IN2, ENA, PWM_CHA, IN3, IN4, ENB, PWM_CHB, true);
bool ready = false;

bool active = false;

void setup() {
  Serial.begin(115200);
  pinMode(ENABLE_BUTTON, INPUT_PULLUP);
  ready = motors.begin();
  Serial.println(ready ? "PRONTO: tieni premuto GPIO23" : "ERR PWM");
}

void loop() {
  if (ready) {
    const bool pressed = digitalRead(ENABLE_BUTTON) == LOW;
    if (pressed && !active) {
      ready = motors.run(1, 50);  // Solo ponte A, marcia positiva.
      active = ready;
      if (ready) Serial.println("M1=50 M2=0");
    } else if (!pressed && active) {
      motors.stop(3);
      active = false;
      Serial.println("STOP");
    }
    if (!motors.isReady()) ready = false;
    if (!ready) { motors.stop(3); Serial.println("ERR PWM"); }
  }
  delay(1);
}
