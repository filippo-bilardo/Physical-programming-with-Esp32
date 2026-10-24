/** ****************************************************************************************
* @file motori.h
* @brief Pilotaggio due motori con L298N
* @author Filippo Bilardo
* @date 22.05.20
* @version 1.0 22.05.20 Versione iniziale
*/

#ifndef MY_MOTORS_H
#define MY_MOTORS_H
#include "L298N_2M.h"

// Piedinatura del progetto originale, conservata per i collegamenti esistenti.
#define IN1 5
#define IN2 18
#define ENA 19
#define IN3 17
#define IN4 16
#define ENB 4
#define ENABLE_BUTTON 23  // Pulsante tra GPIO23 e GND, INPUT_PULLUP.

class MyMotors : public L298N_2M {
 public:
  MyMotors(int in1, int in2, int ena, int channelA,
           int in3, int in4, int enb, int channelB, bool debug)
      : L298N_2M(in1, in2, ena, channelA, in3, in4, enb, channelB, debug) {}
};
#endif // MY_MOTORS_H
