#include <Arduino.h>
#include <cstring>
#include "line_receiver.h"

LineReceiver receiver(Serial2);
bool ledOn = false;

void sendLine(const char* text) {
  Serial2.print(text);
  Serial2.write(uint8_t('\n'));
}

void handleCommand(const char* line) {
  char response[48];
  if (strcmp(line, "PING") == 0) sendLine("PONG");
  else if (strcmp(line, "LED 0") == 0 || strcmp(line, "LED 1") == 0) {
    ledOn = line[4] == '1';
    digitalWrite(18, ledOn ? HIGH : LOW);
    sendLine(ledOn ? "OK LED 1" : "OK LED 0");
  } else if (strcmp(line, "ADC?") == 0) {
    const int raw = analogRead(34);
    snprintf(response, sizeof(response), "ADC=%d", raw);
    sendLine(response);
  } else if (strcmp(line, "GET") == 0) {
    const int raw = analogRead(34);
    snprintf(response, sizeof(response), "STATE LED=%d ADC=%d", ledOn ? 1 : 0, raw);
    sendLine(response);
  } else sendLine("ERR COMMAND");
}

void setup() {
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  analogReadResolution(12);
  analogSetPinAttenuation(34, ADC_11db);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  sendLine("READY");
}

void loop() {
  receiver.poll(millis(), handleCommand);
  delay(1);
}
