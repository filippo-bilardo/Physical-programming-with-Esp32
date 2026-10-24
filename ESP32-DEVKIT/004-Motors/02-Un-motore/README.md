# 02-Un-motore

Comanda soltanto il motore A al 50% mantenendo premuto il pulsante 23 verso GND. Rilasciando si disabilita il ponte.

## Preparazione

Usa un driver L298N e alimentazione motori esterna, con massa comune; non collegare i motori ai GPIO. Prima di alimentare segui la [tabella completa dei collegamenti e dei jumper](../README.md#piedinatura-del-progetto).

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [02-Un-motore.ino](02-Un-motore.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Confronta i segnali di enable e direzione durante rilascio e nuova pressione.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
