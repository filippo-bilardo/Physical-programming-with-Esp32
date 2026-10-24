#include <Arduino.h>

/*
 * PIR_06_sistema_allarme.ino
 *
 * Sistema di allarme con sensore PIR che può essere attivato/disattivato
 * tramite un pulsante. Quando attivo, rileva movimenti e fa scattare l'allarme.
 *
 * Componenti necessari:
 * - ESP32 WROOM-32
 * - Sensore PIR HC-SR501
 * - LED rosso e verde
 * - Buzzer
 * - Pulsante
 * - Resistori (220Ω per LED, 10kΩ per pulsante se non si usa pull-up interno)
 * - Cavi di collegamento
 *
 * Collegamento:
 * PIR VCC        -> 5V del modulo, uscita OUT compatibile 3.3V
 * PIR GND        -> GND comune
 * PIR OUT        -> GPIO 23
 * LED rosso       -> GPIO 18 -> 220 ohm -> anodo; catodo -> GND
 * LED verde       -> GPIO 19 -> 220 ohm -> anodo; catodo -> GND
 * Piezo (+)      -> GPIO 27 tramite resistenza 1 kohm
 * Buzzer (-)     -> GND comune
 * Pulsante       -> GPIO 22 e GND (con INPUT_PULLUP)
 *
 * Autore: Filippo Bilardo
 * Data: 29/11/2025
 */

const int PIR_PIN = 23;       // Pin a cui è collegato il sensore PIR
const int LED_RED = 18;       // Pin a cui è collegato il LED rosso
const int LED_GREEN = 19;    // Pin a cui è collegato il LED verde
const int BUZZER_PIN = 27;   // Pin a cui è collegato il buzzer
const int ARM_BUTTON = 22;    // Pin del pulsante per attivare/disattivare l'allarme

// Stati del sistema
enum AlarmState {
  DISARMED,    // Sistema disattivato
  ARMED,       // Sistema attivo
  TRIGGERED    // Allarme scattato
};

AlarmState currentState = DISARMED;
int pirState = LOW;
int lastPirState = LOW;
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void toggleAlarm();
void triggerAlarm();
unsigned long lastBeep = 0;
bool beepOn = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_RED, OUTPUT); digitalWrite(LED_RED, LOW);
  pinMode(LED_GREEN, OUTPUT); digitalWrite(LED_GREEN, LOW);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ARM_BUTTON, INPUT_PULLUP);

  // Stato iniziale: disattivato
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Sistema di allarme con PIR");
  Serial.println("Inizializzazione sensore PIR...");
  Serial.println("Attendere 60 secondi per la stabilizzazione...");
  delay(60000);
  buttonState = lastButtonState = digitalRead(ARM_BUTTON);
  lastDebounceTime = millis();
  Serial.println("Sistema pronto!");
  Serial.println("Premere il pulsante per attivare/disattivare l'allarme");
}

void loop() {
  // Gestione del pulsante con debouncing
  int reading = digitalRead(ARM_BUTTON);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) >= DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {  // Pulsante premuto
        toggleAlarm();
      }
    }
  }
  lastButtonState = reading;

  // Gestione del sensore PIR
  pirState = digitalRead(PIR_PIN);

  // Se il sistema è armato e viene rilevato movimento
  if (currentState == ARMED && pirState == HIGH) {
    triggerAlarm();
  }

  lastPirState = pirState;

  // Gestione del buzzer se l'allarme è scattato
  if (currentState == TRIGGERED) {
    const unsigned long now = millis();
    if (now - lastBeep >= (beepOn ? 200UL : 100UL)) {
      lastBeep = now;
      beepOn = !beepOn;
      if (beepOn) tone(BUZZER_PIN, 1000); else noTone(BUZZER_PIN);
    }
  }
  delay(1);
}

// Funzione per attivare/disattivare l'allarme
void toggleAlarm() {
  if (currentState == DISARMED) {
    currentState = ARMED;
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    Serial.println("Sistema ATTIVATO");
  } else {
    currentState = DISARMED;
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    noTone(BUZZER_PIN); beepOn = false;
    Serial.println("Sistema DISATTIVATO");
  }
}

// Funzione per far scattare l'allarme
void triggerAlarm() {
  currentState = TRIGGERED;
  beepOn = true; lastBeep = millis(); tone(BUZZER_PIN, 1000);
  Serial.println("!!! ALLARME SCATTATO !!!");
  Serial.println("Movimento rilevato!");
}
