/** ****************************************************************************************
 * \mainpage ESP32-T-Display/01-ESPNow_GetMacAddress.ino
 *
 * @brief Recupero dell'indirizzo macaddress della scheda ESP32-T-Display
 * 
 * https://github.com/filippo-bilardo/ESP32-TTGO-T-Display
 * https://randomnerdtutorials.com/get-change-esp32-esp8266-mac-address-arduino/
 * 
 * @author Filippo Bilardo
 * @version 1.0  09/05/22  Versione iniziale
 */
#include <TFT_eSPI.h>   // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <WiFi.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library // size:135x240 pixels height.

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Start...");
  
  tft.init();    //Initialise the TFT screen     
  pinMode(TFT_BL, OUTPUT); // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on.

  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("MAC ADDRESS:");  
  tft.println(WiFi.macAddress());  
}

void loop() {;}
