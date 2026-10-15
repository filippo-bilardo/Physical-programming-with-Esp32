# Più attività con temporizzazioni indipendenti

## Obiettivi e prerequisiti

Prerequisiti: guida 01 e LED con resistenza. Imparerai a usare riferimenti temporali separati, a distinguere intervallo di cambio e periodo completo e a riconoscere i limiti della pianificazione cooperativa.

## Teoria e collegamento con l'architettura

### Un solo ciclo, più controlli brevi

Nell'[esempio con due temporizzazioni](esempi/02_01-Due-temporizzazioni/README.md) il LED rosso cambia ogni 250 ms e il giallo ogni 700 ms. Una sequenza `delay(250); delay(700);` sommerebbe le attese e collegherebbe il ritmo del primo LED al secondo.

Con due riferimenti separati, ogni giro controlla invece due condizioni. La CPU esegue le istruzioni in sequenza; i due comportamenti avanzano perché ciascuno richiede un lavoro breve e restituisce il controllo al ciclo principale. È **pianificazione cooperativa**, senza thread, coroutine o interrupt applicativi.

| LED | GPIO | Intervallo tra cambiamenti | Periodo completo | Frequenza nominale |
| --- | --- | --- | --- | --- |
| Rosso | 18 | 250 ms | 500 ms | 2 Hz |
| Giallo | 19 | 700 ms | 1400 ms | circa 0,714 Hz |

Ogni attività conserva il proprio livello e il proprio istante dell'ultimo cambiamento in RAM. Il valore `now` può invece essere letto una volta per giro e usato da entrambi i controlli.

## Esempi commentati

```cpp
const unsigned long now = millis();
if (now - lastRed >= RED_INTERVAL_MS) {
  lastRed = now;
  redOn = !redOn;
  digitalWrite(18, redOn ? HIGH : LOW);
}
if (now - lastYellow >= YELLOW_INTERVAL_MS) {
  lastYellow = now;
  yellowOn = !yellowOn;
  digitalWrite(19, yellowOn ? HIGH : LOW);
}
```

```python
now = ticks_ms()
if ticks_diff(now, last_red) >= RED_INTERVAL_MS:
    last_red = now
    red_on = not red_on
    red.value(1 if red_on else 0)
if ticks_diff(now, last_yellow) >= YELLOW_INTERVAL_MS:
    last_yellow = now
    yellow_on = not yellow_on
    yellow.value(1 if yellow_on else 0)
```

I due `if` sono indipendenti. Con `else if` / `elif`, il secondo controllo sarebbe saltato nei giri in cui il primo risulta vero. Il primo esempio di entrambi in scadenza, nel modello ideale, arriva a 3500 ms: entrambi devono poter cambiare nello stesso giro.

Entrambi partono spenti. Nei primi 1000 ms ideali:

| Tempo relativo | Rosso | Giallo | Azione |
| --- | --- | --- | --- |
| 0 ms | spento | spento | Avvio |
| 250 ms | acceso | spento | Cambia rosso |
| 500 ms | spento | spento | Cambia rosso |
| 700 ms | spento | acceso | Cambia giallo |
| 750 ms | acceso | acceso | Cambia rosso |
| 1000 ms | spento | acceso | Cambia rosso |

### Ritardi e scelta del riferimento

Il codice assegna `last = now` quando cambia il LED. Se un giro arriva in ritardo di 10 ms, il cambiamento avviene in ritardo e il prossimo intervallo parte da quel momento. Non vengono riprodotti tutti i cambiamenti che sarebbero dovuti avvenire durante il ritardo.

Per mantenere una fase prefissata si può avanzare un riferimento della durata dell'intervallo (`last += intervallo` in C++, `ticks_add()` in MicroPython), ma bisogna anche decidere cosa fare delle scadenze perse. Questa variante non è implementata: qui privilegiamo una sola azione per attività e per giro.

### Il tempo disponibile nel ciclo

Un'operazione lunga aggiunta a una delle attività ritarda anche l'altra. Anche una stampa seriale può richiedere tempo. La pausa finale di 1 ms degli esempi lascia un piccolo intervallo tra giri; le soglie da 250 e 700 ms vengono controllate, non attese con pause della stessa durata. Il risultato è adatto a LED e interazioni umane, senza garanzie di tempo reale rigido.

## Buone pratiche e debug

- Non riutilizzare `lastRed` per il LED giallo: un aggiornamento azzererebbe la misura dell'altro.
- Mantieni breve ogni sezione del ciclo; evita un `while` che aspetti una scadenza.
- Modifica un intervallo alla volta e annota l'effetto sull'altro LED.
- Riavvia prima di confrontare le fasi: i riferimenti in RAM ripartono con il programma.

## Autovalutazione

1. **Perché servono due riferimenti temporali?**

   - A. Per scegliere due alimentazioni diverse.
   - B. Perché ogni attività deve ricordare il proprio ultimo cambiamento.
   - C. Per attivare automaticamente due CPU.
   - D. Per evitare di usare i GPIO.

2. **Perché il secondo controllo usa un altro `if`?**

   - A. Perché entrambe le scadenze possono risultare raggiunte nello stesso giro.
   - B. Per fermare il primo LED.
   - C. Per eliminare la necessità delle resistenze.
   - D. Per rendere infinito il contatore.

3. **Se il giallo cambia ogni 700 ms, il suo periodo completo nominale è:**

   - A. 350 ms.
   - B. 700 ms.
   - C. 1400 ms.
   - D. 7000 ms.

## Esercizi pratici

1. **Consegna:** porta il solo intervallo rosso da 250 a 100 ms.

   **Risultato atteso:** il rosso passa a un periodo di 200 ms; il giallo mantiene quello nominale di 1400 ms.

2. **Consegna:** imposta entrambi gli intervalli a 500 ms e riavvia.

   **Risultato atteso:** nel modello ideale entrambi cambiano nello stesso giro; il codice non esclude il secondo controllo quando il primo è vero.

3. **Consegna:** aggiungi un LED verde su GPIO 21, con una propria resistenza da 220 Ω, e un intervallo di 1100 ms.

   **Risultato atteso:** tre riferimenti indipendenti e nessuna attesa lunga; il verde ha periodo nominale di 2200 ms. Aggiorna anche il diagramma e la tabella delle prove.

## Soluzioni dell'autovalutazione

1. **B.** Un solo riferimento condiviso collegherebbe le due temporizzazioni.
2. **A.** Due attività possono essere entrambe pronte.
3. **C.** Un ciclo acceso/spento contiene due intervalli.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente](01-Attese-e-tempo-trascorso.md)
- [➡️ Guida successiva](03-Macchine-a-stati-e-semaforo.md)
