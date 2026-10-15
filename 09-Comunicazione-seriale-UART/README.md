# 09 · Comunicazione seriale UART

Passa dalla trasmissione di byte a un protocollo testuale: collega UART2, verifica il ritorno dei dati e comanda un LED richiedendo misure ADC al dispositivo.

## Prerequisiti e obiettivi

**Prerequisiti:** esercitazioni 01–05: GPIO, temporizzazioni, stringhe e ADC. Non è necessario aver completato I²C, SPI o PWM.

Al termine saprai:

- Configurare baud rate e formato 8N1, collegando TX/RX e massa comune.
- Distinguere UART0 di programmazione da UART2 applicativa.
- Verificare un'eco e un loopback con timeout.
- Ricomporre righe frammentate in un buffer limitato e recuperare dopo un errore.
- Usare comandi e risposte dichiarati, separando il client PC dal firmware.

## Materiali e ambienti

DOIT ESP32 DEVKIT V1 con ESP32-WROOM-32, cavo USB dati, breadboard e cavetti; LED con resistenza da **220 Ω** e potenziometro da 10 kΩ per il progetto finale. Il loopback richiede solo un ponticello. Per gli altri esempi su hardware serve un adattatore **USB-UART con segnali a 3,3 V**, separato dall'USB della scheda; in Wokwi lo sostituisce il monitor collegato a UART2.

| Segnale ESP32 | Collegamento esterno |
| --- | --- |
| GPIO 17, TX2 | RX dell'adattatore |
| GPIO 16, RX2 | TX dell'adattatore |
| GND | GND dell'adattatore |
| GPIO 18 | 220 Ω → anodo LED; catodo a GND |
| GPIO 34, ADC1 | Cursore del potenziometro, estremi a 3V3/GND |

Alimenta la scheda dal suo USB e lascia VCC dell'adattatore scollegato. Non usare direttamente segnali RS-232 o TX a 5 V. Le schede con PSRAM possono impiegare GPIO 16/17 per altri scopi: questa piedinatura vale per il modello di riferimento.

## Guide teoriche

1. [UART, collegamenti e loopback](01-UART-collegamenti-e-loopback.md)
2. [Righe, buffer e timeout](02-Righe-buffer-e-timeout.md)
3. [Protocollo testuale per LED e misure](03-Protocollo-LED-e-misure.md)

Ogni guida comprende esempi commentati, autovalutazione con soluzioni ed esercizi progressivi.

## Esempi completi

| Esempio | Guida | Implementazioni |
| --- | --- | --- |
| [Eco dei byte UART2](esempi/01_01-Echo-byte-UART2/README.md) | 01 | C++ e MicroPython |
| [Loopback UART2](esempi/01_02-Loopback-UART2/README.md) | 01 | C++ e MicroPython |
| [Comandi LED](esempi/02_01-Comandi-LED/README.md) | 02 | C++ e MicroPython |
| [Protocollo LED e ADC](esempi/03_01-Protocollo-LED-e-ADC/README.md) | 03 | C++ e MicroPython, più client PC |

C++ usa HardwareSerial di Arduino-ESP32, senza librerie esterne. MicroPython usa `machine.UART`; i due ultimi esempi includono `line_receiver.py` da copiare con `main.py`. Il client `client_uart.py` gira sul PC con Python e pySerial: non va installato sulla scheda. Le istruzioni per Wokwi e hardware sono nei README degli esempi.

## Percorso pratico guidato

1. Esegui l'eco con il monitor Wokwi collegato a TX2/RX2. Invia una riga breve e osserva i byte restituiti.
2. Esegui il loopback con il suo diagramma: TX2 è collegato a RX2 e il monitor è su UART0. Osserva TX e RX di A.
3. A prova ferma rimuovi il ponticello e riavvia per vedere il timeout di 200 ms; poi ripristina il circuito.
4. Esegui i comandi LED, inviando una riga per volta con LF. Confronta LF e CRLF; non usare solo CR.
5. Prova comando sconosciuto, riga troppo lunga e riga parziale in timeout. Dopo un errore il parser scarta fino a LF, segnala il problema e accetta una nuova riga.
6. Aggiungi il potenziometro ed esegui il protocollo finale: PING, LED 1, GET, ADC?, LED 0. Muovi il potenziometro fra due richieste.
7. Su hardware usa il client PC sulla porta dell'adattatore USB-UART a 3,3 V, lasciando UART0 a upload e REPL.

## Attività autonoma conclusiva

**Consegna:** aggiungi `SAMPLE`, che esegue una sola conversione ADC, aggiorna minimo e massimo delle letture SAMPLE e risponde `MIN=n MAX=n`. Aggiungi `CLEAR`, che azzera lo storico e risponde `OK CLEAR`. Il primo SAMPLE dopo avvio o CLEAR deve impostare entrambi gli estremi alla propria lettura. GET e ADC? conservano il comportamento originale e non aggiornano questo storico.

**Risultato atteso:** niente zeri iniziali fittizi, memoria soltanto in RAM, nessun campione generato da righe errate. Aggiorna la tabella del protocollo e il client; prova valori crescenti, decrescenti, CLEAR e riavvio. Mantieni limite, grammatica e risincronizzazione del parser.

## Verifica dell'apprendimento

Spiega la differenza fra bit, byte, lettura e messaggio completo; calcola il limite teorico dei byte/s in 8N1. Distingui timeout del loopback, timeout fra byte di riga e timeout del client PC. Non assumere che più read() corrispondano a più comandi.

## Stato dei materiali e delle prove

Guide, sorgenti, client e circuiti sono disponibili. I controlli locali hanno superato **37 scenari e 148 esecuzioni** dei programmi C++ e Python con UART e clock sostituiti: eco, loopback, righe frammentate, limiti del buffer, caratteri non validi, timeout e risincronizzazione, comandi e letture ADC, anche al ritorno a zero del timer. Il client PC ha superato tre controlli: dialogo ordinario, risposta incompleta e scrittura parziale. Gli sketch sono stati compilati sul computer con API sostitutive; sintassi Python, collegamenti locali e diagrammi JSON sono stati controllati.

**Compilazione con core ESP32, esecuzione nel runtime MicroPython, Wokwi e collaudo hardware: da eseguire.** I controlli sul computer non misurano la trasmissione elettrica o la tenuta al carico dei driver reali. Ogni esempio offre una tabella per le prove effettive.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [⬅️ Esercitazione precedente disponibile: 07](../07-Sensori-e-display-I2C/README.md)
- Le esercitazioni 08 e 10 restano pianificate; consulta l'indice per il percorso numerico completo.
