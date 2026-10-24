# TFT · Testo e grafica sulla TTGO T-Display

Il TFT usa un controller ST7789 e comunica via SPI. Il programma imposta colori e coordinate del display; rotazione e font cambiano lo spazio disponibile. Lo sfondo esplicito del testo consente di cancellare i pixel precedenti.

## Preparazione comune

Gli sketch riguardano la **TTGO T-Display originale con ESP32 e TFT ST7789 135×240**, non la T-Display S3. Display e pulsanti sono già sulla scheda; usa un cavo USB dati.

Installa il core esp32 by Espressif Systems e la libreria **TFT_eSPI**. Nella configurazione della libreria seleziona soltanto [Setup25_TTGO_T_Display.h](https://github.com/Bodmer/TFT_eSPI/blob/master/User_Setups/Setup25_TTGO_T_Display.h) in `User_Setup_Select.h`, disattivando la configurazione predefinita alternativa. Controlla driver, dimensioni e pin rispetto alla revisione della tua scheda. La configurazione è della libreria: un aggiornamento può sostituirla.

Apri lo sketch dalla sua cartella mantenendo anche i file locali `.h` e `.cpp`, seleziona scheda e porta e usa la seriale a **115200 baud**. Per schermo nero verifica alimentazione, configurazione TFT e comando della retroilluminazione prima di cambiare i pin.

I pulsanti sono sui GPIO **0 e 35**, attivi LOW. GPIO 35 non ha pull-up interno: il riferimento deve provenire dal circuito della scheda. GPIO 0 è anche coinvolto nell’avvio; rilascia il pulsante durante il reset se non vuoi entrare nel caricatore.

## Percorso

1. [Testo, font e rotazioni](01-TftTextTest/README.md): esegui prima questo esempio per verificare display e pulsante.
2. [Forme e grafici](02-TftGraphicsTest/README.md): cerchi, ellissi, rettangoli, triangoli e funzioni trigonometriche.

Premi e rilascia il pulsante sul GPIO 0 per passare fra le schermate. Le funzioni di attesa sono bloccanti e non costituiscono un filtro completo dei rimbalzi. Leggi le particolarità dei due programmi nelle rispettive guide.

## Esercizi

1. Disegna tre etichette usando allineamenti diversi e verifica il taglio ai bordi.
2. Confronta dimensioni del display e coordinate dopo una rotazione.
3. Sostituisci l’attesa bloccante con uno stato di pagina aggiornato da un evento di click.

La documentazione descrive il codice presente; compilazione ed esecuzione su TTGO sono da verificare.

[Indice TTGO](../README.md).
