# Funzioni, cicli e sequenze luminose

## Obiettivi e prerequisiti

Prerequisiti: guida 02 e nozioni iniziali di funzioni. Obiettivi: usare una collezione di GPIO, indicizzare correttamente i dati e separare una funzione di comando dalla sequenza temporale.

## Teoria e collegamento con l’architettura

### Sostituire ripetizioni con dati

Per tre LED potremmo scrivere tre blocchi quasi identici. Una collezione dei pin permette di esprimere una sola volta la stessa operazione. In C++ un **array** contiene elementi dello stesso tipo; in Python una **tupla** può rappresentare la sequenza fissa dei numeri dei pin e una **lista** contiene gli oggetti `Pin` creati.

L’**indice** è la posizione nella collezione e parte da zero. Per tre elementi sono validi 0, 1 e 2. Il numero GPIO contenuto nell’elemento è un’altra cosa: `LED_PINS[0]` vale 18.

| Indice | GPIO | Colore nel circuito |
| --- | --- | --- |
| 0 | 18 | Rosso |
| 1 | 19 | Giallo |
| 2 | 21 | Verde |

### Una funzione con un compito preciso

`showOnly(selected)` / `show_only(selected)` riceve l’indice da accendere. Prima spegne tutti i LED, poi accende quello selezionato. La **precondizione**, cioè la condizione necessaria prima della chiamata, è che l’indice sia valido. Il codice didattico non valida input esterni: il ciclo interno garantisce indici da 0 a 2.

La funzione non aspetta: decide soltanto le uscite. Il ciclo principale sceglie l’ordine, stampa l’indice e aspetta. Questa separazione consente di cambiare ordine e durata senza riscrivere il controllo di ciascun pin.

### Come leggere i cicli

In C++ `for (int i = 0; i < LED_COUNT; i++)` inizializza `i` a zero, verifica il limite ed esegue l’incremento dopo ogni giro. La condizione è `<`, non `<=`: includere il valore 3 accederebbe oltre l’array.

In Python `range(len(leds))` produce gli indici validi della lista. La costruzione `[Pin(number, Pin.OUT, value=0) for number in LED_PINS]` è una **comprensione di lista**: per ogni numero crea un oggetto Pin e lo inserisce nella lista. È equivalente a creare una lista vuota e aggiungere un Pin per volta.

### Collegamento con l’architettura

La CPU usa l’indice per accedere ai dati che indicano quale periferica comandare. In MicroPython gli oggetti Pin e la lista occupano RAM; in C++ la collocazione precisa delle costanti dipende da compilatore e ottimizzazioni. Una struttura di dati evita di confondere ordine applicativo e cablaggio fisico.

Le attese rimangono bloccanti per il nostro flusso: mentre un LED è acceso il ciclo non esegue altre azioni applicative. Questo è adatto a una sequenza autonoma semplice; per rispondere a pulsanti durante più attività useremo successivamente la gestione esplicita del tempo.

## Esempi commentati

Dalla [sequenza completa](esempi/03_01-Sequenza-tre-LED/README.md):

```cpp
for (int i = 0; i < LED_COUNT; i++) {
  showOnly(i);               // i è un indice, non un GPIO.
  delay(STEP_MS);
}
```

```python
for i in range(len(leds)):
    show_only(i)
    sleep_ms(STEP_MS)
```

Le definizioni delle funzioni e le inizializzazioni sono nei file completi. Le stampe presenti nell’esempio consentono di controllare l’ordine della sequenza.

## Buone pratiche e debug

Prova la funzione con ciascun indice valido prima di cambiare il ciclo. In Python un indice non valido può generare IndexError; in C++ l’accesso fuori dai limiti può avere effetti imprevedibili. Mantieni `LED_COUNT` coerente con la collezione C++ se aggiungi elementi.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Quanto vale LED_PINS[0] nell’esempio?**

   - A. 0
   - B. 1
   - C. 18
   - D. 21

2. **Quale condizione visita i tre indici validi in C++?**

   - A. i <= 3 partendo da 0
   - B. i < 3 partendo da 0
   - C. i == 3 partendo da 0
   - D. i < 0 partendo da 0

3. **Perché l’attesa è fuori dalla funzione di selezione del LED?**

   - A. Per separare comando delle uscite e durata delle fasi
   - B. Per eliminare la RAM
   - C. Per far eseguire tre istruzioni nello stesso istante
   - D. Per cambiare la tensione USB

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Scambia 18 e 21 nella collezione senza cambiare i fili.

   **Risultato atteso:** Ordine visivo invertito, mentre gli indici stampati restano 0, 1, 2.

2. **Consegna:** Realizza la sequenza di indici 0, 1, 2, 1 con 300 ms per fase.

   **Risultato atteso:** Movimento di andata e ritorno con periodo nominale 1200 ms.

3. **Consegna:** Costruisci un semaforo didattico: rosso 2 s, verde 2 s, giallo 1 s.

   **Risultato atteso:** Un solo LED acceso per volta, ordine 0 → 2 → 1 e periodo nominale 5 s; non è un dispositivo per il traffico reale.

## Soluzioni dell’autovalutazione

1. **C — 18.** L’indice zero seleziona il primo GPIO della collezione.

2. **B — i < 3 partendo da 0.** Produce gli indici 0, 1 e 2.

3. **A — Per separare comando delle uscite e durata delle fasi.** La stessa funzione può essere riutilizzata con sequenze e tempi differenti.

## Riferimenti

[Riferimento MicroPython ESP32](https://docs.micropython.org/en/latest/esp32/quickref.html).

## Navigazione del corso

- [📑 Indice generale](../../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](02-GPIO-e-uscite-digitali.md)
- [➡️ Guida successiva](04-Drive-strength-dei-GPIO.md)
