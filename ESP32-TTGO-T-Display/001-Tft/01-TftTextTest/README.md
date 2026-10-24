# TFT · Test del testo

Lo sketch [01-TftTextTest.ino](01-TftTextTest.ino) prova colori di sfondo, cursore, rotazioni 0–3, font, dimensioni, ritorno a capo, allineamento e inversione dei colori. Segui prima la [configurazione TFT_eSPI](../README.md).

## Procedura

1. Carica il programma sulla TTGO T-Display originale.
2. Apri la seriale a 115200 baud per vedere il numero della prova.
3. Premi e rilascia il pulsante sul GPIO 0 per passare alla schermata successiva; alla fine la sequenza riparte.
4. Confronta testo trasparente e testo con sfondo, font numerici e font con lettere.

L’attesa del pulsante usa cicli e ritardi: blocca le altre attività del loop. Se il tasto è già premuto quando la funzione viene chiamata, il codice può saltare l’attesa; il ritardo di 10 ms non verifica da solo una stabilità completa del contatto.

## Esercizi

Crea una schermata con titolo centrato, valore numerico e unità; verifica che il passaggio da tre a una cifra cancelli il testo precedente. Poi sostituisci i cicli di attesa con una macchina a stati.

Codice preesistente documentato tramite lettura; prove su scheda da eseguire.

[Guida TFT](../README.md).
