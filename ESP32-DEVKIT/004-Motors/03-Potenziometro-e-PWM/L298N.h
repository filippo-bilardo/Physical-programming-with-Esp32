/** ****************************************************************************************
 * @file L298N.h
 * @brief Library for operating with a L298N motor driver work with ESP32 boards
 * @author Filippo Bilardo (http://fb-labs.blogspot.com/, http://fb-projects.blogspot.com/)
 *
 *  this is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \par History:
 * <pre>
 * Date       Version  Descr
 * 02.01.21   1.0.0    Versione iniziale. Ispirazione grazie al codice
 *                     Robojax_L298N_DC_motor.h, Written by Ahmad Shamshiri (Robojax.com)
 *                     RX14, June 7, 2014 - https://github.com/RX14/L298N-lib
 *                     https://github.com/AndreaLombardo/L298N
 * </pre>
 */

#ifndef L298N_H
#define L298N_H
#include <Arduino.h>

#define PWM_CHA 0
#define PWM_CHB 1
#define PWM_RES 12
#define PWM_FREQ 5000

class L298N {
 public:
  enum Status { STOP = 3, BRAKE, FORWARD, REVERSE };
  L298N(int inaPin, int inbPin, int enPin);
  L298N(int inaPin, int inbPin, int enPin, int pwmCh, bool debug);
  bool begin();
  bool isReady() const;
  bool run(int percentage);  // -100..100; zero disabilita il ponte.
  void stop();
  void brake();
  void forward();
  void reverse();
  void setSpeed(int percentage);  // Modulo 0..100, senza minimo nascosto.
  int getSpeed() const;
  void setStatus(int status);
  Status getStatus() const;
  void test();  // Prova bloccante: non usata dagli sketch con pulsante.

 private:
  int _enPin, _inaPin, _inbPin, _pwmCh;
  bool _debug;
  bool _configured = false;
  bool _ready = false;
  int _speed = 0;
  Status _status = STOP;
  static const uint32_t PWM_MAX = (1UL << PWM_RES) - 1;
  bool writeDuty(uint32_t duty);
  bool direction(Status requested);
};
#endif // L298N_H
