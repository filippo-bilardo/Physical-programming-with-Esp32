# Circuiti, LED e resistenze

## Obiettivi e prerequisiti

Prerequisiti: esercitazione 01 completata. Obiettivi: leggere un circuito in serie, stimare la corrente del LED, usare la breadboard e distinguere simulazione logica e misura elettrica.

## Teoria e collegamento con l’architettura

### Un percorso chiuso per la corrente

Un circuito deve collegare sorgente e ritorno attraverso i componenti. Nel nostro montaggio il GPIO alto fornisce corrente al ramo resistenza–LED e GND chiude il percorso. Se il catodo rimane scollegato, impostare HIGH non basta per accendere il LED.

Due componenti sono **in serie** quando la stessa corrente li attraversa uno dopo l’altro. In una breadboard alcuni fori sono già uniti internamente: spesso gruppi di cinque costituiscono una riga elettrica, mentre le barre laterali distribuiscono alimentazione. La disposizione e le eventuali interruzioni delle barre vanno controllate sul modello reale. Mettere entrambi i terminali di un componente nella stessa riga lo può cortocircuitare.

### Stimare una resistenza

La legge di Ohm per una resistenza è V = R × I. Per un LED occorre tenere conto della sua **caduta diretta**, la tensione ai suoi capi quando conduce. È un valore dipendente dal componente e dalla corrente, non una costante universale.

Supponiamo un GPIO vicino a 3,3 V, un LED rosso con caduta approssimata di 2 V e una resistenza da 330 Ω:

```text
Tensione sulla resistenza ≈ 3,3 V − 2,0 V = 1,3 V
Corrente ≈ 1,3 V / 330 Ω = 0,00394 A ≈ 3,9 mA
Potenza nella resistenza ≈ 1,3 V × 0,00394 A ≈ 0,0051 W
```

Una resistenza da 330 Ω, 1/4 W è adeguata a questo esempio. Il calcolo è una stima: tensione di uscita, tolleranze e caratteristiche del LED influenzano la misura. Non usare questo risultato come limite di corrente universale per qualsiasi GPIO o scheda.

Con 1 kΩ la stima diventa 1,3 mA: la corrente diminuisce e normalmente diminuisce anche la luce emessa. Il LED non è una resistenza lineare; collegarlo direttamente fra GPIO e GND non controlla adeguatamente la corrente.

### Misurare sulla scheda reale

1. A circuito spento controlla cablaggio, polarità e valore della resistenza.
2. Alimenta e imposta il multimetro sulla tensione continua, con portata adatta a pochi volt.
3. Collega il puntale nero a GND e il rosso al GPIO per leggere la tensione rispetto alla massa.
4. Misura la tensione ai capi della resistenza e stima I = V/R, senza spostare il multimetro sulla misura di corrente.
5. Scollega l’alimentazione prima di sostituire componenti.

Il multimetro in modalità corrente va inserito in serie, non fra alimentazione e massa. Per queste attività basta ricavare la corrente dalla tensione sulla resistenza: evita di cambiare modalità senza conoscere il cablaggio richiesto.

### Collegamento con l’architettura

L’uscita GPIO include un circuito di pilotaggio con capacità limitata. La CPU decide il livello logico; non fornisce direttamente energia illimitata al carico. Carichi come motori richiedono circuiti esterni dedicati. Un livello logico alto non garantisce una tensione esatta indipendentemente dalla corrente.

La simulazione è utile per controllare polarità e connessioni previste. Le misure elettriche e la luminosità fisica vanno confermate sull’hardware; un risultato visivo del simulatore non è una certificazione del circuito.

## Esempi commentati

Nell’[esempio LED e resistenza](esempi/01_01-LED-e-resistenza/README.md) l’uscita resta alta:

```cpp
pinMode(LED_PIN, OUTPUT);
digitalWrite(LED_PIN, HIGH);  // Una scrittura basta a mantenere il comando.
```

```python
led = Pin(LED_PIN, Pin.OUT, value=1)  # Imposta il livello iniziale alto.
```

Il codice non cambia quando si passa da 330 Ω a 1 kΩ: cambia il circuito elettrico, non la funzione di controllo.

## Buone pratiche e debug

Controlla la continuità della breadboard solo a circuito non alimentato. Se il LED non si accende, controlla prima polarità, riga e massa; non ridurre a caso la resistenza. Ogni ramo LED deve avere una propria resistenza.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Con 1,3 V su 330 Ω, quale corrente si stima?**

   - A. Circa 3,9 mA
   - B. Circa 330 A
   - C. Circa 1,3 A
   - D. Esattamente 0 A

2. **Cosa significa collegare resistenza e LED in serie?**

   - A. Condividere soltanto il nome
   - B. Essere attraversati dalla stessa corrente nello stesso ramo
   - C. Collegare entrambi i terminali a GND
   - D. Eliminare la polarità del LED

3. **Come si misura la tensione ai capi di una resistenza?**

   - A. Inserendo il multimetro in modalità corrente fra 3V3 e GND
   - B. Con la scheda spenta e il multimetro su corrente
   - C. Con il multimetro su tensione continua, collegato ai due capi
   - D. Toccando un solo terminale senza riferimento

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Disegna GPIO 18 → 330 Ω → LED → GND e identifica A/C.

   **Risultato atteso:** Un circuito in serie con polarità dichiarata.

2. **Consegna:** Calcola la corrente approssimata sostituendo 330 Ω con 1 kΩ, assumendo 2 V sul LED.

   **Risultato atteso:** Circa 1,3 mA, inferiore al caso iniziale.

3. **Consegna:** Su hardware misura la tensione sulla resistenza e confronta corrente ricavata e corrente stimata.

   **Risultato atteso:** Una tabella con ipotesi, misura e possibile spiegazione degli scostamenti; in assenza di hardware, prova segnata come non eseguita.

## Soluzioni dell’autovalutazione

1. **A — Circa 3,9 mA.** I = V/R = 1,3/330 A.

2. **B — Essere attraversati dalla stessa corrente nello stesso ramo.** Nel ramo in serie la corrente attraversa entrambi i componenti.

3. **C — Con il multimetro su tensione continua, collegato ai due capi.** La misura di tensione confronta i potenziali dei due capi.

## Riferimenti

[API GPIO e modalità di uscita](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html).

## Navigazione del corso

- [📑 Indice generale](../../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](../01-Introduzione-ESP32/06-Wokwi-e-Tinkercad.md)
- [➡️ Guida successiva](02-GPIO-e-uscite-digitali.md)
