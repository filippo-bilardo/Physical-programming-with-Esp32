/** ****************************************************************************************
 * \mainpage ESP32-DEVKIT_001-LedBlink
 *
 * @brief Ledblink
 * 
 * https://circuits4you.com/2018/02/02/esp32-led-blink-example/
 * 
 * @author Filippo Bilardo
 * @version 1.0  05/01/21  Versione iniziale
 */
#define LED_PIN 2 //ON Board LED GPIO 2

void setup() {
  // Set pin mode
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  delay(500);
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
}
