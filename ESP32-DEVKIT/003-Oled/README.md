# OLED · Testo, grafica e misure con ESP32

## Introduzione teorica

Un display **OLED** emette luce nei propri pixel e non richiede la retroilluminazione tipica di un LCD. In questa attività usiamo un modulo **SSD1306 monocromatico 128×64 con interfaccia I²C**: ciascun pixel è acceso o spento. Il colore visibile dipende dal pannello; alcuni moduli hanno zone di colore diverso, senza permettere di scegliere liberamente il colore via software.

Il controller SSD1306 gestisce il pannello; l’ESP32 prepara testo e forme e li invia attraverso il bus. Non basta scegliere un display della stessa dimensione: un modulo SH1106 o un OLED SPI richiede un driver o un collegamento diverso.

### Il framebuffer

La libreria conserva l’immagine in un’area della RAM chiamata **framebuffer**. Per 128×64 pixel monocromatici occorrono `128 × 64 / 8 = 1024 byte`, oltre alla memoria delle altre strutture del programma.

Un fotogramma si costruisce in tre passaggi:

```cpp
oled.clearDisplay();            // Cancella l'immagine in RAM.
oled.setCursor(0, 0);
oled.print("Ciao ESP32");       // Disegna il testo nel buffer.
oled.display();                // Trasferisce l'immagine al pannello.
```

`clearDisplay()` non spegne immediatamente i pixel fisici e `print()` non invia da solo il nuovo testo. Il trasferimento avviene con `display()`. Ridisegnare tutto il fotogramma evita cifre residue quando un numero diventa più corto.

### Coordinate e dimensioni

Con l’orientamento usato negli esempi, l’origine `(0, 0)` è in alto a sinistra; `x` cresce verso destra e `y` verso il basso. I pixel validi hanno `x` fra 0 e 127 e `y` fra 0 e 63. Il font predefinito usa una cella di circa 6×8 pixel a dimensione 1; aumentando `setTextSize()` aumentano anche larghezza e altezza occupate dal testo. I nuovi sketch disattivano il ritorno a capo automatico: una scritta troppo lunga viene tagliata, quindi occorre progettare le righe.

### Bus I²C e indirizzo

Il modulo usa **SDA** per i dati e **SCL** per il clock, più alimentazione e massa. L’ESP32 seleziona il dispositivo tramite un indirizzo a 7 bit; gli esempi usano **0x3C**. Alcuni moduli rispondono invece a 0x3D: verifica con lo scanner prima di cambiare il programma.

Uno scanner rileva un ACK, cioè una risposta all’indirizzo: non identifica con certezza il controller e non dimostra che un’immagine sia visibile. Il trasferimento completo di 1024 byte richiede almeno circa 92 ms a 100 kHz, più i comandi. `display()` è un’operazione sincrona; anche un programma basato su `millis()` deve considerare questo costo.

### Pixel, bitmap e pagine di memoria

Una bitmap monocromatica associa un bit a ogni pixel: 0 e 1 rappresentano i due stati possibili. Nel framebuffer della libreria SSD1306 i byte raggruppano colonne di otto pixel verticali. Per 64 righe ci sono otto gruppi, chiamati pagine; la libreria traduce coordinate, testo e forme nella disposizione dei bit richiesta dal controller. [Implementazione Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.cpp).

Il framebuffer nell’ESP32 e la memoria grafica del display sono due memorie distinte. Se modifichi una cifra in RAM e non chiami `display()`, il pannello continua a mostrare l’immagine precedente. Se cancelli soltanto un’area troppo piccola, possono restare pixel della cifra vecchia: passare da 100 a 9 rende evidente il problema.

```mermaid
flowchart LR
    A[Valori e stato del programma] --> B[Disegno nel framebuffer ESP32]
    B --> C[Trasferimento I2C con display]
    C --> D[Memoria grafica SSD1306]
    D --> E[Pixel visibili]
```

La freccia del trasferimento richiede tempo: il disegno in RAM e la comunicazione sul bus sono due fasi diverse del lavoro.

### Indirizzamento I²C e pull-up

I²C usa linee condivise: i dispositivi possono portarle a livello basso, mentre i pull-up le riportano alte quando vengono rilasciate. La corretta tensione dei pull-up è quindi parte del collegamento elettrico. La capacità di fili e moduli rallenta la risalita del segnale: un bus funzionante con fili corti non garantisce lo stesso risultato con collegamenti molto più lunghi.

L’indirizzo a 7 bit identifica il dispositivo sul bus. Durante una transazione il bit di lettura/scrittura viene aggiunto al byte di indirizzamento: il valore da passare alla libreria rimane quello a 7 bit, per esempio `0x3C`. Il controller distingue inoltre comandi di configurazione e dati grafici; è il driver a costruire questa comunicazione. [Datasheet SSD1306, interfaccia I²C](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf).

### Frequenza di aggiornamento e budget del bus

Considerando soltanto 1024 byte grafici e nove impulsi di clock per byte, compreso l’ACK, un trasferimento richiede almeno:

```text
t_bus ≈ 1024 × 9 / f_I2C
100 kHz → circa 92,2 ms
400 kHz → circa 23,0 ms
```

Sono limiti inferiori di calcolo, con comando e overhead esclusi; il secondo valore è un confronto ipotetico con un bus configurato a 400 kHz e compatibile con tutti i componenti. A 100 kHz un obiettivo di 20 fotogrammi al secondo lascia 50 ms per fotogramma, meno dei soli 92 ms del trasferimento: il programma non può rispettarlo aumentando semplicemente la velocità del loop.

Conviene scegliere una frequenza di presentazione adatta ai dati. Una temperatura può essere aggiornata poche volte al secondo; un’animazione richiede più fotogrammi. Acquisizione, elaborazione e ridisegno possono avere intervalli differenti, conservando l’ultimo valore acquisito finché serve visualizzarlo.

### Layout e qualità della visualizzazione

Separa il valore numerico dal modo in cui viene presentato. Un codice ADC può essere filtrato e poi trasformato in percentuale; la barra usa quella percentuale, mentre il testo può mostrare anche il codice originale. Il numero di pixel disponibili limita la risoluzione grafica: su una barra larga 100 pixel più codici ADC diversi finiscono nella stessa lunghezza.

Ridisegnare soltanto quando cambiano i dati, o a un intervallo massimo definito, evita traffico inutile. La presentazione deve anche distinguere un dato valido da un errore: una schermata rimasta ferma sull’ultima misura non rende visibile che il sensore ha smesso di rispondere. Questi criteri collegano framebuffer, temporizzazione e significato dei dati mostrati.

## Materiali e collegamenti

- ESP32 classico con modulo WROOM-32, per esempio DOIT ESP32 DEVKIT V1, e cavo USB dati.
- Display **SSD1306 I²C 128×64**, con alimentazione e livelli logici compatibili con **3,3 V**.
- Breadboard e cavetti.
- Per l’esempio della barra: potenziometro lineare da **10 kΩ**.

| Display OLED | ESP32 |
| --- | --- |
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

Controlla le etichette del tuo modulo: l’ordine fisico dei terminali può cambiare. Il reset è configurato a `-1` perché il modulo previsto non richiede un GPIO di reset separato. Se il tuo modulo ha esigenze diverse, segui il suo schema.

SDA e SCL richiedono pull-up verso 3V3. Molti moduli li includono già: verifica prima di aggiungerne altri. Non alimentare il modulo in modo da portare i pull-up a 5 V sui GPIO dell’ESP32. Monta e modifica i collegamenti a scheda scollegata.

Per il potenziometro aggiungi:

| Potenziometro | ESP32 |
| --- | --- |
| Primo estremo | 3V3 |
| Secondo estremo | GND |
| Cursore centrale | GPIO 34, ADC1 |

Il GPIO 34 è un ingresso: non usarlo come uscita del display. Scambiare fra loro i due estremi del potenziometro inverte il verso della regolazione.

## Librerie e installazione

In Arduino IDE installa **esp32 by Espressif Systems** dal gestore schede e seleziona il modello reale. Per la DOIT usa **DOIT ESP32 DEVKIT V1**. Consulta, se necessario, la [guida Arduino IDE del corso](../../01-Introduzione-ESP32/04-Arduino-IDE-e-DOIT-DevKit-V1.md).

Dal gestore librerie installa:

1. **Adafruit SSD1306**, per il controller e il framebuffer.
2. **Adafruit GFX Library**, per testo e primitive grafiche.
3. **Adafruit BusIO**, dipendenza delle librerie Adafruit.

Accetta l’installazione delle dipendenze. I file `libraries.txt` elencano i nomi per Wokwi; non installano automaticamente le librerie nell’IDE del computer. Lo scanner richiede soltanto `Wire`, inclusa nel core ESP32. Registra le versioni effettive di core e librerie usate.

## File e sketch disponibili

| Sketch | Obiettivo | File da aprire |
| --- | --- | --- |
| 00 · Scanner I²C | Verificare l’indirizzo dei dispositivi | [00-Scanner-I2C.ino](00-Scanner-I2C/00-Scanner-I2C.ino) |
| 01 · Demo MyOled | Presentazione, forme, testo, bitmap e animazione | [01-Oled.ino](01-Oled/01-Oled.ino), con [MyOled.h](01-Oled/MyOled.h) e [MyOled.cpp](01-Oled/MyOled.cpp) |
| 02 · Testo e contatore | Ridisegnare testo e numeri a intervalli | [02-Testo-e-contatore.ino](02-Testo-e-contatore/02-Testo-e-contatore.ino) |
| 03 · Grafica e animazione | Muovere una pallina dentro un riquadro | [03-Grafica-e-animazione.ino](03-Grafica-e-animazione/03-Grafica-e-animazione.ino) |
| 04 · Potenziometro e barra | Visualizzare codice ADC, percentuale e barra | [04-Potenziometro-e-barra.ino](04-Potenziometro-e-barra/04-Potenziometro-e-barra.ino) |

Tutti e cinque gli sketch si trovano nelle rispettive sottocartelle di `003-Oled`. I quattro nuovi esempi sono indipendenti: ciascuno contiene il proprio `setup()` e `loop()` e non richiede `MyOled`. Apri **uno sketch alla volta** dalla sua sottocartella; il nome del file principale coincide con quello della cartella Arduino.

Per la demo 01 apri direttamente `01-Oled/01-Oled.ino`: i file `MyOled.h` e `MyOled.cpp` sono già nella stessa cartella. Non riunire gli altri sketch nella stessa cartella: Arduino compilerebbe più definizioni di `setup()` e `loop()`.

## Percorso pratico e risultati attesi

### 00 · Trovare il display

1. Apri lo scanner, compila e carica.
2. Apri il monitor seriale a **115200 baud**.
3. All’avvio e ogni tre secondi circa viene ripetuta la scansione degli indirizzi da 0x08 a 0x77.
4. Con il solo OLED previsto, è attesa una riga `I2C 0x3C`.

`Nessun dispositivo` indica che nessun indirizzo della scansione ha risposto. Se trovi 0x3D, modifica `OLED_ADDRESS` negli esempi 02–04 oppure `OLED_I2C` in `MyOled.h` per la demo 01. Nei nuovi sketch aggiorna anche le scritte o i messaggi che citano 0x3C. Non cambiare indirizzo per tentativi senza verificare i collegamenti.

### 01 · Capire la demo originale

`setup()` inizializza la seriale, controlla `oled.begin()`, chiama `hello()` e poi, se `MYOLED_DEMO` è definita, `demo()`.

La classe locale `MyOled` racchiude un oggetto Adafruit SSD1306 e offre metodi semplificati. `hello()` mostra la presentazione **DidaBot v1.0**; la demo prosegue con linee, rettangoli, cerchi, triangoli, caratteri, scorrimento e una bitmap. Alla fine entra in `testanimate()`, che anima dieci icone con una pausa di 200 ms fra i fotogrammi.

**L’animazione finale contiene un ciclo infinito:** con la demo attiva `setup()` non termina e il programma non passa al normale `loop()`. Questa scelta serve alla dimostrazione; per aggiungere letture di pulsanti o altre attività usa la struttura dell’esempio 03 o disattiva la demo.

| Metodo MyOled | Comportamento |
| --- | --- |
| `begin()` | Configura I²C su 21/22 a 100 kHz, verifica ACK e inizializzazione; restituisce `true`/`false` |
| `hello()` | Disegna la schermata iniziale e attende tre secondi |
| `demo()` | Esegue le prove grafiche, poi resta nell’animazione finale |
| `println(testo, dimensione)` | Pulisce, scrive una schermata e la trasferisce |
| `lf_println(numero)` | Mostra l’intestazione LineFollower e un intero |
| `lf_print(testo)` | Mostra l’intestazione LineFollower e una stringa |

Per provare soltanto una scritta, commenta `oled.demo()` e aggiungi dopo l’inizializzazione:

```cpp
oled.println("Ciao ESP32", 2);
```

Se vuoi vedere subito questa scritta, commenta anche `oled.hello()`. Il parametro di `println()` è la scala del font, non un numero di riga. I metodi che scrivono una schermata ne cancellano il contenuto precedente.

### 02 · Testo e contatore

Il display mostra `ESP32 OLED`, l’etichetta `Contatore:`, un numero grande e l’indirizzo. Il primo valore è **0**; a intervalli nominali di un secondo avanza fino a 9999 e poi torna a 0. La seriale riporta `CONT=n`.

Il numero conta gli aggiornamenti richiesti dal programma, non i secondi di un orologio preciso né i fotogrammi fisicamente confermati dal pannello. Il programma prepara la schermata completa prima di chiamare `display()`.

### 03 · Una pallina che rimbalza

Una pallina di raggio 4 pixel si muove nel riquadro sotto il titolo, con un aggiornamento nominale ogni **200 ms**. La seriale mostra le coordinate `X=n Y=m`.

Il centro resta fra **5 e 122** sull’asse x e fra **21 e 58** sull’asse y: il raggio viene considerato per mantenere la pallina all’interno della cornice. Al bordo la coordinata viene corretta e il verso si inverte. Il fotogramma viene cancellato e ricostruito, evitando una scia permanente.

### 04 · Una misura rappresentata con una barra

Il programma legge il potenziometro all’avvio e poi ogni **200 ms nominali**. Configura l’ADC a 12 bit con attenuazione a 11 dB e mostra:

- Il codice ADC grezzo da 0 a 4095.
- La percentuale `raw × 100 / 4095`, con divisione intera.
- Una barra larga fino a 124 pixel all’interno della cornice.

Per i codici 0, 2048 e 4095 sono attesi rispettivamente **0%, 50% e 100%**, con larghezze **0, 62 e 124** pixel. La percentuale esprime la posizione nella scala dei codici: non è una misura calibrata di tensione. La saturazione e la non linearità dell’ADC reale possono alterare la relazione con la rotazione della manopola.

Ogni aggiornamento esegue una sola conversione e stampa `ADC=n PCT=p`. In caso di ritardo il programma esegue un solo aggiornamento utile, senza recuperare campioni arretrati. Il trasferimento OLED occupa parte del tempo disponibile.

## Esecuzione in Wokwi

Ogni sottocartella include un `diagram.json`; gli esempi grafici, compresa la demo 01, includono anche `libraries.txt`.

1. Apri un modello **ESP32 Arduino** dalla [guida Wokwi](https://docs.wokwi.com/guides/esp32).
2. Copia lo sketch scelto nell’editor, usando il nome principale richiesto dal modello, normalmente `sketch.ino`.
3. Sostituisci `diagram.json` con quello della stessa sottocartella.
4. Per gli esempi 02–04 copia anche `libraries.txt` oppure aggiungi le tre librerie con il gestore del simulatore.
5. Avvia e confronta display e monitor seriale con i risultati attesi. Nell’esempio 04 muovi la manopola.

Il componente simulato è `board-ssd1306` a 0x3C. La simulazione aiuta a controllare disegno e logica; non verifica tensioni, pull-up del modulo reale o accuratezza dell’ADC. Per la demo 01 aggiungi al progetto anche entrambi i file `MyOled` e usa il diagramma incluso nella sua cartella.

## Errori comuni e limiti

| Sintomo | Verifica |
| --- | --- |
| `Adafruit_SSD1306.h: No such file` | Installa Adafruit SSD1306 e le dipendenze |
| `ERR I2C` | Il bus non è stato configurato; verifica modello e pin |
| `ERR OLED` o nessun ACK | Controlla alimentazione, SDA/SCL, massa e indirizzo con lo scanner |
| Scanner positivo ma schermo vuoto | Controlla controller, risoluzione, eventuale reset e chiamata `display()` |
| Testo tagliato o fuori schermo | Riduci font, lunghezza o coordinate della scritta |
| Più definizioni di `setup()` o `loop()` | Apri una sola sottocartella sketch per volta |
| Non viene eseguito altro dopo la demo 01 | Il ciclo finale di `testanimate()` è intenzionalmente infinito |
| Barra al massimo prima del fondo corsa | Controlla saturazione ADC, alimentazione e cablaggio del potenziometro |

I nuovi sketch e `MyOled::begin()` verificano presenza e inizializzazione **all’avvio**. Dopo un errore non ritentano automaticamente: correggi il collegamento a scheda spenta e riavvia. Un ACK non certifica il modello del display; `display()` della libreria Adafruit non restituisce un esito della consegna del fotogramma. Un distacco dopo l’avvio non viene diagnosticato in modo completo.

Le attese con `millis()` evitano lunghi `delay()` negli esempi 02–04, ma le operazioni I²C restano sincrone. Non si garantiscono un frame rate rigido o un campionamento preciso.

## Esercizi progressivi

### 1. Impaginare una schermata

**Consegna:** modifica l’esempio 02 per mostrare nome del progetto, una versione e il contatore, mantenendo tutti i contenuti visibili. Confronta font a dimensione 1 e 2.

**Risultato atteso:** niente righe troncate, sovrapposizioni o cifre residue. Spiega perché il testo più grande occupa anche più larghezza.

### 2. Costruire un cronometro

**Consegna:** sostituisci il contatore dei fotogrammi con il tempo trascorso dall’avvio ricavato da `millis()`. Mostra minuti e secondi e limita il ridisegno a quando cambia il secondo visualizzato.

**Risultato atteso:** un rallentamento del display non viene interpretato come un secondo più lungo del tempo conteggiato. Gestisci correttamente il ritorno a zero del contatore temporale.

### 3. Confrontare movimento e cancellazione

**Consegna:** nell’esempio 03 prova a omettere temporaneamente `clearDisplay()`, osserva la scia e poi ripristinalo. Modifica velocità e periodo separatamente.

**Risultato atteso:** sai distinguere pixel per aggiornamento e tempo fra aggiornamenti; la pallina continua a rispettare tutti i bordi.

### 4. Media e allarme sulla misura

**Consegna:** modifica l’esempio 04 per mediare blocchi di otto campioni e mostrare media e indicazione di allarme. Scegli una soglia con isteresi e conserva l’ultimo risultato fra due blocchi completi.

**Risultato atteso:** nessuna media iniziale con zeri fittizi; a 200 ms nominali per campione la prima media richiede circa 1,6 s. Confronta stabilità e ritardo senza attribuire al filtro una correzione della calibrazione ADC.

### 5. Menu touch e pianoforte con display

**Consegna:** integra le letture di [TouchPress](../002-TouchPress/README.md) per passare fra due pagine: testo e misura del potenziometro. Cambia pagina una sola volta per nuovo tocco, senza ripetere il comando finché il dito rimane sulla piazzola.

**Estensione:** riprendi il pianoforte capacitivo a quattro tasti e mostra sul display nome e frequenza della nota selezionata, oppure `PAUSA`. Mantieni la priorità dichiarata per i tocchi contemporanei. Aggiorna il display solo quando cambia la nota o a intervalli moderati: il trasferimento del framebuffer può ritardare la scansione dei tasti, anche se il tono è generato dal PWM hardware.

**Risultato atteso:** rilascio e cambio di nota rimangono utilizzabili; nella relazione indichi il ritardo osservato e le differenze fra programma con e senza aggiornamento OLED.

## Stato delle verifiche

Controlli locali del **24 ottobre 2026**: i cinque sketch, compresa l’implementazione `MyOled.cpp`, sono stati compilati con g++ e API sostituite, senza avvisi. Sono state superate **36 esecuzioni**: scansione, demo fino all’animazione finale, ciclo completo del contatore fino al ritorno a zero, rimbalzi sui quattro bordi, tutti i 4096 codici ADC, ritardi del ciclo, ritorno a zero del timer, errori di inizializzazione e metodi pubblici della classe. Sono stati verificati anche i cinque diagrammi JSON, i collegamenti locali e la corrispondenza fra nomi dei file principali e cartelle Arduino.

Il modello locale registra comandi di disegno e risultati della logica; non riproduce il font, il controller o il costo temporale delle chiamate I²C. Il test temporale C++ usa la larghezza nativa di `unsigned long` del computer. **Compilazione con il core ESP32 e le librerie reali, esecuzione in Wokwi e collaudo su hardware sono da eseguire.** Le procedure sopra descrivono prove e risultati attesi, non un collaudo già effettuato sulla tua scheda.

| Data | Sketch | Scheda, core e librerie | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | 00 · Scanner | — | Indirizzo e dispositivo assente | — | Da verificare |
| Da compilare | 01 · Demo | — | Sequenza grafica e animazione finale | — | Da verificare |
| Da compilare | 02 · Contatore | — | Avvio e incremento | — | Da verificare |
| Da compilare | 03 · Animazione | — | Rimbalzi sui quattro bordi | — | Da verificare |
| Da compilare | 04 · Barra | — | Minimo, centro e massimo | — | Da verificare |

## Riferimenti e navigazione

- [Adafruit SSD1306: libreria e sorgenti](https://github.com/adafruit/Adafruit_SSD1306).
- [Adafruit GFX: primitive grafiche](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives).
- [Espressif: I²C Arduino](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2c.html).
- [Espressif: ADC Arduino](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html).
- [Wokwi: display SSD1306](https://docs.wokwi.com/parts/board-ssd1306).
- [Arduino: struttura di uno sketch](https://docs.arduino.cc/arduino-cli/sketch-specification/).
- [Approfondimento del corso su OLED e framebuffer](../../07-Sensori-e-display-I2C/03-Display-OLED-e-framebuffer.md).
- [Indice ESP32-DEVKIT](../README.md).
- [Indice generale del corso](../../README.md).
