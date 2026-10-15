#include <Arduino.h>

unsigned long lastSend;
unsigned long sentAt;
bool waiting = false;

void setup() {
  Serial.begin(115200);  // Diagnostica su UART0, separata dal loopback.
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  lastSend = millis();
}

void loop() {
  const unsigned long now = millis();
  int budget = 32;
  while (budget > 0 && Serial2.available() > 0) {
    const int value = Serial2.read();
    if (value == 'A' && waiting) {
      waiting = false;
      Serial.println("RX: A");
    } else Serial.println("RX inatteso");
    budget--;
  }
  if (waiting && now - sentAt >= 200) {
    waiting = false;
    Serial.println("ERR TIMEOUT");
  }
  if (!waiting && now - lastSend >= 1000) {
    lastSend = now;
    sentAt = now;
    waiting = true;
    Serial2.write(uint8_t('A'));
    Serial.println("TX: A");
  }
  delay(1);
}
