/** ****************************************************************************************
 * @file L298N_2M.h
 * @brief L298N Library for controlling two motor. Work with ESP32 boards
 * @author Filippo Bilardo
 *
 * TODO: Migliorare il logging, Funzione Steer
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
 * 22.05.20   1.0.0    Versione iniziale - Da RobotOfficial_v4.0.0 e DidaBot_v0.1
 * 02.01.21   1.0.1    Aggiunto il supporto per le schede ESP32. Grazie al codice
 *                     Robojax_L298N_DC_motor.h, Written by Ahmad Shamshiri (Robojax.com)
 *                     RX14, June 7, 2014 - https://github.com/RX14/L298N-lib
 *                     https://github.com/AndreaLombardo/L298N
 *                     https://makecode.mindstorms.com/reference/motors
 * </pre>
 */


#ifndef L298N_2M_H
#define L298N_2M_H
#include "L298N.h"

class L298N_2M {
 public:
  enum TimeUnit { MILLISECONDS = 0, SECONDS = 1 };
  L298N_2M(int in1, int in2, int ena, int channelA,
           int in3, int in4, int enb, int channelB, bool debug);
  bool begin();
  bool isReady() const;
  void stop(int motor = 3);   // 1=A, 2=B, 3=entrambi.
  void brake(int motor = 3);
  bool run(int motor, int speed);
  bool tank(int left, int right);
  bool steer(int turnRatio, int speed);
  // Overload bloccanti: value nella unita' dichiarata; value=0 continua.
  bool run(int motor, int speed, int value, int unit);
  bool tank(int left, int right, int value, int unit);
  bool steer(int turnRatio, int speed, int value, int unit);
  void test(int number);  // Selettori '1'..'4'; prove bloccanti, senza lettura pulsante.
  void demo();
 private:
  L298N _motor1, _motor2;
  static bool durationMs(int value, int unit, uint32_t& milliseconds);
};
#endif // L298N_2M_H
