# LED 07 knight rider

Sei LED sui GPIO 18, 19, 21, 22, 25, 26, ciascuno con 220 Ω. Un punto luminoso percorre la fila e torna indietro a passi di 100 ms.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [LED_07_knight_rider.ino](LED_07_knight_rider.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Rendi regolabile il tempo del passo senza superare i limiti dell’array.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
