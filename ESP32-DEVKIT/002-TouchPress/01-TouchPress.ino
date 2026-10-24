/** ****************************************************************************************
 * \mainpage ESP32-DEVKIT_002-TouchPress
 *
 * @brief TouchPress
 * 
 * https://circuits4you.com/2018/12/31/esp32-capacitive-touch-pad-example/
 * https://randomnerdtutorials.com/esp32-touch-pins-arduino-ide/
 * 
 * @author Filippo Bilardo
 * @version 1.0  05/01/21  Versione iniziale
 */

#define LED_PIN 2 //ON Board LED GPIO 2
//T4 //#define TOUCH4_PIN 13 //GPIO 13
//T5 //#define TOUCH5_PIN 12 //GPIO 12
#define debug(fmt, ...) Serial.printf("%s: " fmt "\r\n", __func__, ##__VA_ARGS__)
#define TOUCH_THRESHOLD 20 //Livello minimo per distinguere il touch

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  test3();
}

/**
 * @brief Test1 - stato dei pin touch sul monitor seriale
 * @date 05/01/21
 */
void test1() {
  byte t4 = touchRead(T4);
  byte t5 = touchRead(T5);

  debug("TOUCH4_PIN=%d, TOUCH5_PIN=%d", t4, t5);
  delay(100);
}

/**
 * @brief Test2 - stato dei pin touch sul plotter seriale
 * @date 05/01/21
 */
void test2() {
  byte t4 = touchRead(T4);
  Serial.println(t4);
}

/**
 * @brief Test3 - accensione e spegnimento del led
 * @date 05/01/21
 */
void test3() {
  byte t4 = touchRead(T4);
  byte t5 = touchRead(T5);

  //debug("TOUCH4_PIN=%d, TOUCH5_PIN=%d", t4, t5);
  Serial.println(t4); //Visualizzare su Plotter seriale
  
  if(t4 < TOUCH_THRESHOLD && t4) { // turn LED on
    digitalWrite(LED_PIN, HIGH);
    //Serial.println(" - LED on");
  }
  if(t5 < TOUCH_THRESHOLD && t5) { // turn LED off
    digitalWrite(LED_PIN, LOW);
    //Serial.println(" - LED off");
  }
}
