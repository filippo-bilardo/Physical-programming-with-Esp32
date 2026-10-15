#include <Arduino.h>

void setup() {
  Serial2.begin(115200, SERIAL_8N1, 16, 17);  // RX=16, TX=17.
  Serial2.print("READY UART2\n");
}

void loop() {
  int budget = 32;
  while (budget > 0 && Serial2.available() > 0) {
    const int value = Serial2.read();
    if (value >= 0) Serial2.write(uint8_t(value));
    budget--;
  }
  delay(1);
}
