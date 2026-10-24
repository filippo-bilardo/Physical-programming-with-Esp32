/*
 * Importato da filippo-bilardo/ROBOTICA, Led/LED_10_led_seriale.ino.
 * Revisione locale di riferimento: be14c4db788f02186c714e241a8c2fa19b975b7d.
 * Adattamento ESP32 WROOM-32 del 24/10/2026; dettagli in ../PROVENIENZA.md.
 * Licenza del sorgente: GNU AGPLv3, vedi LICENSE nella radice del repository.
 */
#include <Arduino.h>

/*
 * LED_10_led_seriale.ino
 *
 * Questo sketch dimostra come controllare un LED tramite comandi inviati
 * attraverso la comunicazione seriale. L'utente può inviare comandi per
 * accendere, spegnere o far lampeggiare il LED.
 *
 * Circuito:
 * - LED collegato al GPIO 18 e GND attraverso una resistenza da 220 ohm
 *
 * Comandi seriali:
 * - 'a': accende il LED
 * - 's': spegne il LED
 * - 'l': fa lampeggiare il LED 5 volte
 * - 'b' seguito da un numero (0-255): imposta la luminosità del LED
 *
 * Creato il: 2023
 */

/*
 * Controllo LED da seriale: a, s, l, b0..b255, una richiesta per riga.
 * LED esterno GPIO18 con 220 ohm; seriale 115200 baud.
 * Il lampeggio di cinque cicli resta intenzionalmente bloccante.
 */
const int LED_PIN = 18;
char line[6];  // Fino a b255 + CR, piu' terminatore.
int length = 0;
bool overflow = false;
int brightness = 0;

void applyBrightness(int value) {
  brightness = constrain(value, 0, 255);
  analogWrite(LED_PIN, brightness);
}

void executeCommand() {
  if (length == 1 && line[0] == 'a') {
    applyBrightness(255);
    Serial.println("LED acceso");
  } else if (length == 1 && line[0] == 's') {
    applyBrightness(0);
    Serial.println("LED spento");
  } else if (length == 1 && line[0] == 'l') {
    const int saved = brightness;
    Serial.println("Lampeggio LED 5 volte");
    for (int i = 0; i < 5; i++) {
      analogWrite(LED_PIN, 255); delay(200);
      analogWrite(LED_PIN, 0); delay(200);
    }
    applyBrightness(saved);
    Serial.println("Lampeggio completato");
  } else if (length >= 2 && length <= 4 && line[0] == 'b') {
    int value = 0;
    for (int i = 1; i < length; i++) {
      if (line[i] < '0' || line[i] > '9') { Serial.println("ERR COMMAND"); return; }
      value = value * 10 + line[i] - '0';
    }
    applyBrightness(value);  // Massimo tre cifre, poi limita a 255.
    Serial.print("Luminosita impostata a: "); Serial.println(brightness);
  } else Serial.println("ERR COMMAND");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  analogWriteResolution(LED_PIN, 8);
  analogWriteFrequency(LED_PIN, 5000);
  applyBrightness(0);
  Serial.println("Comandi: a, s, l, b0..b255; termina ogni riga con LF");
}

void loop() {
  int budget = 32;
  while (budget-- > 0 && Serial.available() > 0) {
    const char value = char(Serial.read());
    if (value == '\n') {
      if (overflow) Serial.println("ERR LENGTH");
      else {
        if (length > 0 && line[length - 1] == '\r') length--;
        line[length] = '\0';
        if (length > 0) executeCommand();
      }
      length = 0;
      overflow = false;
    } else if (!overflow) {
      if (length < 5) line[length++] = value;
      else overflow = true;  // Scarta fino a LF, senza eseguire un suffisso.
    }
  }
  delay(1);
}
