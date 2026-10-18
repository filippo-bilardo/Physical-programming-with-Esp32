# Audio con DAC

## Obiettivo e prerequisiti

Produrre audio dal vero DAC mediante una tabella di otto campioni, confrontando gradini analogici e tono PWM. Leggi la [guida associata](../../04-Melodie-e-audio-con-DAC.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).

Nessuna libreria esterna o pacchetto pip. C++: core Arduino-ESP32 **3.x**. MicroPython: firmware per ESP32 classico con DAC, PWM.duty_u16 e ADC.read_u16 secondo l’esempio. Registra le versioni effettive. La scheda di riferimento è DOIT ESP32 DEVKIT V1 con modulo WROOM-32, non ESP32-C3 o S3.

## Materiali e collegamenti

Scheda ESP32 classico, piccolo piezo passivo ad alta impedenza e resistenza da 1 kΩ. Per questa prova il ramo resistenza/piezo va sul GPIO 25, lasciando libero GPIO 18. Non collegare cuffie o altoparlanti direttamente al DAC.

Monta a scheda scollegata e usa massa comune. I numeri sono GPIO, non posizioni fisiche dei terminali. Il DAC è un’uscita di segnale: non deve alimentare carichi di potenza. Non applicare 5 V ai pin.

| Da | A |
| --- | --- |
| GPIO 25, DAC1 | Resistenza 1 kΩ |
| Altro capo della resistenza | Positivo piezo, pin 2 nel diagramma |
| Negativo piezo, pin 1 nel diagramma | GND |
| Sonda oscilloscopio, facoltativa | GPIO 25, massa a GND |

## Esecuzione in Wokwi

I diagrammi forniti sono una traccia del cablaggio. La tabella Wokwi ESP32 non dichiara il DAC: non usare questo progetto per validare la tensione o ascoltare l’audio DAC. Esegui la prova completa sulla scheda reale. Il componente testo descrive il tester ma non ne simula uno; eventuali messaggi seriali non attestano un’uscita analogica simulata.

## Esecuzione sulla scheda reale

1. C++: apri cpp/cpp.ino in Arduino IDE, seleziona DOIT ESP32 DEVKIT V1 e porta, compila e carica. Lo sketch resta nella cartella cpp, coerente con il nome del file.
2. MicroPython: in Thonny seleziona interprete e porta ESP32; copia main.py nella radice della scheda, poi riavvia.
3. Apri la console UART0 a 115200 baud per C++, oppure la console MicroPython. Segui le prove prima di modificare il circuito.
4. Prima di spostare i componenti spegni la scheda. Per arrestare definitivamente l’uscita, considera anche il riavvio del programma e l’alimentazione del circuito.

## Prova guidata e risultato atteso

1. All’avvio il DAC viene posto a 128; compare `AUDIO DAC: 500 periodi`.
2. Il programma ripete i campioni 128, 173, 192, 173, 128, 83, 64, 83, attendendo 250 µs dopo ogni scrittura.
3. Ogni venti periodi cede 1 ms al sistema. Dopo 500 periodi pone il DAC a 128 e stampa `PAUSA DAC`.
4. Mantiene il livello per un secondo, poi riparte. Il suono può essere debole e presentare clic o modulazioni.
5. Se disponibile, misura la forma a gradini e gli intervalli. Confronta C++ e MicroPython senza assumere uguali frequenze effettive.

## Come funziona e limiti

Otto attese da 250 µs suggeriscono 500 Hz soltanto ignorando esecuzione e pause. Il blocco sonoro comprende 1000 ms di attese fra campioni più 25 ms di yield, oltre al tempo del codice. Non garantisce né 500 Hz né un secondo esatto. Il ciclo applicativo resta occupato durante la generazione. Il codice 128 nella pausa è un livello intermedio costante, non zero volt. Non ci sono filtro di ricostruzione, amplificatore, file audio o DMA. La sinusoide è solo approssimata e il carico del piezo influenza l’uscita.

## Modifica autonoma

Raddoppia l’attesa fra campioni e confronta il tono; registra periodo reale e discontinuità anziché attribuire al software una frequenza esatta.

## Stato delle prove

Compilazione con core ESP32, runtime MicroPython e collaudo hardware sono **da eseguire**. Le prove Wokwi sono da eseguire per il PWM; per il DAC non si assume il supporto del simulatore. I controlli locali con API sostituite verificano soltanto il comportamento del programma.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell’esercitazione](../../README.md)
- [📖 Guida associata](../../04-Melodie-e-audio-con-DAC.md)
