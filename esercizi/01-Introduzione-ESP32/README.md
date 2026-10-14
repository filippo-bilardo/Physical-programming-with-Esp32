# 01 · Introduzione a ESP32

Dal computer al circuito: riconosci i componenti della scheda, prepara gli ambienti e realizza il primo lampeggio nei due linguaggi.

## Prerequisiti e obiettivi

**Prerequisiti:** Nozioni iniziali di variabili, condizioni, cicli e funzioni; capacità di gestire file e installare programmi. Non serve esperienza con ESP32.

Al termine saprai:

- Distinguere CPU, RAM, Flash, GPIO e periferiche.
- Preparare Wokwi, Arduino IDE e un ambiente MicroPython.
- Installare il core ESP32, selezionare la DOIT ESP32 DEVKIT V1 e verificare il driver USB-seriale.
- Confrontare la simulazione ESP32 con le attività introduttive di Tinkercad Circuits.
- Eseguire un programma su ESP32 e leggere la console seriale.
- Prevedere l’effetto di una modifica dei tempi e confrontare i due linguaggi.

## Materiali e ambienti

DOIT ESP32 DEVKIT V1 con modulo ESP32-WROOM, cavo USB dati, breadboard, cavetti, un LED rosso e una resistenza da 330 Ω (1/4 W). In Wokwi questi componenti sono virtuali; non è necessario disporre della scheda.

Gli esempi usano ESP32 classico con modulo WROOM-32 e logica a 3,3 V. Wokwi consente tutte le prove di programma e interazione qui proposte; montaggio, correnti, luminosità reale e verifica dei contatti richiedono hardware. I collegamenti completi sono nel README di ciascun esempio e nei relativi `diagram.json`.

## Guide teoriche

1. [Architettura di ESP32](01-Architettura-ESP32.md)
2. [Ambienti di sviluppo](02-Ambienti-di-sviluppo.md)
3. [Primo programma](03-Primo-programma.md)
4. [Installare Arduino IDE e DOIT ESP32 DEVKIT V1](04-Arduino-IDE-e-DOIT-DevKit-V1.md)
5. [Driver USB-seriale: Windows, macOS e Linux](05-Driver-USB-seriale.md)
6. [Wokwi e introduzione a Tinkercad](06-Wokwi-e-Tinkercad.md)

Le guide 04–06 approfondiscono la preparazione degli ambienti: consultale quando richiesto dalla guida 02, prima della prova pratica del primo programma.

Ogni guida include esempi commentati, domande a scelta multipla, esercizi progressivi, soluzioni motivate e navigazione verso la guida successiva.

## Esempi completi

| Esempio | Guida | Implementazioni |
| --- | --- | --- |
| [LED lampeggiante](esempi/03_01-LED-lampeggiante/README.md) | 03 | C++ e MicroPython |
| [Variazione della temporizzazione](esempi/03_02-Variazione-temporizzazione/README.md) | 03 | C++ e MicroPython |

Le istruzioni comuni sono nella [guida agli ambienti](../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md). Ogni esempio contiene anche la propria procedura di esecuzione, dipendenze e risultato atteso.

## Percorso pratico guidato

1. Leggi la guida 01 e disegna il percorso dal programma al GPIO.
2. Segui la guida 02: usa la guida 06 per preparare i due progetti Wokwi; se hai hardware, usa le guide 04–05 per installare Arduino IDE, core ESP32 e driver della DOIT. Configura anche Thonny per MicroPython.
3. Leggi la guida 03 e controlla il circuito del primo esempio: GPIO 18 → 330 Ω → anodo del LED; catodo → GND. Sulla scheda reale monta a USB scollegata.
4. Esegui il lampeggio in C++ e MicroPython. Osserva almeno cinque cicli e associa i messaggi acceso/spento al LED.
5. Passa alla variazione temporale: confronta 500/500 ms e 200/800 ms, mantenendo invariato il circuito.
6. Se disponibile, ripeti su hardware. Registra versioni, risultato osservato e differenze rispetto alla simulazione.
7. Rispondi alle autovalutazioni e realizza l’attività autonoma.

## Attività autonoma conclusiva

**Consegna:** Realizza un segnalatore con tre lampi: 100 ms acceso e 100 ms spento per ciascun lampo, poi 1400 ms di pausa aggiuntiva. Usa lo stesso GPIO e realizza entrambe le versioni.

**Risultato atteso e criteri di completamento:** Tre lampi raggruppati, ripetuti ogni 2 s nominali; messaggio di inizio gruppo in console; descrizione di CPU, RAM, Flash e GPIO coinvolti.

Consegna sorgenti, diagramma e tabella con tempi previsti/osservati. Spiega perché il periodo è 3 × (100 + 100) + 1400 = 2000 ms.

## Verifica dell’apprendimento

Prima di procedere, spiega a parole il circuito, prevedi l’effetto di almeno una modifica e riproduci il comportamento in entrambi i linguaggi. Distingui sempre una prova eseguita da un risultato soltanto atteso. Non serve possedere una scheda per completare le attività di simulazione, ma le prove elettriche restano da svolgere.

## Stato dei materiali e delle prove

Guide, esempi e circuiti sono disponibili. **Le prove Wokwi e su hardware reale sono da eseguire in entrambe le implementazioni.** Per i controlli locali riproducibili consulta il [rapporto delle verifiche](../VERIFICHE.md).

## Navigazione del corso

- [📑 Indice generale](../../README.md)
- [➡️ Esercitazione successiva](../02-Uscite-digitali-e-LED/README.md)
