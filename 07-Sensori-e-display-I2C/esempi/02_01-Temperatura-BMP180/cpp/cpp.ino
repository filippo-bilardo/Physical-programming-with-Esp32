#include <Arduino.h>
#include <Wire.h>
#include "bmp180_temperature.h"

BMP180Temperature sensor(Wire);
bool ready = false;
unsigned long lastSample;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22, 100000);
  Wire.setTimeOut(50);
  lastSample = millis();
}

void loop() {
  const unsigned long now = millis();
  if (now - lastSample >= 1000) {
    lastSample = now;
    if (!ready) ready = sensor.begin();
    int temperature;
    if (ready && sensor.readDeciC(temperature)) {
      Serial.print("T_C=");
      Serial.println(temperature / 10.0, 1);
    } else {
      ready = false;  // Il prossimo aggiornamento ritenta l'inizializzazione.
      Serial.println("ERR BMP180");
    }
  }
  delay(1);
}
