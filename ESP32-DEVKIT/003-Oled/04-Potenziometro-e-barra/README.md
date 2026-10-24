# 04-Potenziometro-e-barra

SSD1306 0x3C su SDA 21/SCL 22, VCC 3V3. Potenziometro da 10 kΩ fra 3V3 e GND, cursore su 34. Mostra codice ADC a 12 bit, percentuale e barra.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [04-Potenziometro-e-barra.ino](04-Potenziometro-e-barra.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Installa Adafruit SSD1306, Adafruit GFX e le dipendenze. Installa le librerie elencate in [libraries.txt](libraries.txt). Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Verifica i due estremi e inverti il verso scambiando gli estremi del potenziometro.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
