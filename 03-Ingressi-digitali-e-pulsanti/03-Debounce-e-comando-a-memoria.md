# Debounce e comando a memoria

## Obiettivi e prerequisiti

Prerequisiti: guide 01 e 02, fronte di discesa e stato in RAM. Obiettivi: filtrare cambiamenti instabili, alternare il LED una volta per pressione e introdurre la misura del tempo trascorso.

## Teoria e collegamento con l’architettura

### Una pressione fisica non è sempre un solo fronte

I contatti meccanici possono aprirsi e richiudersi più volte durante pressione e rilascio. Il software che conta ogni fronte potrebbe interpretare una sola azione umana come più eventi. Il **debounce**, o antirimbalzo, è un filtro che decide quando accettare un cambiamento.

Qui usiamo una regola: il livello osservato deve restare invariato per almeno **30 ms** prima di diventare lo stato accettato. È una scelta didattica, non un valore universale per ogni pulsante. Un disturbo persistente oltre la soglia può essere accettato e un impulso più breve viene scartato, anche se intenzionale.

### Tre informazioni da non confondere

| Dato | Significato |
| --- | --- |
| Lettura grezza `raw` | Valore letto in questo giro |
| Ultima lettura `lastRaw` / `last_raw` | Valore grezzo osservato nel giro precedente |
| Stato stabile `stableState` / `stable_state` | Ultimo livello accettato dal filtro |
| Istante `lastChange` / `last_change` | Quando è cambiata l’ultima lettura grezza |

A ogni cambiamento grezzo ricominciamo a misurare la finestra. Finché continuano i cambiamenti, lo stato accettato non viene aggiornato. Quando il nuovo livello dura abbastanza, lo accettiamo e generiamo l’azione solo se è il livello premuto.

```text
Tempo (ms)       0     10     14     18                 48
Lettura          1      0      1      0                  0
Ultimo cambio    0     10     14     18                 18
Stato accettato  1      1      1      1                  0
Azione           —      —      —      —             una pressione
```

Anche il rilascio deve diventare stabile prima che una pressione seguente possa essere riconosciuta. Questa scelta evita di riarmare il comando su un brevissimo rimbalzo di rilascio.

### Misurare il tempo senza aspettare tutta la finestra

`millis()` in Arduino e `ticks_ms()` in MicroPython restituiscono contatori temporali. Il loro valore torna a zero periodicamente: non sono contatori infiniti. In C++ usiamo la sottrazione fra valori `unsigned long`; in MicroPython usiamo `ticks_diff(now, last_change)`, progettata per calcolare differenze fra tick.

Per gli intervalli brevi e le letture frequenti di questo esempio queste operazioni gestiscono il passaggio attraverso lo zero. In MicroPython non confrontare tick arbitrariamente lontani: le differenze sono significative entro metà del periodo del contatore. In C++ non sostituire la sottrazione con un confronto ingenuo `now >= lastChange + soglia`.

Il programma non esegue una lunga attesa dopo ogni pressione; torna a controllare l’ingresso, con una pausa di 1 ms per giro. Questa è un’anticipazione della gestione del tempo che sarà sviluppata nell’esercitazione 04. Il polling e le stampe hanno comunque un costo: non promettiamo campionamenti esattamente ogni millisecondo.

### Collegamento con l’architettura e limiti

La periferica fornisce il livello, il riferimento temporale consente di misurare intervalli, la CPU applica il filtro e la RAM conserva letture e stato del LED. Questo **comando a memoria** conserva acceso/spento dopo il rilascio, ma soltanto durante l’esecuzione: un riavvio azzera LED e conteggio.

Il software non modifica la meccanica del pulsante e non osserva ciò che avviene fra due campioni. La prova deve includere pressione lunga, rilascio, ripetizioni e avvio con pulsante già premuto, oltre ai rimbalzi.

## Esempi commentati

Dall’[esempio completo con debounce](esempi/03_01-Pulsante-con-debounce/README.md):

```cpp
if (raw != lastRaw) {
  lastRaw = raw;
  lastChange = now;  // Riavvia la misura a ogni cambiamento osservato.
}
if (raw != stableState && now - lastChange >= DEBOUNCE_MS) {
  stableState = raw;
  // Nel programma completo solo LOW inverte il LED e conta una pressione.
}
```

```python
if raw != last_raw:
    last_raw = raw
    last_change = now
if raw != stable_state and ticks_diff(now, last_change) >= DEBOUNCE_MS:
    stable_state = raw
    # Il programma completo agisce solo quando stable_state vale 0.
```

Il filtro parte dal livello iniziale letto. Un tasto già premuto all’avvio deve essere rilasciato stabilmente prima che una nuova pressione possa produrre un evento.

## Buone pratiche e debug

Stampa soltanto gli eventi accettati per non riempire la console. Mantieni attivi i rimbalzi Wokwi nella prova del filtro. Dopo una modifica della soglia prova sia pressioni sia rilasci: una finestra molto lunga rende il comando meno reattivo. Se vuoi rilevare pressioni più brevi, devi rivedere esplicitamente i requisiti del filtro.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Quando viene accettato un nuovo livello nel filtro proposto?**

   - A. Alla prima lettura differente
   - B. Dopo 30 letture, indipendentemente dal tempo
   - C. Dopo almeno 30 ms senza cambiamenti osservati
   - D. Soltanto dopo un riavvio

2. **Quale operazione usa MicroPython per la differenza dei tick?**

   - A. now / last_change
   - B. ticks_diff(now, last_change)
   - C. now + last_change
   - D. len(now)

3. **Cosa accade al rilascio stabilizzato?**

   - A. Si aggiorna lo stato stabile senza invertire il LED
   - B. Si incrementa sempre il contatore delle pressioni
   - C. Si cancella il firmware
   - D. Si spegne sempre il LED

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Esegui dieci pressioni da almeno 100 ms, con rilasci di almeno 100 ms.

   **Risultato atteso:** Dieci incrementi e LED spento al termine, partendo da spento.

2. **Consegna:** Mantieni premuto per due secondi, poi riavvia tenendo premuto.

   **Risultato atteso:** Una sola azione durante la pressione lunga; dopo riavvio nessuna azione fino a rilascio stabile e nuova pressione.

3. **Consegna:** Realizza un comando per la sequenza dei tre LED: ogni pressione stabilizzata avanza di un indice, il rilascio non agisce.

   **Risultato atteso:** Stato iniziale indice 0; tre pressioni producono 1, 2, 0. Usa i LED dell’esercitazione 02 e conserva il filtro del pulsante.

## Soluzioni dell’autovalutazione

1. **C — Dopo almeno 30 ms senza cambiamenti osservati.** La soglia riguarda il tempo trascorso dall’ultimo cambiamento grezzo.

2. **B — ticks_diff(now, last_change).** ticks_diff gestisce il contatore circolare entro il suo intervallo di validità.

3. **A — Si aggiorna lo stato stabile senza invertire il LED.** L’azione è associata soltanto alla transizione accettata verso il livello premuto.

## Riferimenti

[Contatori e ticks_diff in MicroPython](https://docs.micropython.org/en/latest/library/time.html), [rimbalzi Wokwi](https://docs.wokwi.com/parts/wokwi-pushbutton).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](02-Polling-stato-e-fronti.md)
