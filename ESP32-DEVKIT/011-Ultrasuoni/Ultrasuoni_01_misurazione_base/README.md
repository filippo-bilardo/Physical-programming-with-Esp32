# Ultrasuoni 01 misurazione base

Misura singola ogni 500 ms e stampa in cm.

## Preparazione

HC-SR04: VCC 5 V, GND comune, TRIG 25; Echo → 10 kΩ → nodo GPIO 26, e nodo → 15 kΩ → GND. Non collegare Echo a 5 V direttamente al GPIO. Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [Ultrasuoni_01_misurazione_base.ino](Ultrasuoni_01_misurazione_base.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Confronta le letture a distanze note e prova l’assenza di eco; annota il risultato prima di cambiare un parametro.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
