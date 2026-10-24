# Servo 01 controllo base

Comandi 0°, 90°, 180° con attesa di 1 s.

## Preparazione

Segnale servo 18 (anche 19 nella 06), alimentazione esterna adatta alla corrente di spunto/stallo, GND comune. Non alimentare i motori dal GPIO o dal 3V3. Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [Servo_01_controllo_base.ino](Servo_01_controllo_base.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Installa le librerie elencate in [libraries.txt](libraries.txt). Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Prova inizialmente senza carico; modifica un limite o una temporizzazione e confronta comando e movimento.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
