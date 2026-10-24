#include <Arduino.h>

// Sketch con funzionalità non bloccante
const int BUTTON_PIN = 23;  // Pin a cui è collegato il pulsante
const int LED_PIN = 18;    // Pin a cui è collegato il LED
const int ANALOG_PIN = 34;  // Cursore potenziometro 10 kohm, estremi a 3V3/GND

// Variabili di stato
int ledState = LOW;                        // Stato corrente del LED
int buttonState = HIGH;                    // Stato corrente del pulsante
int lastButtonState = HIGH;                // Stato precedente del pulsante

// Variabili per il timing
unsigned long lastDebounceTime = 0;        // Ultimo momento in cui il pin è cambiato
unsigned long lastAnalogReadTime = 0;        // Ultimo momento in cui è stata letta la lettura analogica
const unsigned long DEBOUNCE_DELAY = 50;   // Tempo di debounce (ms)
const unsigned long ANALOG_READ_INTERVAL = 2000;  // Intervallo di lettura della lettura analogica (ms)

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(ANALOG_PIN, ADC_11db);
  lastAnalogReadTime = millis();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  buttonState = lastButtonState = digitalRead(BUTTON_PIN);
  lastDebounceTime = millis();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  unsigned long currentMillis = millis();

  // Task 1: Gestione del pulsante con debouncing
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = currentMillis;
  }

  if ((currentMillis - lastDebounceTime) >= DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {  // Se il pulsante è premuto (LOW con pull-up)
        ledState = !ledState;    // Inverti lo stato del LED
        digitalWrite(LED_PIN, ledState);
        Serial.println(ledState ? "LED acceso" : "LED spento");
      }
    }
  }
  lastButtonState = reading;

  // Task 2: Lettura analogica periodica
  if (currentMillis - lastAnalogReadTime >= ANALOG_READ_INTERVAL) {
    lastAnalogReadTime = currentMillis;
    const int raw = analogRead(ANALOG_PIN);
    Serial.print("ADC="); Serial.println(raw);
  }

  // Altri task possono essere aggiunti qui senza bloccare l'esecuzione
  delay(1);
}
