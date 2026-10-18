# Buzzer con PWM

## Obiettivo e prerequisiti

Riprodurre un tono a 440 Hz per un secondo, seguito da un secondo di silenzio, usando un timer hardware. Leggi la [guida associata](../../03-Buzzer-passivo-e-PWM.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).

Nessuna libreria esterna o pacchetto pip. C++: core Arduino-ESP32 **3.x**. MicroPython: firmware per ESP32 classico con DAC, PWM.duty_u16 e ADC.read_u16 secondo l’esempio. Registra le versioni effettive. La scheda di riferimento è DOIT ESP32 DEVKIT V1 con modulo WROOM-32, non ESP32-C3 o S3.

## Materiali e collegamenti

Scheda, piccolo piezo passivo ad alta impedenza e resistenza da 1 kΩ. Il buzzer attivo non è adatto alla scelta delle note; un altoparlante da 8 Ω richiede un amplificatore.

Monta a scheda scollegata e usa massa comune. I numeri sono GPIO, non posizioni fisiche dei terminali. Il DAC è un’uscita di segnale: non deve alimentare carichi di potenza. Non applicare 5 V ai pin.

| Da | A |
| --- | --- |
| GPIO 18 | Resistenza 1 kΩ |
| Altro capo della resistenza | Positivo piezo, pin 2 in Wokwi |
| Negativo piezo, pin 1 in Wokwi | GND |

## Esecuzione in Wokwi

1. Apri il modello ESP32 Arduino o MicroPython dalla [guida Wokwi](https://docs.wokwi.com/guides/esp32).
2. C++: copia cpp.ino in sketch.ino e usa un ambiente con Arduino-ESP32 3.x; MicroPython: copia main.py.
3. Copia diagram.json dalla stessa sottocartella. Il monitor è su UART0; il buzzer è sul GPIO 18.
4. Avvia, abilita l’audio della scheda del browser e segui la prova guidata. Il diagramma imposta un volume ridotto; il volume non è una misura elettrica.
5. Se ledcAttach non è riconosciuta, verifica la versione del core C++; non mescolare firme LEDC 2.x e 3.x.

## Esecuzione sulla scheda reale

1. C++: apri cpp/cpp.ino in Arduino IDE, seleziona DOIT ESP32 DEVKIT V1 e porta, compila e carica. Lo sketch resta nella cartella cpp, coerente con il nome del file.
2. MicroPython: in Thonny seleziona interprete e porta ESP32; copia main.py nella radice della scheda, poi riavvia.
3. Apri la console UART0 a 115200 baud per C++, oppure la console MicroPython. Segui le prove prima di modificare il circuito.
4. Prima di spostare i componenti spegni la scheda. Per arrestare definitivamente l’uscita, considera anche il riavvio del programma e l’alimentazione del circuito.

## Prova guidata e risultato atteso

1. Avvia: compare `TONE=440` e si sente un tono per circa un secondo.
2. Compare `TONE=0`: il tono si arresta per un secondo.
3. L’alternanza riparte. In MicroPython interrompi con Ctrl+C: il finally disattiva il PWM.
4. Sostituisci 440 con 880 in tutti i punti che avviano il tono e confronta l’altezza.

## Come funziona e limiti

C++ usa ledcAttach e ledcWriteTone dell’API 3.x; l’errore di inizializzazione o avvio del tono produce ERR PWM e arresta la sequenza. MicroPython usa duty_u16 al 50% circa o zero; non chiama freq(0). Il timer genera i cicli anche fra due passaggi del programma. Un ritardo del ciclo può allungare uno stato.

## Modifica autonoma

Riproduci 200 ms di suono e 800 ms di silenzio scegliendo la durata in base allo stato, senza lunghe attese.

## Stato delle prove

Compilazione con core ESP32, runtime MicroPython e collaudo hardware sono **da eseguire**. Le prove Wokwi sono da eseguire per il PWM; per il DAC non si assume il supporto del simulatore. I controlli locali con API sostituite verificano soltanto il comportamento del programma.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell’esercitazione](../../README.md)
- [📖 Guida associata](../../03-Buzzer-passivo-e-PWM.md)
