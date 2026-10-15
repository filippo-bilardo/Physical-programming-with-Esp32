/** ****************************************************************************************
 * \mainpage ESP32-T-Display/01-TftTextTest.ino
 *
 * @brief Test delle funzionalita per la scritture testo della libreria TFT_eSPI
 * 
 * https://github.com/Xinyuan-LilyGO/TTGO-T-Display/tree/master/TFT_eSPI
 * https://github.com/Bodmer/User_Manual_TFT_eSPI/blob/master/TFT_eSPI.cpp.All.pdf
 * 
 * @author Filippo Bilardo
 * @version 1.0  24/04/22  Versione iniziale
 */
#include <TFT_eSPI.h>   // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library //size:135x240 pixels

#define BTN_SX_PIN      0
#define BTN_DX_PIN      35
#define BTN_PRESSED     0
#define BTN_RELEASED    1

void waitBtnSxClick() {
  //Se il pulsante non è premuto
  while(digitalRead(BTN_SX_PIN)==BTN_RELEASED) {
    delay(10); //Debounce   
    //aspetto che il pulsante venga premuto
    //Se il pulsante è premuto
    while(digitalRead(BTN_SX_PIN)==BTN_PRESSED) {
      delay(10); //Debounce       
      //aspetto che il pulsante venga rilasciato
      //Se il pulsante è rilasciato -> Click completo 
      if(digitalRead(BTN_SX_PIN)==BTN_RELEASED) {
        delay(100); //Ritardo per il click successivo
        return;
      }
    }
  }
}
 
/** 
 *  fillScreen(uint32_t color)
 *  Clear the screen to defined background colour
 *   
 *  setCursor(int16_t x, int16_t y, uint8_t font)
 *  Set the text cursor x,y position and font
 *  
 *  setTextColor(uint16_t c)
 *  Set the font foreground colour (background is transparent)
 *  
 *  println 
 *  
 *  TFT_BLACK, TFT_NAVY, TFT_DARKGREEN, TFT_DARKCYAN, TFT_MAROON
 *  TFT_PURPLE, TFT_OLIVE, TFT_LIGHTGREY, TFT_DARKGREY, TFT_BLUE
 *  TFT_GREEN, TFT_CYAN, TFT_RED, TFT_MAGENTA, TFT_YELLOW
 *  TFT_WHITE, TFT_ORANGE, TFT_GREENYELLOW, TFT_PINK, TFT_BROWN
 *  TFT_GOLD, TFT_SILVER, TFT_SKYBLUE, TFT_VIOLET
 */
void TftTextTest1(void) {
  Serial.println("#1 - Clear the screen to defined background colour"); 
  tft.fillScreen(TFT_NAVY); delay(300);
  tft.fillScreen(TFT_PURPLE); delay(300);
  tft.fillScreen(TFT_CYAN); delay(300);
  tft.fillScreen(TFT_MAGENTA); delay(300);
  tft.fillScreen(TFT_SKYBLUE); delay(300);
  tft.fillScreen(TFT_VIOLET); delay(300);
  tft.fillScreen(random(0xFFFF)); delay(300);
  tft.fillScreen(random(0xFFFF)); delay(300);
  tft.fillScreen(TFT_BLACK);    //Clear the screen with the color TFT_BLACK

  tft.setCursor(40,20,4);         //Set "cursor" at(x,y) and select font 
  tft.setTextColor(TFT_RED, TFT_BLACK); // Set the font colour to be TFT_RED with a TFT_BLACK background
  tft.println("Red text");
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Green text");
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.println("Blue text");
  tft.setTextColor(TFT_GOLD);
  tft.println("Gold text");
  tft.setTextColor(TFT_OLIVE);
  tft.println("Olive text");
  waitBtnSxClick(); 
}
/** 
 *  setRotation(uint8_t m)
 *  rotate the screen orientation m = 0-3 or 4-7 for BMP drawing
 *  Set rotation to 1,3=horizontally, 0,2=vertically
 */
void TftTextTest2(void) {
  Serial.println("#2 - rotate the screen orientation m = 0-3"); 
  tft.fillScreen(TFT_BLACK);    //Clear the screen with the color TFT_BLACK
  tft.setCursor(0,0,4);         //Set "cursor" at(x,y) and select font 
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setRotation(0);           //Set screen rotation to vertically
  tft.println("setRotation(0)");
  waitBtnSxClick(); 
}
void TftTextTest2a(void) {
  tft.fillScreen(TFT_BLACK);    //Clear the screen with the color TFT_BLACK
  tft.setCursor(0,0,4);         //Set "cursor" at(x,y) and select font 
  tft.setRotation(1);           //Set screen rotation to vertically
  tft.println("setRotation(1)");
  waitBtnSxClick(); 
}
void TftTextTest2b(void) {
  tft.fillScreen(TFT_BLACK);    //Clear the screen with the color TFT_BLACK
  tft.setCursor(0,0,4);         //Set "cursor" at(x,y) and select font 
  tft.setRotation(2);           //Set screen rotation to vertically
  tft.println("setRotation(2)");
  waitBtnSxClick(); 
}
void TftTextTest2c(void) {
  tft.fillScreen(TFT_BLACK);    //Clear the screen with the color TFT_BLACK
  tft.setCursor(0,0,4);         //Set "cursor" at(x,y) and select font 
  tft.setRotation(3);           //Set screen rotation to vertically
  tft.println("setRotation(3)");
  waitBtnSxClick(); 
}
/** 
 *  setTextFont(uint8_t f) 
 *  Set the font for the print stream
 *  
 *  setTextSize(uint8_t s) 
 *  Set the text size multiplier, 1<=s<=7 
 *  
 *  setTextWrap(bool wrapX, bool wrapY)
 *  Define if text should wrap at end of line
 */
void TftTextTest3(void) {
  Serial.println("#3 - setTextFont, setTextSize, setTextWrap"); 
  tft.setRotation(0);         //Set screen rotation to vertically
  tft.fillScreen(TFT_BLACK);  //Clear the screen with the color TFT_WHITE
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the font colour to be TFT_WHITE with a TFT_BLACK background
  tft.setCursor(0,0);         //Set "cursor" at(0,0)
  tft.setTextFont(1);         //Set the font for the print stream
  tft.setTextWrap(false);
  tft.setTextSize(1); tft.println("-123456789012345678901-");
  tft.setTextSize(2); tft.println("-1234567890-");
  tft.setTextSize(3); tft.println("-123456-");
  tft.setTextSize(4); tft.println("-4444-");
  tft.setTextSize(5); tft.println("-555-");
  tft.setTextSize(6); tft.println("-66-");
  tft.setTextSize(7); tft.println("-77-");
  waitBtnSxClick(); 
}
void TftTextTest3a(void) {
  tft.setRotation(0);         //Set screen rotation to vertically
  tft.fillScreen(TFT_BLACK);  //Clear the screen with the color TFT_WHITE
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the font colour to be TFT_WHITE with a TFT_BLACK background
  tft.setCursor(0,0);         //Set "cursor" at(0,0)
  tft.setTextFont(2);         //Set the font for the print stream
  tft.setTextWrap(false);
  tft.setTextSize(1); tft.println("-123456789012345-");
  tft.setTextSize(2); tft.println("-123456-");
  tft.setTextSize(3); tft.println("-1234-");
  tft.setTextSize(4); tft.println("-44-");
  tft.setTextSize(5); tft.println("-5-");
  waitBtnSxClick(); 
}
void TftTextTest3b(void) {
  tft.setRotation(0);         //Set screen rotation to vertically
  tft.fillScreen(TFT_BLACK);  //Clear the screen with the color TFT_WHITE
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the font colour to be TFT_WHITE with a TFT_BLACK background
  tft.setCursor(0,0);         //Set "cursor" at(0,0)
  tft.setTextFont(4);         //Set the font for the print stream
  tft.setTextWrap(false);
  tft.setTextSize(1); tft.println("-12345678-");
  tft.setTextSize(2); tft.println("-1234-");
  tft.setTextSize(3); tft.println("-12-");
  tft.setTextSize(4); tft.println("-4-");
  waitBtnSxClick(); 
}
void TftTextTest3c(void) {
  tft.setRotation(0);         //Set screen rotation to vertically
  tft.fillScreen(TFT_BLACK);  //Clear the screen with the color TFT_WHITE
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the font colour to be TFT_WHITE with a TFT_BLACK background
  tft.setCursor(0,0);         //Set "cursor" at(0,0)
  tft.setTextFont(6);         //Set the font for the print stream
  tft.setTextWrap(false);
  tft.setTextSize(1); tft.println("-1234-");
  tft.setTextSize(2); tft.println("-22");
  tft.setTextSize(3); tft.println("-3-");
  waitBtnSxClick(); 
}
void TftTextTest3d(void) {
  tft.setRotation(0);         //Set screen rotation to vertically
  tft.fillScreen(TFT_BLACK);  //Clear the screen with the background color
  tft.setTextColor(TFT_WHITE);//Set the font foreground colour 
  tft.setCursor(0,0);         //Set "cursor" at(0,0)
  tft.setTextSize(1);         //Set the text size multiplier
  //Set the font for the print stream
  tft.setTextFont(1); tft.println("TextFont11111111111111-");
  tft.setTextWrap(true);
  tft.setTextFont(2); tft.println("TextFont22222222222222-");
  tft.setTextWrap(false);
  tft.setTextFont(4); tft.println("TextFont444");
  tft.setTextFont(6); tft.println("6666 TextFont"); //Solo numeri
  tft.setTextFont(7); tft.println("7777"); //Solo numeri
  tft.setTextFont(8); tft.println("888"); //Solo numeri
  waitBtnSxClick(); 
}
/**
 * setTextDatum(uint8_t d) 
 * Set the text position reference datum
 * MC_DATUM, TL_DATUM
 * #define TL_DATUM 0 // Top left (default)
 * #define TC_DATUM 1 // Top centre
 * #define TR_DATUM 2 // Top right
 * #define ML_DATUM 3 // Middle left
 * #define CL_DATUM 3 // Centre left, same as above
 * #define MC_DATUM 4 // Middle centre
 * #define CC_DATUM 4 // Centre centre, same as above
 * #define MR_DATUM 5 // Middle right
 * #define CR_DATUM 5 // Centre right, same as above
 * #define BL_DATUM 6 // Bottom left
 * #define BC_DATUM 7 // Bottom centre
 * #define BR_DATUM 8 // Bottom right
 * 
 * drawString(const String& string, int32_t poX, int32_t poY) 
 * drawString(const String& string, int32_t poX, int32_t poY, uint8_t font) 
 * drawString(const char *string, int32_t poX, int32_t poY)
 * drawString(const char *string, int32_t poX, int32_t poY, uint8_t font)
 * draw string with padding if it is defined
 * 
 * setTextPadding(uint16_t x_width)
 * Define padding width (aids erasing old text and numbers)
 */
void TftTextTest4(void) {
  Serial.println("#4 - "); 
  tft.setRotation(1);
  tft.setCursor(0, 0, 2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN);
  tft.fillScreen(TFT_BLACK);

  tft.setTextDatum(TL_DATUM);  
  tft.drawString("Button:", tft.width() / 2, tft.height() / 2 - 32);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("[WiFi Scan]", tft.width() / 2, tft.height() / 2 - 16);
  tft.setTextDatum(TR_DATUM);  
  tft.drawString("RightButton:", tft.width() / 2, tft.height() / 2 );
  tft.setTextDatum(CL_DATUM);  
  tft.drawString("[Voltage Monitor]", tft.width() / 2, tft.height() / 2 + 16);
  tft.setTextDatum(CC_DATUM);  
  tft.drawString("RightButtonLongPress:", tft.width() / 2, tft.height() / 2 + 32 );
  tft.setTextDatum(CR_DATUM);  
  tft.drawString("[Deep Sleep]", tft.width() / 2, tft.height() / 2 + 48);
  waitBtnSxClick(); 
}
/**
 * invertDisplay(bool i) 
 * invert the display colours i=0 invert, i=1 normal
 */
void TftTextTest5(void) {
  Serial.println("#5 - invert the display colours"); 
  // Binary inversion of colours
  tft.setRotation(0);
  tft.setCursor(0, 0, 2);
  tft.setTextSize(2);
  tft.fillScreen(TFT_BLACK); 
  
  tft.invertDisplay(0); 
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Invert ON\n");
  tft.println("White text");
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.println("Red text");
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Green text");
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.println("Blue text");
  waitBtnSxClick(); 
}
void TftTextTest5a(void) {
  // Binary inversion of colours
  tft.fillScreen(TFT_BLACK); 
  tft.setCursor(0, 0, 2);
  
  tft.invertDisplay(1);   
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Invert OFF\n");
  tft.println("White text");
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.println("Red text");
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Green text");
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.println("Blue text");
  waitBtnSxClick(); 
}
/** 
 *  setFreeFont(const GFXfont *f)
 *  Sets the GFX free font to use
 */

void setup(void) {
  
  Serial.begin(115200);
  Serial.println("Start...");
  
  tft.init();               //Initialise the TFT screen     
  pinMode(TFT_BL, OUTPUT);  // Set backlight pin to output mode
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on

  pinMode(BTN_SX_PIN, INPUT_PULLUP);
  pinMode(BTN_DX_PIN, INPUT_PULLUP);
}

void loop() {

  TftTextTest1(); 
  TftTextTest2(); TftTextTest2a(); TftTextTest2b(); TftTextTest2c();
  TftTextTest3(); TftTextTest3a(); TftTextTest3b(); TftTextTest3c(); TftTextTest3d();
  TftTextTest4();
  TftTextTest5(); TftTextTest5a();
}
