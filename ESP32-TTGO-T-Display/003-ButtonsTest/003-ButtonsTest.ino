/** ****************************************************************************************
 * \mainpage ESP32-T-Display/001-ButtonsTest.ino
 *
 * @brief Test delle funzionalita per la scritture testo della libreria TFT_eSPI
 * 
 * https://github.com/filippo-bilardo/TPSIT_2/blob/main/008/pulsanti.c * 
 * 
 * @author Filippo Bilardo
 * @version 1.0  24/04/22  Versione iniziale
 */
#include <TFT_eSPI.h>   // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "MyBtn.h"

TFT_eSPI tft = TFT_eSPI();  // Invoke library // size:135x240 pixels height.

void btnCheckScreen(void) {
  //Controllo se il testo è arrivato in fondo allo schermo
  if(tft.getCursorY()>tft.height()) {
    //Clear screen
    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 0);
    tft.println("Test buttons\n");  
  }
}
void btnTest(void) {
  
  if(checkPressButtons() == BTN_PRESS_SX) {
    tft.println("BTN_PRESS_SX"); 
  } else if(checkPressButtons() == BTN_PRESS_DX) {
    tft.println("BTN_PRESS_DX"); 
  } else if(checkPressButtons() == BTN_PRESS_BOTH) {
    tft.println("BTN_PRESS_BOTH"); 
  }

  btnCheckScreen();
}
void btnTest1(void) {
  /* Il controllo dei tre eventi è mutuamente esclusivo */
  //if(btnDwIsPressed()) tft.println("btnDwIsPressed"); 
  if(btnDwIsLongPressed()) tft.println("btnDwIsLongPressed"); 
  //if(btnDwIsClicked()) tft.println("btnDwIsClicked"); 

  //if(btnUpIsPressed()) tft.println("btnUpIsPressed"); 
  //if(btnUpIsLongPressed()) tft.println("btnUpIsLongPressed"); 
  if(btnUpIsClicked()) tft.println("btnUpIsClicked"); 
  
  btnCheckScreen();
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Start...");
  
  tft.init();    //Initialise the TFT screen     
  pinMode(TFT_BL, OUTPUT); // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_tft.h

  btnInit();

  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Test buttons\n");  
}

void loop()
{
  btnTest();
}
