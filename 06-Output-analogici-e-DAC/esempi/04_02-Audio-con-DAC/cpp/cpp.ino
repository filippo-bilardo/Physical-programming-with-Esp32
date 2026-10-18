#include <Arduino.h>

// Un periodo di sinusoide approssimata: centro 128, ampiezza 64 codici.
const int samples[] = {128, 173, 192, 173, 128, 83, 64, 83};

void setup() {
  Serial.begin(115200);
  dacWrite(25, 128);
}

void loop() {
  Serial.println("AUDIO DAC: 500 periodi");
  for (int cycle = 0; cycle < 500; cycle++) {
    for (int i = 0; i < 8; i++) {
      dacWrite(25, samples[i]);
      delayMicroseconds(250);
    }
    if ((cycle + 1) % 20 == 0) delay(1);  // Yield ogni blocco di circa 40 ms.
  }
  dacWrite(25, 128);  // Livello costante: fine dell'oscillazione.
  Serial.println("PAUSA DAC");
  delay(1000);
}
