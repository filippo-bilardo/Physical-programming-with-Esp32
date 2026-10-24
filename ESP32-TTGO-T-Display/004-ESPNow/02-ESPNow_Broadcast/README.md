# ESP-NOW · Broadcast dei pulsanti

Lo sketch [02-ESPNow_Broadcast.ino](02-ESPNow_Broadcast.ino) inizializza display, pulsanti e radio station. I moduli locali `L1_EspNow` ed `ESPNow_Broadcast` registrano un peer FF:FF:FF:FF:FF:FF senza cifratura e trasmettono un evento per il click di ciascun tasto.

Consulta prima [configurazione e compatibilità](../README.md). Apri la cartella completa con tutti i `.h` e `.cpp`; servono almeno due TTGO sullo stesso canale e seriale a 115200 baud. Il comportamento previsto distingue TX/RX sul display con cerchi di colore diverso.

## Punto da correggere prima della prova radio

Nel codice presente il trasmettitore invia un **uint8_t**, mentre `EspNowRxTest()` copia `sizeof(int)` byte senza controllare `dataLen`. Non è un formato coerente: la ricezione può leggere oltre il messaggio. Prima del caricamento uniforma il tipo dell’evento a un byte anche in ricezione e verifica che la lunghezza sia quella attesa. Le callback richiedono inoltre verifica rispetto al core scelto.

Le operazioni TFT eseguite nelle callback radio sono un altro punto da rivedere: sposta elaborazione e aggiornamento del display nel loop tramite una coda, mantenendo le callback brevi.

## Esercizi

1. Correggi tipo e controllo della lunghezza; scarta un evento sconosciuto.
2. Prova prima un solo tasto e registra TX e RX su entrambe le schede.
3. Aggiungi contatore di sequenza e conferma applicativa senza assumere che un invio broadcast raggiunga tutti.

Questa guida documenta anche limiti già presenti; non è stata eseguita una prova radio né modificato lo sketch.

[Percorso ESP-NOW](../README.md).
