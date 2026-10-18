# 06 · Output analogici e DAC

Genera livelli analogici, trasforma la lettura di un potenziometro in un comando DAC e riproduci suoni con un buzzer piezo passivo. Confronta il tono prodotto dal PWM hardware con l’audio ottenuto scrivendo campioni sul DAC.

## Prerequisiti e obiettivi

**Prerequisiti:** esercitazioni 01–05: ambiente, GPIO, tensione e corrente, ADC, array e temporizzazioni.

Al termine saprai:

- Distinguere uscita digitale, PWM, valore medio e livello analogico del DAC.
- Usare il DAC a 8 bit dell’ESP32 classico e misurare l’uscita senza sovraccaricarla.
- Riscalare codici ADC in codici DAC, riconoscendo quantizzazione e saturazione.
- Pilotare un piccolo piezo passivo con PWM e riprodurre una melodia.
- Generare una forma d’onda a campioni sul DAC e descrivere i limiti della temporizzazione software.

## Materiali e ambienti

Scheda **DOIT ESP32 DEVKIT V1 con ESP32-WROOM-32**, cavo USB dati, breadboard e cavetti; potenziometro lineare da **10 kΩ**, piccolo **buzzer piezo passivo ad alta impedenza** e resistenza da **1 kΩ** in serie. Per la tensione DAC serve un multimetro; per le forme d’onda un oscilloscopio è facoltativo. Un analizzatore logico misura il PWM, non la tensione analogica del DAC.

| Funzione | Collegamento |
| --- | --- |
| DAC1 | GPIO 25 |
| DAC2, citato ma non utilizzato | GPIO 26 |
| Potenziometro | Estremi a 3V3/GND, cursore a GPIO 34 |
| Buzzer negli esempi PWM | GPIO 18 → 1 kΩ → positivo piezo; negativo a GND |
| Buzzer nell’esempio audio DAC | GPIO 25 → 1 kΩ → positivo piezo; negativo a GND |
| Misura DAC | Tester DC: rosso a GPIO 25, nero a GND |

Il DAC non alimenta carichi di potenza. Il piezo previsto è un componente passivo adatto a una piccola eccitazione; non sostituirlo con un buzzer attivo, un trasduttore elettromagnetico o un altoparlante da 8 Ω. Per questi carichi servono un driver e un’alimentazione dimensionati. Scollega l’alimentazione prima di spostare il piezo da GPIO 18 a GPIO 25.

## Guide teoriche

1. [Uscite analogiche, PWM e DAC](01-Uscite-analogiche-PWM-e-DAC.md)
2. [DAC e regolazione della tensione](02-DAC-e-regolazione-della-tensione.md)
3. [Buzzer passivo e PWM](03-Buzzer-passivo-e-PWM.md)
4. [Melodie e audio con DAC](04-Melodie-e-audio-con-DAC.md)

Ogni guida include esempi commentati, tre domande con soluzioni ed esercizi progressivi.

## Esempi completi

| Esempio | Attività | Ambiente della prova |
| --- | --- | --- |
| [Cinque livelli DAC](esempi/01_01-Livelli-DAC/README.md) | Codici 0, 64, 128, 192, 255 | Scheda e tester |
| [Potenziometro e DAC](esempi/02_01-Potenziometro-e-DAC/README.md) | ADC 12 bit → DAC 8 bit | Scheda e tester |
| [Buzzer con PWM](esempi/03_01-Buzzer-con-PWM/README.md) | 440 Hz, un secondo acceso e uno spento | Wokwi e scheda |
| [Melodia con buzzer](esempi/04_01-Melodia-con-buzzer/README.md) | Note, pause e articolazione senza lunghe attese | Wokwi e scheda |
| [Audio con DAC](esempi/04_02-Audio-con-DAC/README.md) | Tabella di otto campioni, 500 periodi e pausa | Scheda; oscilloscopio facoltativo |

Ogni esempio contiene sorgenti equivalenti C++ e MicroPython, diagrammi e istruzioni. Non servono librerie esterne. **C++ richiede Arduino-ESP32 3.x** per l’API LEDC riferita al pin; i progetti con API 2.x devono essere aggiornati. MicroPython richiede il firmware per ESP32 classico con `machine.DAC`, `PWM.duty_u16()` e `ADC.read_u16()`.

Wokwi dichiara il PWM LEDC nella [tabella delle periferiche](https://docs.wokwi.com/guides/esp32#simulation-features), ma non dichiara il DAC. Per questo le prove DAC sono su hardware: i relativi diagrammi costituiscono una traccia del cablaggio e non un collaudo della conversione simulata. Il testo che indica i puntali del tester non è uno strumento virtuale.

## Percorso pratico guidato

1. Ripassa la distinzione fra PWM e DAC; identifica GPIO 25 sul pinout della DOIT.
2. Sulla scheda reale esegui i cinque livelli, misurando il GPIO 25 con un tester DC ad alta impedenza. Confronta valori ideali e reali.
3. Aggiungi il potenziometro sul GPIO 34 ed esegui la conversione dei codici. Confronta tensione del cursore e tensione d’uscita senza assumere che coincidano.
4. A scheda scollegata monta il piccolo piezo sul GPIO 18 con 1 kΩ ed esegui il tono PWM. Ripeti in Wokwi abilitando l’audio del browser.
5. Esegui la melodia; confronta durata dell’evento e durata del suono. Cambia una sola frequenza e poi una sola durata.
6. Su hardware sposta il ramo resistenza/piezo sul GPIO 25 ed esegui l’audio DAC. Ascolta il tono approssimato e la pausa; osserva i gradini se hai un oscilloscopio.
7. Registra versioni, tempi, codici e misure. Distingui l’API richiesta dal segnale effettivamente osservato.

## Attività autonoma conclusiva

**Consegna:** aggiungi al progetto della melodia un potenziometro sul GPIO 34 che regoli il tempo delle note. All’inizio di ciascun evento acquisisci una sola volta il codice 0–4095 e calcola `fattore = 50 + raw × 100 / 4095`, con divisione intera. La durata dell’evento è `durata_base × fattore / 100`: il fattore varia dal 50% al 150%. Conserva frequenze, articolazione 80/20 e pausa finale, ridimensionando anche quest’ultima.

**Risultato atteso:** la manopola cambia la velocità senza trasporre le note; il nuovo fattore entra in vigore all’inizio dell’evento successivo e rimane costante durante quell’evento. Consegna entrambi i programmi, circuito aggiornato e prove ai due estremi e durante una nota. Non aggiungere acquisizioni nel ciclo che genera ciascun periodo PWM.

## Stato dei materiali e delle prove

Guide, cinque esempi nei due linguaggi e dieci diagrammi sono disponibili. Controlli locali del **16 ottobre 2026**: i cinque sketch sono stati compilati con g++ e API sostituite, senza avvisi; quindici scenari sono stati eseguiti nei due linguaggi con clock ordinario e attraverso il ritorno a zero, oltre a quattro casi di errore PWM specifici C++: **64 esecuzioni superate**. Sono stati confrontati codici DAC, acquisizioni, attivazione dei toni e messaggi. Le prove comprendono riavvio delle sequenze, estremi ADC, ritardi del ciclo, articolazione, pausa finale e tutti i 4000 campioni del primo blocco audio DAC. È stata controllata la riscalatura di tutti i 4096 codici ADC.

Sintassi Python, collegamenti locali e coerenza dei dieci diagrammi JSON sono stati verificati. Il test C++ usa la larghezza nativa di `unsigned long` del computer; il modello non emula la CPU ESP32 né il tempo delle chiamate alle periferiche.

**Compilazione con core ESP32, esecuzione nel runtime MicroPython, prove Wokwi e collaudo hardware: da eseguire.** Un controllo con API sostituite non misura tensione, suono, carico del piezo, jitter o supporto DAC nel simulatore.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [⬅️ Esercitazione precedente: 05 · Ingressi analogici e ADC](../05-Ingressi-analogici-e-ADC/README.md)
- [➡️ Esercitazione successiva: 07 · Sensori e display I²C](../07-Sensori-e-display-I2C/README.md)
