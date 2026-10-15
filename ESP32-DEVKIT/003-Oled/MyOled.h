/** ****************************************************************************************
 * @file MyOled.h
 * @brief MyOled Class Library
 * @author Filippo Bilardo (http://fb-labs.blogspot.com/, http://fb-projects.blogspot.com/)
 * 
 *  this is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *    
 * \par History:
 * <pre>
 * Date       Version  Descr
 * 02.01.21   1.0.0    Versione iniziale. Grazie al codice 
 *                     
 * </pre>
 */

#ifndef MYOLED_H
#define MYOLED_H
//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//------------------------------------------------------------------------------------------
//=== Constants ============================================================================
//------------------------------------------------------------------------------------------
// MyOled DEMO
#define MYOLED_DEMO

#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

// MyOled display I2C address
#define OLED_I2C   0x3C
// MyOled display dimension
#define SCREEN_WIDTH 128 // width, in pixels
#define SCREEN_HEIGHT 64 // height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (-1 if sharing Arduino reset pin)

//------------------------------------------------------------------------------------------
//=== Class ================================================================================
//------------------------------------------------------------------------------------------
class MyOled
{
  public:
  
    void begin();
    void hello();
    void lf_println(int linea);
    void lf_print(char *text);
    void println(char *text, int textsize);
    #ifdef MYOLED_DEMO
    void demo();
    #endif
    
  private:

    #ifdef MYOLED_DEMO
    void testdrawline();
    void testdrawrect(void);
    void testfillrect(void);
    void testdrawcircle(void);
    void testfillcircle(void);
    void testdrawroundrect(void);
    void testfillroundrect(void);
    void testdrawtriangle(void);
    void testfilltriangle(void);
    void testdrawchar(void);
    void testdrawstyles(void);
    void testscrolltext(void);
    void testdrawbitmap(void);
    void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h);
    #endif
};
//------------------------------------------------------------------------------------------
#endif MYOLED_H
