// Implementazione della libreria locale; licenza e attribuzioni in L298N_2M.h.
#include "L298N_2M.h"

L298N_2M::L298N_2M(int in1, int in2, int ena, int channelA,
                   int in3, int in4, int enb, int channelB, bool debug)
    : _motor1(in1, in2, ena, channelA, debug),
      _motor2(in3, in4, enb, channelB, debug) {}

bool L298N_2M::begin() {
  const bool first = _motor1.begin();
  const bool second = _motor2.begin();
  if (!first || !second) { stop(3); return false; }
  return true;
}
bool L298N_2M::isReady() const { return _motor1.isReady() && _motor2.isReady(); }
void L298N_2M::stop(int motor) {
  if (motor == 1 || motor == 3 || motor < 1 || motor > 3) _motor1.stop();
  if (motor == 2 || motor == 3 || motor < 1 || motor > 3) _motor2.stop();
}
void L298N_2M::brake(int motor) {
  if (!isReady() || motor < 1 || motor > 3) { stop(3); return; }
  if (motor == 1 || motor == 3) _motor1.brake();
  if (!isReady()) { stop(3); return; }
  if (motor == 2 || motor == 3) _motor2.brake();
  if (!isReady()) stop(3);
}
bool L298N_2M::run(int motor, int speed) {
  if (!isReady() || motor < 1 || motor > 3) { stop(3); return false; }
  if ((motor == 1 || motor == 3) && !_motor1.run(speed)) { stop(3); return false; }
  if ((motor == 2 || motor == 3) && !_motor2.run(speed)) { stop(3); return false; }
  return true;
}
bool L298N_2M::tank(int left, int right) {
  if (!isReady()) { stop(3); return false; }
  if (!_motor1.run(left)) { stop(3); return false; }
  if (!_motor2.run(right)) { stop(3); return false; }
  return true;
}
bool L298N_2M::steer(int turnRatio, int speed) {
  turnRatio = constrain(turnRatio, -100, 100);
  speed = constrain(speed, -100, 100);
  int left = speed, right = speed;
  if (turnRatio < 0) left = speed * (100 + turnRatio) / 100;
  else right = speed * (100 - turnRatio) / 100;
  return tank(left, right);
}
bool L298N_2M::durationMs(int value, int unit, uint32_t& ms) {
  if (value < 0 || (unit != MILLISECONDS && unit != SECONDS)) return false;
  const uint64_t total = uint64_t(value) * (unit == SECONDS ? 1000 : 1);
  if (total > UINT32_MAX) return false;
  ms = uint32_t(total);
  return true;
}
bool L298N_2M::run(int motor, int speed, int value, int unit) {
  uint32_t ms;
  if (!durationMs(value, unit, ms)) { stop(3); return false; }
  if (!run(motor, speed)) return false;
  if (value != 0) { delay(ms); stop(motor); }
  return isReady();
}
bool L298N_2M::tank(int left, int right, int value, int unit) {
  uint32_t ms;
  if (!durationMs(value, unit, ms)) { stop(3); return false; }
  if (!tank(left, right)) return false;
  if (value != 0) { delay(ms); stop(3); }
  return isReady();
}
bool L298N_2M::steer(int ratio, int speed, int value, int unit) {
  uint32_t ms;
  if (!durationMs(value, unit, ms)) { stop(3); return false; }
  if (!steer(ratio, speed)) return false;
  if (value != 0) { delay(ms); stop(3); }
  return isReady();
}
void L298N_2M::test(int number) {
  if (number == '1') {
    run(1, 50, 1, SECONDS); delay(500);
    run(1, -50, 1, SECONDS);
  } else if (number == '2') {
    run(3, 50, 1, SECONDS); delay(500);
    run(3, -50, 1, SECONDS);
  } else if (number == '3') {
    tank(50, 50, 1, SECONDS); delay(500);
    tank(-50, 50, 1, SECONDS);
  } else if (number == '4') {
    steer(-50, 50, 1, SECONDS); delay(500);
    steer(50, 50, 1, SECONDS);
  }
  stop(3);
}
void L298N_2M::demo() { test('2'); }
