# 02 · Uscite digitali e LED

Passa dal singolo lampeggio a circuiti con più uscite. Studia corrente e resistenza e organizza una sequenza luminosa con dati, funzioni e cicli.

## Prerequisiti e obiettivi

**Prerequisiti:** Esercitazione 01: ambiente configurato, caricamento dei programmi e lampeggio compresi.

Al termine saprai:

- Stimare la corrente di un ramo LED usando la legge di Ohm.
- Configurare uscite GPIO e costruire una tabella degli stati.
- Pilotare più LED con resistenze indipendenti.
- Usare indici e funzioni per cambiare l’ordine di una sequenza.
- Configurare il drive strength e distinguerlo da corrente costante e PWM.

## Materiali e ambienti

Materiale dell’esercitazione 01, tre LED (rosso, giallo, verde), tre resistenze da 330 Ω (1/4 W), una resistenza da 1 kΩ per il confronto. Multimetro per le sole prove elettriche reali.

Gli esempi usano ESP32 classico con modulo WROOM-32 e logica a 3,3 V. Wokwi permette le prove di logica e sequenza; l’effetto elettrico del drive strength, le correnti e la luminosità reale richiedono hardware e multimetro. I collegamenti completi sono nel README di ciascun esempio e nei relativi `diagram.json`.

## Guide teoriche

1. [Circuiti LED e resistenze](01-Circuiti-LED-e-resistenze.md)
2. [GPIO e uscite digitali](02-GPIO-e-uscite-digitali.md)
3. [Funzioni, cicli e sequenze](03-Funzioni-cicli-e-sequenze.md)
4. [Drive strength dei GPIO](04-Drive-strength-dei-GPIO.md)

Ogni guida include esempi commentati, domande a scelta multipla, esercizi progressivi, soluzioni motivate e navigazione verso la guida successiva.

## Esempi completi

| Esempio | Guida | Implementazioni |
| --- | --- | --- |
| [LED e resistenza](esempi/01_01-LED-e-resistenza/README.md) | 01 | C++ e MicroPython |
| [Due LED alternati](esempi/02_01-Due-LED-alternati/README.md) | 02 | C++ e MicroPython |
| [Sequenza di tre LED](esempi/03_01-Sequenza-tre-LED/README.md) | 03 | C++ e MicroPython |
| [Confronto del drive strength](esempi/04_01-Confronto-drive-strength/README.md) | 04 | C++ e MicroPython |

Le istruzioni comuni sono nella [guida agli ambienti](../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md). Ogni esempio contiene anche la propria procedura di esecuzione, dipendenze e risultato atteso.

## Percorso pratico guidato

1. Calcola la corrente approssimata del LED rosso con 330 Ω e avvia l’esempio a luce fissa.
2. Su hardware, se disponibile, misura la tensione sulla resistenza. Togli alimentazione prima di sostituirla con 1 kΩ.
3. Aggiungi il secondo ramo: GPIO 19 → 330 Ω → anodo LED giallo; catodo → GND. Mantieni il rosso su GPIO 18 con la propria resistenza.
4. Esegui l’alternanza A/B nei due linguaggi; confronta la tabella degli stati con le stampe.
5. Aggiungi il terzo ramo sul GPIO 21, con resistenza da 330 Ω e LED verde. Esegui la sequenza 0, 1, 2.
6. Cambia l’ordine dei pin nella collezione senza spostare i fili; spiega il nuovo ordine visivo.
7. Leggi la guida 04 e prova i quattro livelli di drive strength sul solo LED del GPIO 18, sempre con resistenza. Su hardware misura la tensione sulla resistenza; nel simulatore controlla soltanto il flusso del programma.
8. Svolgi le domande e prepara l’attività autonoma usando la funzione che accende un solo LED.

## Attività autonoma conclusiva

**Consegna:** Realizza un semaforo didattico con rosso per 2 s, verde per 2 s e giallo per 1 s. Conserva i GPIO 18/19/21 e sviluppa entrambe le versioni. È un modello da laboratorio.

**Risultato atteso e criteri di completamento:** Un solo LED acceso per fase; ordine rosso → verde → giallo; ciclo nominale di 5 s; nessuna resistenza condivisa fra i rami.

Consegna tabella degli stati, codice, circuito e calcolo del periodo. Motiva la distinzione fra indice del LED e numero GPIO.

## Verifica dell’apprendimento

Prima di procedere, spiega a parole il circuito, prevedi l’effetto di almeno una modifica e riproduci il comportamento in entrambi i linguaggi. Distingui sempre una prova eseguita da un risultato soltanto atteso. Non serve possedere una scheda per completare le attività di simulazione, ma le prove elettriche restano da svolgere.

## Stato dei materiali e delle prove

Guide, esempi e circuiti sono disponibili. **Le prove Wokwi e su hardware reale sono da eseguire in entrambe le implementazioni.** Per i controlli locali riproducibili consulta il [rapporto delle verifiche](../VERIFICHE.md).

## Navigazione del corso

- [📑 Indice generale](../../README.md)
- [⬅️ Esercitazione precedente](../01-Introduzione-ESP32/README.md)
- [➡️ Esercitazione successiva](../03-Ingressi-digitali-e-pulsanti/README.md)
