# LED 02 controllo pulsante

LED 18 con 220 Ω; pulsante fra GPIO 23 e GND, INPUT_PULLUP. Il LED segue la pressione, premuto = LOW; non è previsto debounce.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [LED_02_controllo_pulsante.ino](LED_02_controllo_pulsante.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Aggiungi il rilevamento del fronte e un filtro dei rimbalzi.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
