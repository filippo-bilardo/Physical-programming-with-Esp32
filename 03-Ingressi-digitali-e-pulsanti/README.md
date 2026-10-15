# 03 · Ingressi digitali e pulsanti

Leggi un comando umano e trasformalo in un evento affidabile: confronta pull-up e pull-down, riconosci i fronti e filtra i rimbalzi prima di cambiare lo stato del LED.

## Prerequisiti e obiettivi

**Prerequisiti:** Esercitazioni 01 e 02: ingressi/uscite concettualmente distinti, condizioni, funzioni, LED e collezioni di pin. La misura del tempo trascorso è introdotta nella guida 03.

Al termine saprai:

- Evitare ingressi flottanti e interpretare logiche attive basse/alte.
- Distinguere livello, fronte e pressione mantenuta.
- Usare polling e dati in RAM per memorizzare uno stato.
- Applicare un filtro temporale a pressione e rilascio.

## Materiali e ambienti

ESP32, cavo USB dati, breadboard, cavetti, LED rosso con resistenza da 330 Ω, pulsante normalmente aperto e resistenza da 10 kΩ per il pull-down. Per l’attività finale servono anche gli altri due LED e le rispettive resistenze dell’esercitazione 02.

Gli esempi usano ESP32 classico con modulo WROOM-32 e logica a 3,3 V. Wokwi consente tutte le prove di programma e interazione qui proposte; montaggio, correnti, luminosità reale e verifica dei contatti richiedono hardware. I collegamenti completi sono nel README di ciascun esempio e nei relativi `diagram.json`.

## Guide teoriche

1. [Ingressi, pull-up e pull-down](01-Ingressi-pull-up-e-pull-down.md)
2. [Polling, stato e fronti](02-Polling-stato-e-fronti.md)
3. [Debounce e comando a memoria](03-Debounce-e-comando-a-memoria.md)

Ogni guida include esempi commentati, domande a scelta multipla, esercizi progressivi, soluzioni motivate e navigazione verso la guida successiva.

## Esempi completi

| Esempio | Guida | Implementazioni |
| --- | --- | --- |
| [Pulsante con pull-up interno](esempi/01_01-Pulsante-con-pull-up/README.md) | 01 | C++ e MicroPython |
| [Pulsante con pull-down esterno](esempi/01_02-Pulsante-con-pull-down/README.md) | 01 | C++ e MicroPython |
| [Rilevamento del fronte senza debounce](esempi/02_01-Rilevamento-del-fronte/README.md) | 02 | C++ e MicroPython |
| [Pulsante con debounce temporale](esempi/03_01-Pulsante-con-debounce/README.md) | 03 | C++ e MicroPython |

Le istruzioni comuni sono nella [guida agli ambienti](../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md). Ogni esempio contiene anche la propria procedura di esecuzione, dipendenze e risultato atteso.

## Percorso pratico guidato

1. A scheda scollegata, lascia il LED sul GPIO 18. Collega un contatto del pulsante a GPIO 23 e l’altro a GND; abilita il pull-up come indicato nel primo esempio.
2. Esegui: a riposo il LED è spento; durante la pressione resta acceso. Registra i livelli logici.
3. Togli alimentazione e realizza il pull-down: resistenza da 10 kΩ fra GPIO 23 e GND, pulsante fra GPIO 23 e 3V3. Usa il codice dedicato e confronta i livelli.
4. Ripristina il circuito pull-up per gli esempi successivi. Avvia il rilevamento del fronte; in Wokwi prova prima senza rimbalzi, poi riattivali seguendo il README dell’esempio.
5. Mantieni premuto per due secondi. Distingui la ripetizione dovuta al livello dai possibili eventi aggiuntivi dovuti ai rimbalzi.
6. Esegui il debounce con soglia di 30 ms, prova dieci pressioni e dieci rilasci da almeno 100 ms. Ripeti con un tasto già premuto all’avvio.
7. Confronta le due implementazioni, completa l’autovalutazione e integra il pulsante con i tre LED.

## Attività autonoma conclusiva

**Consegna:** Crea un selettore luminoso: all’avvio accendi il LED di indice 0; ogni pressione filtrata avanza a 1, poi 2, poi torna a 0. Usa il pulsante pull-up su GPIO 23 e la funzione di selezione dell’esercitazione 02.

**Risultato atteso e criteri di completamento:** Un solo LED acceso; una sola avanzata per pressione; nessuna avanzata per pressione mantenuta o rilascio. Avvio con tasto premuto: nessuna avanzata fino a rilascio stabile e nuova pressione. Dieci pressioni portano dall’indice 0 all’indice 1.

Consegna versioni C++/MicroPython, circuito a tre LED e pulsante, tabella delle prove (pressione breve, lunga, rimbalzi, riavvio). Usa indice = (indice + 1) modulo 3; in entrambi i linguaggi l’operatore è `%`.

## Verifica dell’apprendimento

Prima di procedere, spiega a parole il circuito, prevedi l’effetto di almeno una modifica e riproduci il comportamento in entrambi i linguaggi. Distingui sempre una prova eseguita da un risultato soltanto atteso. Non serve possedere una scheda per completare le attività di simulazione, ma le prove elettriche restano da svolgere.

## Stato dei materiali e delle prove

Guide, esempi e circuiti sono disponibili. **Le prove Wokwi e su hardware reale sono da eseguire in entrambe le implementazioni.** Per i controlli locali riproducibili consulta il [rapporto delle verifiche](../strumenti/VERIFICHE.md).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [⬅️ Esercitazione precedente](../02-Uscite-digitali-e-LED/README.md)
- [➡️ Esercitazione successiva](../04-Tempo-e-macchine-a-stati/README.md)
