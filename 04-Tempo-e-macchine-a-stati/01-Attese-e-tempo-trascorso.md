# Attese e tempo trascorso

## Obiettivi e prerequisiti

Prerequisiti: lampeggio, lettura del pulsante e misura temporale del debounce dell'esercitazione 03. Imparerai a distinguere attesa e controllo di una scadenza, e a mantenere disponibile il ciclo principale.

## Teoria e collegamento con l'architettura

### Il limite dell'attesa bloccante

`delay(1000)` in Arduino e `sleep_ms(1000)` in MicroPython sospendono l'avanzamento del flusso che li chiama. Il codice successivo non legge il pulsante durante quell'attesa. Le periferiche e altre attività del sistema possono continuare: non significa che tutta la CPU e tutti gli interrupt siano fermi.

Nell'[esempio bloccante](esempi/01_01-Attesa-bloccante/README.md) il programma legge il pulsante una volta, accende il LED rosso per 1 s e lo spegne per 1 s. Torna poi alla lettura: tra due campioni passano circa 2 s. Una pressione e un rilascio interamente compresi tra quei campioni possono passare inosservati. Inoltre il LED giallo conserva l'ultimo livello letto fino al campione successivo.

### Ricordare quando, invece di aspettare

La versione con [lampeggio senza lunghe attese](esempi/01_02-Lampeggio-non-bloccante/README.md) conserva due dati in RAM: il livello del LED e l'istante del suo ultimo cambiamento. Ogni giro legge il pulsante e controlla se è trascorso l'intervallo. Se non è trascorso, prosegue con le altre istruzioni.

| Dato | Esempio | Significato |
| --- | --- | --- |
| Istante corrente | `now = millis()` | Valore letto dal contatore |
| Riferimento | `lastToggle` | Istante dell'ultimo cambiamento |
| Durata | `INTERVAL_MS = 1000` | Intervallo da attendere fra due cambiamenti |
| Tempo trascorso | `now - lastToggle` | Durata già passata, con le cautele sul tipo |

Il contatore deriva dal riferimento temporale del sistema; la CPU controlla la condizione e aggiorna il GPIO. Non introduciamo un timer hardware dedicato o un interrupt scritto dall'utente.

## Esempi commentati

In C++, dopo la configurazione del LED e l'inizializzazione di `lastToggle` con `millis()`:

```cpp
// now e lastToggle sono unsigned long; ledOn e' bool.
const unsigned long now = millis();
if (now - lastToggle >= INTERVAL_MS) {
  lastToggle = now;
  ledOn = !ledOn;
  digitalWrite(18, ledOn ? HIGH : LOW);
}
// Il ciclo puo' continuare con la lettura degli ingressi.
```

In MicroPython:

```python
# last_toggle e' inizializzato con ticks_ms(); led_on parte da False.
now = ticks_ms()
if ticks_diff(now, last_toggle) >= INTERVAL_MS:
    last_toggle = now
    led_on = not led_on
    led.value(1 if led_on else 0)
```

Il LED parte spento. Il primo cambio arriva dopo 1000 ms: un secondo acceso e uno spento danno un **periodo completo di 2000 ms**, cioè frequenza nominale 0,5 Hz.

### Il contatore torna a zero

Su ESP32 Arduino `unsigned long` è a 32 bit: `millis()` ricomincia dopo circa 49,7 giorni. Usa la sottrazione tra valori unsigned, non `now >= lastToggle + INTERVAL_MS`: la somma della scadenza può superare il massimo. La differenza funziona attraverso il ritorno a zero purché non si lasci passare un intero giro del contatore fra riferimento e controllo.

Per ragionare a mano, immagina un contatore a 8 bit: il riferimento è 250 e il tempo corrente, dopo il ritorno a zero, è 14. La differenza modulo 256 è 20, non una durata negativa. Il timer reale è più ampio; l'idea è la stessa.

In MicroPython usa `ticks_diff(now, last_toggle)`, senza sottrarre o confrontare direttamente i tick. La differenza è valida soltanto se i due istanti distano meno di metà del periodo del contatore. I nostri intervalli sono brevi e il ciclo li controlla frequentemente. Se vuoi calcolare scadenze esplicite, la funzione dedicata è `ticks_add()`.

### Reattività e precisione

Gli esempi cooperativi terminano ogni giro con una pausa di 1 ms: è una piccola attesa intenzionale, non un'attesa lunga quanto l'intervallo del LED. Non è una garanzia di campionamento esattamente ogni millisecondo. Latenza, stampe, altre attività del firmware e durata del ciclo possono ritardare un aggiornamento.

Aggiornando il riferimento con `lastToggle = now` misuriamo il prossimo intervallo dal cambiamento appena deciso. Un ciclo in ritardo può quindi spostare la fase nel tempo. Questa soluzione elementare evita raffiche di recupero e va bene per le prove; non è un orologio di precisione.

## Buone pratiche e debug

- Usa sempre la stessa unità: qui tutte le durate sono in millisecondi.
- Scegli `>=`, perché il ciclo potrebbe non passare esattamente sul valore della soglia.
- Aggiorna il riferimento solo quando esegui l'azione, non a ogni giro.
- Evita stampe continue nel ciclo: stampa eventi o riepiloghi a intervalli.
- I primi due esempi mostrano il livello grezzo del pulsante. Per contare pressioni serve il debounce già studiato.

## Autovalutazione

Scegli una risposta per domanda.

1. **Una pressione dura 100 ms durante `delay(1000)`. Che cosa garantisce il polling che riprende dopo il delay?**

   - A. Che la pressione sarà registrata comunque.
   - B. Che il livello sarà letto soltanto alla successiva lettura; la pressione può andare persa.
   - C. Che il GPIO memorizza sempre tutti i fronti.
   - D. Che il pulsante sarà letto da un secondo `loop()`.

2. **Il LED cambia ogni 1000 ms. Quanto dura un ciclo acceso/spento completo?**

   - A. 500 ms.
   - B. 1000 ms.
   - C. 2000 ms.
   - D. Dipende dal numero del GPIO.

3. **Quale confronto è adatto in MicroPython?**

   - A. `ticks_diff(now, last_toggle) >= INTERVAL_MS`.
   - B. `now == last_toggle`.
   - C. `now - last_toggle` per qualunque tick, senza limiti.
   - D. `sleep_ms(now)`.

## Esercizi pratici

1. **Consegna:** durante una delle attese del primo esempio premi per circa 100 ms e rilascia prima che ricominci il ciclo.

   **Risultato atteso:** la pressione può non apparire sul giallo. Una pressione mantenuta oltre il campione successivo viene invece letta.

2. **Consegna:** esegui la stessa prova con la versione senza lunghe attese.

   **Risultato atteso:** il giallo segue la pressione anche mentre il rosso resta acceso o spento. Eventuali rimbalzi riguardano il livello grezzo, non una macchina a eventi filtrati.

3. **Consegna:** porta l'intervallo a 200 ms e calcola periodo e frequenza nominali.

   **Risultato atteso:** periodo di 400 ms, frequenza di 2,5 Hz; la lettura del pulsante continua durante entrambe le fasi.

## Soluzioni dell'autovalutazione

1. **B.** Il polling non conserva ciò che è successo fra due letture.
2. **C.** Servono due cambiamenti per tornare allo stato iniziale.
3. **A.** `ticks_diff()` gestisce il ritorno a zero entro l'intervallo ammesso.

## Riferimenti

- [Arduino: millis()](https://docs.arduino.cc/language-reference/en/functions/time/millis/).
- [Arduino: delay()](https://docs.arduino.cc/language-reference/en/functions/time/delay/).
- [MicroPython: time, tick e differenze](https://docs.micropython.org/en/latest/library/time.html). Seleziona la documentazione della versione del firmware usato; `latest` descrive il ramo di sviluppo.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente](../03-Ingressi-digitali-e-pulsanti/03-Debounce-e-comando-a-memoria.md)
- [➡️ Guida successiva](02-Temporizzazioni-indipendenti.md)
