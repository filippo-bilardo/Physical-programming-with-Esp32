/** ****************************************************************************************
 * \mainpage ESP32-T-Display/ES01-L7_L2_L1.ino
 *
 * @brief Test Network Comunication Protocol
 * 
 * @author Filippo Bilardo
 * @version 1.0  11/05/22  Versione iniziale
 */
#include "MyBtn.h"
#include "MyTft.h"
#include "NCP.h"
#include <WiFi.h>

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Start...");

  //Inizializzazione wifi 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  WiFi.disconnect(); //Non è necessario rimanere connessi

  tftInit();
  tftTest();
  btnInit();
  NcpInit();
}

void loop()
{
  vTaskDelay(10);
}
