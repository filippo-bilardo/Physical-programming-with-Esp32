# Eco dei byte su UART2

## Obiettivo e prerequisiti

Restituire gli stessi byte ricevuti su UART2, distinguendo il trasporto dei byte da un protocollo a comandi. Consulta la [guida associata](../../01-UART-collegamenti-e-loopback.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).

C++ usa Arduino-ESP32 senza librerie esterne. MicroPython usa machine e time inclusi nel firmware. Non servono libraries.txt o pip sulla scheda. Registra le versioni effettive.

## Materiali e collegamenti

DOIT ESP32 DEVKIT V1 con ESP32-WROOM-32, cavo USB dati e cavetti; un adattatore USB-UART con TX/RX a 3,3 V per la prova su hardware.

Collega a scheda spenta e usa massa comune. I pin 16/17 possono avere altri impieghi su moduli con PSRAM: verifica la scheda, non sostituire automaticamente il WROOM-32. Non usare segnali RS-232 o TX a 5 V.

| Da | A |
| --- | --- |
| GPIO 17, TX2 | RX dell’adattatore a 3,3 V |
| GPIO 16, RX2 | TX dell’adattatore a 3,3 V |
| GND | GND dell’adattatore |

Alimenta l’ESP32 dal proprio USB e lascia scollegato VCC dell’adattatore. TX e RX sono incrociati. L’USB integrato della DOIT è UART0: carica il firmware ma non porta direttamente il protocollo UART2.

## Esecuzione in Wokwi

1. Apri il modello ESP32 Arduino oppure MicroPython dalla [guida ufficiale](https://docs.wokwi.com/guides/esp32).
2. Copia cpp.ino in sketch.ino, oppure copia main.py nel progetto MicroPython.
3. Copia diagram.json dalla stessa sottocartella. Il monitor è collegato a TX2/RX2 e il diagramma configura il terminatore lf. Non spostarlo su UART0.
4. Avvia e segui la prova guidata. Invia una riga alla volta dal monitor e attendi la risposta.

## Esecuzione su scheda reale

1. Carica lo sketch C++ in Arduino IDE selezionando DOIT ESP32 DEVKIT V1 e porta di upload; oppure copia main.py sulla scheda MicroPython tramite Thonny.
2. Apri un terminale sulla porta dell’adattatore USB-UART, a 115200 baud, 8 bit, nessuna parità, 1 stop, nessun controllo di flusso. La porta USB della scheda resta disponibile per upload o REPL.
3. Configura LF oppure CRLF per i comandi a righe. UART0 e UART2 sono canali distinti; una console UART0 vuota non indica un guasto del protocollo.
4. Chiudi gli altri programmi che occupano la stessa porta; per modificare il cablaggio togli alimentazione.

## Prova guidata e risultato atteso

1. Avvia: sul monitor collegato a UART2 appare READY UART2.
2. Invia Ciao e premi Invio: tornano gli stessi byte, compreso LF.
3. Prova cifre e spazi: non sono interpretati come comandi.
4. Disabilita l’eco locale nell’eventuale terminale PC per non vedere una copia aggiuntiva del testo.
5. Confronta i due linguaggi: ogni giro legge al massimo 32 byte; il testo può arrivare in più frammenti.

## Come funziona e limiti

C++ usa available/read/write su Serial2; MicroPython legge fino a 32 byte e li riscrive. Non applica grammatica, timeout di riga o controllo di flusso. Usa messaggi brevi; scritture parziali sotto carico non sono recuperate.

Le letture sono eseguite in polling, con al massimo 32 byte per giro e una pausa di 1 ms. Non si promette latenza rigida o assenza di perdite sotto flusso continuo. Su hardware il ritmo dipende anche dai buffer e dai tempi di trasmissione.

## Modifica autonoma

Modifica il baud rate coerentemente nei due estremi e documenta la prova. Non cambiare i pin della console per nascondere un errore di cablaggio.

## Stato delle prove

Compilazione con core ESP32, runtime MicroPython, Wokwi e collaudo elettrico sono **da eseguire**. I test sul computer con UART e tempo sostituiti controllano la logica; non misurano baud rate, contesa dei buffer reali o livelli elettrici.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell'esercitazione](../../README.md)
- [📖 Guida associata](../../01-UART-collegamenti-e-loopback.md)
