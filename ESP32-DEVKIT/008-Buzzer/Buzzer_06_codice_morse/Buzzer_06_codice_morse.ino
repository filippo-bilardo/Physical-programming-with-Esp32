#include <Arduino.h>

const char* morseDict[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", // A-J
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",  // K-T
  "..-", "...-", ".--", "-..-", "-.--", "--..",                         // U-Z
  "-----", ".----", "..---", "...--", "....-",                          // 0-4
  ".....", "-....", "--...", "---..", "----."};

const int BUZZER_PIN=27;
char line[65]; int length=0; bool overflow=false;
const int DOT=200;
void playCode(const char* code) {
  for (int i=0;code[i];i++) {
    if (i>0) delay(DOT);
    tone(BUZZER_PIN,1000); delay(code[i]=='.'?DOT:DOT*3); noTone(BUZZER_PIN);
  }
}
void playMessage() {
  for (int i=0;i<length;i++) {
    const unsigned char c=line[i];
    if (!((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c==' ')) { Serial.println("ERR MORSE"); return; }
  }
  bool first=true, wordGap=false;
  for (int i=0;i<length;i++) {
    char c=line[i];
    if (c==' ') { wordGap=true; continue; }
    if (c>='a'&&c<='z') c=char(c-'a'+'A');
    if (!first) delay(wordGap?DOT*7:DOT*3);
    const int index=c>='A'&&c<='Z'?c-'A':26+c-'0';
    Serial.print(morseDict[index]); Serial.print(" ");
    playCode(morseDict[index]); first=false; wordGap=false;
  }
  Serial.println("FINE MORSE");
}
void setup() {
  Serial.begin(115200); pinMode(BUZZER_PIN,OUTPUT); digitalWrite(BUZZER_PIN,LOW);
  Serial.println("Invia lettere, numeri e spazi, poi LF; massimo 64 caratteri");
}
void loop() {
  int budget=32;
  while (budget-- >0 && Serial.available()>0) {
    const char c=char(Serial.read());
    if (c=='\n') {
      if (length>0 && line[length-1]=='\r') length--;
      if (overflow) Serial.println("ERR LENGTH"); else if (length>0) playMessage();
      length=0; overflow=false;
    } else if (!overflow) {
      if (length<64) line[length++]=c; else overflow=true;
    }
  }
  delay(1);
}
