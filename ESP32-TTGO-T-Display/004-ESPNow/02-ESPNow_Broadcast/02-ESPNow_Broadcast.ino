/** ****************************************************************************************
 * \mainpage ESP32-T-Display/02-ESPNow_Broadcast.ino
 *
 * @brief Esempio di trasmissione broadcast
 * ogni scheda può trasmettere e ricevere
 * 
 * https://github.com/filippo-bilardo/ESP32-TTGO-T-Display/
 * 
 * @author Filippo Bilardo
 * @version 1.0  11/05/22  Versione iniziale
 */
#include <TFT_eSPI.h>   // Graphics and font library for ST7735 driver chip
#include "WiFi.h"
#include "MyBtn.h"
#include "MyTft.h"
#include "L1_EspNow.h"
#include "ESPNow_Broadcast.h"

extern TFT_eSPI tft;

void setup(void)
{
  //Inizializzazione porta seriale
  Serial.begin(115200);
  Serial.println("Start...");

  //Inizializzazione display
  tftInit();
  tftTest(); 
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  //Inizializzazione wifi 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  tft.println(WiFi.macAddress());
  WiFi.disconnect(); //Non è necessario rimanere connessi
 
  //Inizializzazione pulsanti
  btnInit();

  //Inizializzazione protocollo fisico EspNow 
  L1_EspNowInit();
  //Inizializzazione della demo
  EspNowBroadcastInit();
}

void loop()
{
  EspNowTxTestTask();
  vTaskDelay(10); //Prevent Task watchdog got triggered
}
