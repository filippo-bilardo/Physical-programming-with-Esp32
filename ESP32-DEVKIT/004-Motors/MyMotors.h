/** ****************************************************************************************
* @file motori.h
* @brief Pilotaggio due motori con L298N
* @author Filippo Bilardo
* @date 22.05.20
* @version 1.0 22.05.20 Versione iniziale
*/
#ifndef MY_MOTORS_H
#define MY_MOTORS_H
//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
#include <Arduino.h>
#include "L298N_2M.h"

//------------------------------------------------------------------------------------------
//=== Constants ============================================================================
//------------------------------------------------------------------------------------------
// motor 1 settings
#define IN3 17
#define IN4 16
#define ENB 4// this pin must be PWM enabled pin if Arduino board is used
// motor 2 settings
#define ENA 19 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 5  //18 motore collegato al contrario
#define IN2 18 //5

//------------------------------------------------------------------------------------------
//=== Global Functions =====================================================================
//------------------------------------------------------------------------------------------
class MyMotors:public L298N_2M
{
  public:

  MyMotors(int in1Pin,int in2Pin,int enAPin, int pwmChA, 
        int in3Pin, int in4Pin,int enBPin, int pwmChB, boolean debug): 
        L298N_2M(in1Pin, in2Pin, enAPin, pwmChA, 
          in3Pin, in4Pin, enBPin, pwmChB, debug){};   
  private:
};

#endif MY_MOTORS_H
