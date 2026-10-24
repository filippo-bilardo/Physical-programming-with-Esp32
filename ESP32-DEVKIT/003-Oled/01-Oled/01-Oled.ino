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
  Serial.begin(115200);
  if (!oled.begin()) {
    Serial.println("ERR OLED: controlla alimentazione e indirizzo 0x3C");
    return;
  }
  oled.hello();
#ifdef MYOLED_DEMO
  oled.demo();
#endif
}

void loop() {
  delay(1);
}
