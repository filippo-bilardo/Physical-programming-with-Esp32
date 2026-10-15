# Due temporizzazioni indipendenti

## Obiettivo e prerequisiti

Far cambiare il rosso ogni 250 ms e il giallo ogni 700 ms mediante due riferimenti temporali indipendenti. Leggi la [guida associata](../../02-Temporizzazioni-indipendenti.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Programma C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Programma MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: core Arduino-ESP32 e API Arduino di base, nessuna libreria esterna.
- MicroPython: firmware per ESP32-WROOM-32, moduli `machine` e `time` inclusi; nessun pacchetto pip.

## Materiali e collegamenti

ESP32 DOIT ESP32 DEVKIT V1 o DevKit equivalente con ESP32-WROOM-32, cavo USB dati, 2 LED e **2 resistenze da 220 Ω**, breadboard e cavetti.

Monta a scheda scollegata. I numeri sono GPIO, non posizioni fisiche dei terminali. Ogni LED ha una propria resistenza; usa logica a 3,3 V e massa comune.

| Da | A |
| --- | --- |
| GPIO 18 | R1 da 220 Ω → anodo LED rosso |
| Catodo LED rosso | GND |
| GPIO 19 | R2 da 220 Ω → anodo LED giallo |
| Catodo LED giallo | GND |

Questo esempio non usa il pulsante; non occorrono altri componenti.

## Esecuzione in Wokwi

1. Apri un progetto Arduino ESP32 o MicroPython ESP32 dalla [guida ufficiale](https://docs.wokwi.com/guides/esp32).
2. Per C++ sostituisci `sketch.ino` con il contenuto di `cpp/cpp.ino`; per MicroPython sostituisci `main.py` con quello fornito.
3. Sostituisci `diagram.json` con quello della stessa sottocartella. Non mantenere due sketch con le stesse funzioni.
4. Avvia e segui la prova guidata. Non servono `libraries.txt` o moduli aggiuntivi.

## Esecuzione su scheda reale

1. Controlla collegamenti, resistenze e polarità prima di collegare l'USB.
2. **C++:** apri `cpp/cpp.ino` in Arduino IDE; seleziona **DOIT ESP32 DEVKIT V1** per la scheda di riferimento, porta e core ESP32 installato. Compila e carica mantenendo lo sketch nella cartella `cpp`. L'esempio non stampa sulla seriale: osserva i LED.
3. **MicroPython:** seleziona l'interprete ESP32 e la porta in Thonny; salva il programma come `/main.py` sulla scheda e riavvia. Ctrl+C interrompe il ciclo e restituisce la console.
4. Registra le versioni effettive di core o firmware. I programmi usano API di base; la compilazione sul computer con sostituti delle API non equivale a quella per ESP32.

## Prova guidata e risultato atteso

1. Riavvia: entrambi i LED partono spenti.
2. Il rosso cambia per la prima volta dopo circa 250 ms; il giallo dopo circa 700 ms.
3. Osserva almeno 5 s: i periodi completi nominali sono 500 ms e 1400 ms.
4. Cambia solo `RED_INTERVAL_MS` a 100 e riavvia: il giallo mantiene il proprio ritmo.

Nel modello ideale, a 3500 ms scadono entrambi gli intervalli: entrambi i controlli vengono eseguiti. Non sono garantiti allineamenti precisi sul dispositivo, perché il programma aggiorna ciascun riferimento all'istante osservato.

## Come funziona e confronto dei linguaggi

Due variabili ricordano gli ultimi cambiamenti e due conservano i livelli. I due `if` separati permettono di eseguire entrambe le azioni nello stesso giro; non sostituirli con `else if` / `elif`. La pausa finale è di 1 ms. Non sono usati due task o due interrupt.

## Modifica autonoma

Imposta entrambi gli intervalli a 500 ms e riavvia. I LED devono cambiare nello stesso giro del modello; poi ripristina gli intervalli originali.

## Debug e stato delle prove

Se il LED non si accende, controlla GPIO, polarità, resistenza e GND. Non eseguire `main.py` con Python del computer: richiede MicroPython ESP32.

**Wokwi e scheda reale: da verificare separatamente per C++ e MicroPython.** Un controllo della logica con GPIO e tempo simulati sul computer non prova montaggio o precisione temporale sul dispositivo.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Risultato osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell'esercitazione](../../README.md)
- [📖 Guida associata](../../02-Temporizzazioni-indipendenti.md)
