# Confronto del drive strength con un LED

## Obiettivo e prerequisiti

Configurare in sequenza i quattro livelli di pilotaggio del GPIO 18, mantenendo lo stesso circuito. Leggi la [guida al drive strength](../../04-Drive-strength-dei-GPIO.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Programma C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Programma MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: Arduino IDE 2.x, pacchetto **esp32 by Espressif Systems**, ramo 3.x. `driver/gpio.h` ed `esp_err.h` sono inclusi nel core: non installare librerie omonime dal gestore librerie.
- MicroPython: firmware ESP32_GENERIC, riferimento di compatibilità 1.24 o successivo, moduli integrati `machine` e `time`. La presenza del parametro è verificabile anche nel [sorgente ESP32 di MicroPython 1.24.1](https://github.com/micropython/micropython/blob/v1.24.1/ports/esp32/machine_pin.c). Nessun pacchetto pip.

Questi riferimenti non dichiarano un collaudo sul dispositivo. Annota le versioni effettive usate nella tua prova.

## Materiali e collegamenti

ESP32 classico su DOIT ESP32 DEVKIT V1 con modulo WROOM, cavo USB dati, breadboard, cavetti, LED rosso, resistenza da 330 Ω (1/4 W). Per il confronto: una resistenza da 1 kΩ. Per misurare: multimetro in tensione continua.

| Da | A |
| --- | --- |
| GPIO 18 (`D18` nel diagramma) | Resistenza da 330 Ω → anodo A del LED |
| Catodo C del LED | GND |

Monta a scheda scollegata. Mantieni sempre la resistenza in serie e non applicare 5 V al GPIO. Il drive strength non sostituisce la limitazione di corrente esterna.

## Esecuzione in Wokwi

1. Apri il modello Arduino ESP32 oppure MicroPython ESP32 dalla [guida ufficiale Wokwi](https://docs.wokwi.com/guides/esp32).
2. Per Arduino copia `cpp/cpp.ino` in `sketch.ino`; per MicroPython sostituisci `main.py` con il file fornito.
3. Sostituisci `diagram.json` con quello della stessa versione. Non servono librerie aggiuntive.
4. Avvia e osserva le etichette nella console e le fasi acceso/spento.

La prova in Wokwi riguarda il flusso del programma. **L’effetto elettrico del drive strength non è validato da questo circuito simulato**: non aspettarti differenze di luminosità o corrente fedeli alla scheda reale. Se il runtime del modello non supporta l’API, registra l’errore e prova su un firmware ESP32 compatibile; non rimuovere silenziosamente la configurazione e dichiarare riuscita la prova.

## Esecuzione sulla DOIT ESP32 DEVKIT V1

1. Controlla il circuito e collega il cavo USB dati.
2. **C++:** apri `cpp/cpp.ino` in Arduino IDE; seleziona **DOIT ESP32 DEVKIT V1** dal pacchetto Espressif e la porta seriale. Compila, carica e apri il monitor a **115200 baud**. Per la preparazione completa usa la [guida Arduino IDE](../../../01-Introduzione-ESP32/04-Arduino-IDE-e-DOIT-DevKit-V1.md).
3. **MicroPython:** seleziona l’interprete ESP32 e la porta in Thonny, trasferisci il file come `/main.py` sul dispositivo e riavvia. Chiudi prima le altre console sulla stessa porta.
4. Osserva un giro completo prima di misurare. Per avere più tempo aumenta `ON_MS` a 10000 in entrambe le versioni.

## Prova guidata e risultato atteso

1. Leggi `DRIVE_0`: il LED resta acceso circa 5 s, poi spento circa 1 s.
2. Seguono DRIVE_1, DRIVE_2 e DRIVE_3 con gli stessi tempi; il ciclo ricomincia. Il periodo nominale dell’intera sequenza è 24 s.
3. Su hardware collega il multimetro **in modalità tensione continua ai due capi della resistenza**. Durante una fase accesa annota la tensione e l’etichetta mostrata.
4. Ripeti per tutti i livelli e calcola la corrente: `I_mA = 1000 × V_R / R_ohm`.
5. Scollega alimentazione, sostituisci 330 Ω con 1 kΩ e ripeti. Non cambiare il multimetro in modalità corrente fra GPIO e massa.

| Drive | R esterna (Ω) | Tensione sulla resistenza (V) | Corrente calcolata (mA) | Osservazioni |
| --- | --- | --- | --- | --- |
| 0 | 330 | Da misurare | Da calcolare | — |
| 1 | 330 | Da misurare | Da calcolare | — |
| 2 | 330 | Da misurare | Da calcolare | — |
| 3 | 330 | Da misurare | Da calcolare | — |

**Risultato atteso:** ordine e temporizzazione uguali nei due linguaggi. Su hardware il pilotaggio può influenzare tensione e corrente sotto carico, ma il LED resta limitato dalla resistenza esterna. La differenza visiva può essere piccola; le etichette non rappresentano misure di corrente.

## Parti principali e confronto dei linguaggi

Le collezioni `DRIVE_LEVELS` e `LABELS` associano ciascuna impostazione a una scritta. Il ciclo spegne il LED, applica il livello, stampa la fase, accende per cinque secondi e introduce una pausa di un secondo.

In C++ `gpio_set_drive_capability` usa i tipi ESP-IDF e restituisce un codice verificato con `ESP_ERROR_CHECK`; un errore arresta il percorso normale e può provocare un riavvio secondo la configurazione del core. In MicroPython `led.init(drive=...)` aggiorna il parametro del Pin; gli errori di API vengono mostrati nella console. Il GPIO resta configurato come uscita in entrambe le versioni.

Il programma comanda il pilotaggio ma non misura tensioni o correnti: questo compito spetta al multimetro. Non usa PWM e non presume una regolazione lineare della luminosità.

## Modifica autonoma

Inverti l’ordine dei livelli e delle etichette, mantenendo tempi e circuito. Prevedi l’ordine delle stampe e verifica che il periodo resti 24 s. Poi confronta le misure con quelle raccolte nell’ordine crescente, senza dedurre la corrente dalla sola etichetta.

## Debug e stato delle verifiche

Se il LED non si accende controlla polarità, massa e GPIO 18. Se Arduino non trova `driver/gpio.h`, controlla che sia selezionata una scheda del core ESP32. Se MicroPython non riconosce `DRIVE_0` o `drive`, verifica il port e il firmware. Una luminosità apparentemente uguale non dimostra che la configurazione sia stata ignorata.

**Compilazione ESP32, esecuzione Wokwi e misure su scheda reale: da verificare in entrambe le versioni.** Il [rapporto delle verifiche](../../../VERIFICHE.md) documenta i controlli locali con API sostituite, che non modellano l’effetto elettrico.

## Navigazione del corso

- [📑 Indice generale](../../../../README.md)
- [📂 Indice dell’esercitazione](../../README.md)
- [📖 Guida associata](../../04-Drive-strength-dei-GPIO.md)
