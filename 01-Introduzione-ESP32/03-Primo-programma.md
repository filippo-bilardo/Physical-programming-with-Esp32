# Primo programma: LED lampeggiante

## Obiettivi e prerequisiti

Prerequisiti: guide 01 e 02, ambiente configurato. Obiettivi: montare un ramo LED, riconoscere configurazione e ciclo, modificare tempi e confrontare i due linguaggi.

## Teoria e collegamento con l’architettura

### Il circuito minimo

La **tensione** è una differenza di potenziale tra due punti; la **corrente** è il flusso di carica in un percorso chiuso. Una **resistenza** limita la corrente. **GND**, o massa, è il riferimento comune delle tensioni del circuito. Un **LED** è un diodo che emette luce: ha un anodo A e un catodo C e richiede la corretta polarità.

Per questa prova usa un LED rosso con resistenza da **330 Ω**: GPIO 18 → resistenza → anodo; catodo → GND. La resistenza può stare prima o dopo il LED purché sia nello stesso ramo in serie. Il suo dimensionamento sarà approfondito nell’esercitazione 02. Non eliminarla durante le prove.

Monta a USB scollegata. Verifica la sigla del GPIO sulla scheda, i collegamenti della breadboard e l’assenza di contatti accidentali. I livelli dei GPIO sono a 3,3 V: il pin 5V/VIN della scheda non è un livello logico da applicare ai GPIO. Usiamo un LED esterno per non dipendere dalla presenza e dal cablaggio del LED integrato.

### Configurare una volta, ripetere molte volte

In Arduino `setup()` viene eseguita una volta all’avvio; il framework chiama `loop()` in continuazione. In MicroPython le istruzioni iniziali vengono eseguite in ordine e poi un `while True` ripete il corpo indefinitamente. `True` è il valore booleano vero.

Le **costanti** assegnano un nome a valori che il programma non modifica. `const` esprime questa intenzione in C++; in Python i nomi maiuscoli sono una convenzione, non un vincolo imposto dal linguaggio. Sostituire 500 con un nome come `ON_MS` chiarisce l’unità di misura.

Il ciclo accende, attende, spegne e attende. Il GPIO mantiene il livello durante l’attesa: non bisogna riscrivere continuamente HIGH. `delay` e `sleep_ms` sospendono l’avanzamento di questo flusso applicativo; non significano che tutta la scheda smetta di funzionare.

### Tempo acceso e periodo

Il **periodo** è la durata di un ciclo completo. Trascurando il tempo delle istruzioni:

```text
T = tempo acceso + tempo spento
f = 1 / T, con T espresso in secondi
```

Con 500 ms acceso e 500 ms spento, T = 1 s e f = 1 Hz. Con 200 ms acceso e 800 ms spento il periodo resta 1 s, ma il LED è acceso soltanto per il 20% del ciclo. I valori sono nominali: stampe e gestione del runtime aggiungono tempo.

### Architettura in azione

La Flash conserva il programma; la CPU esegue chiamate e ciclo; la RAM ospita lo stato di esecuzione; la periferica GPIO pilota il pin e la UART invia i messaggi. Il programma esprime un tempo di attesa usando servizi del runtime. Non stiamo ancora programmando direttamente un timer hardware.

## Esempi commentati

Dal [lampeggio completo](esempi/03_01-LED-lampeggiante/README.md):

```cpp
digitalWrite(LED_PIN, HIGH);  // GPIO alto: LED acceso nel circuito proposto.
delay(ON_MS);                // Millisecondi, non secondi.
digitalWrite(LED_PIN, LOW);
delay(OFF_MS);
```

```python
led.value(1)                 # Equivalente logico di HIGH.
sleep_ms(ON_MS)
led.value(0)
sleep_ms(OFF_MS)
```

Il [secondo esempio](esempi/03_02-Variazione-temporizzazione/README.md) mantiene lo stesso circuito e separa i tempi acceso/spento. Il codice completo in entrambe le cartelle include configurazione e stampe.

## Buone pratiche e debug

In Python mantieni quattro spazi coerenti nei blocchi e non mescolare tabulazioni. In C++ controlla parentesi graffe e punti e virgola. Prima di modificare i fili verifica che il programma invii i messaggi previsti. Non usare lampeggi velocissimi come misura precisa di frequenza: vista umana e console hanno limiti.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Con 200 ms acceso e 800 ms spento, qual è il periodo nominale?**

   - A. 200 ms
   - B. 800 ms
   - C. 1000 ms
   - D. 1600 ms

2. **Qual è il ruolo della resistenza in serie?**

   - A. Memorizzare il programma
   - B. Limitare la corrente nel LED
   - C. Aumentare la frequenza della CPU
   - D. Cambiare il numero del GPIO

3. **Durante delay(500), cosa accade al GPIO precedentemente impostato HIGH?**

   - A. Diventa automaticamente un ingresso
   - B. Il LED deve essere riscritto ogni millisecondo
   - C. Si scollega dalla massa
   - D. Mantiene il livello comandato

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Esegui il primo esempio e annota cinque coppie di messaggi.

   **Risultato atteso:** Alternanza coerente fra console e LED.

2. **Consegna:** Esegui il secondo esempio, poi scambia 200 e 800 ms.

   **Risultato atteso:** Stesso periodo nominale, durata dell’accensione differente.

3. **Consegna:** Crea in entrambi i linguaggi tre lampi da 100 ms, ciascuno seguito da 100 ms spento, e aggiungi una pausa di 1400 ms.

   **Risultato atteso:** Tre lampi raggruppati ogni 2 s nominali; la pausa finale si somma ai 600 ms del gruppo.

## Soluzioni dell’autovalutazione

1. **C — 1000 ms.** Il periodo comprende entrambe le fasi.

2. **B — Limitare la corrente nel LED.** La resistenza limita la corrente del ramo elettrico.

3. **D — Mantiene il livello comandato.** La periferica mantiene lo stato senza una nuova scrittura continua.

## Riferimenti

[GPIO Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html), [riferimento MicroPython ESP32](https://docs.micropython.org/en/latest/esp32/quickref.html).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](02-Ambienti-di-sviluppo.md)
- [➡️ Guida successiva](04-Arduino-IDE-e-DOIT-DevKit-V1.md)
