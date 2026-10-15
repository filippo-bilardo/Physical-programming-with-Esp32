/** ****************************************************************************************
 * \mainpage ESP32-T-Display/002-TftGraphicsTest.ino
 *
 * @brief Test delle funzionalita per la scritture testo della libreria TFT_eSPI
 * 
 * https://github.com/Xinyuan-LilyGO/TTGO-T-Display/tree/master/TFT_eSPI
 * https://github.com/Xinyuan-LilyGO/TTGO-T-Display/blob/master/TFT_eSPI/examples/160%20x%20128/UTFT_demo_fast/UTFT_demo_fast.ino
 * https://github.com/Bodmer/User_Manual_TFT_eSPI/blob/master/TFT_eSPI.cpp.All.pdf 
 * Adapted from the Adafruit graphicstest sketch.
 * 
 * @author Filippo Bilardo
 * @version 1.0  26/04/22  Versione iniziale
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
 *  Draw a circle outline 
 *  drawCircle(int32_t x0, int32_t y0, int32_t r, uint32_t color)
 *  draw a filled circle
 *  fillCircle(int32_t x0, int32_t y0, int32_t r, uint32_t color)
 *  Display size:135x240
 */
void TftGraphicsTest1(void) {
  Serial.println("#1 - Draw a circle outline"); 
  tft.setRotation(0);         //Set screen rotation to vertically
  tft.fillScreen(TFT_BLACK);  //Clear the screen with the color TFT_WHITE
  tft.drawCircle(30, 120, 14, TFT_WHITE);
  tft.fillCircle(60, 120, 14, TFT_BLUE);
  tft.fillCircle(90, 120, 14, TFT_RED);
  tft.fillCircle(120,120, 14, TFT_GREEN);
  waitBtnSxClick(); 

  Serial.println("#1a - Draw a filled circle - horrizontally"); 
  tft.setRotation(1);           //Set screen rotation to 
  tft.fillScreen(TFT_DARKGREEN);//Clear the screen
  tft.drawCircle(50,  67, 23, TFT_WHITE);
  tft.fillCircle(100, 67, 23, TFT_BLUE);
  tft.fillCircle(150, 67, 23, TFT_RED);
  tft.fillCircle(200, 67, 23, TFT_GREEN);
  waitBtnSxClick(); 
}
/**
 * drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color)
 * Draw a ellipse outline
 * fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) 
 * Draw a filled ellipse
 */
void TftGraphicsTest2(void) {
  Serial.println("#2 - Draw random filled ellipse and outline elipsesc"); 
  tft.setRotation(1);         //Set screen rotation to 
  tft.fillScreen(TFT_BLACK);  //Clear the screen
  // Draw some random filled elipses
  for (int i = 0; i < 10; i++)
  {
    int rx = random(40);
    int ry = random(40);
    int x = rx + random(tft.width() - rx - rx);
    int y = ry + random(tft.height() - ry - ry);
    tft.fillEllipse(x, y, rx, ry, random(0xFFFF));
  }
  waitBtnSxClick(); 

  // Draw some random outline elipses
  tft.fillScreen(TFT_BLACK);  //Clear the screen
  for (int i = 0; i < 10; i++)
  {
    int rx = random(40);
    int ry = random(40);
    int x = rx + random(tft.width() - rx - rx);
    int y = ry + random(tft.height() - ry - ry);
    tft.drawEllipse(x, y, rx, ry, random(0xFFFF));
  }
  waitBtnSxClick(); 
}
/**
 * drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) 
 * Draw a rectangle outline
 * drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, uint32_t color)
 * Draw a rounded corner rectangle outline
 * fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, uint32_t color) 
 * Draw a rounded corner filled rectangle
 * fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) 
 * draw a filled rectangle
 */
void TftGraphicsTest3(void) {
  Serial.println("#3 - drawRect"); 

  uint16_t color=TFT_ORANGE, color1=TFT_PINK, color2=TFT_DARKCYAN;

  tft.fillScreen(TFT_BLACK);
  for (int16_t x=0; x < tft.width(); x+=20) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
  waitBtnSxClick(); 

  tft.fillScreen(TFT_BLACK);
  for (int16_t x=tft.width()-1; x > 20; x-=20) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
  waitBtnSxClick(); 
}
/**
 * drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color) 
 * Draw a triangle outline using 3 arbitrary points
 * fillTriangle ( int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
 * Draw a filled triangle using 3 arbitrary points
 */
void TftGraphicsTest4(void) {
  Serial.println("#4 - drawTriangle"); 
  tft.fillScreen(TFT_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t+=1) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
  waitBtnSxClick(); 
}
/**
 * drawPixel(int32_t x, int32_t y, uint32_t color) 
 * push a single pixel at an arbitrary position
 */
void TftGraphicsTest5(void) {
  Serial.println("#5 - drawPixel"); 
  
  tft.fillScreen(TFT_BLACK);
  for (int16_t x=10; x <= tft.width()-10; x+=5) {
    for (int16_t y=10; y <= tft.height()-10; y+=5) {
      tft.drawPixel(x, y, TFT_GREEN);
    }
  }
  waitBtnSxClick(); 

  // Draw Axis
  tft.fillScreen(TFT_BLACK);
  for (int16_t x=0; x <= tft.width(); x++) {
    tft.drawPixel(x, tft.height()/2, TFT_GREEN);
  }
  for (int16_t y=0; y <= tft.height(); y++) {
    tft.drawPixel(tft.width()/2, y, TFT_GREEN);
  }
  waitBtnSxClick(); 
  // Draw sin-, cos- and tan- lines
  tft.setTextColor(TFT_CYAN);
  tft.drawString("Sin", 5, 15, 2);
  for (int16_t i=1; i < tft.width()-2; i++) {
    tft.drawPixel(i, tft.height()/2-1 + (sin(((i*2.26)*3.14)/180)*48), TFT_CYAN);
  }
  waitBtnSxClick(); 
  tft.setTextColor(TFT_RED);
  tft.drawString("Cos", 5, 30, 2);
  for (int16_t i=1; i < tft.width()-2; i++) {
    tft.drawPixel(i, tft.height()/2-1 + (cos(((i*2.26)*3.14)/180)*48), TFT_RED);
  }
  waitBtnSxClick(); 
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("Tan", 5, 45, 2);
  for (int16_t i=1; i < tft.width()-2; i++) {
    tft.drawPixel(i, tft.height()/2-1 + (tan(((i*2.26)*3.14)/180)), TFT_YELLOW);
  }
  waitBtnSxClick(); 
}
/**
 * drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color) 
 * draw a line between 2 arbitrary points
 * drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color) 
 * draw a vertical line
 * drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color) 
 * draw a horizontal line
 */
void TftGraphicsTest6(void) {
  
  Serial.println("#6 - drawLine"); 
  
  uint16_t color=TFT_ORANGE, color1=TFT_PINK, color2=TFT_DARKCYAN;

  tft.fillScreen(TFT_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
  }  
  waitBtnSxClick(); 

  tft.fillScreen(TFT_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  waitBtnSxClick(); 

  tft.fillScreen(TFT_BLACK);
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
  waitBtnSxClick(); 
}

void setup(void) {
  
  Serial.begin(115200);
  Serial.println("Start...");
  
  tft.init();               //Initialise the TFT screen     
  pinMode(TFT_BL, OUTPUT);  // Set backlight pin to output mode
  //digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on

  pinMode(BTN_SX_PIN, INPUT_PULLUP);
  pinMode(BTN_DX_PIN, INPUT_PULLUP);
}

void loop() {
  
  TftGraphicsTest1(); 
  TftGraphicsTest2(); 
  TftGraphicsTest3(); 
  TftGraphicsTest4();
  TftGraphicsTest5();
  TftGraphicsTest6();
}
