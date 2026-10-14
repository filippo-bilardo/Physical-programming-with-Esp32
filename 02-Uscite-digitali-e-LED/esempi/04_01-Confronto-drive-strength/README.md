# Confronto del drive strength con un LED

## Obiettivo e prerequisiti

Osservare in sequenza i livelli di pilotaggio 5, 10, 20 e 40 mA richiesti al GPIO 18, mantenendo una resistenza limitatrice da 220 Ω in serie al LED. Leggi la [guida al drive strength](../../04-Drive-strength-dei-GPIO.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Programma C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Programma MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: Arduino-ESP32, con `driver/gpio.h` incluso nel core.
- MicroPython: firmware ESP32 con `machine.Pin.DRIVE_0`, `DRIVE_1`, `DRIVE_2` e `DRIVE_3`.
- Nessuna libreria esterna.

## Collegamento nel simulatore

Collega GPIO 18 → resistenza da **220 Ω** → anodo del LED; collega il catodo a GND. Il diagramma Wokwi include già la resistenza. Usala anche su hardware: il drive strength non limita né regola la corrente e non sostituisce la resistenza. Senza resistenza, le variazioni della curva del LED e del GPIO potrebbero causare una corrente eccessiva e danneggiare LED o scheda.

## Esecuzione in Wokwi

1. Apri un modello ESP32 Arduino o MicroPython dalla [guida ufficiale Wokwi](https://docs.wokwi.com/guides/esp32).
2. Copia il file `cpp/cpp.ino` in `sketch.ino`, oppure sostituisci `main.py` con il programma MicroPython.
3. Sostituisci `diagram.json` con quello della stessa versione.
4. Avvia la simulazione e osserva le etichette sulla console e il lampeggio virtuale.

La prova mostra l’ordine delle impostazioni richieste. Il simulatore non fornisce una misura valida della corrente del GPIO o del LED; le etichette riportano stime di calcolo, non misure.

## Sequenza guidata e risultato atteso

1. Osserva le fasi con stime di circa 3,7, 4,6, 5,2 e 5,5 mA nel LED per drive 5, 10, 20 e 40 mA.
2. Ogni fase dura circa 5 s accesa e 1 s spenta.
3. L’intera sequenza dura 24 s e poi ricomincia.

Le stime assumono alimentazione 3,3 V, LED rosso con caduta di circa 2 V, resistenza esterna da 220 Ω e resistenze interne approssimate di 130, 60, 30 e 15 Ω. I valori 5, 10, 20 e 40 mA identificano le classi di pilotaggio selezionate, non la corrente erogata al LED: DRIVE_3 non impone 40 mA. Le correnti stimate non sono misurate e possono variare con il componente e la scheda. Per una misura reale, misura la tensione ai capi della resistenza e calcola `I = V/220 Ω`.

## Parti principali e confronto dei linguaggi

Il C++ usa quattro blocchi di chiamate dirette, senza array, condizioni o funzioni aggiuntive. `loop()` viene ripetuto da Arduino. MicroPython usa una tupla con i quattro livelli e un ciclo `for`; le due versioni mostrano lo stesso ordine e gli stessi tempi.

Il programma invia una richiesta di configurazione al GPIO e stampa un’etichetta con una stima. Non rileva se la configurazione è stata accettata e non misura la corrente.

## Modifica autonoma

Inverti l’ordine delle fasi C++ oppure delle tuple MicroPython. Verifica in Wokwi il nuovo ordine delle etichette; la durata complessiva deve restare 24 s.

## Debug e stato delle verifiche

Se il LED non si accende, controlla polarità, GND, resistenza da 220 Ω e GPIO 18 nel diagramma. Se MicroPython non riconosce una costante `DRIVE_0`–`DRIVE_3`, verifica che il firmware ESP32 scelto la supporti.

**Esecuzione Wokwi: da verificare per entrambe le versioni.** Per il collaudo su scheda reale conserva sempre la resistenza in serie.

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell’esercitazione](../README.md)
- [📖 Guida associata](../../04-Drive-strength-dei-GPIO.md)
