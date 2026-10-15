#include <Arduino.h>
#include <Wire.h>

unsigned long lastScan;

void scanBus() {
  int found = 0;
  for (int address = 8; address <= 119; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      found++;
    }
  }
  if (found == 0) Serial.println("Nessun dispositivo");
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22, 100000);
  Wire.setTimeOut(50);
  scanBus();
  lastScan = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastScan >= 3000) {
    lastScan = now;
    scanBus();
  }
  delay(1);
}
