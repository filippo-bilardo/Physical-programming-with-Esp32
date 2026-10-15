/** ****************************************************************************************
 * \mainpage ESP32-DEVKIT_003-MyOled
 *
 * @brief MyOled Class library
 * 
 * @author Filippo Bilardo
 * @version 1.0  05/01/21  Versione iniziale
 */
#include "MyOled.h"

MyOled oled;

void setup() {
  oled.begin();
  oled.hello();
  oled.demo();
}

void loop() { 
}
