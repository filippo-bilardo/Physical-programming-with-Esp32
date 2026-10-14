#include <Arduino.h>
#include "driver/gpio.h"  // API ESP-IDF inclusa nel core Arduino-ESP32.
#include "esp_err.h"

const int LED_PIN = 18;
const gpio_num_t LED_GPIO = GPIO_NUM_18;
const gpio_drive_cap_t DRIVE_LEVELS[] = {
  GPIO_DRIVE_CAP_0, GPIO_DRIVE_CAP_1, GPIO_DRIVE_CAP_2, GPIO_DRIVE_CAP_3
};
const char* const LABELS[] = {"DRIVE_0", "DRIVE_1", "DRIVE_2", "DRIVE_3"};
const int LEVEL_COUNT = 4;
const unsigned long ON_MS = 5000;
const unsigned long OFF_MS = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  for (int i = 0; i < LEVEL_COUNT; i++) {
    digitalWrite(LED_PIN, LOW);  // Cambia configurazione a LED spento.
    ESP_ERROR_CHECK(gpio_set_drive_capability(LED_GPIO, DRIVE_LEVELS[i]));
    Serial.println(LABELS[i]);  // Impostazione richiesta, non corrente misurata.
    digitalWrite(LED_PIN, HIGH);
    delay(ON_MS);               // Tempo per leggere il multimetro.
    digitalWrite(LED_PIN, LOW);
    delay(OFF_MS);
  }
}
