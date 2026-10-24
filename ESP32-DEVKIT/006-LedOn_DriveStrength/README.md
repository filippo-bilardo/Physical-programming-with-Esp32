# LED · Drive strength dei GPIO ESP32

## Introduzione teorica

Il **drive strength**, o capacità di pilotaggio, configura lo stadio elettrico di uscita di un GPIO. `digitalWrite()` sceglie HIGH o LOW; il drive strength influenza il modo in cui il circuito di uscita sostiene quel livello quando il carico richiede corrente.

Un GPIO configurato come uscita push-pull può fornire corrente al carico quando è alto e assorbirla verso GND quando è basso. Lo stadio di uscita ha un’impedenza interna: sotto carico il livello HIGH può scendere rispetto alla tensione di alimentazione. Un pilotaggio più forte permette in genere di sostenere meglio il livello e modifica la carica e scarica delle capacità del collegamento. Il risultato dipende da carico, cablaggio e caratteristiche del chip.

### Livelli di pilotaggio e corrente effettiva

L’ESP32 classico espone quattro impostazioni, dalla più debole alla più forte:

| Costante | Livello |
| --- | --- |
| `GPIO_DRIVE_CAP_0` | Più debole |
| `GPIO_DRIVE_CAP_1` | Intermedio |
| `GPIO_DRIVE_CAP_2` | Più forte del livello 1 |
| `GPIO_DRIVE_CAP_3` | Più forte fra i quattro disponibili |

La funzione `gpio_set_drive_capability()` imposta il livello del pin. I valori in mA riportati nel commento iniziale dello sketch descrivono classi indicative di pilotaggio: **non rappresentano una corrente imposta al LED o misurata dal programma**. La corrente reale dipende dalla tensione d’uscita, dal LED e dalla resistenza del circuito. Per condizioni e limiti elettrici occorre consultare il datasheet del modello usato. [Espressif: configurazione GPIO](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html).

### Perché serve sempre una resistenza

La corrente di un LED può crescere rapidamente al variare della tensione applicata. Il drive strength **non è un limitatore di corrente**: anche al livello più debole occorre una resistenza esterna in serie, dimensionata per il LED e per il GPIO.

Usa una resistenza da **220 Ω**. Con un’uscita idealizzata a 3,3 V e un LED rosso con caduta di circa 2 V, la legge di Ohm dà:

```text
I ≈ (3,3 − 2,0) / 220 ≈ 0,0059 A = 5,9 mA
```

È una stima: la tensione del GPIO sotto carico e la caduta reale del LED cambiano il risultato. La luminosità può variare poco fra due livelli e non fornisce una misura affidabile della corrente. Per misurarla, rileva la tensione ai capi della resistenza e calcola `I = V_R / 220`.

### Differenza rispetto al PWM

Il PWM regola la frazione di tempo in cui l’uscita è alta, modificando la luminosità media. Il drive strength modifica invece le caratteristiche elettriche dell’uscita durante il pilotaggio. La resistenza rimane necessaria anche quando si usa il PWM, perché limita la corrente durante ogni impulso.

### Modello equivalente dell’uscita sotto carico

Per interpretare le misure si può rappresentare lo stadio HIGH con un generatore ideale e una resistenza interna equivalente `R_out`. È un modello locale e approssimato dei transistor, non una resistenza fisica costante valida a qualsiasi corrente.

```text
3,3 V ideali → R_out equivalente → GPIO → R_esterna 220 Ω → LED → GND
```

Con questo modello la corrente sarebbe:

```text
I ≈ (3,3 − V_F) / (R_out + R_esterna)
```

Per esempio, assumendo soltanto per il calcolo `R_out = 100 Ω` e `V_F = 2 V`, si ottengono circa 4,1 mA. Con `R_out = 30 Ω` si ottengono circa 5,2 mA. **I due valori di resistenza interna sono ipotesi illustrative, senza corrispondenza assegnata alle costanti DRIVE**. Mostrano perché rafforzare l’uscita può aumentare la corrente e perché una resistenza esterna molto maggiore di `R_out` riduce la differenza fra i livelli.

### Capacità del collegamento e velocità dei fronti

Un filo, un ingresso collegato e una sonda presentano capacità elettrica. Per passare da LOW a HIGH occorre caricarla; per tornare a LOW occorre scaricarla. Nel modello RC il tempo caratteristico è `τ = R × C`: aumentando capacità o impedenza del pilotaggio, la transizione diventa più lenta.

Un pilotaggio più forte può accelerare il fronte, ma fili e piste introducono anche induttanza e riflessioni. Fronti molto rapidi possono produrre sovraelongazioni e disturbi. Il livello adatto si sceglie quindi rispetto al carico e alla velocità del segnale. Le fasi di due secondi del LED non permettono di vedere transizioni elettriche che avvengono su scale temporali molto più brevi.

### Sorgente, assorbimento e riferimento di misura

Nel ramo GPIO → resistenza → LED → GND il GPIO fornisce corrente quando è HIGH. Un circuito con LED e resistenza verso l’alimentazione può invece richiedere assorbimento di corrente quando il GPIO è LOW e avere logica di accensione invertita. La polarità del comando e la funzione elettrica vanno lette sul circuito effettivo.

Misurare il GPIO rispetto a GND rileva la tensione d’uscita; misurare fra i due terminali della resistenza rileva la sua caduta, da cui si ricava la corrente. Sono misure diverse. Per esempio, 1,1 V sulla resistenza da 220 Ω corrispondono a 5 mA, mentre 3,0 V sul GPIO non permettono da soli di conoscere la corrente senza considerare LED e resistenza.

### Come confrontare correttamente i livelli

Mantieni invariati LED, resistenza, alimentazione, strumento e cablaggio; cambia soltanto il livello di pilotaggio. Registra tensione sul GPIO, tensione sulla resistenza e corrente calcolata. Ripeti la misura per distinguere differenze riproducibili da oscillazioni dello strumento o dal riscaldamento del componente.

La tolleranza della resistenza e la risoluzione del voltmetro introducono incertezza: risultati vicini possono non essere distinguibili con lo strumento usato. Una scritta seriale conferma soltanto il percorso del software; una misura elettrica verifica ciò che accade sul ramo. Questi criteri spiegano anche perché la luminosità simulata non è una caratterizzazione del pilotaggio reale.

## Materiali e collegamenti

Servono ESP32 classico WROOM-32, per esempio DOIT ESP32 DEVKIT V1, un LED, una resistenza da **220 Ω**, cavetti e cavo USB dati.

```text
GPIO 21 → resistenza 220 Ω → anodo LED
GND     ← catodo LED
```

Il GPIO 21 è il pin usato dallo sketch; non coincide necessariamente con la posizione fisica 21 del connettore. Usa logica a 3,3 V e modifica i collegamenti a scheda scollegata.

![Fotografia della dimostrazione con ESP32 e LED](DriveStrength.PNG)

La fotografia illustra la prova. Per il montaggio segui il circuito riportato sopra, con la resistenza da 220 Ω in serie al LED.

## Sketch e risultato atteso

Apri [006-LedOn_DriveStrength.ino](006-LedOn_DriveStrength.ino) in Arduino IDE, seleziona scheda e porta corrette con il core **esp32 by Espressif Systems**. Lo sketch usa l’API ESP-IDF inclusa nel core; per dichiarare esplicitamente funzione e tipi inserisci all’inizio, se necessario:

```cpp
#include "driver/gpio.h"
```

Il nome della cartella coincide già con quello del file principale. Apri il monitor seriale a **115200 baud**.

All’avvio il LED resta acceso per un secondo. Il loop prova **soltanto i livelli 0, 1 e 2**, nell’ordine: per ciascuno stampa il nome della costante e mantiene il LED acceso per 2 s, seguito da 200 ms spento. Il periodo nominale del giro è quindi 6,6 s, oltre al tempo del codice. Il livello 3 è descritto nella teoria ma non viene eseguito da questo sketch.

Le stampe indicano il livello richiesto; il programma non misura corrente o tensione e non controlla l’esito della chiamata di configurazione. Le attese sono bloccanti. Un esempio separato con tutti e quattro i livelli è disponibile nel [confronto del drive strength](../../02-Uscite-digitali-e-LED/esempi/04_01-Confronto-drive-strength/README.md).

## Simulazione e verifica pratica

È disponibile il [progetto Wokwi della dimostrazione](https://wokwi.com/projects/330929970048139859). Per riprodurre il circuito reale mantieni la resistenza da 220 Ω anche se un vecchio schema mostra un collegamento diverso. Usa il simulatore per studiare ordine e tempi; la verifica delle differenze elettriche richiede misure sul circuito fisico.

## Esercizi

1. Prevedi e verifica sulla seriale l’ordine dei livelli e il periodo nominale del giro.
2. Per ciascun livello misura la tensione sulla resistenza da 220 Ω e calcola la corrente. Confronta i valori osservati senza interpretarli come correnti fissate dalla costante.
3. A scheda scollegata sostituisci la resistenza con 1 kΩ, ripeti le misure e spiega perché la corrente diminuisce.
4. Confronta questo programma con un esempio PWM e descrivi quale parametro cambia in ciascun caso.

## Riferimenti e navigazione

- [Approfondimento sul drive strength e sulla resistenza del LED](../../02-Uscite-digitali-e-LED/04-Drive-strength-dei-GPIO.md).
- [API GPIO di Espressif](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html).
- [Datasheet ESP32](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf).
- [Indice ESP32-DEVKIT](../README.md).

Documentazione verificata rispetto al codice presente; compilazione e misure fisiche non eseguite durante questo controllo.
