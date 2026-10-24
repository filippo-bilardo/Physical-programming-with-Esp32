# 03-Grafica-e-animazione

Una pallina si muove e rimbalza nel riquadro sullo SSD1306 128×64, SDA 21/SCL 22, VCC 3V3. La pianificazione con millis() resta soggetta al costo del trasferimento I²C.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [03-Grafica-e-animazione.ino](03-Grafica-e-animazione.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Installa Adafruit SSD1306, Adafruit GFX e le dipendenze. Installa le librerie elencate in [libraries.txt](libraries.txt). Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Cambia raggio e velocità mantenendo tutta la pallina nel riquadro.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
