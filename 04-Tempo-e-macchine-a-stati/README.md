# 04 · Tempo e macchine a stati

Fai avanzare un programma senza fermarne a lungo il ciclo principale. Confronta un'attesa bloccante con la misura del tempo trascorso, gestisci due LED indipendenti e costruisci un semaforo con richiesta pedonale.

## Prerequisiti e obiettivi

**Prerequisiti:** esercitazioni 01–03: uscite digitali, pulsante con pull-up, condizioni, funzioni, fronte di pressione e debounce temporale.

Al termine saprai:

- Spiegare perché un programma può perdere una pressione durante un'attesa.
- Usare `millis()` in C++ e `ticks_ms()` / `ticks_diff()` in MicroPython.
- Conservare in RAM un riferimento temporale per ogni attività.
- Descrivere stati, eventi, condizioni di transizione e uscite.
- Integrare un pulsante filtrato con una sequenza temporizzata.

## Materiali e ambienti

ESP32 classico con modulo ESP32-WROOM-32, per esempio DOIT ESP32 DEVKIT V1, cavo USB dati, breadboard e cavetti. Servono quattro LED (rosso, giallo e due verdi), **quattro resistenze da 220 Ω**, un pulsante normalmente aperto e il pull-up interno del GPIO 23. Nessuna libreria esterna.

I primi tre esempi richiedono soltanto due LED; il semaforo usa tutti e quattro. Ogni LED ha una propria resistenza in serie e il catodo a GND. I diagrammi Wokwi e i programmi usano gli stessi GPIO della tabella in ciascun README. I collegamenti sono previsti per logica a 3,3 V.

## Guide teoriche

1. [Attese e tempo trascorso](01-Attese-e-tempo-trascorso.md)
2. [Più attività con temporizzazioni indipendenti](02-Temporizzazioni-indipendenti.md)
3. [Macchine a stati e semaforo](03-Macchine-a-stati-e-semaforo.md)

Ogni guida contiene teoria, frammenti C++ e MicroPython, domande con soluzioni ed esercizi progressivi.

## Esempi completi

| Esempio | Guida | Implementazioni |
| --- | --- | --- |
| [Attesa bloccante](esempi/01_01-Attesa-bloccante/README.md) | 01 | C++ e MicroPython |
| [Lampeggio senza lunghe attese](esempi/01_02-Lampeggio-non-bloccante/README.md) | 01 | C++ e MicroPython |
| [Due temporizzazioni indipendenti](esempi/02_01-Due-temporizzazioni/README.md) | 02 | C++ e MicroPython |
| [Semaforo con richiesta pedonale](esempi/03_01-Semaforo-con-richiesta/README.md) | 03 | C++ e MicroPython |

La [guida agli ambienti](../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md) spiega la preparazione di Arduino IDE e MicroPython. Ogni esempio include le istruzioni per Wokwi e scheda reale.

## Percorso pratico guidato

1. Collega LED rosso a GPIO 18 e LED giallo a GPIO 19, ciascuno con 220 Ω. Collega GPIO 23 a un contatto del pulsante e l'altro a GND.
2. Esegui l'attesa bloccante. Premi e rilascia brevemente mentre il LED rosso è acceso: il programma può non leggere la pressione.
3. Esegui il lampeggio senza lunghe attese sullo stesso circuito. Il rosso continua a lampeggiare mentre il giallo segue il pulsante. I primi due esempi leggono il livello grezzo: qui non stiamo contando pressioni.
4. Esegui le due temporizzazioni: il rosso cambia ogni 250 ms, il giallo ogni 700 ms. Calcola il periodo completo di ciascun lampeggio.
5. Monta il circuito a quattro LED del semaforo. Avvia senza premere: resta verde per le auto finché non arriva una richiesta.
6. Premi durante i primi 5 s: la richiesta viene memorizzata, ma il verde auto termina soltanto al raggiungimento dei 5 s minimi. Se premi più tardi, termina alla pressione filtrata.
7. Prova una pressione mantenuta, richieste durante l'attraversamento e riavvio con il tasto premuto. Confronta il risultato con la politica descritta nell'esempio.

## Attività autonoma conclusiva

**Consegna:** aggiungi un LED di richiesta su GPIO 25, con una quinta resistenza da 220 Ω. Deve accendersi quando viene accettata la richiesta, restare acceso durante l'attesa del verde minimo e spegnersi entrando nel giallo auto. Conserva i quattro stati e i tempi dell'esempio.

**Risultato atteso:** una pressione nel verde genera una sola prenotazione; la spia rappresenta la variabile `requestPending` / `request_pending`. Le pressioni negli altri stati non prenotano un secondo attraversamento. Nessuna lunga attesa impedisce di aggiornare il filtro del pulsante.

Consegna circuito, due programmi, tabella delle transizioni e prove di pressione anticipata, tardiva, mantenuta e fuori fase.

## Verifica dell'apprendimento

Spiega la differenza tra un istante e una durata, perché ogni attività conserva il proprio riferimento e perché il debounce deve continuare anche quando una pressione viene ignorata dalla macchina a stati. Non descrivere il polling come esecuzione simultanea di due programmi.

## Stato dei materiali e delle prove

Guide, sorgenti e diagrammi sono forniti per entrambe le implementazioni. Le prove Wokwi e su ESP32 reale sono **da eseguire**: i controlli sul computer non sostituiscono compilazione per ESP32, simulazione e collaudo elettrico. Registra ambiente, versioni e risultato osservato nelle tabelle degli esempi.

Controlli sul computer del **15 ottobre 2026**: sintassi dei quattro programmi Python, compilazione dei quattro sketch con g++ e API Arduino sostituite, otto diagrammi JSON e collegamenti delle nuove guide. Diciotto scenari sono stati eseguiti nei due linguaggi sia con contatore ordinario sia attraverso il ritorno a zero: **72 esecuzioni superate**, con uscite e messaggi coincidenti nel modello. I casi includono pressioni perse, ritmi indipendenti, richieste anticipate e tardive, rimbalzi, riarmo e attese nel verde oltre un giro del contatore MicroPython simulato. Il modello C++ usa la larghezza nativa di `unsigned long` del computer, non emula la CPU ESP32. Non è stata eseguita una compilazione con il core ESP32.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [⬅️ Esercitazione precedente](../03-Ingressi-digitali-e-pulsanti/README.md)
- La prossima esercitazione, “Ingressi analogici e ADC”, è pianificata e non ancora disponibile.
