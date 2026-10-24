# Pulsanti 07 macchina stati

OFF → rosso → verde → blu → OFF, un passaggio per pressione.

## Preparazione

Pulsante principale fra GPIO 23 e GND, pull-up interno; premuto = LOW. LED principale su 18 con 220 Ω, catodo a GND. Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [Pulsanti_07_macchina_stati.ino](Pulsanti_07_macchina_stati.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Prova pressione breve, mantenuta e rilascio; annota quando viene generato l’evento e modifica una temporizzazione.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
