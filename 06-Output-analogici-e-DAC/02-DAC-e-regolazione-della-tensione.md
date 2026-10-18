# DAC e regolazione della tensione

## Obiettivi e prerequisiti

Prerequisiti: guida 01 e ADC dell’esercitazione 05. Trasformerai un ingresso in un comando DAC, distinguendo riscalatura numerica e riproduzione fedele di una tensione.

## Teoria e collegamento con l’architettura

### Dall’ADC al DAC

L’[esempio completo](esempi/02_01-Potenziometro-e-DAC/README.md) collega il cursore di un potenziometro da 10 kΩ al GPIO 34. L’uscita DAC rimane sul GPIO 25; i due pin non sono collegati fra loro. Il tester misura GPIO 25 rispetto a GND.

Ogni 20 ms il programma acquisisce un codice nella scala comune 0–4095 e calcola:

```text
codice_DAC = codice_ADC × 255 / 4095   (divisione intera)
```

| ADC | DAC |
| --- | --- |
| 0 | 0 |
| 2048 | 127 |
| 4095 | 255 |

Il punto centrale produce 127 per troncamento, non 128 per arrotondamento. Molti codici ADC producono lo stesso codice DAC: passare da dodici a otto bit elimina informazione. Non sono creati nuovi dettagli aumentando i numeri stampati.

### Normalizzare non significa calibrare

In MicroPython `read_u16()` restituisce una scala a 16 bit; con l’ADC configurato a 12 bit, `// 16` riporta il valore alla scala usata qui. C++ imposta `analogReadResolution(12)`. L’attenuazione è a 11 dB in entrambi gli esempi, come nell’esercitazione 05.

Non si realizza un buffer analogico a guadagno unitario: l’ADC ha il proprio intervallo, può saturare prima di 3,3 V e non è perfettamente lineare; anche il DAC ha errori. Perciò tensione del cursore e tensione DAC possono differire sensibilmente. La relazione garantita dal programma riguarda i **codici**.

### Campionamento e costo della seriale

L’acquisizione è nominalmente a 50 Hz; la stampa è ridotta a una volta ogni 200 ms. Il DAC conserva il livello fra due acquisizioni: l’uscita cambia a gradini quando cambia il codice. Il polling non garantisce un periodo esatto né recupera le acquisizioni saltate; in caso di ritardo viene eseguita una sola acquisizione al giro utile.

## Esempi commentati

```cpp
const int raw = analogRead(34);
const int code = raw * 255L / 4095;  // Moltiplica prima della divisione.
dacWrite(25, code);
```

```python
raw = adc.read_u16() // 16
code = raw * 255 // 4095
dac.write(code)
```

Non scrivere `raw / 4095 * 255` con divisione intera in C++: quasi tutti i valori diventerebbero zero prima della moltiplicazione.

## Buone pratiche e debug

Collega gli estremi del potenziometro a 3V3 e GND, mai a 5 V. Il cursore va solo al GPIO 34. Se il DAC resta alto per una parte della corsa, confronta prima il codice ADC: potrebbe essere già saturo. Non correggere un errore di cablaggio cambiando la formula.

Misura almeno cinque posizioni: tensione del cursore, codice ADC, codice DAC e tensione d’uscita. Non attribuire al DAC un errore introdotto dall’ADC. La prova completa è su hardware; il circuito Wokwi aiuta a riconoscere i collegamenti, senza attestare una tensione DAC simulata.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Quanto vale il DAC con ADC=2048 nella formula proposta?**

   - A. 127
   - B. 128
   - C. 2048
   - D. 4095

2. **La tensione DAC è necessariamente uguale a quella del cursore?**

   - A. Sì, perché i pin sono collegati
   - B. Sì, per ogni ESP32
   - C. No: intervalli, quantizzazione ed errori possono differire
   - D. Solo con la seriale aperta

3. **Perché stampare meno spesso di quanto si acquisisce?**

   - A. Per portare il DAC a 16 bit
   - B. Per ridurre traffico e costo della seriale
   - C. Per eliminare la saturazione
   - D. Per alimentare il potenziometro

## Esercizi pratici

1. **Consegna:** Prova i valori ADC 0, 2048 e 4095 e controlla la formula anche con un calcolo manuale.

   **Risultato atteso:** Codici DAC rispettivamente 0, 127 e 255.

2. **Consegna:** Aggiungi un arrotondamento al più vicino usando (raw × 255 + 2047) / 4095, con divisione intera.

   **Risultato atteso:** Il centro diventa 128; gli estremi restano 0 e 255. La calibrazione non cambia.

3. **Consegna:** Porta il periodo di aggiornamento a 200 ms e muovi lentamente il potenziometro.

   **Risultato atteso:** Gradini temporali più distanziati, senza aumentare la risoluzione del DAC.

## Soluzioni dell’autovalutazione

1. **A.** La divisione intera tronca 127,53 a 127.
2. **C.** La riscalatura lavora sui codici e non calibra i due convertitori.
3. **B.** La stampa è un’attività distinta dall’aggiornamento dell’uscita.

## Riferimenti

- [MicroPython ESP32: ADC e DAC](https://docs.micropython.org/en/latest/esp32/quickref.html#dac-digital-to-analog-conversion).
- [MicroPython: machine.DAC](https://docs.micropython.org/en/latest/library/machine.DAC.html).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](README.md)
- [⬅️ Guida precedente](01-Uscite-analogiche-PWM-e-DAC.md)
- [➡️ Guida successiva](03-Buzzer-passivo-e-PWM.md)
