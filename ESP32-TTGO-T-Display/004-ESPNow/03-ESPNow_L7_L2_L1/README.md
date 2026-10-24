# ESP-NOW · Livelli applicativi e code FreeRTOS

[03-ESPNow_L7_L2_L1.ino](03-ESPNow_L7_L2_L1.ino) avvia un esperimento di protocollo suddiviso in task denominati L7, L2 e L1. I nomi organizzano il programma didattico; non implementano un’intera pila di rete standard. Le code trasferiscono frame con sorgente, destinazione e dato.

## Preparazione

Segui la [guida TTGO ed ESP-NOW](../README.md), mantenendo tutti i file locali. In [NCP.h](NCP.h) assegna a ogni scheda un `BOARD_ADDRESS` diverso: il valore attuale è 3, mentre i pulsanti destinano eventi agli indirizzi logici 1 e 2. Usa solo schede con questo stesso formato di frame e sullo stesso canale radio.

I LED esterni sono su **GPIO 21 e 27**, ciascuno verso anodo tramite **220 Ω**, catodo a GND. Il drive strength configurato nel codice non limita la corrente e non sostituisce le resistenze. La seriale è a 115200 baud.

## Flusso da leggere nel codice

L7 genera eventi dai pulsanti. Il task L1 di trasmissione legge attualmente la coda L7 direttamente; parte del percorso L2 TX è commentata. In ricezione la callback accoda il frame, L2 filtra la destinazione e L7 aggiorna display e LED. La destinazione locale può essere inoltrata direttamente alla coda applicativa senza radio.

## Verifiche necessarie prima dell’esecuzione

Il codice crea i task prima delle code, non controlla tutte le allocazioni e usa un’attesa potenzialmente bloccante nella callback di ricezione, senza validare la lunghezza del frame. Prima delle prove crea le code prima dei task, controlla gli esiti, valida la lunghezza e usa un accodamento non bloccante con gestione della coda piena. Verifica anche le firme delle callback per il core scelto e serializza l’accesso condiviso al TFT.

## Esercizi

1. Disegna il percorso effettivo delle code, distinguendo collegamenti attivi e codice commentato.
2. Completa e verifica le inizializzazioni nell’ordine corretto.
3. Aggiungi un numero di sequenza e gestisci frame errati, coda piena e destinatario diverso.
4. Confronta invio locale e radio per un evento destinato alla stessa scheda.

Documentazione del materiale presente: il codice non è stato modificato, compilato o provato via radio in questa attività.

[Percorso ESP-NOW](../README.md).
