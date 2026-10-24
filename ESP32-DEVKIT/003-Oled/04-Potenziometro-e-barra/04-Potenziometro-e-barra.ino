#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int OLED_ADDRESS = 0x3C;
Adafruit_SSD1306 oled(128, 64, &Wire, -1, 100000, 100000);
bool ready = false;

unsigned long lastSample;

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

void updateDisplay() {
  const int raw = analogRead(34);
  const int percent = raw * 100L / 4095;
  const int barWidth = raw * 124L / 4095;
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setCursor(0, 0);  oled.print("Potenziometro");
  oled.setCursor(0, 16); oled.print("ADC: "); oled.print(raw);
  oled.setCursor(0, 28); oled.print("Livello: ");
  oled.print(percent); oled.print("%");
  oled.drawRect(0, 42, 128, 18, SSD1306_WHITE);
  if (barWidth > 0) oled.fillRect(2, 44, barWidth, 14, SSD1306_WHITE);
  oled.display();
  Serial.print("ADC="); Serial.print(raw);
  Serial.print(" PCT="); Serial.println(percent);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(34, ADC_11db);
  ready = startDisplay();
  if (ready) updateDisplay();
  lastSample = millis();
}

void loop() {
  const unsigned long now = millis();
  if (ready && now - lastSample >= 200) {
    lastSample = now;
    updateDisplay();
  }
  delay(1);
}
