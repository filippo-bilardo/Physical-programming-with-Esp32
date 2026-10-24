// Implementazione della libreria locale; licenza e attribuzioni in L298N.h.
#include "L298N.h"

L298N::L298N(int inaPin, int inbPin, int enPin)
    : L298N(inaPin, inbPin, enPin, 0, false) {}

L298N::L298N(int inaPin, int inbPin, int enPin, int pwmCh, bool debug)
    : _enPin(enPin), _inaPin(inaPin), _inbPin(inbPin), _pwmCh(pwmCh), _debug(debug) {}

bool L298N::begin() {
  // Prima gli enable a zero, poi ingressi e periferica PWM.
  pinMode(_enPin, OUTPUT);
  digitalWrite(_enPin, LOW);
  pinMode(_inaPin, OUTPUT); digitalWrite(_inaPin, LOW);
  pinMode(_inbPin, OUTPUT); digitalWrite(_inbPin, LOW);
  _configured = true;
  _speed = 0;
  _status = STOP;
  _ready = ledcAttachChannel(_enPin, PWM_FREQ, PWM_RES, _pwmCh);
  if (!_ready) return false;
  return writeDuty(0);
}

bool L298N::writeDuty(uint32_t duty) {
  if (!_ready) return false;
  if (ledcWrite(_enPin, duty)) return true;
  // Errore rilevato: abbandona il PWM e porta EN esplicitamente basso.
  ledcDetach(_enPin);
  pinMode(_enPin, OUTPUT);
  digitalWrite(_enPin, LOW);
  digitalWrite(_inaPin, LOW);
  digitalWrite(_inbPin, LOW);
  _ready = false;
  _speed = 0;
  _status = STOP;
  if (_debug) Serial.println("ERR PWM: canale disabilitato");
  return false;
}

bool L298N::isReady() const { return _ready; }

void L298N::stop() {
  _speed = 0;
  if (_configured) {
    if (_ready) writeDuty(0);
    else digitalWrite(_enPin, LOW);
    digitalWrite(_inaPin, LOW);
    digitalWrite(_inbPin, LOW);
  }
  _status = STOP;
}

void L298N::brake() {
  if (!_ready || !writeDuty(0)) return;
  digitalWrite(_inaPin, LOW);
  digitalWrite(_inbPin, LOW);
  _speed = 0;
  _status = BRAKE;
  writeDuty(PWM_MAX);  // EN alto, ingressi uguali: frenatura elettrica.
}

bool L298N::direction(Status requested) {
  if (!_ready) return false;
  if (_status != requested) {
    const bool reversing = (_status == FORWARD && requested == REVERSE) ||
                           (_status == REVERSE && requested == FORWARD);
    if (!writeDuty(0)) return false;
    digitalWrite(_inaPin, LOW);
    digitalWrite(_inbPin, LOW);
    if (reversing) delay(20);  // Pausa elettrica, non misura l'arresto meccanico.
    digitalWrite(_inaPin, requested == FORWARD ? HIGH : LOW);
    digitalWrite(_inbPin, requested == REVERSE ? HIGH : LOW);
    _status = requested;
  }
  return writeDuty(uint32_t(_speed) * PWM_MAX / 100);
}

bool L298N::run(int percentage) {
  if (!_ready) return false;
  percentage = constrain(percentage, -100, 100);
  if (percentage == 0) { stop(); return _ready; }
  _speed = percentage < 0 ? -percentage : percentage;
  return direction(percentage > 0 ? FORWARD : REVERSE);
}

void L298N::setSpeed(int percentage) {
  _speed = constrain(percentage, 0, 100);
  if (_ready && (_status == FORWARD || _status == REVERSE)) {
    writeDuty(uint32_t(_speed) * PWM_MAX / 100);
  }
}
int L298N::getSpeed() const { return _speed; }
L298N::Status L298N::getStatus() const { return _status; }
void L298N::forward() { direction(FORWARD); }
void L298N::reverse() { direction(REVERSE); }
void L298N::setStatus(int status) {
  switch (status) {
    case FORWARD: forward(); break;
    case REVERSE: reverse(); break;
    case BRAKE: case 7: brake(); break;
    default: stop(); break;
  }
}
void L298N::test() {
  if (!run(50)) return;
  delay(1000); stop(); delay(500);
  if (!run(-50)) return;
  delay(1000); stop();
}
