#include <Arduino.h>

const int RED_PIN = 18;
const int YELLOW_PIN = 19;
const int GREEN_PIN = 21;
const int PEDESTRIAN_PIN = 22;
const int BUTTON_PIN = 23;
const unsigned long DEBOUNCE_MS = 30;
const unsigned long GREEN_MIN_MS = 5000;
const unsigned long YELLOW_MS = 2000;
const unsigned long PEDESTRIAN_MS = 4000;
const unsigned long RED_PAUSE_MS = 1000;

enum State { AUTO_VERDE, AUTO_GIALLO, PEDONI_VERDE, PAUSA_ROSSA };
// Prototipo esplicito: State e' gia' dichiarato anche nel preprocessing Arduino.
void enterState(State next, unsigned long now);

State state;
unsigned long enteredAt;
unsigned long lastChange;
int lastRaw;
int stableState;
bool requestPending = false;
bool greenReady = false;

void enterState(State next, unsigned long now) {
  state = next;
  enteredAt = now;  // Si aggiorna all'ingresso, non a ogni giro.
  // Prima spegni le uscite, poi accendi quelle previste dal nuovo stato.
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(PEDESTRIAN_PIN, LOW);
  switch (state) {
    case AUTO_VERDE:
      greenReady = false;
      digitalWrite(GREEN_PIN, HIGH);
      Serial.println("AUTO_VERDE");
      break;
    case AUTO_GIALLO:
      digitalWrite(YELLOW_PIN, HIGH);
      Serial.println("AUTO_GIALLO");
      break;
    case PEDONI_VERDE:
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(PEDESTRIAN_PIN, HIGH);
      Serial.println("PEDONI_VERDE");
      break;
    case PAUSA_ROSSA:
      digitalWrite(RED_PIN, HIGH);
      Serial.println("PAUSA_ROSSA");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(PEDESTRIAN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastRaw = digitalRead(BUTTON_PIN);
  stableState = lastRaw;  // Un tasto gia' premuto non genera un evento.
  lastChange = millis();
  enterState(AUTO_VERDE, lastChange);
}

void loop() {
  const int raw = digitalRead(BUTTON_PIN);
  const unsigned long now = millis();

  // Il filtro continua ad aggiornarsi in tutti gli stati.
  if (raw != lastRaw) {
    lastRaw = raw;
    lastChange = now;
  }
  if (raw != stableState && now - lastChange >= DEBOUNCE_MS) {
    stableState = raw;
    if (stableState == LOW && state == AUTO_VERDE && !requestPending) {
      requestPending = true;
      Serial.println("Richiesta accettata");
    }
  }

  switch (state) {
    case AUTO_VERDE:
      // Ricorda la soglia raggiunta: il verde puo' durare indefinitamente.
      if (!greenReady && now - enteredAt >= GREEN_MIN_MS) {
        greenReady = true;
      }
      if (requestPending && greenReady) {
        requestPending = false;
        enterState(AUTO_GIALLO, now);
      }
      break;
    case AUTO_GIALLO:
      if (now - enteredAt >= YELLOW_MS) {
        enterState(PEDONI_VERDE, now);
      }
      break;
    case PEDONI_VERDE:
      if (now - enteredAt >= PEDESTRIAN_MS) {
        enterState(PAUSA_ROSSA, now);
      }
      break;
    case PAUSA_ROSSA:
      if (now - enteredAt >= RED_PAUSE_MS) {
        enterState(AUTO_VERDE, now);
      }
      break;
  }
  delay(1);
}
