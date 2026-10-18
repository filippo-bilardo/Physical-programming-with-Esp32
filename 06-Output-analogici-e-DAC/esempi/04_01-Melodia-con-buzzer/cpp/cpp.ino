#include <Arduino.h>

// Ogni durata comprende il suono (80%) e l'articolazione silenziosa (20%).
const int notes[] = {262, 294, 330, 262, 330, 349, 392, 0};
const int durations[] = {300, 300, 300, 300, 300, 300, 600, 1000};
int noteIndex = 0;
bool ready = false;
bool sounding = false;
unsigned long noteStarted;

void startNote() {
  const int frequency = notes[noteIndex];
  sounding = frequency > 0;
  const uint32_t actual = ledcWriteTone(18, frequency);
  if (sounding && actual == 0) {
    ready = false;
    sounding = false;
    ledcWriteTone(18, 0);
    Serial.println("ERR PWM");
    return;
  }
  Serial.print("NOTE="); Serial.print(frequency);
  Serial.print(" MS="); Serial.println(durations[noteIndex]);
}

void setup() {
  Serial.begin(115200);
  ready = ledcAttach(18, 440, 8);
  if (!ready) Serial.println("ERR PWM");
  else startNote();
  noteStarted = millis();
}

void loop() {
  const unsigned long now = millis();
  if (ready) {
    const unsigned long elapsed = now - noteStarted;
    const unsigned long duration = durations[noteIndex];
    if (elapsed >= duration) {
      noteIndex = (noteIndex + 1) % 8;
      noteStarted = now;
      startNote();
    } else if (sounding && elapsed >= duration * 4 / 5) {
      ledcWriteTone(18, 0);
      sounding = false;
    }
  }
  delay(1);
}
