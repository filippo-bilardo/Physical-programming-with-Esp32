// @author Filippo Bilardo
#include <Arduino.h>

const int BUZZER_PIN=27;
// Note MIDI (frequenze in Hz)
const int notes[] = {
  262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
  523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988
};

// Nomi delle note
const char* noteNames[] = {
  "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
  "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5"
};


char line[4]; int length=0; bool overflow=false;
void setup() {
  Serial.begin(115200); pinMode(BUZZER_PIN,OUTPUT); digitalWrite(BUZZER_PIN,LOW);
  Serial.println("Seleziona una nota 1..24 e invia LF; non e una porta MIDI");
}
void loop() {
  int budget=32;
  while (budget-- >0 && Serial.available()>0) {
    const char c=char(Serial.read());
    if (c=='\n') {
      if (length>0&&line[length-1]=='\r') length--;
      bool valid=!overflow&&length>0&&length<=2; int number=0;
      for (int i=0;i<length&&valid;i++) {
        if (line[i]<'0'||line[i]>'9') valid=false; else number=number*10+line[i]-'0';
      }
      if (valid&&number>=1&&number<=24) {
        Serial.print(noteNames[number-1]); Serial.print(" Hz="); Serial.println(notes[number-1]);
        tone(BUZZER_PIN,notes[number-1]); delay(500); noTone(BUZZER_PIN);
      } else Serial.println("ERR NOTA");
      length=0; overflow=false;
    } else if (!overflow) {
      if (length<3) line[length++]=c; else overflow=true;
    }
  }
  delay(1);
}
