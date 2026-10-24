/*
 * Importato da filippo-bilardo/ROBOTICA, Led/LED_06_led_rgb.ino.
 * Revisione locale di riferimento: be14c4db788f02186c714e241a8c2fa19b975b7d.
 * Adattamento ESP32 WROOM-32 del 24/10/2026; dettagli in ../PROVENIENZA.md.
 * Licenza del sorgente: GNU AGPLv3, vedi LICENSE nella radice del repository.
 */
#include <Arduino.h>

/*
 * LED_06_led_rgb.ino
 *
 * Questo sketch dimostra come controllare un LED RGB (Red, Green, Blue)
 * per creare vari colori attraverso la miscelazione dei tre colori primari.
 *
 * Circuito:
 * - LED RGB a catodo comune: rosso su GPIO 18, verde su GPIO 19, blu su GPIO 21
 * - Catodo comune collegato a GND
 * - Resistenze da 220 ohm per ciascun colore
 *
 * Creato il: 2023
 */

const int RED_PIN = 18;    // Pin PWM per il colore rosso
const int GREEN_PIN = 19; // Pin PWM per il colore verde
const int BLUE_PIN = 21;  // Pin PWM per il colore blu

void setColor(int red, int green, int blue);
void rainbowCycle();

void setup() {
  // Inizializza i pin come output
  pinMode(RED_PIN, OUTPUT);
  analogWriteResolution(RED_PIN, 8);
  analogWriteFrequency(RED_PIN, 5000);
  pinMode(GREEN_PIN, OUTPUT);
  analogWriteResolution(GREEN_PIN, 8);
  analogWriteFrequency(GREEN_PIN, 5000);
  pinMode(BLUE_PIN, OUTPUT);
  analogWriteResolution(BLUE_PIN, 8);
  analogWriteFrequency(BLUE_PIN, 5000);

  // Inizia con il LED spento
  setColor(0, 0, 0);
}

void loop() {
  // Rosso
  setColor(255, 0, 0);
  delay(1000);

  // Verde
  setColor(0, 255, 0);
  delay(1000);

  // Blu
  setColor(0, 0, 255);
  delay(1000);

  // Giallo (rosso + verde)
  setColor(255, 255, 0);
  delay(1000);

  // Ciano (verde + blu)
  setColor(0, 255, 255);
  delay(1000);

  // Magenta (rosso + blu)
  setColor(255, 0, 255);
  delay(1000);

  // Bianco (tutti i colori)
  setColor(255, 255, 255);
  delay(1000);

  // Transizione graduale attraverso lo spettro dei colori
  rainbowCycle();
}

// Funzione per impostare il colore del LED RGB
void setColor(int red, int green, int blue) {
  // Catodo comune a GND: 0 = spento, 255 = duty massimo per ciascun colore.
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

// Funzione per creare un effetto arcobaleno
void rainbowCycle() {
  // Ciclo attraverso tutti i colori dello spettro
  for (int i = 0; i < 256; i++) {
    // Effetto arcobaleno utilizzando la ruota dei colori HSV
    // Dividiamo il ciclo in 3 parti per creare una transizione fluida
    if (i < 85) {
      setColor(255 - i * 3, i * 3, 0);
    } else if (i < 170) {
      setColor(0, 255 - (i - 85) * 3, (i - 85) * 3);
    } else {
      setColor((i - 170) * 3, 0, 255 - (i - 170) * 3);
    }
    delay(20);
  }
}
