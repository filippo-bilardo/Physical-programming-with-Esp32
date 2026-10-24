# ESP-NOW · Leggere il MAC della scheda

L’indirizzo MAC identifica un’interfaccia di rete e non coincide con l’indirizzo logico di un protocollo applicativo. [01-ESPNow_GetMacAddress.ino](01-ESPNow_GetMacAddress.ino) visualizza `WiFi.macAddress()` sul TFT e sulla seriale; non invia messaggi ESP-NOW.

Segui la [preparazione della TTGO](../README.md), apri lo sketch e usa la seriale a 115200 baud. Non serve conoscere SSID o password per leggere il MAC. Confronta seriale e display e annota una scheda alla volta.

Il codice attuale non chiama `WiFi.mode(WIFI_STA)` prima della lettura. Se ottieni un MAC nullo o inatteso sul tuo core, inizializza esplicitamente l’interfaccia station e ripeti la lettura prima di usare il valore come peer.

## Esercizi

Leggi il MAC di due schede, verifica che i valori differiscano e spiega perché il MAC station può differire da quello soft-AP. Registra versione del core e modalità dell’interfaccia.

Documentazione basata sul codice; compilazione e verifica su scheda da eseguire.

[Percorso ESP-NOW](../README.md).
