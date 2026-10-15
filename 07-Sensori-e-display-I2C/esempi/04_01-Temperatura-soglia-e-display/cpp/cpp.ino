#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bmp180_temperature.h"

BMP180Temperature sensor(Wire);
Adafruit_SSD1306 oled(128, 64, &Wire, -1, 100000, 100000);
bool sensorReady = false;
bool oledReady = false;
bool alarmOn = false;
unsigned long lastUpdate;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22, 100000);
  Wire.setTimeOut(50);
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  analogReadResolution(12);
  analogSetPinAttenuation(34, ADC_11db);
  lastUpdate = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastUpdate >= 1000) {
    lastUpdate = now;
    const int setting = analogRead(34);
    const int threshold = 150 + setting * 200L / 4095;  // Da 15.0 a 35.0 C.
    if (!sensorReady) sensorReady = sensor.begin();
    int temperature = 0;
    const bool valid = sensorReady && sensor.readDeciC(temperature);
    if (!valid) {
      sensorReady = false;
      alarmOn = false;  // Politica didattica: errore separato, non temperatura zero.
      Serial.println("ERR BMP180");
    } else {
      if (!alarmOn && temperature >= threshold + 5) alarmOn = true;
      else if (alarmOn && temperature <= threshold - 5) alarmOn = false;
      Serial.print("T_C="); Serial.print(temperature / 10.0, 1);
      Serial.print(" S_C="); Serial.print(threshold / 10.0, 1);
      Serial.print(" AL="); Serial.println(alarmOn ? 1 : 0);
    }
    digitalWrite(18, alarmOn ? HIGH : LOW);

    Wire.beginTransmission(0x3C);
    if (Wire.endTransmission() != 0) oledReady = false;
    else if (!oledReady) oledReady = oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, true, false);
    if (oledReady) {
      char text[24];
      oled.clearDisplay(); oled.setTextSize(1);
      oled.setTextColor(SSD1306_WHITE); oled.setTextWrap(false);
      oled.setCursor(0, 0);
      if (valid) { snprintf(text, sizeof(text), "T: %.1f C", temperature / 10.0); oled.print(text); }
      else oled.print("T: ERRORE");
      snprintf(text, sizeof(text), "S: %.1f C", threshold / 10.0);
      oled.setCursor(0, 16); oled.print(text);
      oled.setCursor(0, 32); oled.print(alarmOn ? "Allarme: ON" : "Allarme: OFF");
      oled.setCursor(0, 48); oled.print(valid ? "BMP180 + OLED" : "DATO ASSENTE");
      oled.display();
    } else Serial.println("ERR OLED");
  }
  delay(1);
}
