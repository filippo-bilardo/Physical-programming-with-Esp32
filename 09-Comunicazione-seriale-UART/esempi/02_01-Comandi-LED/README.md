# Comandi LED a righe

## Obiettivo e prerequisiti

Eseguire LED 0, LED 1 e GET soltanto dopo una riga ASCII completa, con limite di lunghezza e risincronizzazione dopo errore. Consulta la [guida associata](../../02-Righe-buffer-e-timeout.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- [Header del ricevitore](cpp/line_receiver.h) e [modulo MicroPython](micropython/line_receiver.py).

C++ usa Arduino-ESP32 senza librerie esterne. MicroPython usa machine e time inclusi nel firmware più il modulo locale fornito. Non servono libraries.txt o pip sulla scheda. Registra le versioni effettive.

## Materiali e collegamenti

DOIT ESP32 DEVKIT V1 con ESP32-WROOM-32, cavo USB dati e cavetti; un adattatore USB-UART con TX/RX a 3,3 V per la prova su hardware; LED e resistenza da 220 Ω.

Collega a scheda spenta e usa massa comune. I pin 16/17 possono avere altri impieghi su moduli con PSRAM: verifica la scheda, non sostituire automaticamente il WROOM-32. Non usare segnali RS-232 o TX a 5 V.

| Da | A |
| --- | --- |
| GPIO 17, TX2 | RX dell’adattatore a 3,3 V |
| GPIO 16, RX2 | TX dell’adattatore a 3,3 V |
| GND | GND dell’adattatore |
| GPIO 18 | 220 Ω → anodo LED |
| Catodo LED | GND |

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

1. Avvia: compare READY e il LED è spento.
2. Invia LED 1, poi GET, poi LED 0, una riga per volta: OK LED 1, LED=1, OK LED 0.
3. Prova led 1, LED  1 e LED 1 seguito da uno spazio: ERR COMMAND, senza modifiche del LED.
4. Imposta temporaneamente newline crlf: gli stessi comandi sono accettati.
5. Invia più di 32 byte sulla stessa riga e poi LF: ERR LONG; una nuova riga GET deve funzionare.
6. Per il timeout imposta newline none, invia LED, attendi oltre 1 s, invia la coda 1 e infine LF: ERR TIMEOUT, senza eseguire il suffisso. Ripristina lf e invia un comando valido.
7. Una riga vuota non produce risposta; un CR interno o un byte non ASCII produce ERR ASCII al terminatore.

## Come funziona e limiti

I moduli line_receiver sono inclusi e identici a quelli del protocollo finale. Conservano al massimo 32 byte prima di LF, contando il CR finale opzionale. Dopo overflow, byte invalido o timeout si scarta fino al successivo LF. Il primo errore rilevato viene notificato lì una sola volta, poi la ricezione riparte.

Le letture sono eseguite in polling, con al massimo 32 byte per giro e una pausa di 1 ms. Non si promette latenza rigida o assenza di perdite sotto flusso continuo. Su hardware il ritmo dipende anche dai buffer e dai tempi di trasmissione.

## Modifica autonoma

Aggiungi il comando LED? come alias di GET, conservando risposte e grammatica degli altri comandi. Non cambiare i pin della console per nascondere un errore di cablaggio.

## Stato delle prove

Compilazione con core ESP32, runtime MicroPython, Wokwi e collaudo elettrico sono **da eseguire**. I test sul computer con UART e tempo sostituiti controllano la logica; non misurano baud rate, contesa dei buffer reali o livelli elettrici.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell'esercitazione](../../README.md)
- [📖 Guida associata](../../02-Righe-buffer-e-timeout.md)
