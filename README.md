# Physical Programming with ESP32 by Example

## Programmare ESP32 con MicroPython, C++, Wokwi e Arduino IDE

Un corso pratico per imparare a programmare un microcontrollore attraverso esercitazioni guidate: dal primo LED lampeggiante a un sistema con sensori, display e connessione Wi-Fi. Ogni tappa collega il comportamento osservato nel circuito ai componenti di un sistema di elaborazione: CPU, memorie, ingressi e uscite, bus, timer e interrupt.

Il percorso prevede esempi equivalenti in **MicroPython** e **C++ con il framework Arduino**, per confrontare sintassi, API e modalità di esecuzione. Si parte dalla simulazione in **Wokwi** e si passa alla scheda reale con **Arduino IDE** per C++ e gli strumenti MicroPython.

> **Stato dei materiali:** le esercitazioni **01–05, 07 e 09 sono disponibili**, con ventisette guide e ventisei esempi in C++ e MicroPython, ciascuno corredato dai circuiti Wokwi. Le esercitazioni 06, 08 e 10–16 sono pianificate e le relative cartelle non esistono ancora. Le prove in Wokwi e su hardware sono da eseguire; ogni esempio indica procedura e risultato atteso.

## 🎯 Obiettivi formativi

Al termine del percorso saprai:

- Scrivere, eseguire e correggere programmi per ESP32 in MicroPython e C++ Arduino.
- Simulare un circuito in Wokwi e trasferire un progetto sulla scheda reale.
- Leggere pulsanti e sensori, controllare LED e attuatori e visualizzare informazioni su un display.
- Distinguere il ruolo della CPU, della RAM, della memoria Flash e delle periferiche.
- Usare i GPIO, ossia i pin di ingresso e uscita configurabili, e le interfacce I²C, SPI e UART.
- Gestire temporizzazioni, eventi e interrupt senza bloccare inutilmente il programma.
- Memorizzare configurazioni e misure e scambiare dati attraverso una rete Wi-Fi.
- Confrontare le due implementazioni di un progetto, riconoscendo differenze nelle API, nelle risorse impiegate e nella gestione degli errori.
- Documentare collegamenti, dipendenze, prove effettuate e limiti di un prototipo.

## Prerequisiti

Sono sufficienti conoscenze iniziali di programmazione: variabili, condizioni, cicli e funzioni in almeno un linguaggio. Occorre saper gestire file e cartelle e installare un programma sul computer. Non è richiesta una conoscenza precedente di ESP32, MicroPython o del framework Arduino.

Tensione, corrente, resistenza, polarità e massa comune saranno introdotte prima dei primi collegamenti. Le basi della comunicazione in rete saranno affrontate prima delle esercitazioni Wi-Fi.

Le esercitazioni vanno svolte nell’ordine dell’indice: ciascuna riprende strumenti e concetti già acquisiti. Le prime tre consolidano anche le differenze essenziali tra Python e C++.

## 🧰 Strumenti e materiali

### Software

| Strumento | Impiego nel corso |
| --- | --- |
| Computer con browser e accesso a Internet | Consultazione dei materiali e simulazione online |
| [Wokwi](https://docs.wokwi.com/guides/esp32) | Simulazione di progetti ESP32 Arduino e MicroPython |
| [Arduino IDE](https://www.arduino.cc/en/software) e [pacchetto Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) | Compilazione, caricamento degli sketch C++ e monitor seriale |
| [Firmware MicroPython per ESP32](https://micropython.org/download/esp32/) | Esecuzione dei programmi Python sulla scheda di riferimento |
| [Thonny](https://thonny.org/) | Editor, accesso alla console MicroPython e trasferimento dei file |
| [mpremote](https://docs.micropython.org/en/latest/reference/mpremote.html), facoltativo | Accesso alla scheda MicroPython dalla riga di comando |
| Servizi HTTP e broker MQTT di prova | Attività di rete, introdotti nelle esercitazioni 12 e 13 |

Le versioni di firmware, core Arduino e librerie utilizzate dovranno essere indicate negli esempi insieme alle istruzioni di installazione. La configurazione di Wokwi e quella del computer andranno documentate separatamente quando differiscono.

### Hardware

La scheda di riferimento del percorso è una **ESP32 DevKit basata sul modulo ESP32-WROOM-32**, con connettore USB; la guida di installazione usa la **DOIT ESP32 DEVKIT V1**. Modelli come ESP32-C3, S2 e S3 richiedono una verifica specifica di piedinatura, periferiche e firmware: non vanno sostituiti automaticamente alla scheda di riferimento.

| Quando serve | Materiale previsto |
| --- | --- |
| Prime esercitazioni su scheda reale | ESP32, cavo USB dati compatibile, breadboard e cavetti |
| Uscite e ingressi digitali | LED, resistenze limitatrici di corrente, pulsanti e resistenze per le attività sui circuiti di ingresso |
| Ingressi analogici | Potenziometro da 10 kΩ |
| PWM e attuatori | LED, buzzer passivo e, come estensione, un servomotore con alimentazione adeguata |
| I²C e sensori | Sensore BMP180 e display OLED SSD1306 I²C 128×64, compatibili con 3,3 V |
| SPI | Display TFT con interfaccia SPI, per esempio ILI9341 |
| UART | Seconda ESP32 o adattatore USB-UART con livelli logici compatibili a 3,3 V |
| Misure sul circuito | Multimetro; analizzatore logico facoltativo |
| Rete e progetto finale | Rete Wi-Fi a 2,4 GHz e componenti scelti nelle esercitazioni precedenti |

L’elenco preciso, i valori delle resistenze e la tabella dei collegamenti saranno riportati in ciascun esempio. Per iniziare in Wokwi non serve acquistare hardware.

Sulla scheda reale si lavora con logica a **3,3 V**: non applicare segnali a 5 V ai GPIO. Prima di alimentare il circuito verifica piedinatura, polarità e massa comune; usa una resistenza in serie a ogni LED e non alimentare motori o altri carichi di potenza direttamente dai pin. Le attività con attuatori specificheranno alimentazione e circuito di pilotaggio.

## 🚀 Come iniziare

### 1. Parti dalla simulazione

1. Apri la [guida ESP32 di Wokwi](https://docs.wokwi.com/guides/esp32) e scegli il modello di progetto **Arduino-ESP32** indicato nella sezione iniziale.
2. Avvia il modello e individua il codice, il circuito e il monitor seriale. Annota il tipo di scheda e i GPIO utilizzati.
3. Apri anche il modello **MicroPython ESP32** collegato dalla stessa guida e individua il file `main.py`.
4. Prova gli esempi Blink ufficiali collegati nella guida: osserva il lampeggio, modifica l’intervallo di attesa e confronta il risultato nei due linguaggi.
5. Comincia dall’[esercitazione 01](01-Introduzione-ESP32/README.md) e segui il relativo README per riprodurre il circuito e gli esempi.

La [guida Wokwi con accenni a Tinkercad](01-Introduzione-ESP32/06-Wokwi-e-Tinkercad.md) approfondisce importazione, console e circuiti. Wokwi supporta entrambe le modalità; le periferiche simulate e i relativi limiti sono elencati nella [documentazione ufficiale ESP32](https://docs.wokwi.com/guides/esp32).

### 2. Prepara C++ sulla scheda reale

1. Installa Arduino IDE.
2. Segui la [procedura ufficiale Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html): aggiungi nelle preferenze l’URL dell’indice stabile indicato dalla guida e installa **esp32 by Espressif Systems** dal gestore delle schede.
3. Collega ESP32 con un cavo USB dati e seleziona il modello di scheda e la porta seriale corretti. Per la DOIT segui la [guida Arduino IDE](01-Introduzione-ESP32/04-Arduino-IDE-e-DOIT-DevKit-V1.md) e la [guida ai driver USB-seriali](01-Introduzione-ESP32/05-Driver-USB-seriale.md).
4. Apri lo sketch dell’esempio, installa le dipendenze dichiarate e avvia la verifica della compilazione.
5. Carica il programma e apri il monitor seriale alla velocità indicata dall’esempio. Confronta messaggi e comportamento del circuito con il risultato atteso.

### 3. Prepara MicroPython sulla scheda reale

1. Installa Thonny e collega ESP32 tramite USB.
2. Identifica il modello esatto e scarica il firmware adatto. Per la scheda di riferimento usa la [pagina ESP32 di MicroPython](https://micropython.org/download/esp32/).
3. Installa il firmware seguendo le istruzioni della pagina della scheda e la [guida introduttiva ufficiale](https://docs.micropython.org/en/latest/esp32/tutorial/intro.html). L’eventuale cancellazione della Flash elimina i dati presenti: salva prima i file da conservare.
4. In Thonny seleziona l’interprete MicroPython per ESP32 e la porta seriale della scheda. Verifica l’accesso alla **REPL**, la console interattiva, eseguendo `print("Ciao ESP32")`.
5. Trasferisci sulla scheda `main.py` e gli eventuali moduli richiesti dall’esempio. Riavvia e controlla l’uscita della console e il comportamento del circuito.

Caricare uno sketch Arduino e installare il firmware MicroPython modifica il software presente sulla scheda. Per confrontare i due ambienti puoi utilizzare due schede oppure alternarli, conservando sul computer programmi e configurazioni.

## 📚 Indice delle esercitazioni

Le esercitazioni **01–05, 07 e 09 sono disponibili**: i rispettivi link aprono cartelle con README, guide ed esempi. Le esercitazioni **06, 08 e 10–16 sono pianificate**: i loro link indicano i percorsi futuri e non sono ancora navigabili. I prerequisiti delle 07 e 09 permettono di affrontarle dopo la 05, senza richiedere le due tappe intermedie ancora mancanti.

**Ambienti:** “Wokwi + scheda” indica attività progettate per entrambi gli ambienti, subordinatamente al supporto dei componenti scelti. Le verifiche elettriche, le misure dei consumi e le prove di affidabilità fisica richiedono hardware reale.

| N. | Esercitazione | Concetti e collegamento con l’architettura | Attività conclusiva prevista | Ambiente |
| --- | --- | --- | --- | --- |
| 01 | [Introduzione a ESP32](01-Introduzione-ESP32/) | Microcontrollore, CPU, RAM, Flash, programma compilato e runtime MicroPython; strumenti e console | Eseguire un primo programma nei due linguaggi e modificare un lampeggio | Wokwi + scheda |
| 02 | [Uscite digitali e LED](02-Uscite-digitali-e-LED/) | GPIO in uscita, livelli logici, corrente e resistenza; funzioni, cicli e drive strength | Realizzare una sequenza luminosa con più LED | Wokwi + scheda |
| 03 | [Ingressi digitali e pulsanti](03-Ingressi-digitali-e-pulsanti/) | GPIO in ingresso, pull-up, pull-down, lettura periodica e rimbalzi dei contatti | Comandare una luce con un pulsante e filtrare i rimbalzi | Wokwi + scheda |
| 04 | [Tempo e macchine a stati](04-Tempo-e-macchine-a-stati/) | Attese bloccanti, contatori temporali, gestione del tempo e stato del programma | Costruire un semaforo con richiesta pedonale senza bloccare la lettura del pulsante | Wokwi + scheda |
| 05 | [Ingressi analogici e ADC](05-Ingressi-analogici-e-ADC/) | Conversione analogico-digitale, risoluzione, campionamento e rumore | Regolare una soglia con un potenziometro e segnalare il superamento | Wokwi + scheda; misure reali con multimetro |
| 06 | [PWM e attuatori](06-PWM-e-attuatori/) | Modulazione di larghezza d’impulso, frequenza, duty cycle e periferiche hardware | Variare luminosità e segnalazione sonora in base a un ingresso | Wokwi + scheda; alimentazione da verificare su hardware |
| 07 | [Sensori e display I2C](07-Sensori-e-display-I2C/) | Bus I²C, indirizzi, registri dei dispositivi, librerie e gestione delle letture | Visualizzare una temperatura e una soglia su un display OLED | Wokwi + scheda, con componenti supportati |
| 08 | [Bus SPI e display grafici](08-Bus-SPI-e-display-grafici/) | Clock, selezione del dispositivo, trasferimento seriale e memoria dei dati grafici | Mostrare su un display SPI un indicatore dell’ingresso analogico | Wokwi + scheda |
| 09 | [Comunicazione seriale UART](09-Comunicazione-seriale-UART/) | Trasmissione asincrona, baud rate, buffer e formato dei messaggi | Comandare un LED e leggere misure attraverso un semplice protocollo testuale | Wokwi + scheda; collegamento a PC o seconda scheda su hardware |
| 10 | [Timer e interrupt](10-Timer-e-interrupt/) | Timer hardware, eventi, routine di interrupt e dati condivisi | Contare impulsi e aggiornare periodicamente il display | Wokwi + scheda |
| 11 | [Memorie e persistenza](11-Memorie-e-persistenza/) | RAM e Flash, file, configurazioni persistenti, allocazione e limiti di scrittura | Salvare una soglia e ripristinarla al riavvio | Wokwi per la logica; scheda per verificare la persistenza dopo spegnimento |
| 12 | [WiFi e HTTP](12-WiFi-e-HTTP/) | Connessione di rete, indirizzi IP, richieste e risposte HTTP, timeout | Inviare una misura a un servizio HTTP e gestire un errore di connessione | Wokwi con rete simulata + scheda |
| 13 | [Messaggistica MQTT](13-Messaggistica-MQTT/) | Broker, topic, pubblicazione, sottoscrizione e riconnessione | Pubblicare misure e ricevere una nuova soglia tramite MQTT | Wokwi + scheda, con broker raggiungibile |
| 14 | [Attività concorrenti e robustezza](14-Attivita-concorrenti-e-robustezza/) | Pianificazione cooperativa, coroutine MicroPython, introduzione ai task FreeRTOS in C++, risorse condivise | Integrare acquisizione, display e rete mantenendo reattivi i comandi | Wokwi + scheda |
| 15 | [Risparmio energetico](15-Risparmio-energetico/) | Consumo, sospensione, deep sleep, risveglio e stato conservato | Acquisire una misura, trasmetterla e sospendere la scheda tra due rilevazioni | Scheda reale per risvegli e misure dei consumi |
| 16 | [Progetto finale: stazione ambientale](16-Progetto-finale-stazione-ambientale/) | Integrazione di periferiche, memoria, rete e gestione degli errori | Realizzare una stazione con display, allarme locale, soglia persistente e telemetria MQTT | Wokwi per le parti supportate + collaudo su scheda |

Le attività di rete introdurranno le dipendenze esterne e le condizioni di accesso ai servizi. Credenziali personali e chiavi non devono essere inserite nei materiali condivisi. L’esercitazione 15 costituisce anche un’estensione energetica del progetto finale.

## Metodo di lavoro

Ogni esercitazione seguirà questa sequenza:

1. **Preparazione:** verifica dei prerequisiti, lettura degli obiettivi e identificazione dei materiali.
2. **Teoria:** studio di un argomento alla volta, con definizione dei termini e collegamento all’hardware coinvolto.
3. **Montaggio:** lettura della tabella dei collegamenti e preparazione del circuito, prima in simulazione e poi su scheda quando previsto.
4. **Esecuzione guidata:** avvio dell’esempio e osservazione di uscite, messaggi, misure e tempi.
5. **Confronto:** esecuzione delle versioni MicroPython e C++, mettendo in relazione le API e il comportamento.
6. **Modifica e debug:** variazione di un parametro alla volta, previsione del risultato e analisi di eventuali errori.
7. **Autovalutazione:** domande con quattro alternative e una sola risposta corretta; soluzioni raccolte dopo tutte le domande, con lettera, testo e spiegazione.
8. **Attività autonoma:** realizzazione di una variante che combini quanto appreso, con consegna e risultato atteso espliciti.

Prima di passare alla tappa successiva, lo studente dovrà saper spiegare il ruolo dei componenti utilizzati, riprodurre il comportamento previsto e motivare le modifiche apportate al programma.

Il confronto tra i linguaggi riguarderà anche gli strumenti: in C++ lo sketch viene compilato e caricato sulla scheda; con MicroPython si installa un firmware che esegue i programmi e offre una console interattiva. Per gli esempi non direttamente equivalenti, come coroutine e task, saranno spiegate le differenze e le eventuali limitazioni.

## 📁 Organizzazione prevista dei materiali

```text
.
├── README.md
├── 01-Introduzione-ESP32/
├── 02-Uscite-digitali-e-LED/
├── 03-Ingressi-digitali-e-pulsanti/
├── 04-Tempo-e-macchine-a-stati/
├── 05-Ingressi-analogici-e-ADC/
├── 07-Sensori-e-display-I2C/
│   ├── README.md
│   ├── 01-Bus-I2C-e-indirizzi.md
│   ├── 02-Registri-e-temperatura-BMP180.md
│   ├── 03-Display-OLED-e-framebuffer.md
│   ├── 04-Temperatura-soglia-ed-errori.md
│   └── esempi/
│       ├── 01_01-Scanner-I2C/
│       ├── 02_01-Temperatura-BMP180/
│       ├── 03_01-Testo-su-OLED/
│       └── 04_01-Temperatura-soglia-e-display/
└── 09-Comunicazione-seriale-UART/
    ├── README.md
    ├── 01-UART-collegamenti-e-loopback.md
    ├── 02-Righe-buffer-e-timeout.md
    ├── 03-Protocollo-LED-e-misure.md
    └── esempi/
        ├── 01_01-Echo-byte-UART2/
        ├── 01_02-Loopback-UART2/
        ├── 02_01-Comandi-LED/
        └── 03_01-Protocollo-LED-e-ADC/
            ├── README.md
            ├── client_uart.py
            ├── cpp/
            │   ├── cpp.ino
            │   ├── line_receiver.h
            │   └── diagram.json
            └── micropython/
                ├── main.py
                ├── line_receiver.py
                └── diagram.json
```

- Le cartelle delle esercitazioni usano due cifre progressive e nomi separati da trattini.
- Le guide teoriche sono collocate direttamente nella cartella dell’esercitazione; la numerazione riparte da `01` in ogni cartella.
- Ogni guida comprende obiettivi, prerequisiti, teoria, collegamenti con l’architettura, frammenti commentati, link agli esempi completi, suggerimenti per il debug, autovalutazione ed esercizi progressivi.
- Gli esempi usano il formato `GG_EE-Nome-esempio`: `GG` identifica la guida e `EE` il numero dell’esempio associato.
- Il README di ciascun esempio descrive obiettivo, componenti, collegamenti, dipendenze, installazione, esecuzione, comportamento atteso e differenze tra i linguaggi.
- Nella struttura mostrata lo sketch si chiama `cpp.ino` per corrispondere alla cartella Arduino `cpp/`; il programma MicroPython usa `main.py`. Saranno aggiunti i moduli e i file delle dipendenze necessari, incluso `libraries.txt` per Wokwi quando richiesto.
- Ogni guida termina con i collegamenti all’indice generale, all’indice dell’esercitazione e alle guide precedente e successiva, omettendo le direzioni non disponibili.

La struttura illustrata è applicata alle esercitazioni disponibili; le successive seguiranno la stessa convenzione. Quando servono driver o moduli locali, ogni esempio li include nelle proprie sottocartelle.

## Verifica e documentazione delle prove

Ogni esempio dovrà distinguere **verificato in Wokwi**, **verificato su scheda reale** e **da verificare**, riportando separatamente lo stato delle versioni C++ e MicroPython. Una verifica documenterà ambiente e versioni, scheda, dipendenze, procedura, risultato atteso e osservato ed eventuali limiti.

La simulazione permette di studiare la logica e molte periferiche, ma non dimostra la correttezza elettrica del circuito, la precisione delle misure o i consumi reali. Per questi aspetti il percorso prevede prove sulla scheda. I limiti aggiornati della simulazione sono consultabili nella [tabella delle periferiche Wokwi](https://docs.wokwi.com/guides/esp32#simulation-features).

Il progetto finale sarà completato quando acquisirà e visualizzerà le misure, gestirà l’allarme e i comandi locali, recupererà la configurazione dopo un riavvio e riprenderà la comunicazione dopo un’interruzione di rete. La relazione finale dovrà includere schema dei collegamenti, istruzioni riproducibili e prove svolte per entrambe le implementazioni.
