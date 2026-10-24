# 01-LedBlink

Lampeggiare il LED sul GPIO 2, se presente, o un LED esterno con 220 Ω. Dopo 500 ms iniziali alterna 500 ms acceso e 500 ms spento.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [01-LedBlink.ino](01-LedBlink.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Modifica acceso a 200 ms e spento a 800 ms; calcola periodo e duty del lampeggio.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
