/** ****************************************************************************************
 * \mainpage ESP32-DEVKIT_006-LedOn_DriveStrength
 *
 * @brief  
 * esp_err_t gpio_set_drive_capability(gpio_num_t gpio_num, gpio_drive_cap_t strength)
 * enum gpio_drive_cap_t = 0-3 ->0=5ma, 1=10ma, 2(default)=20ma, 3=40ma
 *  
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
 * 
 * @author Filippo Bilardo
 * @version 1.0  06/05/22  Versione iniziale
 */
#define LED_PIN 21

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
}

void loop() {
  gpio_set_drive_capability((gpio_num_t)LED_PIN, GPIO_DRIVE_CAP_0);
  Serial.println("GPIO_DRIVE_CAP_0");
  digitalWrite(LED_PIN, HIGH);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
  delay(200);

  digitalWrite(LED_PIN, HIGH);
  gpio_set_drive_capability((gpio_num_t)LED_PIN, GPIO_DRIVE_CAP_1);
  Serial.println("GPIO_DRIVE_CAP_1");
  delay(2000);
  digitalWrite(LED_PIN, LOW);
  delay(200);
  digitalWrite(LED_PIN, HIGH);

  digitalWrite(LED_PIN, HIGH);
  gpio_set_drive_capability((gpio_num_t)LED_PIN, GPIO_DRIVE_CAP_2);
  Serial.println("GPIO_DRIVE_CAP_2");
  delay(2000);
  digitalWrite(LED_PIN, LOW);
  delay(200);
  digitalWrite(LED_PIN, HIGH);
}
