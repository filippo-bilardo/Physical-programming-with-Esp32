# Melodia con buzzer

## Obiettivo e prerequisiti

Riprodurre una breve sequenza monofonica con note, durata e articolazione, mantenendo breve il giro del programma. Leggi la [guida associata](../../04-Melodie-e-audio-con-DAC.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).

Nessuna libreria esterna o pacchetto pip. C++: core Arduino-ESP32 **3.x**. MicroPython: firmware per ESP32 classico con DAC, PWM.duty_u16 e ADC.read_u16 secondo l’esempio. Registra le versioni effettive. La scheda di riferimento è DOIT ESP32 DEVKIT V1 con modulo WROOM-32, non ESP32-C3 o S3.

## Materiali e collegamenti

Scheda, piccolo piezo passivo ad alta impedenza e resistenza da 1 kΩ. Il circuito è lo stesso del tono singolo.

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

1. Avvia: la sequenza richiesta è 262, 294, 330, 262, 330, 349, 392 Hz e una pausa.
2. Per ogni evento compare `NOTE=frequenza MS=durata`. Le prime sei durate sono 300 ms, SOL è 600 ms e la pausa è 1000 ms.
3. Ogni nota termina il suono all’80% della propria durata; il resto è silenzio. La pausa finale rimane interamente silenziosa.
4. Il ciclo nominale dura 3400 ms e si ripete. Prova due note uguali consecutive per sentire l’articolazione.

## Come funziona e limiti

Frequenze e durate sono array paralleli; il numero zero è un simbolo della tabella per il riposo. Il programma non esegue freq(0) in MicroPython. A un ritardo segue un solo avanzamento dal tempo osservato, senza raffiche di note arretrate. La stampa riporta frequenze richieste, non frequenze misurate. Un errore PWM in C++ interrompe la sequenza.

## Modifica autonoma

Aggiungi LA4 prima della pausa, aggiornando entrambe le tabelle e il limite C++: nove eventi e durata nominale totale di 4000 ms.

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
