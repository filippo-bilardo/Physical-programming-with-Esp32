# LED 05 semaforo

LED rosso 18, giallo 19, verde 21, ciascuno con 220 Ω. Sequenza rosso 3 s, rosso+giallo 1 s, verde 3 s, giallo 1 s.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [LED_05_semaforo.ino](LED_05_semaforo.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Trasforma la sequenza didattica in una macchina a stati con una richiesta memorizzata.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
