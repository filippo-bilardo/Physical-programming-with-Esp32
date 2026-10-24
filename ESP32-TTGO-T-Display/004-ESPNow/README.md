# ESP-NOW · Messaggi fra schede TTGO

ESP-NOW consente di scambiare piccoli messaggi fra dispositivi Espressif senza una connessione a un access point. Occorre distinguere indirizzo MAC del peer, canale radio, dati dell’applicazione e conferma di ricezione.

## Preparazione comune

Gli sketch riguardano la **TTGO T-Display originale con ESP32 e TFT ST7789 135×240**, non la T-Display S3. Display e pulsanti sono già sulla scheda; usa un cavo USB dati.

Installa il core esp32 by Espressif Systems e la libreria **TFT_eSPI**. Nella configurazione della libreria seleziona soltanto [Setup25_TTGO_T_Display.h](https://github.com/Bodmer/TFT_eSPI/blob/master/User_Setups/Setup25_TTGO_T_Display.h) in `User_Setup_Select.h`, disattivando la configurazione predefinita alternativa. Controlla driver, dimensioni e pin rispetto alla revisione della tua scheda. La configurazione è della libreria: un aggiornamento può sostituirla.

Apri lo sketch dalla sua cartella mantenendo anche i file locali `.h` e `.cpp`, seleziona scheda e porta e usa la seriale a **115200 baud**. Per schermo nero verifica alimentazione, configurazione TFT e comando della retroilluminazione prima di cambiare i pin.

I pulsanti sono sui GPIO **0 e 35**, attivi LOW. GPIO 35 non ha pull-up interno: il riferimento deve provenire dal circuito della scheda. GPIO 0 è anche coinvolto nell’avvio; rilascia il pulsante durante il reset se non vuoi entrare nel caricatore.

## Percorso

1. [Leggere il MAC](01-ESPNow_GetMacAddress/README.md), con una scheda.
2. [Broadcast dei pulsanti](02-ESPNow_Broadcast/README.md), con almeno due schede.
3. [Livelli L7/L2/L1 e code](03-ESPNow_L7_L2_L1/README.md), con indirizzi logici diversi.

## Compatibilità e limiti del codice presente

Questi esempi del 2022 usano firme di callback ESP-NOW precedenti ai core attuali. Non considerarli pronti per Arduino-ESP32 3.x: verifica la [guida di migrazione](https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html) e le firme della [API ESP-NOW](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/network/esp_now.html) del core effettivamente installato. Prima del caricamento registra versione e risultato della compilazione.

Le schede devono usare lo stesso canale radio. Il peer configurato è broadcast e senza cifratura; il risultato di invio non equivale a una conferma applicativa da tutti i destinatari. I due esempi di comunicazione hanno formati diversi: esegui lo stesso esempio su tutte le schede partecipanti.

## Esercizi

Confronta MAC e indirizzo logico; definisci un formato di messaggio con lunghezza verificabile; aggiungi una conferma con numero di sequenza per distinguere consegna e duplicati.

Documentazione aggiunta tramite lettura del codice; gli sketch richiedono le verifiche e le correzioni indicate nelle rispettive guide prima delle prove radio.

[Indice TTGO](../README.md).
