#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int OLED_ADDRESS = 0x3C;
Adafruit_SSD1306 oled(128, 64, &Wire, -1, 100000, 100000);
bool ready = false;

int x = 6, y = 24;
int dx = 3, dy = 2;
unsigned long lastFrame;

bool startDisplay() {
  if (!Wire.begin(21, 22, 100000)) {
    Serial.println("ERR I2C");
    return false;
  }
  Wire.setTimeOut(50);
  Wire.beginTransmission(OLED_ADDRESS);
  if (Wire.endTransmission() != 0) {
    Serial.println("ERR OLED: nessun ACK a 0x3C");
    return false;
  }
  if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS, true, false)) {
    Serial.println("ERR OLED: inizializzazione fallita");
    return false;
  }
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextWrap(false);
  return true;
}

void drawFrame() {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setCursor(0, 0); oled.print("Rimbalzo OLED");
  oled.drawRect(0, 16, 128, 48, SSD1306_WHITE);
  oled.fillCircle(x, y, 4, SSD1306_WHITE);
  oled.display();
  Serial.print("X="); Serial.print(x);
  Serial.print(" Y="); Serial.println(y);
}

void setup() {
  Serial.begin(115200);
  ready = startDisplay();
  if (ready) drawFrame();
  lastFrame = millis();
}

void loop() {
  const unsigned long now = millis();
  if (ready && now - lastFrame >= 200) {
    lastFrame = now;
    x += dx;
    y += dy;
    // Il raggio e' 4: il centro deve restare dentro questi limiti.
    if (x < 5) { x = 5; dx = -dx; }
    else if (x > 122) { x = 122; dx = -dx; }
    if (y < 21) { y = 21; dy = -dy; }
    else if (y > 58) { y = 58; dy = -dy; }
    drawFrame();
  }
  delay(1);
}
