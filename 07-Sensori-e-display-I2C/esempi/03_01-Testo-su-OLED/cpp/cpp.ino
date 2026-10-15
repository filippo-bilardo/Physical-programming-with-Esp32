#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1, 100000, 100000);
bool ready = false;
int counter = 0;
unsigned long lastUpdate;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22, 100000);
  Wire.setTimeOut(50);
  lastUpdate = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastUpdate >= 1000) {
    lastUpdate = now;
    Wire.beginTransmission(0x3C);
    if (Wire.endTransmission() != 0) ready = false;
    else if (!ready) ready = oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, true, false);
    if (ready) {
      oled.clearDisplay();
      oled.setTextSize(1);
      oled.setTextColor(SSD1306_WHITE);
      oled.setTextWrap(false);
      oled.setCursor(0, 0);  oled.print("ESP32 I2C");
      oled.setCursor(0, 16); oled.print("OLED 128x64");
      oled.setCursor(0, 32); oled.print("Addr 0x3C");
      oled.setCursor(0, 48); oled.print("Conteggio: "); oled.print(counter);
      oled.display();
      Serial.print("Conteggio: "); Serial.println(counter);
      counter = (counter + 1) % 10000;
    } else Serial.println("ERR OLED");
  }
  delay(1);
}
