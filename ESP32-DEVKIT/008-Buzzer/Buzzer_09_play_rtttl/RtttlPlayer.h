#pragma once
#include <Arduino.h>
#include <math.h>
#include <string.h>

// Lettore didattico: d=1..64 (potenze di due), o=3..7, b=25..900.
class Buzzer {
  int pin;
  const char* position = nullptr;
  int defaultDuration = 4, defaultOctave = 5, bpm = 120;
  bool playing = false, sounding = false, error = false;
  unsigned long started = 0, duration = 0;
  static void spaces(const char*& p) { while (*p==' ' || *p=='\t') p++; }
  static bool number(const char*& p, int& value) {
    value=0; const char* first=p;
    while (*p>='0' && *p<='9') {
      if (value>10000) return false;
      value=value*10+*p++-'0';
    }
    return p!=first;
  }
  static bool validDuration(int d) { return d>=1 && d<=64 && (d & (d-1))==0; }
  bool fail() {
    stop(); error=true; Serial.println("ERR RTTTL"); return false;
  }
  bool next() {
    spaces(position);
    if (!*position) { stop(); return true; }
    int denominator=defaultDuration, octave=defaultOctave, accidental=0;
    bool dotted=false;
    if (*position>='0' && *position<='9') {
      if (!number(position,denominator)) return fail();
    }
    if (!validDuration(denominator)) return fail();
    char note=*position;
    if (note>='A' && note<='Z') note=char(note-'A'+'a');
    if (!note) return fail();
    position++;
    int semitone;
    switch (note) {
      case 'c': semitone=0; break; case 'd': semitone=2; break;
      case 'e': semitone=4; break; case 'f': semitone=5; break;
      case 'g': semitone=7; break; case 'a': semitone=9; break;
      case 'b': case 'h': semitone=11; break;
      case 'p': semitone=0; break; default: return fail();
    }
    if (*position=='#' || *position=='b') {
      if (note=='p') return fail();
      accidental=*position++=='#'?1:-1;
    }
    if (*position=='.') { dotted=true; position++; }
    if (*position>='0' && *position<='9') octave=*position++-'0';
    if (*position=='.') { if (dotted) return fail(); dotted=true; position++; }
    if (octave<3 || octave>7) return fail();
    spaces(position);
    if (*position==',') position++;
    else if (*position) return fail();
    duration=(240000UL/unsigned(bpm))/unsigned(denominator);
    if (dotted) duration=duration*3/2;
    started=millis();
    if (note=='p') { noTone(pin); sounding=false; }
    else {
      const int midi=(octave+1)*12+semitone+accidental;
      const int frequency=int(440.0*pow(2.0,(midi-69)/12.0)+0.5);
      tone(pin,frequency); sounding=true;
    }
    return true;
  }
 public:
  explicit Buzzer(int p) : pin(p) {}
  void begin() { pinMode(pin,OUTPUT); digitalWrite(pin,LOW); }
  bool startPlay(const char* melody) {
    stop(); error=false;
    if (!melody || !*melody) return fail();
    const char* p=strchr(melody,':');
    if (!p) return fail();
    defaultDuration=4; defaultOctave=5; bpm=120;
    p++;
    while (true) {
      spaces(p);
      if (*p==':') { p++; break; }
      const char key=*p;
      if (!key) return fail();
      p++;
      if (*p++!='=') return fail();
      int value;
      if (!number(p,value)) return fail();
      if (key=='d') defaultDuration=value;
      else if (key=='o') defaultOctave=value;
      else if (key=='b') bpm=value;
      else return fail();
      spaces(p);
      if (*p==',') p++;
      else if (*p!=':') return fail();
    }
    if (!validDuration(defaultDuration) || defaultOctave<3 || defaultOctave>7 || bpm<25 || bpm>900) return fail();
    position=p; playing=true;
    return next();
  }
  void update() {
    if (!playing) return;
    const unsigned long elapsed=millis()-started;
    if (elapsed>=duration) { noTone(pin); sounding=false; next(); }
    else if (sounding && elapsed>=duration*9/10) { noTone(pin); sounding=false; }
  }
  void stop() { noTone(pin); playing=sounding=false; }
  bool isPlayingMelody() const { return playing; }
  bool hasError() const { return error; }
  bool play(const char* melody) {
    if (!startPlay(melody)) return false;
    while (playing) { update(); delay(1); }
    return !error;
  }
};
using NonBlockingBuzzer = Buzzer;
