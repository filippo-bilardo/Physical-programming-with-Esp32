#include <Arduino.h>

// Sketch base per la lettura di un pulsante
const int BUTTON_PIN = 23;  // Pin a cui è collegato il pulsante

void setup() {
  Serial.begin(115200);       // Inizializza la comunicazione seriale
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Imposta il pin del pulsante come input con pull-up
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);  // Leggi lo stato del pulsante

  if (buttonState == LOW) {  // Se il pulsante è premuto (LOW con pull-up)
    Serial.println("Pulsante premuto");
  } else {
    Serial.println("Pulsante rilasciato");
  }

  delay(100);  // Campionamento ogni 100 ms: non e un filtro debounce
}
