# Loopback locale UART2

## Obiettivo e prerequisiti

Inviare il byte A su TX2 e rileggerlo sul proprio RX2 tramite un ponticello, con timeout di risposta e diagnostica separata su UART0. Consulta la [guida associata](../../01-UART-collegamenti-e-loopback.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).

C++ usa Arduino-ESP32 senza librerie esterne. MicroPython usa machine e time inclusi nel firmware. Non servono libraries.txt o pip sulla scheda. Registra le versioni effettive.

## Materiali e collegamenti

DOIT ESP32 DEVKIT V1 con ESP32-WROOM-32, cavo USB dati e cavetti; un ponticello, senza adattatore aggiuntivo.

Collega a scheda spenta e usa massa comune. I pin 16/17 possono avere altri impieghi su moduli con PSRAM: verifica la scheda, non sostituire automaticamente il WROOM-32. Non usare segnali RS-232 o TX a 5 V.

| Da | A |
| --- | --- |
| GPIO 17 (TX2) | GPIO 16 (RX2), ponticello sulla stessa scheda |

Il ponticello collega la UART2 alla propria ricezione; non collegare nello stesso momento un trasmettitore esterno a RX2.

## Esecuzione in Wokwi

1. Apri il modello ESP32 Arduino oppure MicroPython dalla [guida ufficiale](https://docs.wokwi.com/guides/esp32).
2. Copia cpp.ino in sketch.ino, oppure copia main.py nel progetto MicroPython.
3. Copia diagram.json dalla stessa sottocartella. Il monitor resta su UART0 per i messaggi TX/RX; il circuito include il ponticello TX2–RX2.
4. Avvia e segui la prova guidata. Non servono comandi dal monitor per avviare la prova.

## Esecuzione su scheda reale

1. Carica lo sketch C++ in Arduino IDE selezionando DOIT ESP32 DEVKIT V1 e porta di upload; oppure copia main.py sulla scheda MicroPython tramite Thonny.
2. Apri il monitor seriale UART0 a 115200 baud o osserva la console Thonny: la UART2 serve solo al ponticello.
3. Osserva TX: A e RX: A, poi prepara la prova senza ponticello a scheda spenta.
4. Chiudi gli altri programmi che occupano la stessa porta; per modificare il cablaggio togli alimentazione.

## Prova guidata e risultato atteso

1. Avvia con ponticello TX2–RX2: dopo circa 1 s compare TX: A, poi RX: A.
2. La prova si ripete circa ogni secondo, con una sola richiesta in attesa.
3. Ferma, rimuovi il ponticello e riavvia: circa 200 ms dopo ogni TX compare ERR TIMEOUT.
4. Ripristina il circuito a prova ferma e riavvia.
5. Il test riguarda la UART locale: non dimostra correttezza di un dispositivo remoto o di un protocollo complesso.

## Come funziona e limiti

La UART2 trasmette un byte per prova; le stampe vanno su UART0. Il ricevitore controlla fino a 32 byte per giro e accetta A soltanto quando una prova è in attesa. Altri byte producono RX inatteso. Se un byte è già leggibile nel giro in cui si controlla la scadenza, viene elaborato prima del timeout.

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
