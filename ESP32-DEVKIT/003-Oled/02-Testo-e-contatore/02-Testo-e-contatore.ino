#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int OLED_ADDRESS = 0x3C;
Adafruit_SSD1306 oled(128, 64, &Wire, -1, 100000, 100000);
bool ready = false;

int counter = 0;
unsigned long lastUpdate;

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

void drawCounter() {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setCursor(0, 0);  oled.print("ESP32 OLED");
  oled.setCursor(0, 16); oled.print("Contatore:");
  oled.setTextSize(2);
  oled.setCursor(0, 32); oled.print(counter);
  oled.setTextSize(1);
  oled.setCursor(0, 56); oled.print("I2C 0x3C");
  oled.display();  // Trasferisce il fotogramma dopo averlo completato.
  Serial.print("CONT="); Serial.println(counter);
}

void setup() {
  Serial.begin(115200);
  ready = startDisplay();
  if (ready) drawCounter();
  lastUpdate = millis();
}

void loop() {
  const unsigned long now = millis();
  if (ready && now - lastUpdate >= 1000) {
    lastUpdate = now;
    counter = (counter + 1) % 10000;
    drawCounter();
  }
  delay(1);
}
