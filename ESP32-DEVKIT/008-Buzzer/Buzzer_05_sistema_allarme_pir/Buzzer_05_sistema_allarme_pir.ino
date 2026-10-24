#include <Arduino.h>

/**
 * \Buzzer_05_sistema_allarme_pir
 *
 * Sistema di allarme con sensore PIR
 * Questo sketch attiva un allarme quando viene rilevato del movimento da un sensore PIR.
 * L'allarme è composto da un buzzer che suona per un certo periodo di tempo e da un LED che lampeggia.
 * Il sensore PIR è collegato al GPIO 23, il buzzer al GPIO 27 e il LED al GPIO 18.
 *
 *
 * @author Filippo Bilardo
 * @version 1.0  20/03/25 - Versione iniziale
 */


const int BUZZER_PIN=27, PIR_PIN=23, LED_PIN=18;
bool alarmActive=false;
unsigned long alarmStarted=0, lastStep=0;
int frequency=800, direction=10;
void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN,INPUT); pinMode(LED_PIN,OUTPUT); digitalWrite(LED_PIN,LOW);
  pinMode(BUZZER_PIN,OUTPUT); digitalWrite(BUZZER_PIN,LOW);
  Serial.println("Stabilizzazione PIR: 60 s"); delay(60000);
}
void loop() {
  const unsigned long now=millis();
  if (!alarmActive && digitalRead(PIR_PIN)==HIGH) {
    alarmActive=true; alarmStarted=lastStep=now; frequency=800; direction=10;
    tone(BUZZER_PIN,frequency); digitalWrite(LED_PIN,HIGH);
    Serial.println("ALLARME");
  }
  if (alarmActive && now-alarmStarted>=3000) {
    alarmActive=false; noTone(BUZZER_PIN); digitalWrite(LED_PIN,LOW);
  } else if (alarmActive && now-lastStep>=5) {
    lastStep=now; frequency+=direction;
    if (frequency>=2000 || frequency<=800) {
      direction=-direction; digitalWrite(LED_PIN,direction>0?HIGH:LOW);
    }
    tone(BUZZER_PIN,frequency);
  }
  delay(1);
}
