#include <Arduino.h>
#include "driver/gpio.h"

const int LED_PIN = 18;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Collega una resistenza da 220 ohm in serie al LED (anche su hardware).

  digitalWrite(LED_PIN, LOW);
  gpio_set_drive_capability(GPIO_NUM_18, GPIO_DRIVE_CAP_0);
  Serial.println("Drive 5 mA; I LED circa 3.7 mA stimata con R=220 ohm");
  digitalWrite(LED_PIN, HIGH);
  delay(5000);  // Durata virtuale di questa fase.
  digitalWrite(LED_PIN, LOW);
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  gpio_set_drive_capability(GPIO_NUM_18, GPIO_DRIVE_CAP_1);
  Serial.println("Drive 10 mA; I LED circa 4.6 mA stimata con R=220 ohm");
  digitalWrite(LED_PIN, HIGH);
  delay(5000);  // Durata virtuale di questa fase.
  digitalWrite(LED_PIN, LOW);
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  gpio_set_drive_capability(GPIO_NUM_18, GPIO_DRIVE_CAP_2);
  Serial.println("Drive 20 mA; I LED circa 5.2 mA stimata con R=220 ohm");
  digitalWrite(LED_PIN, HIGH);
  delay(5000);  // Durata virtuale di questa fase.
  digitalWrite(LED_PIN, LOW);
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  gpio_set_drive_capability(GPIO_NUM_18, GPIO_DRIVE_CAP_3);
  Serial.println("Drive 40 mA; I LED circa 5.5 mA stimata con R=220 ohm");
  digitalWrite(LED_PIN, HIGH);
  delay(5000);  // Durata virtuale di questa fase.
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
