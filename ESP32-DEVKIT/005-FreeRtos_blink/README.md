# FreeRTOS · Due task per due LED

## Introduzione teorica

FreeRTOS pianifica più attività: ogni task ha una propria funzione e un proprio stack. Sull’ESP32 classico a due core si può assegnare un task a un core con `xTaskCreatePinnedToCore()`. Le pause consentono allo scheduler di eseguire altre attività; due task non diventano automaticamente sincronizzati.


### Task, scheduler e attese

Lo **scheduler** sceglie quali task pronti eseguire in base a priorità e disponibilità dei core. Un task può essere in esecuzione, pronto oppure bloccato in attesa di un evento o di una temporizzazione. In Arduino-ESP32 una pausa con `delay()` sospende il task che la chiama e lascia tempo alle altre attività; un ciclo che controlla continuamente il tempo senza sospendersi occupa invece la CPU.

La **concorrenza** permette a più attività di progredire nello stesso intervallo. Con due core è possibile anche l’esecuzione in parallelo. Assegnare i task a core distinti non garantisce che i loro comandi inizino nello stesso istante: nello sketch i task vengono creati in momenti diversi.

Ogni task conserva le proprie variabili locali nello stack; variabili globali e periferiche possono essere condivise. Se più task modificano lo stesso dato o usano una risorsa comune, occorre coordinarli, per esempio con **mutex** o **code**. In questa prova ogni task comanda un LED diverso, mentre entrambi scrivono sulla seriale.

### Collegamento con lo sketch

`xTaskCreatePinnedToCore()` specifica funzione, nome, dimensione dello stack, parametro, priorità, handle e core. I due task hanno priorità 1; il valore 10000 indica byte di stack nell’implementazione ESP-IDF. Le funzioni dei task contengono un ciclo infinito perché devono continuare a eseguire la propria attività. I ritardi sono relativi alla chiamata: il periodo comprende anche il tempo delle istruzioni e non costituisce una temporizzazione precisa.

### Cambio di contesto e priorità

Quando cambia il task in esecuzione, il sistema salva il contesto necessario per riprenderlo e ripristina quello del successivo. Per il programmatore ogni funzione prosegue dal proprio punto, ma nel frattempo altri task possono aver modificato dati condivisi o usato una periferica.

La priorità influenza quale task pronto possa usare un core, tenendo conto dell’affinità. Un task ad alta priorità che rimane sempre pronto può sottrarre tempo a task meno prioritari. Alzare la priorità non rende più accurato un algoritmo che usa ritardi relativi: occorre prima capire quali attività attendono e quali occupano la CPU. Le regole effettive della pianificazione su due core sono descritte da [Espressif per IDF FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/freertos_idf.html).

### Tick, periodo e jitter

Il sistema usa un riferimento temporale a tick. La conversione fra millisecondi e tick e il momento in cui il task viene nuovamente eseguito introducono una granularità; il task può inoltre trovare il core occupato. La variazione fra istante desiderato e istante effettivo prende il nome di **jitter**.

Considera un’attività che impiega 8 ms per leggere ed elaborare, poi attende 100 ms: il periodo sarà circa 108 ms più gli altri ritardi. Per un’attività periodica si può invece mantenere una sequenza di scadenze assolute tramite `vTaskDelayUntil()`, convertendo l’intervallo con `pdMS_TO_TICKS()`. Se il lavoro supera il periodo richiesto, anche questo approccio richiede una politica per gestire il ritardo. Questa è un’estensione rispetto ai `delay()` dello sketch.

### Condivisione dei dati: perché un incremento può fallire

L’istruzione `contatore++` sembra unica nel sorgente, ma comprende lettura, calcolo e scrittura. Se due task leggono entrambi 10 prima di scrivere, possono produrre entrambi 11: un aggiornamento viene perso. La correttezza dipende dalle operazioni e dalla sincronizzazione, anche quando il tipo di dato può essere letto con una singola istruzione.

| Strumento | Uso tipico |
| --- | --- |
| Mutex | Consentire a un task alla volta di usare una risorsa condivisa |
| Coda | Trasferire valori o richieste fra produttore e consumatore |
| Semaforo o notifica | Segnalare un evento o la disponibilità di una risorsa |

`volatile` non rende atomica una sequenza di operazioni e non sostituisce questi strumenti. Per una schermata aggiornata da più attività, un possibile progetto assegna il display a un solo task: gli altri gli inviano i valori da mostrare tramite una coda. Nel Blink ogni task possiede invece un GPIO distinto, il che semplifica il controllo dei LED.

### Risorse e scelta della struttura

Ogni task richiede memoria per stack e strutture di gestione. Uno stack insufficiente può compromettere il programma, mentre crearne molti con stack sovradimensionati consuma memoria disponibile per dati e librerie. Il risultato della creazione va controllato, e il dimensionamento va valutato sul programma effettivo.

Per due lampeggi basta anche un solo loop con due timer a `millis()`. FreeRTOS diventa utile quando separare responsabilità, attese e scambi di messaggi rende il progetto più comprensibile. Il confronto didattico consiste nel riconoscere ciò che rimane uguale — stati dei LED e intervalli — e ciò che cambia: pianificazione, consumo di memoria e coordinamento delle attività.

## Circuito e avvio

Usa ESP32 WROOM-32 **dual core**, due LED e due resistenze da **220 Ω**: GPIO 2 → resistenza → anodo LED 1, GPIO 4 → resistenza → anodo LED 2; catodi a GND. Il LED integrato su 2, se presente, può sostituire il primo esterno.

Apri [005-FreeRtos_blink.ino](005-FreeRtos_blink.ino), seleziona la scheda con core esp32 by Espressif Systems e carica. Non servono librerie aggiuntive. Apri il monitor a **115200 baud**.

## Risultato atteso

- Task1 sul core 0: LED 1 acceso 300 ms e spento 1700 ms, periodo nominale 2 s.
- Task2 sul core 1: LED 2 acceso 700 ms e spento 700 ms, periodo nominale **1,4 s**.
- La seriale riporta core e iterazioni. I task vengono creati con 500 ms di distanza e i messaggi possono intercalarsi.

Il `loop()` è vuoto perché le attività risiedono nei task. I tempi includono il costo del codice e non sono una misura di precisione. Il programma attuale non controlla il risultato della creazione dei task; non presumere che entrambi siano partiti se mancano messaggi. Non usare invariato su un ESP32 single core.

## Esercizi

1. Calcola il duty di ciascun lampeggio e verifica il periodo con un analizzatore logico.
2. Assegna entrambi i task allo stesso core e osserva la pianificazione.
3. Controlla il valore restituito dalla creazione dei task e stampa un errore se fallisce.
4. Aggiungi una risorsa condivisa e proteggila con un mutex, motivandone l’uso.

Documentazione aggiunta tramite lettura del codice; compilazione e prove sulla scheda da eseguire. [Espressif: FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/freertos_idf.html).

[Indice ESP32-DEVKIT](../README.md).
