# 00-Scanner-I2C

Scansiona gli indirizzi I²C 0x08–0x77 ogni circa 3 s. OLED compatibile con 3,3 V: SDA 21, SCL 22, VCC 3V3, GND comune. Seriale 115200 baud; atteso 0x3C o l’indirizzo reale. Un ACK non identifica il modello.

## Preparazione

Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [00-Scanner-I2C.ino](00-Scanner-I2C.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Scollega il display a scheda spenta e confronta l’assenza di risposte.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
