# TFT · Test della grafica

[02-TftGraphicsTest.ino](02-TftGraphicsTest.ino) disegna cerchi, ellissi, rettangoli, triangoli, pixel e linee; rappresenta anche seno, coseno e tangente. Richiede la [configurazione TFT_eSPI della TTGO originale](../README.md).

## Avvio e risultato

Apri e carica lo sketch con seriale a 115200 baud. Nel setup la chiamata `digitalWrite(TFT_BL, TFT_BACKLIGHT_ON)` è **commentata**: se il display resta buio, abilitala dopo aver verificato che la configurazione selezionata definisca il pin e la polarità corretti.

Premi e rilascia il pulsante GPIO 0 per avanzare. Il programma prova orientamenti verticale e orizzontale; usa `width()` e `height()` per molte coordinate. Le attese sono bloccanti e un pulsante già premuto può saltare una schermata. Alcune forme possono essere tagliate ai bordi: il controller non amplia l’area disegnabile.

## Esercizi

1. Disegna una pallina rispettando un margine pari al suo raggio.
2. Cambia orientamento e confronta l’area disponibile.
3. Limita i valori della tangente prima di convertirli in coordinate del pannello.
4. Anima una forma con millis() mantenendo attivo il controllo dei pulsanti.

Codice preesistente documentato tramite lettura; compilazione e prova fisica da eseguire.

[Guida TFT](../README.md).
