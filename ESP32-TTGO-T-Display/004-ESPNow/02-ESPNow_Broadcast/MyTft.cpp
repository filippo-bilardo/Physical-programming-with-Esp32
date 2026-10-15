#include <Arduino.h>
#include <TFT_eSPI.h>   //https://github.com/Bodmer/TFT_eSPI
#include "MyTft.h"

TFT_eSPI tft = TFT_eSPI();  // Invoke library // size:135x240 pixels height.
//extern TFT_eSPI tft;
 
const int TFT_PWM_FREQ = 5000;
const int TFT_PWM_RESOLUTION = 8;
const int TFT_PWM_LED_CHANNEL = 0;
int tftLedBacklight = 80; // Initial TFT backlight intensity on a scale of 0 to 255. Initial value is 80.

/////////////////////////////////////////////////////////////////
void tftInit() {
  tft.init();    //Initialise the TFT screen     

  //Configuring PWM for TFT backlight
  ledcSetup(TFT_PWM_LED_CHANNEL, TFT_PWM_FREQ, TFT_PWM_RESOLUTION);
  ledcAttachPin(TFT_BL, TFT_PWM_LED_CHANNEL);
  //Setting PWM for TFT backlight to default intensity
  ledcWrite(TFT_PWM_LED_CHANNEL, tftLedBacklight);
  //pinMode(TFT_BL, OUTPUT); // Set backlight pin to output mode
  //digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on.

  //Impostazioni di default
  tft.setRotation(0);         //Verticale
  tft.setCursor(0, 0, 2);     //Font 2
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);  //Cancella lo schermo

  pinMode(TFT_BL, OUTPUT); // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on.
}

void tftTest() {
  tft.fillScreen(TFT_NAVY); delay(100);
  tft.fillScreen(TFT_PURPLE); delay(100);
  tft.fillScreen(TFT_CYAN); delay(200);
  tft.fillScreen(TFT_MAGENTA); delay(200);
  tft.fillScreen(TFT_SKYBLUE); delay(200);
  tft.fillScreen(TFT_VIOLET); delay(200);
  tft.fillScreen(random(0xFFFF)); delay(200);
  tft.fillScreen(random(0xFFFF)); delay(200);
  tft.fillScreen(TFT_BLACK);    //Clear the screen with the color TFT_BLACK
}

void tftCheckFullScreen() {
  //Controllo se il testo è arrivato in fondo allo schermo
  if(tft.getCursorY()>tft.height()) {
    //Clear screen
    tft.fillScreen(TFT_BLACK); 
    tft.setCursor(0, 0);
  }
}
