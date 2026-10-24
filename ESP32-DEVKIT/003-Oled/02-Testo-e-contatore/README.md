# 02-Testo-e-contatore

Ridisegna testo e contatore sul display SSD1306 128×64 I²C 0x3C, SDA 21/SCL 22, VCC 3V3 e GND. display() trasferisce il framebuffer; clearDisplay() agisce sulla RAM.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [02-Testo-e-contatore.ino](02-Testo-e-contatore.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Installa Adafruit SSD1306, Adafruit GFX e le dipendenze. Installa le librerie elencate in [libraries.txt](libraries.txt). Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Cambia intervallo e dimensione del testo evitando righe tagliate.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
