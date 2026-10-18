# Cinque livelli DAC

## Obiettivo e prerequisiti

Impostare cinque codici sul DAC e misurare la tensione, distinguendo valore comandato e valore reale. Leggi la [guida associata](../../01-Uscite-analogiche-PWM-e-DAC.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).

Nessuna libreria esterna o pacchetto pip. C++: core Arduino-ESP32 **3.x**. MicroPython: firmware per ESP32 classico con DAC, PWM.duty_u16 e ADC.read_u16 secondo l’esempio. Registra le versioni effettive. La scheda di riferimento è DOIT ESP32 DEVKIT V1 con modulo WROOM-32, non ESP32-C3 o S3.

## Materiali e collegamenti

Scheda, cavo USB dati e multimetro ad alta impedenza. Non collegare un carico al DAC per questa prima misura.

Monta a scheda scollegata e usa massa comune. I numeri sono GPIO, non posizioni fisiche dei terminali. Il DAC è un’uscita di segnale: non deve alimentare carichi di potenza. Non applicare 5 V ai pin.

| Da | A |
| --- | --- |
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

1. Avvia: viene richiesto il codice 0 e compare `DAC=0`.
2. Ogni due secondi compaiono 64, 128, 192, 255, poi di nuovo 0.
3. Misura ogni livello. La scala ideale didattica è `3,3 × codice / 255`; annota separatamente il valore reale.
4. Ripeti con l’altro linguaggio mantenendo invariato il circuito.

## Come funziona e limiti

Il DAC mantiene l’ultimo livello fra due scritture. Il ciclo usa il tempo trascorso e una pausa di 1 ms per giro; in caso di ritardo avanza di un solo livello, senza recuperare i livelli saltati. La prima uscita è 0 all’avvio. I codici seriali non sono una lettura del tester.

## Modifica autonoma

Aggiungi i livelli 32 e 224. Aggiorna il limite dell’indice C++ e verifica il ritorno al primo elemento.

## Stato delle prove

Compilazione con core ESP32, runtime MicroPython e collaudo hardware sono **da eseguire**. Le prove Wokwi sono da eseguire per il PWM; per il DAC non si assume il supporto del simulatore. I controlli locali con API sostituite verificano soltanto il comportamento del programma.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell’esercitazione](../../README.md)
- [📖 Guida associata](../../01-Uscite-analogiche-PWM-e-DAC.md)
