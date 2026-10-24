# LED 10 led seriale

LED 18 con 220 Ω. Seriale 115200 baud con LF/CRLF: a accende, s spegne, b128 imposta il duty, l esegue cinque lampeggi e ripristina il duty precedente. Il lampeggio seriale è bloccante.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [LED_10_led_seriale.ino](LED_10_led_seriale.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Prova b0, b255 e un comando errato; rendi l’animazione interrompibile.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
