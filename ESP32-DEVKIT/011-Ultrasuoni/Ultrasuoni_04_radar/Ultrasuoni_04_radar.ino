#include <Arduino.h>

// Radar ultrasonico con visualizzazione seriale
const int TRIG_PIN = 25;
const int ECHO_PIN = 26;
const int SERVO_PIN = 18;  // Pin per il servomotore

#include <ESP32Servo.h>

Servo radarServo;  // Crea un oggetto servo

// Parametri del radar
const int MIN_ANGLE = 15;    // Angolo minimo di scansione
const int MAX_ANGLE = 165;   // Angolo massimo di scansione
const int STEP_ANGLE = 5;    // Incremento dell'angolo per ogni passo
const int MAX_DISTANCE = 200; // Distanza massima da visualizzare (cm)

// Variabili di stato
int currentAngle = MIN_ANGLE;
int scanDirection = 1;  // 1 = in senso orario, -1 = in senso antiorario

int measureDistance();

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  radarServo.setPeriodHertz(50);
  radarServo.attach(SERVO_PIN, 1000, 2000);
  if (!radarServo.attached()) { Serial.begin(115200); Serial.println("ERR SERVO"); while (true) delay(100); }
  radarServo.write(currentAngle);  // Posiziona il servo all'angolo iniziale

  Serial.begin(115200);
  Serial.println("Radar ultrasonico attivo");
  Serial.println("Formato dati: angolo,distanza");
  delay(1000);  // Attendi che il servo raggiunga la posizione iniziale
}

void loop() {
  // Misura la distanza all'angolo corrente
  int distance = measureDistance();

  // -1 significa misura non valida; una distanza oltre scala non e' un guasto.
  if (distance > MAX_DISTANCE) distance = MAX_DISTANCE;

  // Invia i dati al monitor seriale nel formato "angolo,distanza"
  Serial.print(currentAngle);
  Serial.print(",");
  Serial.println(distance);

  // Muovi il servo al prossimo angolo
  currentAngle += (STEP_ANGLE * scanDirection);

  // Cambia direzione se raggiungi i limiti
  if (currentAngle >= MAX_ANGLE || currentAngle <= MIN_ANGLE) {
    scanDirection *= -1;  // Inverti la direzione
  }

  // Assicurati che l'angolo rimanga nei limiti
  currentAngle = constrain(currentAngle, MIN_ANGLE, MAX_ANGLE);

  // Posiziona il servo al nuovo angolo
  radarServo.write(currentAngle);

  delay(100);  // Piccolo ritardo per stabilità
}

// Funzione per misurare la distanza
int measureDistance() {
  long duration;

  // Invia impulso ultrasonico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Misura il tempo di ritorno dell'eco
  duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  // Calcola e restituisci la distanza in cm
  return duration == 0 ? -1 : int(duration / 58);
}
