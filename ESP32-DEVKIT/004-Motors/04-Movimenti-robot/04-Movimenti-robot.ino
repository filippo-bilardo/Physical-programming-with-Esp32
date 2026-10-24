#include "MyMotors.h"

MyMotors motors(IN1, IN2, ENA, PWM_CHA, IN3, IN4, ENB, PWM_CHB, true);
bool ready = false;

// Comandi logici: verificare il verso fisico delle ruote prima del movimento.
const int left[]  = {60, 0, 30, 0, 60, 0, 50, 0};
const int right[] = {60, 0, 60, 0, 30, 0, -50, 0};
const unsigned long durations[] = {1500, 500, 1000, 500, 1000, 500, 800, 500};
int phase = 0;
bool active = false;
unsigned long phaseStarted;

bool startPhase() {
  Serial.print("FASE="); Serial.print(phase);
  Serial.print(" SX="); Serial.print(left[phase]);
  Serial.print(" DX="); Serial.println(right[phase]);
  return motors.tank(left[phase], right[phase]);
}

void setup() {
  Serial.begin(115200);
  pinMode(ENABLE_BUTTON, INPUT_PULLUP);
  ready = motors.begin();
  Serial.println(ready ? "PRONTO: tieni premuto GPIO23" : "ERR PWM");
}

void loop() {
  const unsigned long now = millis();
  if (ready) {
    if (digitalRead(ENABLE_BUTTON) == HIGH) {
      if (active) { motors.stop(3); Serial.println("STOP"); }
      active = false;
    } else if (!active) {
      active = true;
      phase = 0;
      phaseStarted = now;
      ready = startPhase();
    } else if (now - phaseStarted >= durations[phase]) {
      phase = (phase + 1) % 8;
      phaseStarted = now;
      ready = startPhase();
    }
    if (!motors.isReady()) ready = false;
    if (!ready) { motors.stop(3); Serial.println("ERR PWM"); }
  }
  delay(1);
}
