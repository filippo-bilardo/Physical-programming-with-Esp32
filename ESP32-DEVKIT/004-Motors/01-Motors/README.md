# 01-Motors

Due ponti L298N: sequenza +60% per 2 s, stop 500 ms, −60% per 2 s, stop 500 ms. Il pulsante 23 verso GND deve restare premuto per abilitare.

## Preparazione

Usa un driver L298N e alimentazione motori esterna, con massa comune; non collegare i motori ai GPIO. Prima di alimentare segui la [tabella completa dei collegamenti e dei jumper](../README.md#piedinatura-del-progetto).

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [01-Motors.ino](01-Motors.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Rilascia durante una fase e verifica stop e riavvio come descritti nella guida.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
