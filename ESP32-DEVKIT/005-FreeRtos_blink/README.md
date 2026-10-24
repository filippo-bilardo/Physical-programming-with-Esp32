# FreeRTOS · Due task per due LED

FreeRTOS pianifica più attività: ogni task ha una propria funzione e un proprio stack. Sull’ESP32 classico a due core si può assegnare un task a un core con `xTaskCreatePinnedToCore()`. Le pause consentono allo scheduler di eseguire altre attività; due task non diventano automaticamente sincronizzati.

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
