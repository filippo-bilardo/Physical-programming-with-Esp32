# UART, collegamenti e loopback

## Obiettivi e prerequisiti

Prerequisiti: esercitazioni 01–05, GPIO e temporizzazioni. Le esercitazioni 06–08 non sono necessarie per questi esempi. Imparerai a configurare UART2, incrociare TX/RX e verificare un collegamento con eco e loopback.

## Teoria e collegamento con l'architettura

### Comunicazione asincrona

UART trasmette byte senza una linea di clock condivisa. I due estremi devono concordare velocità e formato. Usiamo **115200 baud, 8N1**: otto bit dati, nessuna parità e un bit di stop. Con un bit di start si trasmettono almeno dieci bit per byte: il massimo teorico è 11520 byte/s per direzione, prima dei limiti del programma e dei buffer.

TX trasmette e RX riceve. L'ESP32 può comunicare nelle due direzioni; per un collegamento fra due schede servono TX di A verso RX di B, TX di B verso RX di A e GND comune. I livelli sono logici a **3,3 V**, non quelli elettrici RS-232. Un adattatore seriale a 5 V o RS-232 non va collegato direttamente ai GPIO.

### Separare UART2 dalla console

Sulla DOIT ESP32 DEVKIT V1 con modulo WROOM-32 usiamo RX = GPIO 16 e TX = GPIO 17. Non trasferire questi collegamenti a schede che usano quei pin per PSRAM o altre periferiche. UART0 resta alla programmazione e alla REPL MicroPython.

| ESP32 | Adattatore USB-UART con segnali a 3,3 V |
| --- | --- |
| GPIO 17, TX | RX dell'adattatore |
| GPIO 16, RX | TX dell'adattatore |
| GND | GND |

Alimenta l'ESP32 con il proprio USB: per queste prove non collegare il pin VCC dell'adattatore. Il selettore della tensione su alcuni adattatori riguarda solo l'alimentazione: verifica anche i livelli effettivi di TX/RX.

### Eco e loopback sono prove diverse

L'[eco](esempi/01_01-Echo-byte-UART2/README.md) restituisce i byte arrivati da un terminale. Nel [loopback](esempi/01_02-Loopback-UART2/README.md) un cavetto collega il TX2 allo stesso RX2 della scheda: il programma invia A ogni secondo e aspetta il ritorno entro il controllo di 200 ms. Non dimostra che un secondo dispositivo interpreti correttamente un protocollo.

In Wokwi l'eco usa il monitor collegato a TX2/RX2; il loopback usa invece UART0 per la diagnostica e il ponticello fra TX2 e RX2. Sono i diagrammi a definire dove si trova la console della simulazione.

## Esempi commentati

```cpp
Serial2.begin(115200, SERIAL_8N1, 16, 17);  // Ordine: RX, TX.
```

```python
from machine import UART, Pin
uart = UART(2, baudrate=115200, bits=8, parity=None, stop=1,
            rx=Pin(16), tx=Pin(17), timeout=0, timeout_char=0)
data = uart.read(32)
if data:
    uart.write(data)
```

Ogni giro elabora al massimo 32 byte e termina con una breve pausa di 1 ms. Un byte non è ancora una riga né un comando. Nel caso di scritture sostenute i buffer possono esaurirsi e le scritture possono bloccare o risultare incomplete; gli esempi interattivi non implementano controllo di flusso o ritrasmissioni.

## Buone pratiche e debug

- Controlla quale porta seriale appartiene all’adattatore e quale alla scheda.
- Non collegare insieme due TX, entrambi uscite.
- Se i caratteri sono illeggibili, controlla baud rate, 8N1, massa e livelli.
- Un terminale con eco locale può mostrare due copie del testo: disabilita l’eco locale.
- Nel loopback rimuovi il cavetto a scheda spenta per preparare la prova di timeout.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Quale collegamento è corretto fra due UART?**

   - A. TX con TX soltanto.
   - B. TX di A con RX di B e viceversa, più GND.
   - C. SDA con SCL.
   - D. Solo VCC.

2. **Che cosa significa 8N1?**

   - A. Otto pin, nove volt, una CPU.
   - B. Otto byte per pacchetto.
   - C. Otto bit dati, nessuna parità, un bit di stop.
   - D. Otto bit di stop.

3. **Perché usiamo UART2 negli esempi interattivi?**

   - A. Per tenere separati protocollo e console di programmazione UART0.
   - B. Perché UART0 non esiste.
   - C. Per aumentare i GPIO a 5 V.
   - D. Per avere un clock I²C.

## Esercizi pratici

1. **Consegna:** Esegui l’eco e invia Ciao dal monitor Wokwi.

   **Risultato atteso:** Tornano gli stessi byte e il terminatore configurato nel monitor.

2. **Consegna:** Esegui il loopback con il ponticello.

   **Risultato atteso:** TX: A è seguito da RX: A; non si accumulano invii in attesa.

3. **Consegna:** A prova ferma rimuovi il ponticello e riavvia il loopback.

   **Risultato atteso:** Dopo ciascun invio senza ritorno compare ERR TIMEOUT; gli invii proseguono circa ogni secondo.

## Soluzioni dell'autovalutazione

1. **B.** Le uscite devono raggiungere gli ingressi dell’altro dispositivo.
2. **C.** Il formato deve essere uguale ai due estremi.
3. **A.** La separazione evita di trattare la REPL come un protocollo applicativo.

## Riferimenti

- [Espressif: HardwareSerial](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/serial.html).
- [MicroPython: UART](https://docs.micropython.org/en/latest/library/machine.UART.html).
- [Wokwi: monitor seriale](https://docs.wokwi.com/guides/serial-monitor).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente disponibile](../07-Sensori-e-display-I2C/04-Temperatura-soglia-ed-errori.md)
- [➡️ Guida successiva](02-Righe-buffer-e-timeout.md)
