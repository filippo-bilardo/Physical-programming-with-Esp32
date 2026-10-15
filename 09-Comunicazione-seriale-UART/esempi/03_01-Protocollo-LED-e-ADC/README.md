# Protocollo LED e ADC

## Obiettivo e prerequisiti

Comandare il LED e chiedere misure nuove del potenziometro mediante un protocollo ASCII richiesta/risposta e un client Python sul PC. Consulta la [guida associata](../../03-Protocollo-LED-e-misure.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- [Header del ricevitore](cpp/line_receiver.h) e [modulo MicroPython](micropython/line_receiver.py).
- [client_uart.py](client_uart.py), da eseguire sul PC con Python e pySerial.

C++ usa Arduino-ESP32 senza librerie esterne. MicroPython usa machine e time inclusi nel firmware più il modulo locale fornito. Non servono libraries.txt o pip sulla scheda. Registra le versioni effettive.

## Materiali e collegamenti

DOIT ESP32 DEVKIT V1 con ESP32-WROOM-32, cavo USB dati e cavetti; un adattatore USB-UART con TX/RX a 3,3 V per la prova su hardware; LED e resistenza da 220 Ω; potenziometro lineare da 10 kΩ.

Collega a scheda spenta e usa massa comune. I pin 16/17 possono avere altri impieghi su moduli con PSRAM: verifica la scheda, non sostituire automaticamente il WROOM-32. Non usare segnali RS-232 o TX a 5 V.

| Da | A |
| --- | --- |
| GPIO 17, TX2 | RX dell’adattatore a 3,3 V |
| GPIO 16, RX2 | TX dell’adattatore a 3,3 V |
| GND | GND dell’adattatore |
| GPIO 18 | 220 Ω → anodo LED |
| Catodo LED | GND |
| Estremi potenziometro VCC/GND | 3V3 / GND |
| Cursore SIG | GPIO 34 |

Alimenta l’ESP32 dal proprio USB e lascia scollegato VCC dell’adattatore. TX e RX sono incrociati. L’USB integrato della DOIT è UART0: carica il firmware ma non porta direttamente il protocollo UART2.

## Esecuzione in Wokwi

1. Apri il modello ESP32 Arduino oppure MicroPython dalla [guida ufficiale](https://docs.wokwi.com/guides/esp32).
2. Copia cpp.ino in sketch.ino e aggiungi line_receiver.h, oppure copia main.py e line_receiver.py nel progetto MicroPython.
3. Copia diagram.json dalla stessa sottocartella. Il monitor è collegato a TX2/RX2 e il diagramma configura il terminatore lf. Non spostarlo su UART0.
4. Avvia e segui la prova guidata. Invia una riga alla volta dal monitor e attendi la risposta.

## Esecuzione su scheda reale

1. Carica lo sketch C++ in Arduino IDE selezionando DOIT ESP32 DEVKIT V1 e porta di upload; oppure copia main.py e line_receiver.py sulla scheda MicroPython tramite Thonny.
2. Apri un terminale sulla porta dell’adattatore USB-UART, a 115200 baud, 8 bit, nessuna parità, 1 stop, nessun controllo di flusso. La porta USB della scheda resta disponibile per upload o REPL.
3. Configura LF oppure CRLF per i comandi a righe. UART0 e UART2 sono canali distinti; una console UART0 vuota non indica un guasto del protocollo.
4. Chiudi gli altri programmi che occupano la stessa porta; per modificare il cablaggio togli alimentazione.

## Prova guidata e risultato atteso

1. Avvia: compare READY; il LED parte spento.
2. Invia PING: PONG. Poi LED 1: OK LED 1.
3. Invia GET: STATE LED=1 ADC=n, con codice ADC fra 0 e 4095.
4. Muovi il potenziometro e invia ADC?: ADC=n con una conversione nuova.
5. Invia LED 0: OK LED 0; GET deve riportare LED=0.
6. Ripeti le prove di riga lunga, CRLF e timeout dell’esempio precedente: i comandi errati non modificano il LED e non acquisiscono l’ADC.
7. Su hardware esegui il client PC sulla porta dell’adattatore collegato a UART2, non sulla porta UART0 della scheda.

| Comando | Risposta |
| --- | --- |
| PING | PONG |
| LED 0 / LED 1 | OK LED 0 / OK LED 1 |
| GET | STATE LED=b ADC=n |
| ADC? | ADC=n |
| Altro | ERR COMMAND |

Il valore ADC è un codice, non volt. I comandi sono esatti, maiuscoli; la riga deve terminare con LF, eventualmente preceduto da un solo CR. Ogni richiesta attende la propria risposta prima della seguente. Non sono implementati flusso continuo, controllo di flusso, CRC o ritrasmissioni. La politica di timeout è nel README del ricevitore a righe.

## Come funziona e limiti

PING non legge l’ADC; ADC? e GET fanno una sola conversione ciascuno quando il comando viene eseguito. Non esiste telemetria spontanea, salvo READY all’avvio. C++ usa codici a 12 bit; MicroPython riporta read_u16() alla scala 0–4095 con // 16.

Le letture sono eseguite in polling, con al massimo 32 byte per giro e una pausa di 1 ms. Non si promette latenza rigida o assenza di perdite sotto flusso continuo. Su hardware il ritmo dipende anche dai buffer e dai tempi di trasmissione.

## Client Python sul PC

Da questa cartella, usando un ambiente virtuale Python sul computer:

```bash
python -m pip install pyserial
python client_uart.py /dev/ttyUSB1
```

Sostituisci la porta con quella del tuo adattatore; su Windows, per esempio, `python client_uart.py COM5`. Chiudi altri terminali che usano la stessa porta. Il client non va copiato sulla scheda o nel progetto Wokwi. Invia PING, LED 1, GET, ADC? e LED 0, attendendo la risposta a ciascuno. Una risposta assente o senza LF produce timeout dopo circa 2 s; un eventuale READY iniziale viene scartato. Una risposta ERR viene mostrata, senza ritrasmissione automatica.

## Modifica autonoma

Aggiungi ADCMAX che risponda ADCMAX=4095, senza effettuare una conversione; aggiorna guida e client. Non cambiare i pin della console per nascondere un errore di cablaggio.

## Stato delle prove

Compilazione con core ESP32, runtime MicroPython, Wokwi e collaudo elettrico sono **da eseguire**. I test sul computer con UART e tempo sostituiti controllano la logica; non misurano baud rate, contesa dei buffer reali o livelli elettrici.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell'esercitazione](../../README.md)
- [📖 Guida associata](../../03-Protocollo-LED-e-misure.md)
