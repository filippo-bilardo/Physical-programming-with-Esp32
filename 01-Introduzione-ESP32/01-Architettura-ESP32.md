# Architettura di ESP32

## Obiettivi e prerequisiti

Prerequisiti: variabili, cicli e funzioni. Al termine saprai distinguere scheda, modulo e microcontrollore, seguire il percorso dal programma al LED e spiegare perché una variabile ordinaria non sopravvive allo spegnimento.

## Teoria e collegamento con l’architettura

### Un piccolo sistema di elaborazione

Un **microcontrollore** integra elaborazione, memoria e periferiche per interagire con dispositivi esterni. Nel nostro caso il chip ESP32 si trova nel **modulo** ESP32-WROOM-32, che comprende anche componenti necessari al suo funzionamento, come memoria Flash e sezione radio. La **scheda di sviluppo** aggiunge connettore USB, alimentazione e contatti accessibili: è l’oggetto che colleghiamo al computer.

Il nome ESP32 indica anche una famiglia di prodotti. Queste prime esercitazioni sono progettate per l’ESP32 classico su DevKit WROOM: i numeri dei pin e le scelte hardware non si trasferiscono automaticamente a C3, S2 o S3.

| Componente | Compito | Esempio nel lampeggio |
| --- | --- | --- |
| CPU, unità centrale di elaborazione | Esegue istruzioni e operazioni | Esegue il ciclo che alterna i livelli |
| RAM, memoria di lavoro volatile | Conserva dati durante l’esecuzione | Contiene variabili, oggetti e pila delle chiamate |
| Flash, memoria non volatile | Conserva firmware e dati persistenti | Mantiene il programma dopo lo spegnimento |
| GPIO, ingresso/uscita generico | Collega il software a livelli elettrici | Porta GPIO 18 alto o basso |
| Periferica UART | Trasferisce dati seriali | Invia messaggi alla console tramite il convertitore USB della DevKit |
| Clock | Fornisce un riferimento temporale all’hardware | Consente il funzionamento della CPU e delle periferiche |

Il **firmware** è il software installato sul dispositivo. In C++ Arduino, gli strumenti compilano lo sketch e le librerie in un programma per il microcontrollore. Con MicroPython si installa prima un firmware contenente l’ambiente di esecuzione; questo legge il programma Python e ne esegue le operazioni. In entrambi i casi è la CPU a eseguire istruzioni: cambia il percorso con cui il sorgente arriva all’hardware.

### Dal sorgente al pin

Il comando del programma passa attraverso una **API**, cioè un insieme di funzioni offerte dall’ambiente, e raggiunge i registri della periferica GPIO. Un registro hardware è una piccola area che permette al software di configurare o osservare una periferica. Non occorre scriverlo direttamente nelle prime lezioni: le API nascondono i dettagli necessari.

```text
Programma → API Arduino / MicroPython → periferica GPIO → resistenza → LED → GND
```

Il LED si accende perché scorre corrente nel circuito esterno. Un valore 1 nella RAM non produce luce da solo: occorre configurare il GPIO e realizzare un circuito chiuso. La CPU decide il comando, la periferica mantiene il livello e l’alimentazione fornisce energia.

### Avvio, esecuzione e riavvio

Dopo un riavvio il firmware riparte. `setup()` in Arduino e le istruzioni iniziali di `main.py` ricreano lo stato del programma. I dati ordinari in RAM non sono un archivio permanente. Un file nella Flash può restare disponibile, ma una variabile non viene automaticamente salvata in quel file.

L’ESP32 può ospitare più attività software e diverse periferiche; in queste lezioni scriviamo un solo flusso applicativo. Avere hardware capace di lavorare in parallelo non rende automaticamente concorrente ogni istruzione del nostro programma.

## Esempi commentati

Questi frammenti mostrano lo stesso comando sul GPIO; studieremo sintassi e collegamenti nella guida 03.

```cpp
pinMode(18, OUTPUT);       // Configura la periferica GPIO.
digitalWrite(18, HIGH);    // Comanda un livello alto sul pin.
```

```python
from machine import Pin
led = Pin(18, Pin.OUT, value=0)
led.value(1)               # Comanda un livello alto sul pin.
```

Il [lampeggio completo](esempi/03_01-LED-lampeggiante/README.md) aggiunge un circuito, le attese e il ciclo di ripetizione. Questi frammenti da soli non sono progetti completi.

## Buone pratiche e debug

Non confondere il numero GPIO con la posizione fisica del piedino. Conserva il sorgente sul computer, anche quando lo carichi sulla scheda. Se un messaggio appare in console ma il LED è spento, separa la diagnosi del software da quella del circuito.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Quale memoria conserva ordinariamente le variabili modificabili durante l’esecuzione?**

   - A. La RAM
   - B. Il connettore USB
   - C. La breadboard
   - D. La resistenza del LED

2. **Quale descrizione distingue correttamente i due ambienti?**

   - A. MicroPython esegue il programma sul computer e manda soltanto luce alla scheda
   - B. Arduino compila lo sketch; il firmware MicroPython esegue il programma Python sulla scheda
   - C. C++ non usa la CPU
   - D. MicroPython non usa la Flash

3. **Cosa rende possibile l’accensione del LED?**

   - A. Una variabile chiamata led, anche senza circuito
   - B. La sola porta seriale aperta
   - C. Il comando GPIO e un circuito alimentato correttamente
   - D. La presenza di due core

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Disegna il percorso CPU → GPIO → LED e aggiungi resistenza e GND.

   **Risultato atteso:** Uno schema che distingue comandi e percorso della corrente.

2. **Consegna:** Classifica sorgente sul computer, variabile in esecuzione e firmware della scheda.

   **Risultato atteso:** Tre ubicazioni distinte: file sul computer, RAM della scheda e Flash della scheda.

3. **Consegna:** Dopo aver svolto il lampeggio della guida 03, riavvia e descrivi cosa riparte.

   **Risultato atteso:** Configurazione e ciclo ricominciano; il programma rimane installato, ma lo stato di esecuzione viene ricreato.

## Soluzioni dell’autovalutazione

1. **A — La RAM.** La RAM è memoria di lavoro; lo spegnimento non ne conserva normalmente il contenuto.

2. **B — Arduino compila lo sketch; il firmware MicroPython esegue il programma Python sulla scheda.** Entrambi eseguono sulla scheda, attraverso ambienti software differenti.

3. **C — Il comando GPIO e un circuito alimentato correttamente.** Il software imposta l’uscita, ma serve un percorso elettrico per la corrente.

## Riferimenti

[Documentazione ESP32 e vincoli dei GPIO](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [➡️ Guida successiva](02-Ambienti-di-sviluppo.md)
