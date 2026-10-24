#include <Arduino.h>

// Theremin digitale con sensore ad ultrasuoni
const int BUZZER_PIN = 27;
const int US_TRIG_PIN = 25;    // Trigger del sensore HC-SR04
const int US_ECHO_PIN = 26;   // Echo del sensore HC-SR04

// Parametri del theremin
const int minFreq = 100;   // Frequenza minima (Hz)
const int maxFreq = 2000;  // Frequenza massima (Hz)
const int minDist = 5;     // Distanza minima (cm)
const int maxDist = 50;    // Distanza massima (cm)

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(US_TRIG_PIN, OUTPUT);
  pinMode(US_ECHO_PIN, INPUT);
  Serial.begin(115200);
  Serial.println("Theremin digitale attivo");
}

void loop() {
  // Misura la distanza
  long duration, distance;

  // Invia impulso ultrasonico
  digitalWrite(US_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(US_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG_PIN, LOW);

  // Calcola la distanza
  duration = pulseIn(US_ECHO_PIN, HIGH, 30000UL);
  if (duration==0) { noTone(BUZZER_PIN); Serial.println("ERR ECO"); delay(50); return; }
  distance = duration / 58;  // Conversione in cm

  // Limita la distanza nell'intervallo definito
  distance = constrain(distance, minDist, maxDist);

  // Mappa la distanza alla frequenza
  int frequency = map(distance, minDist, maxDist, maxFreq, minFreq);

  // Mostra i valori sulla seriale
  Serial.print("Distanza: ");
  Serial.print(distance);
  Serial.print(" cm | Frequenza: ");
  Serial.print(frequency);
  Serial.println(" Hz");

  // Genera il tono corrispondente
  tone(BUZZER_PIN, frequency);

  // Se la mano è troppo lontana, ferma il suono
  if (distance >= maxDist) {
    noTone(BUZZER_PIN);
  }

  delay(50);  // Piccolo ritardo per stabilità
}
