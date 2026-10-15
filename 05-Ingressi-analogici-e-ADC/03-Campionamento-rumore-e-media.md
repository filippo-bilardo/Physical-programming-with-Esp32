# Campionamento, rumore e media

## Obiettivi e prerequisiti

Prerequisiti: guide 01–02, somma, divisione intera e temporizzazioni dell'esercitazione 04. Imparerai a definire un intervallo di campionamento, osservare la variabilità e calcolare una media senza inserire un'attesa per ciascun campione dentro un ciclo bloccante.

## Teoria e collegamento con l'architettura

### Un segnale continuo, letture a istanti separati

Il potenziometro può cambiare tensione in qualunque istante; il programma acquisisce soltanto alcuni valori. Con intervallo nominale `T = 20 ms`, la frequenza nominale è `f = 1 / 0,020 s = 50 campioni/s`, cioè 50 Hz. Con 200 ms era 5 Hz.

Sono frequenze di campionamento, non la frequenza del segnale analogico e neppure quella della CPU. Le conversioni, le stampe e le altre operazioni hanno un costo. Il programma aggiorna il riferimento con il tempo osservato: un ritardo sposta i campioni successivi e non genera una raffica di letture per recuperare quelle perse.

L'ADC converte, la CPU accumula i risultati, la RAM conserva somma, conteggio, minimo e massimo. L'esempio non usa un buffer di tutti i campioni e non acquisisce in parallelo tramite DMA.

### Perché il valore non è perfettamente fermo?

Con la manopola immobile, letture reali possono variare per rumore elettrico, alimentazione, contatti e quantizzazione. Una componente variabile può essere ridotta da una media, mentre un errore sistematico resta: se tutte le letture sono troppo alte, anche la media lo sarà.

Non è necessario osservare rumore nel simulatore. Wokwi può offrire un segnale molto stabile: questo permette di provare l'algoritmo, ma non dimostra l'assenza di rumore su hardware.

### Media a blocchi di otto letture

Nell'[esempio completo](esempi/03_01-Media-di-otto-campioni/README.md) si acquisisce un campione ogni 20 ms. Dopo otto letture si stampa la media intera e si ricomincia con un blocco nuovo. È una **media a blocchi non sovrapposti**, non una media mobile aggiornata a ogni campione.

```text
Campioni:   1990 2010 1990 2010 1990 2010 1990 2010
Somma:      16000
Media:      2000
Minimo:     1990
Massimo:    2010
Ultimo:     2010
```

L'ultimo valore e la media descrivono informazioni diverse. La prima riga arriva nominalmente a 160 ms dall'avvio: campioni a 20, 40, 60, 80, 100, 120, 140 e 160 ms. Le righe successive arrivano ogni 160 ms nominali, circa 6,25 righe/s. Fra primo e ultimo campione dello stesso blocco passano 140 ms.

## Esempi commentati

L'accumulo centrale, eseguito soltanto quando scade il campionamento:

```cpp
total += raw;  // total e' long.
count++;
if (count == SAMPLES) {
  const int average = total / SAMPLES;
  // Nel programma completo stampa anche ultimo, minimo e massimo.
  total = 0;
  count = 0;
}
```

```python
total += raw
count += 1
if count == SAMPLES:
    average = total // SAMPLES
    total = 0
    count = 0
```

Il programma completo inizializza minimo e massimo con il **primo campione del blocco**, non con zero. La somma massima per otto codici a 12 bit è `8 × 4095 = 32760`. In C++ usiamo comunque `long` per rendere più ampio l'accumulatore; se cambi numero di campioni o risoluzione, ricontrolla il prodotto massimo.

### Compromesso tra stabilità e ritardo

Una media più lunga può ridurre fluttuazioni casuali ma rallenta la risposta e mescola valori prima e dopo una variazione. Nell'esempio, un singolo impulso può essere attenuato anziché segnalato subito. Non usare la media come protezione universale per eventi rapidi.

Campionare ogni 20 ms è adeguato alla lenta regolazione manuale proposta. Per ricostruire un segnale variabile serve invece una scelta della frequenza in base alla sua banda: il criterio ideale richiede più del doppio della massima frequenza da rappresentare. Componenti oltre metà della frequenza di campionamento possono apparire come frequenze diverse, fenomeno detto **aliasing**. Una media software dopo l'acquisizione non elimina l'aliasing già avvenuto; servono anche condizioni e filtraggio analogico appropriati.

## Buone pratiche e debug

- Non dividere la somma prima che il blocco sia completo.
- Non inserire otto `sleep_ms(20)` consecutivi per costruire il blocco: conserva i dati tra i giri.
- Stampa una riga per blocco, non una riga aggiuntiva in ogni giro del ciclo.
- Se minimo, massimo e media coincidono nel simulatore, il risultato è valido per un ingresso costante.
- Se l'uscita sembra lenta, calcola prima durata del blocco e intervallo di pubblicazione.

## Autovalutazione

1. **Un campione ogni 20 ms corrisponde nominalmente a:**

   - A. 20 Hz.
   - B. 50 Hz.
   - C. 200 Hz.
   - D. 1000 Hz.

2. **Una media di otto letture corregge automaticamente un errore sistematico dell'ADC?**

   - A. Sì, sempre.
   - B. Sì, perché aumenta la tensione di alimentazione.
   - C. No, l'errore comune alle letture può rimanere nella media.
   - D. Solo con un LED verde.

3. **Quando si stampa la prima media dell'esempio?**

   - A. All'avvio, usando sette zeri.
   - B. Dopo il primo campione.
   - C. Dopo un riavvio della console.
   - D. Dopo otto campioni, nominalmente a 160 ms.

## Esercizi pratici

1. **Consegna:** mantieni fermo il potenziometro e osserva dieci blocchi.

   **Risultato atteso:** la media cade fra minimo e massimo di ciascun blocco. Sul dispositivo reale quantifica l'escursione con `massimo − minimo`.

2. **Consegna:** passa da otto a quattro campioni, mantenendo 20 ms.

   **Risultato atteso:** prima riga dopo circa 80 ms, poi circa 12,5 righe/s; cambia il compromesso fra filtraggio e risposta. Aggiorna l'intestazione `media8` in `media4`.

3. **Consegna:** provoca un cambiamento netto del segnale durante un blocco e confronta ultimo valore e media.

   **Risultato atteso:** un blocco può contenere entrambi i livelli; la media descrive quel gruppo, non soltanto il livello corrente. Il primo blocco interamente dopo il cambiamento torna coerente con il nuovo livello.

## Soluzioni dell'autovalutazione

1. **B.** Un secondo contiene cinquanta intervalli da 20 ms.
2. **C.** Ridurre la dispersione e correggere un errore di misura sono obiettivi diversi.
3. **D.** Non vengono inserite letture iniziali fittizie.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente](02-Risoluzione-attenuazione-e-misura.md)
- [➡️ Guida successiva](04-Soglia-regolabile-e-isteresi.md)
