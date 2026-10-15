# 05 · Ingressi analogici e ADC

Trasforma una tensione variabile in un numero, osserva i limiti della misura e usa una soglia regolabile per comandare un LED. Il potenziometro permette di simulare un sensore senza introdurre ancora una libreria esterna.

## Prerequisiti e obiettivi

**Prerequisiti:** esercitazioni 01–04: GPIO, tensione e massa comune, resistenza del LED, condizioni, cicli e temporizzazioni senza lunghe attese.

Al termine saprai:

- Collegare un potenziometro come partitore e scegliere un ingresso ADC.
- Distinguere codice digitale, risoluzione, percentuale e tensione misurata.
- Impostare risoluzione e attenuazione sull'ESP32 classico.
- Campionare a intervalli, calcolare una media a blocchi e riconoscerne il ritardo.
- Regolare una soglia e applicare isteresi per stabilizzare un comando.

## Materiali e ambienti

ESP32 classico con modulo ESP32-WROOM-32, per esempio DOIT ESP32 DEVKIT V1; cavo USB dati, breadboard e cavetti. Servono due potenziometri lineari da **10 kΩ**, un LED rosso e una resistenza da **220 Ω** in serie al LED. I primi tre esempi usano soltanto il primo potenziometro. Per le misure reali serve un multimetro.

Usiamo GPIO **34** per il segnale e **35** per la regolazione della soglia: appartengono all'ADC1 dell'ESP32 classico e sono ingressi, senza pull-up interno. Il LED va sul GPIO **18**. Non trasferire automaticamente la piedinatura a ESP32-C3, S2 o S3.

Entrambi i potenziometri sono alimentati tra **3V3 e GND**; il cursore va all'ingresso ADC. Non alimentarli a 5 V. L'attenuazione amplia l'intervallo di conversione e non protegge da una tensione eccessiva. Ogni esempio contiene tabella dei collegamenti e circuiti Wokwi per i due linguaggi.

## Guide teoriche

1. [Potenziometro e conversione analogico-digitale](01-Potenziometro-e-ADC.md)
2. [Risoluzione, attenuazione e misura](02-Risoluzione-attenuazione-e-misura.md)
3. [Campionamento, rumore e media](03-Campionamento-rumore-e-media.md)
4. [Soglia regolabile e isteresi](04-Soglia-regolabile-e-isteresi.md)

Ogni guida comprende teoria, esempi commentati nei due linguaggi, autovalutazione con soluzioni ed esercizi progressivi.

## Esempi completi

| Esempio | Guida | Implementazioni |
| --- | --- | --- |
| [Lettura del potenziometro](esempi/01_01-Lettura-potenziometro/README.md) | 01 | C++ e MicroPython |
| [Scala percentuale](esempi/02_01-Scala-percentuale/README.md) | 02 | C++ e MicroPython |
| [Media di otto campioni](esempi/03_01-Media-di-otto-campioni/README.md) | 03 | C++ e MicroPython |
| [Soglia regolabile con isteresi](esempi/04_01-Soglia-regolabile-con-isteresi/README.md) | 04 | C++ e MicroPython |

Per l'installazione consulta la [guida agli ambienti](../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md). Gli esempi C++ usano Arduino-ESP32; quelli MicroPython richiedono il firmware ESP32 con `ADC.read_u16()`, attenuazione a 11 dB e configurazione a 12 bit. Nessuna libreria esterna o installazione con pip.

## Percorso pratico guidato

1. A scheda scollegata, collega estremi del primo potenziometro a 3V3 e GND, cursore a GPIO 34. Identifica i terminali sul componente reale.
2. Esegui la lettura: ruota lentamente, annotando minimo, massimo e valori intermedi. Non pretendere che metà corsa corrisponda esattamente al codice 2048.
3. Passa alla scala percentuale. Confronta la percentuale del codice ADC con la posizione della manopola e spiega perché non è una misura calibrata di tensione.
4. Su hardware, misura il cursore rispetto a GND in almeno cinque posizioni. Compila la tabella della guida 02; osserva eventuali tratti in cui la tensione cambia ma il codice resta al massimo.
5. Esegui la media a blocchi. Confronta ultimo campione, media, minimo e massimo. Nel simulatore il segnale può essere ideale e privo di rumore visibile.
6. Aggiungi il secondo potenziometro sul GPIO 35 e il LED sul GPIO 18 con 220 Ω. Mantieni fermo il secondo e supera lentamente il limite alto con il primo; poi scendi sotto quello basso.
7. Mantieni fermo il segnale e modifica la soglia: anche questo può cambiare lo stato dell'allarme. Prova entrambi gli estremi della regolazione.

## Attività autonoma conclusiva

**Consegna:** integra la media a blocchi di otto campioni del segnale con il comparatore a isteresi. Leggi entrambi i potenziometri ogni 20 ms, ma valuta l'allarme soltanto al completamento del blocco, usando la media del segnale e l'ultima regolazione della soglia. Mantieni il LED invariato fra due blocchi.

**Risultato atteso:** prima decisione dopo otto campioni, circa 160 ms dall'avvio; una decisione per blocco, con semibanda di 100 codici e stato iniziale spento. Non riempire il primo blocco con zeri fittizi. La maggiore stabilità va confrontata con il ritardo introdotto; il filtro non corregge saturazione o errori di calibrazione.

Consegna i due programmi, circuito, tabella delle soglie e prove su segnale costante, gradino, oscillazione nella banda e regolazione ai due estremi.

## Verifica dell'apprendimento

Spiega perché `read_u16()` non implica un ADC fisico a 16 bit, perché più campioni non garantiscono più accuratezza e perché l'isteresi conserva uno stato precedente. Indica sempre unità, intervallo di campionamento e configurazione ADC nella relazione.

## Stato dei materiali e delle prove

Guide, sorgenti e diagrammi sono disponibili per i due linguaggi. **Compilazione con core ESP32, prove Wokwi e collaudo su hardware: da eseguire.** I controlli sul computer con API sostituite verificano la logica, non il convertitore, il rumore o la calibrazione del dispositivo. Ogni esempio offre una tabella per registrare le prove effettive.

Controlli sul computer del **15 ottobre 2026**: sintassi dei quattro programmi Python, compilazione dei quattro sketch con g++ e API sostituite senza avvisi, otto diagrammi JSON e collegamenti dei nuovi materiali. Ventisei scenari sono stati eseguiti nei due linguaggi sia con contatore ordinario sia attraverso il ritorno a zero: **104 esecuzioni superate**, con acquisizioni, uscite e messaggi coincidenti nel modello. I casi comprendono estremi della scala, troncamento, blocchi incompleti, variazioni fra blocchi, ritardi del ciclo, uguaglianze sulle soglie, memoria nella banda e variazione della sola regolazione. È stata controllata anche la normalizzazione di tutti i 4096 codici nel modello. Il test C++ usa la larghezza nativa di `unsigned long` del computer; non emula la CPU o l'ADC ESP32.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [⬅️ Esercitazione precedente](../04-Tempo-e-macchine-a-stati/README.md)
- La prossima esercitazione, “PWM e attuatori”, è pianificata e non ancora disponibile.
- [➡️ Prossima esercitazione disponibile: 07 · Sensori e display I²C](../07-Sensori-e-display-I2C/README.md)
