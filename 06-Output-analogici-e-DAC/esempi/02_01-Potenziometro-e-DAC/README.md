# Potenziometro e DAC

## Obiettivo e prerequisiti

Leggere il potenziometro ogni 20 ms nominali e trasformare il codice ADC 0–4095 in un codice DAC 0–255. Leggi la [guida associata](../../02-DAC-e-regolazione-della-tensione.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).

Nessuna libreria esterna o pacchetto pip. C++: core Arduino-ESP32 **3.x**. MicroPython: firmware per ESP32 classico con DAC, PWM.duty_u16 e ADC.read_u16 secondo l’esempio. Registra le versioni effettive. La scheda di riferimento è DOIT ESP32 DEVKIT V1 con modulo WROOM-32, non ESP32-C3 o S3.

## Materiali e collegamenti

Scheda, potenziometro lineare da 10 kΩ e multimetro. GPIO 25 e GPIO 34 non vanno collegati fra loro.

Monta a scheda scollegata e usa massa comune. I numeri sono GPIO, non posizioni fisiche dei terminali. Il DAC è un’uscita di segnale: non deve alimentare carichi di potenza. Non applicare 5 V ai pin.

| Da | A |
| --- | --- |
| Potenziometro VCC / GND | 3V3 / GND |
| Potenziometro SIG | GPIO 34 |
| GPIO 25 | Puntale rosso del tester DC |
| GND | Puntale nero del tester |

## Esecuzione in Wokwi

I diagrammi forniti sono una traccia del cablaggio. La tabella Wokwi ESP32 non dichiara il DAC: non usare questo progetto per validare la tensione o ascoltare l’audio DAC. Esegui la prova completa sulla scheda reale. Il componente testo descrive il tester ma non ne simula uno; eventuali messaggi seriali non attestano un’uscita analogica simulata.

## Esecuzione sulla scheda reale

1. C++: apri cpp/cpp.ino in Arduino IDE, seleziona DOIT ESP32 DEVKIT V1 e porta, compila e carica. Lo sketch resta nella cartella cpp, coerente con il nome del file.
2. MicroPython: in Thonny seleziona interprete e porta ESP32; copia main.py nella radice della scheda, poi riavvia.
3. Apri la console UART0 a 115200 baud per C++, oppure la console MicroPython. Segui le prove prima di modificare il circuito.
4. Prima di spostare i componenti spegni la scheda. Per arrestare definitivamente l’uscita, considera anche il riavvio del programma e l’alimentazione del circuito.

## Prova guidata e risultato atteso

1. Avvia: il DAC parte da 0; la prima acquisizione arriva dopo circa 20 ms.
2. Ogni 200 ms circa compare `ADC=n DAC=m`. Ruota lentamente il potenziometro.
3. Controlla la formula `m = n × 255 / 4095`, con divisione intera. Per 0, 2048, 4095 sono attesi 0, 127, 255.
4. Misura separatamente cursore e uscita DAC in cinque posizioni; annota la saturazione eventualmente presente nell’ADC.

## Come funziona e limiti

L’uscita conserva il codice fra due campioni. L’attenuazione a 11 dB non protegge il pin da sovratensioni. La riscalatura dei codici non realizza un inseguitore di tensione calibrato. La stampa è meno frequente dell’acquisizione e non genera campioni aggiuntivi.

## Modifica autonoma

Aggiungi l’arrotondamento al più vicino e confronta il codice centrale con quello ottenuto per troncamento.

## Stato delle prove

Compilazione con core ESP32, runtime MicroPython e collaudo hardware sono **da eseguire**. Le prove Wokwi sono da eseguire per il PWM; per il DAC non si assume il supporto del simulatore. I controlli locali con API sostituite verificano soltanto il comportamento del programma.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell’esercitazione](../../README.md)
- [📖 Guida associata](../../02-DAC-e-regolazione-della-tensione.md)
