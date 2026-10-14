# Drive strength: capacità di pilotaggio dei GPIO

## Obiettivi e prerequisiti

Prerequisiti: guide 01–03 dell’esercitazione, legge di Ohm, uscite digitali, funzioni e cicli. Al termine saprai configurare il drive strength, distinguerlo dalla regolazione di corrente e dal PWM, e dimensionare una resistenza in serie al LED. Tutti gli esempi collegano il LED tramite una resistenza da 220 Ω.

## Teoria e collegamento con l’architettura

### Dal bit logico al circuito di uscita

Il **drive strength** è la capacità di pilotaggio dello stadio elettrico di uscita del GPIO. Il livello HIGH/LOW sceglie lo stato logico; il drive strength modifica le caratteristiche del circuito che lo sostiene quando il carico richiede corrente.

Un’uscita **push-pull** può fornire corrente al carico quando è alta (*source*) e assorbirla verso massa quando è bassa (*sink*). Nel collegamento GPIO → resistenza → LED → GND usiamo il primo caso. Il GPIO reale non è una sorgente di tensione ideale: sotto carico la tensione alta può scendere rispetto all’alimentazione, mentre quella bassa può salire rispetto a GND.

Un modello utile rappresenta il pilotaggio con una **resistenza interna equivalente**. Aumentare il drive strength riduce in genere tale resistenza e permette di sostenere meglio il livello sotto carico. Non viene aggiunta una resistenza discreta al circuito: il parametro agisce sui transistor dello stadio d’uscita. È un modello approssimato, non un componente lineare esatto.

### I quattro livelli sull’ESP32 classico

Il port ESP32 di MicroPython espone quattro livelli, corrispondenti alle impostazioni ESP-IDF usate anche dal core Arduino-ESP32. I valori indicativi seguenti provengono dal [riferimento MicroPython ESP32](https://docs.micropython.org/en/latest/esp32/quickref.html#pins-and-gpio):

| Livello | C++ con ESP-IDF | MicroPython | Classe di pilotaggio indicativa | Resistenza interna approssimata |
| --- | --- | --- | --- | --- |
| 0 | `GPIO_DRIVE_CAP_0` | `Pin.DRIVE_0` | 5 mA | 130 Ω |
| 1 | `GPIO_DRIVE_CAP_1` | `Pin.DRIVE_1` | 10 mA | 60 Ω |
| 2 | `GPIO_DRIVE_CAP_2` | `Pin.DRIVE_2` | 20 mA | 30 Ω |
| 3 | `GPIO_DRIVE_CAP_3` | `Pin.DRIVE_3` | 40 mA | 15 Ω |

L’esempio mostra tutti e quattro i livelli, incluso quello da 40 mA. DRIVE_3 resta una classe di pilotaggio e non significa che il LED assorba 40 mA: la resistenza esterna da 220 Ω continua a limitare il ramo.

Questi numeri **non sono correnti imposte al carico**, né una garanzia che ogni pin possa erogare quella corrente in qualsiasi condizione. Per il progetto elettrico contano i limiti, le condizioni di misura e le tensioni garantite del [datasheet ESP32](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf), oltre ai vincoli complessivi della scheda. Non trasferire la tabella automaticamente ad altre famiglie ESP32.

La documentazione indica il livello 2 come predefinito, ma firmware e librerie possono riconfigurare i GPIO. Nell’esperimento impostiamo esplicitamente il livello desiderato. `GPIO_DRIVE_CAP_MAX` è un limite dell’enumerazione, non un quinto livello da usare.

### Perché la resistenza del LED rimane necessaria

Selezionare DRIVE_0 non crea un limitatore da 5 mA. Selezionare DRIVE_3 non forza 40 mA nel LED. I valori in mA della tabella descrivono classi di pilotaggio, non una corrente imposta o un interruttore di sicurezza. Il drive strength modifica il comportamento dei transistor d’uscita; non regola la corrente come farebbe un alimentatore a corrente costante.

Il LED ha una curva corrente-tensione molto ripida: una piccola variazione di tensione può produrre una grande variazione di corrente. Le caratteristiche cambiano inoltre tra LED, temperatura e componenti. Senza una resistenza esterna, la corrente sarebbe determinata solo da queste variazioni e dall’impedenza interna del GPIO, che è approssimata e non è specificata come limitatore affidabile. Si può superare il valore ammesso dal LED o caricare troppo il GPIO, danneggiando uno o entrambi. La resistenza in serie aggiunge invece un elemento prevedibile che limita la corrente in tutte le fasi e resta necessaria qualunque drive strength si scelga. Va comunque dimensionata rispettando i datasheet del LED e della scheda.

Per un LED rosso con caduta ipotizzata di 2 V, alimentazione di 3,3 V e resistenza da 220 Ω, un modello semplificato che include la resistenza interna indicativa dà:

```text
I ≈ (3,3 V − 2,0 V) / (R_esterna + R_interna)
DRIVE_0: I ≈ 1,3 / (220 + 130) A ≈ 3,7 mA
DRIVE_1: I ≈ 1,3 / (220 + 60) A ≈ 4,6 mA
DRIVE_2: I ≈ 1,3 / (220 + 30) A ≈ 5,2 mA
DRIVE_3: I ≈ 1,3 / (220 + 15) A ≈ 5,5 mA
```

Sono stime illustrative basate su 3,3 V, LED con caduta di circa 2 V, resistenza esterna nominale da 220 Ω e resistenza interna approssimata: non valori obbligatori da ritrovare al multimetro. La caduta del LED cambia con la corrente e il modello interno varia con chip e condizioni operative. In particolare, la stima DRIVE_3 non è un invito a scegliere il massimo: verifica sempre i limiti del datasheet e usa la resistenza esterna come limitatore progettato. Con un carico leggero le differenze possono essere piccole; la sola vista non è uno strumento di misura affidabile.

### Drive strength, PWM e pull-up

| Impostazione | Cosa modifica | Cosa non garantisce |
| --- | --- | --- |
| HIGH/LOW | Stato logico comandato | Tensione ideale indipendente dal carico |
| Drive strength | Capacità elettrica del pilotaggio d’uscita | Corrente costante o protezione del LED |
| PWM | Frazione di tempo acceso/spento, a una certa frequenza | Limite alla corrente istantanea durante l’accensione |
| Pull-up/pull-down | Debole collegamento di polarizzazione del nodo | Pilotaggio di un carico di potenza |

Il **PWM**, che studieremo più avanti, è la modulazione della durata degli impulsi e serve anche a regolare la luminosità media. Il drive strength non è il comando da scegliere per ottenere una scala di luminosità precisa.

### Architettura e transizioni

La CPU scrive una configurazione che raggiunge lo stadio del GPIO attraverso i registri delle periferiche. Il pad, cioè il circuito elettrico associato al terminale, applica il pilotaggio selezionato; non occorre riscrivere il parametro a ogni istruzione.

Il pilotaggio influenza anche la carica e scarica delle capacità presenti sui collegamenti: fronti più rapidi possono rendere più evidenti disturbi e oscillazioni. Per segnali veloci si sceglie il livello adeguato al carico e al cablaggio, senza assumere che il massimo sia sempre preferibile. Il LED lento del laboratorio non permette di misurare questi effetti; servirebbero oscilloscopio e una prova dedicata.

## Esempi commentati

Nel [confronto dei quattro livelli da 5, 10, 20 e 40 mA](esempi/04_01-Confronto-drive-strength/README.md) il GPIO 18 viene configurato a LED spento, poi mantenuto alto per cinque secondi e basso per uno.

```cpp
#include "driver/gpio.h"
// Dopo pinMode(18, OUTPUT), all'interno di una funzione:
gpio_set_drive_capability(GPIO_NUM_18, GPIO_DRIVE_CAP_0);
// Con R esterna da 220 ohm: corrente indicativa circa 3,7 mA, non misurata.
```

La funzione è parte di ESP-IDF, incluso nel core Arduino-ESP32; restituisce un codice di esito. Questa versione elementare, con pin e livelli fissi, non controlla il codice restituito. Lo sketch usa tre blocchi di chiamate dirette, senza array, condizioni o cicli sugli indici. Le scritte seriali indicano il drive richiesto; la corrente effettiva non viene misurata né calcolata e la scritta non conferma la configurazione hardware. API e livelli sono descritti nel [riferimento GPIO Espressif](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html).

```python
from machine import Pin
led = Pin(18, Pin.OUT, value=0)
led.init(drive=Pin.DRIVE_0)  # Mantiene gli altri parametri non specificati.
```

Su ESP32 si usa il parametro `drive` del costruttore o di `init`; il metodo `Pin.drive()` non è un’API portabile disponibile su tutti i port. La [documentazione di Pin](https://docs.micropython.org/en/latest/library/machine.Pin.html) distingue queste possibilità. L’esempio richiede firmware ESP32 con le tre costanti usate nell’esempio supportate.

## Buone pratiche e debug

- Collega sempre il LED in serie a una resistenza: negli esempi è da 220 Ω. Il drive strength non sostituisce il limitatore.
- Usa GPIO 18, che supporta l’uscita, e configura la direzione prima del drive strength.
- Non interpretare la scritta `Drive 20 mA` come una misura: indica il pilotaggio richiesto. Il messaggio dichiara che la corrente effettiva non è misurata.
- Se una costante o un parametro manca, controlla modello e versione del firmware. Non ignorare l’errore continuando una prova che non cambia realmente impostazione.
- Nel simulatore osserva ordine e tempi. Non attribuire alla luminosità simulata una misura della resistenza interna o del drive strength.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Che cosa fa DRIVE_0 nell’esperimento?**

   - A. Impone sempre esattamente 5 mA.
   - B. Seleziona il livello più debole di pilotaggio fra i quattro disponibili.
   - C. Disabilita automaticamente il GPIO.
   - D. Sostituisce la resistenza del LED.

2. **Perché rimane la resistenza esterna da 220 Ω?**

   - A. Per limitare la corrente del ramo anche quando cambia il pilotaggio.
   - B. Per scegliere il numero del GPIO.
   - C. Per memorizzare il livello DRIVE_3.
   - D. Per installare il driver USB.

3. **Quale metodo è adatto a regolare la luminosità media tramite tempi acceso/spento?**

   - A. Aumentare la velocità della porta USB.
   - B. Eliminare il catodo del LED.
   - C. Il PWM, mantenendo un circuito elettrico correttamente dimensionato.
   - D. Impostare GPIO_DRIVE_CAP_MAX.

## Esercizi pratici

1. **Consegna:** esegui il programma e annota ordine e durata delle fasi.

   **Risultato atteso:** DRIVE_0 → DRIVE_1 → DRIVE_2 → DRIVE_3; cinque secondi acceso e uno spento per fase, giro nominale di 24 s. La prova di flusso è predisposta per Wokwi.

2. **Consegna:** realizza il circuito dell’esempio su hardware con una resistenza da 220 Ω in serie; misura la tensione ai suoi capi e calcola I = V/R.

   **Risultato atteso:** una tabella di tre misure, con unità e incertezza dello strumento. Confronta le misure senza forzarle a coincidere con la tabella indicativa del drive strength.

3. **Consegna:** togli alimentazione, sostituisci la resistenza da 220 Ω con 1 kΩ e ripeti la prova reale.

   **Risultato atteso:** corrente complessivamente inferiore; spiega il ruolo dominante della resistenza esterna e perché potrebbe essere difficile distinguere le fasi a occhio.

## Soluzioni dell’autovalutazione

1. **B — Seleziona il livello più debole di pilotaggio fra i quattro disponibili.** La corrente effettiva dipende dal circuito, non dal solo indice.
2. **A — Per limitare la corrente del ramo anche quando cambia il pilotaggio.** Il parametro non è un generatore di corrente costante né una protezione contro i cortocircuiti.
3. **C — Il PWM, mantenendo un circuito elettrico correttamente dimensionato.** Cambia il tempo medio di accensione; il dimensionamento elettrico resta necessario.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](03-Funzioni-cicli-e-sequenze.md)
- [➡️ Guida successiva](../03-Ingressi-digitali-e-pulsanti/01-Ingressi-pull-up-e-pull-down.md)
