# Pulsanti · Eventi sul display TTGO

Un livello premuto, un click completo e una pressione lunga sono eventi diversi. Il progetto visualizza gli eventi dei due pulsanti usando i file locali [MyBtn.h](MyBtn.h) e [MyBtn.cpp](MyBtn.cpp).

## Preparazione comune

Gli sketch riguardano la **TTGO T-Display originale con ESP32 e TFT ST7789 135×240**, non la T-Display S3. Display e pulsanti sono già sulla scheda; usa un cavo USB dati.

Installa il core esp32 by Espressif Systems e la libreria **TFT_eSPI**. Nella configurazione della libreria seleziona soltanto [Setup25_TTGO_T_Display.h](https://github.com/Bodmer/TFT_eSPI/blob/master/User_Setups/Setup25_TTGO_T_Display.h) in `User_Setup_Select.h`, disattivando la configurazione predefinita alternativa. Controlla driver, dimensioni e pin rispetto alla revisione della tua scheda. La configurazione è della libreria: un aggiornamento può sostituirla.

Apri lo sketch dalla sua cartella mantenendo anche i file locali `.h` e `.cpp`, seleziona scheda e porta e usa la seriale a **115200 baud**. Per schermo nero verifica alimentazione, configurazione TFT e comando della retroilluminazione prima di cambiare i pin.

I pulsanti sono sui GPIO **0 e 35**, attivi LOW. GPIO 35 non ha pull-up interno: il riferimento deve provenire dal circuito della scheda. GPIO 0 è anche coinvolto nell’avvio; rilascia il pulsante durante il reset se non vuoi entrare nel caricatore.

## Avvio e prove

Apri [003-ButtonsTest.ino](003-ButtonsTest.ino). Il loop attuale chiama `btnTest()` e stampa sul TFT `BTN_PRESS_SX`, `BTN_PRESS_DX` o `BTN_PRESS_BOTH`. Prova i due tasti separatamente e insieme; il display viene ripulito quando il cursore supera l’altezza.

La funzione alternativa `btnTest1()` è presente ma non chiamata: per provarla sostituisci la chiamata nel loop. Nell’assetto attuale mostra la pressione lunga del pulsante down (GPIO 0) e il click di up (GPIO 35). In `MyBtn.h` trovi debounce nominale 20 ms, pressione lunga 2000 ms e intervallo eventi 100 ms; la gestione concreta dipende dalla funzione usata.

`btnTest()` chiama più volte `checkPressButtons()` nello stesso giro: non presumere che ogni chiamata sia una lettura senza effetti. Come esercizio memorizza una sola volta il risultato e confrontalo con le costanti.

## Esercizi

1. Registra cosa compare per pressione breve, mantenuta e contemporanea.
2. Confronta `btnTest()` e `btnTest1()`.
3. Visualizza un contatore per ogni click senza ripetizioni durante il mantenimento.

La documentazione descrive il codice presente; compilazione e prove su scheda da eseguire.

[Indice TTGO](../README.md).
