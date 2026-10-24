# 01-Oled

Demo SSD1306 I²C 128×64 a 0x3C, SDA 21/SCL 22, alimentazione 3,3 V. Usa MyOled.h/.cpp locali. Con MYOLED_DEMO attiva setup() resta nell’animazione finale e non raggiunge loop().

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [01-Oled.ino](01-Oled.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Installa Adafruit SSD1306, Adafruit GFX e le dipendenze. Installa le librerie elencate in [libraries.txt](libraries.txt). Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Disattiva la demo e mostra una tua scritta con oled.println().

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
