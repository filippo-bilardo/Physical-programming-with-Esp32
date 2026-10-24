# PIR 08 classe sensore

Classe SensorePIR con eventi, durata e contatore.

## Preparazione

PIR su GPIO 23 (23/22/21 nella 07), GND comune e alimentazione prevista dal modulo; verifica OUT compatibile con 3,3 V. Attendi 60 s di stabilizzazione. Consulta la [guida della raccolta](../README.md) per teoria, circuito specifico e dipendenze.

Apri [PIR_08_classe_sensore.ino](PIR_08_classe_sensore.ino) in Arduino IDE dalla cartella attuale. Seleziona scheda ESP32 e porta corrette; carica un solo sketch alla volta. Per i messaggi usa il monitor seriale a 115200 baud, quando previsto. Mantieni nella cartella anche gli eventuali file `.h` e `.cpp`.

È incluso [diagram.json](diagram.json): copialo insieme al programma nel progetto Wokwi corrispondente, seguendo la guida della raccolta.

## Prova ed esercizio

Attendi la stabilizzazione, confronta HIGH mantenuto e nuove attivazioni; annota conteggio e tempi.

Registra versione del core o firmware, collegamenti e risultato osservato; lo schema simulato non verifica alimentazione e correnti reali.

[Torna alla raccolta](../README.md).
