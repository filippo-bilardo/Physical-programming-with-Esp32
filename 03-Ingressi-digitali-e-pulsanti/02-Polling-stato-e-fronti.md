# Polling, stato e fronti

## Obiettivi e prerequisiti

Prerequisiti: guida 01, variabili booleane e condizioni. Obiettivi: distinguere livello ed evento, usare una lettura precedente e comprendere cosa può sfuggire a un campionamento periodico.

## Teoria e collegamento con l’architettura

### Leggere periodicamente: polling

Il **polling** è la lettura ripetuta di una periferica da parte del programma. Nell’esempio precedente una pausa da 10 ms separa due letture; il tempo reale del giro comprende anche istruzioni e stampe. La lettura non è continua: una pressione che inizi e termini fra due campionamenti può essere persa.

Un **livello** descrive lo stato rilevato in un momento. Un **fronte** descrive un cambiamento fra due letture: 1 → 0 è un fronte di discesa, 0 → 1 un fronte di salita. Con il nostro pull-up, la pressione corrisponde alla discesa e il rilascio alla salita.

### Perché non basta “se premuto, inverti il LED”

Se invertissimo il LED ogni volta che il tasto risulta premuto, una pressione di due secondi potrebbe produrre centinaia di inversioni. Per eseguire una sola azione sul nuovo evento dobbiamo confrontare presente e passato.

| Lettura precedente | Lettura attuale | Interpretazione con pull-up |
| --- | --- | --- |
| 1 | 1 | Rilasciato, nessun cambiamento |
| 1 | 0 | Nuova pressione osservata |
| 0 | 0 | Pressione mantenuta |
| 0 | 1 | Rilascio osservato |

La variabile `previousReading` / `previous_reading` conserva il campione precedente. Va aggiornata **dopo** il confronto, altrimenti si confronterebbe il nuovo valore con se stesso. Lo stato del LED viene mantenuto in una variabile separata e invertito con `!` in C++ o `not` in Python.

### Inizializzazione e conteggio

All’avvio leggiamo il pin e usiamo quel livello come campione precedente. Un pulsante già tenuto premuto non diventa quindi automaticamente una nuova pressione. Per generare un fronte occorre rilasciare e premere. Il LED parte spento e il contatore parte da zero.

Il contatore registra i fronti osservati, non la durata della pressione. Il tipo `unsigned long` del C++ ha capacità finita; per le prove brevi del corso è sufficiente. Il numero intero Python può crescere allocando altra memoria: anche in questo caso le risorse della scheda sono finite.

### Collegamento con l’architettura

La RAM rende possibile conservare il campione precedente e lo stato del LED fra i giri del ciclo. La CPU esegue confronti e aggiorna il GPIO. Non usiamo ancora interrupt: un evento non letto dal polling non viene automaticamente recuperato in seguito.

Ridurre la pausa da 10 a 1 ms aumenta le occasioni di lettura, ma non garantisce una frequenza esatta. Le stampe seriali possono allungare il ciclo. Soprattutto, leggere più spesso può rendere visibili i **rimbalzi**, rapide aperture e chiusure dovute alla meccanica del contatto. Rilevare i fronti e filtrare i rimbalzi sono due operazioni diverse.

## Esempi commentati

Dall’[esempio senza debounce](esempi/02_01-Rilevamento-del-fronte/README.md):

```cpp
if (previousReading == HIGH && reading == LOW) {
  ledOn = !ledOn;                        // Una nuova discesa osservata.
  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
}
previousReading = reading;              // Dopo il confronto.
```

```python
if previous_reading == 1 and reading == 0:
    led_on = not led_on
    led.value(1 if led_on else 0)
previous_reading = reading
```

Nel codice completo il contatore aumenta e viene stampato. Per isolare il concetto di fronte, prima prova il pulsante senza rimbalzi impostando `"bounce": "0"` nei suoi attributi Wokwi; poi rimuovi l’attributo e confronta i risultati.

## Buone pratiche e debug

Una pressione lunga deve produrre un solo conteggio con contatto ideale. Se il numero cresce continuamente, probabilmente stai reagendo al livello anziché al fronte. Se cresce più volte vicino alla pressione o al rilascio, possono intervenire rimbalzi. La loro assenza apparente in una prova non dimostra che il circuito reale ne sia privo.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Quale transizione indica una nuova pressione con pull-up?**

   - A. 0 → 0
   - B. 0 → 1
   - C. 1 → 0
   - D. 1 → 1

2. **Quando va aggiornata la lettura precedente?**

   - A. Prima di qualsiasi confronto, copiando subito la nuova lettura
   - B. Dopo aver confrontato i due campioni
   - C. Soltanto dopo lo spegnimento
   - D. Mai

3. **Cosa può succedere a un impulso interamente fra due letture?**

   - A. Può non essere rilevato
   - B. È sempre memorizzato dal programma
   - C. Aumenta necessariamente due volte il contatore
   - D. Viene trasformato in una resistenza

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Con bounce disabilitato, tieni premuto due secondi.

   **Risultato atteso:** Un solo incremento e un solo cambio del LED.

2. **Consegna:** Avvia tenendo già premuto, poi rilascia e premi ancora.

   **Risultato atteso:** Nessun conteggio iniziale; la nuova pressione successiva produce il primo evento.

3. **Consegna:** Aumenta la pausa di polling a 500 ms e prova pressioni brevi.

   **Risultato atteso:** Alcune possono sfuggire: documenta il limite senza interpretarlo come errore casuale del GPIO.

## Soluzioni dell’autovalutazione

1. **C — 1 → 0.** La chiusura verso GND produce una discesa.

2. **B — Dopo aver confrontato i due campioni.** Il confronto richiede ancora il valore del giro precedente.

3. **A — Può non essere rilevato.** Il polling vede soltanto i valori ai momenti di campionamento.

## Riferimenti

[Rimbalzi nel pulsante Wokwi](https://docs.wokwi.com/parts/wokwi-pushbutton).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](01-Ingressi-pull-up-e-pull-down.md)
- [➡️ Guida successiva](03-Debounce-e-comando-a-memoria.md)
