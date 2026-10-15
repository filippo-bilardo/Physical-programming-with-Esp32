//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
#include "MyOled.h"

Adafruit_SSD1306 disp(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//------------------------------------------------------------------------------------------
void MyOled::begin() {
  // initialize and clear display
  disp.begin(SSD1306_SWITCHCAPVCC, OLED_I2C);
  disp.clearDisplay();
  disp.display();
  delay(500);
}

#ifdef MYOLED_DEMO
void MyOled::demo() {
  // Draw a single pixel in white
  disp.drawPixel(10, 10, WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  disp.display();
  delay(2000);
  // disp.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // disp.display(). These examples demonstrate both approaches...

  testdrawline();      // Draw many lines
  testdrawrect();      // Draw rectangles (outlines)
  testfillrect();      // Draw rectangles (filled)
  testdrawcircle();    // Draw circles (outlines)
  testfillcircle();    // Draw circles (filled)
  testdrawroundrect(); // Draw rounded rectangles (outlines)
  testfillroundrect(); // Draw rounded rectangles (filled)
  testdrawtriangle();  // Draw triangles (outlines)
  testfilltriangle();  // Draw triangles (filled)
  testdrawchar();      // Draw characters of the default font
  testdrawstyles();    // Draw 'stylized' characters
  testscrolltext();    // Draw scrolling text
  testdrawbitmap();    // Draw a small bitmap image
  // Invert and restore display, pausing in-between
  disp.invertDisplay(true);
  delay(1000);
  disp.invertDisplay(false);
  delay(1000);

  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
}
void MyOled::testdrawline() {
  int16_t i;

  disp.clearDisplay(); // Clear display buffer

  for(i=0; i<disp.width(); i+=4) {
    disp.drawLine(0, 0, i, disp.height()-1, WHITE);
    disp.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<disp.height(); i+=4) {
    disp.drawLine(0, 0, disp.width()-1, i, WHITE);
    disp.display();
    delay(1);
  }
  delay(250);

  disp.clearDisplay();

  for(i=0; i<disp.width(); i+=4) {
    disp.drawLine(0, disp.height()-1, i, 0, WHITE);
    disp.display();
    delay(1);
  }
  for(i=disp.height()-1; i>=0; i-=4) {
    disp.drawLine(0, disp.height()-1, disp.width()-1, i, WHITE);
    disp.display();
    delay(1);
  }
  delay(250);

  disp.clearDisplay();

  for(i=disp.width()-1; i>=0; i-=4) {
    disp.drawLine(disp.width()-1, disp.height()-1, i, 0, WHITE);
    disp.display();
    delay(1);
  }
  for(i=disp.height()-1; i>=0; i-=4) {
    disp.drawLine(disp.width()-1, disp.height()-1, 0, i, WHITE);
    disp.display();
    delay(1);
  }
  delay(250);

  disp.clearDisplay();

  for(i=0; i<disp.height(); i+=4) {
    disp.drawLine(disp.width()-1, 0, 0, i, WHITE);
    disp.display();
    delay(1);
  }
  for(i=0; i<disp.width(); i+=4) {
    disp.drawLine(disp.width()-1, 0, i, disp.height()-1, WHITE);
    disp.display();
    delay(1);
  }

  delay(2000); // Pause for 2 seconds
}
void MyOled::testdrawrect(void) {
  disp.clearDisplay();

  for(int16_t i=0; i<disp.height()/2; i+=2) {
    disp.drawRect(i, i, disp.width()-2*i, disp.height()-2*i, WHITE);
    disp.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}
void MyOled::testfillrect(void) {
  disp.clearDisplay();

  for(int16_t i=0; i<disp.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/black
    disp.fillRect(i, i, disp.width()-i*2, disp.height()-i*2, INVERSE);
    disp.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}
void MyOled::testdrawcircle(void) {
  disp.clearDisplay();

  for(int16_t i=0; i<max(disp.width(),disp.height())/2; i+=2) {
    disp.drawCircle(disp.width()/2, disp.height()/2, i, WHITE);
    disp.display();
    delay(1);
  }

  delay(2000);
}
void MyOled::testfillcircle(void) {
  disp.clearDisplay();

  for(int16_t i=max(disp.width(),disp.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    disp.fillCircle(disp.width() / 2, disp.height() / 2, i, INVERSE);
    disp.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(2000);
}
void MyOled::testdrawroundrect(void) {
  disp.clearDisplay();

  for(int16_t i=0; i<disp.height()/2-2; i+=2) {
    disp.drawRoundRect(i, i, disp.width()-2*i, disp.height()-2*i,
      disp.height()/4, WHITE);
    disp.display();
    delay(1);
  }

  delay(2000);
}
void MyOled::testfillroundrect(void) {
  disp.clearDisplay();

  for(int16_t i=0; i<disp.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    disp.fillRoundRect(i, i, disp.width()-2*i, disp.height()-2*i,
      disp.height()/4, INVERSE);
    disp.display();
    delay(1);
  }

  delay(2000);
}
void MyOled::testdrawtriangle(void) {
  disp.clearDisplay();

  for(int16_t i=0; i<max(disp.width(),disp.height())/2; i+=5) {
    disp.drawTriangle(
      disp.width()/2  , disp.height()/2-i,
      disp.width()/2-i, disp.height()/2+i,
      disp.width()/2+i, disp.height()/2+i, WHITE);
    disp.display();
    delay(1);
  }

  delay(2000);
}
void MyOled::testfilltriangle(void) {
  disp.clearDisplay();

  for(int16_t i=max(disp.width(),disp.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    disp.fillTriangle(
      disp.width()/2  , disp.height()/2-i,
      disp.width()/2-i, disp.height()/2+i,
      disp.width()/2+i, disp.height()/2+i, INVERSE);
    disp.display();
    delay(1);
  }

  delay(2000);
}
void MyOled::testdrawchar(void) {
  disp.clearDisplay();

  disp.setTextSize(1);      // Normal 1:1 pixel scale
  disp.setTextColor(WHITE); // Draw white text
  disp.setCursor(0, 0);     // Start at top-left corner
  disp.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the disp. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') disp.write(' ');
    else          disp.write(i);
  }

  disp.display();
  delay(2000);
}
void MyOled::testdrawstyles(void) {
  disp.clearDisplay();

  disp.setTextSize(1);             // Normal 1:1 pixel scale
  disp.setTextColor(WHITE);        // Draw white text
  disp.setCursor(0,0);             // Start at top-left corner
  disp.println(F("Hello, world!"));

  disp.setTextColor(BLACK, WHITE); // Draw 'inverse' text
  disp.println(3.141592);

  disp.setTextSize(2);             // Draw 2X-scale text
  disp.setTextColor(WHITE);
  disp.print(F("0x")); disp.println(0xDEADBEEF, HEX);

  disp.display();
  delay(2000);
}
void MyOled::testscrolltext(void) {
  disp.clearDisplay();

  disp.setTextSize(2); // Draw 2X-scale text
  disp.setTextColor(WHITE);
  disp.setCursor(10, 0);
  disp.println(F("scroll"));
  disp.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  disp.startscrollright(0x00, 0x0F);
  delay(2000);
  disp.stopscroll();
  delay(1000);
  disp.startscrollleft(0x00, 0x0F);
  delay(2000);
  disp.stopscroll();
  delay(1000);
  disp.startscrolldiagright(0x00, 0x07);
  delay(2000);
  disp.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  disp.stopscroll();
  delay(1000);
}
void MyOled::testdrawbitmap(void) {
  disp.clearDisplay();

  disp.drawBitmap(
    (disp.width()  - LOGO_WIDTH ) / 2,
    (disp.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  disp.display();
  delay(1000);
}

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void MyOled::testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, disp.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    disp.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      disp.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }

    disp.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= disp.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, disp.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}
#endif

void MyOled::hello() {
  // display horizontal lines up and down
  disp.drawLine(0, 0, 127, 0, WHITE);
  disp.drawLine(0, 63, 127, 63, WHITE);
  
  // display a line of text
  disp.setTextSize(2);
  disp.setTextColor(WHITE);
  disp.setCursor(20,20);
  disp.print("DidaBot     v1.0");
 
  // update display with all of the above graphics
  disp.display();
  delay(3000);
}
void MyOled::lf_println(int linea) {
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setCursor(0,0);
  disp.println("--- LineFollower ---");
  disp.println("");
  disp.setTextSize(3);
  disp.println(linea);
  disp.display();
}
void MyOled::lf_print(char *text) {
  
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setCursor(0,0);
  disp.println("--- LineFollower ---");
  disp.println("");
  disp.setTextSize(2);
  disp.println(text);
  disp.display();
}
void MyOled::println(char *text, int textsize) {
  
  disp.clearDisplay();
  disp.setCursor(0,0);
  disp.setTextSize(textsize);
  disp.println(text);
  disp.display();
}
