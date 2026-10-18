# Melodie e audio con DAC

## Obiettivi e prerequisiti

Prerequisiti: guide precedenti, array e macchine a stati. Riprodurrai una breve melodia con PWM e confronterai questa tecnica con la generazione di campioni sul DAC.

## Teoria e collegamento con l’architettura

### Una melodia è una sequenza di eventi

L’[esempio melodia](esempi/04_01-Melodia-con-buzzer/README.md) usa due array paralleli: frequenze e durate in millisecondi. L’indice seleziona l’evento corrente. Il valore zero nella tabella significa pausa; il programma lo traduce in duty zero, senza chiamare `freq(0)` in MicroPython.

| Evento | Frequenza richiesta | Durata totale |
| --- | --- | --- |
| DO4 | 262 Hz | 300 ms |
| RE4 | 294 Hz | 300 ms |
| MI4 | 330 Hz | 300 ms |
| DO4 | 262 Hz | 300 ms |
| MI4 | 330 Hz | 300 ms |
| FA4 | 349 Hz | 300 ms |
| SOL4 | 392 Hz | 600 ms |
| Pausa | 0, convenzione della tabella | 1000 ms |

Sono frequenze arrotondate per una sequenza didattica, non una registrazione musicale. Ogni evento sonoro tiene il tono per l’80% della durata e lascia silenzio per il restante 20%: per 300 ms sono 240 ms di suono e 60 ms di articolazione. Il ciclo nominale dura 3400 ms. Dopo la pausa riparte dall’inizio.

### Macchina a stati e ritardi

Lo stato comprende indice, istante iniziale e indicazione di tono attivo. Il tempo trascorso decide prima il passaggio alla nota successiva, poi l’eventuale inizio del silenzio di articolazione. Si usano sottrazione unsigned in C++ e `ticks_diff()` in MicroPython. Se il programma arriva tardi, avanza di un evento e riparte dal tempo osservato: non esegue raffiche per recuperare tutte le note perse.

```cpp
const unsigned long elapsed = now - noteStarted;
if (elapsed >= duration) {
  // Avanza l'indice e inizia il nuovo evento dal tempo osservato.
} else if (sounding && elapsed >= duration * 4 / 5) {
  ledcWriteTone(18, 0);
  sounding = false;
}
```

```python
elapsed = ticks_diff(now, note_started)
if elapsed >= duration:
    # Il programma completo avanza e avvia l'evento successivo.
    pass
elif sounding and elapsed >= duration * 4 // 5:
    buzzer.duty_u16(0)
    sounding = False
```

Il timer continua a generare il tono mentre il programma può controllare ingressi. Resta una breve pausa di 1 ms per giro: non si garantisce una temporizzazione musicale esatta.

### Audio realmente generato dal DAC

Nell’[esempio audio DAC](esempi/04_02-Audio-con-DAC/README.md) il piezo viene spostato su **GPIO 25**, sempre attraverso **1 kΩ**. GPIO 18 non è utilizzato. Il programma scrive ripetutamente otto campioni:

```text
128, 173, 192, 173, 128, 83, 64, 83
```

La tabella approssima un periodo sinusoidale, centrato a 128 con ampiezza di 64 codici. Tra una scrittura e la seguente attende 250 µs: trascurando il costo del codice, otto campioni occupano 2 ms, ossia circa 500 Hz con frequenza di aggiornamento di 4 kcampioni/s. Sul pin si osservano gradini, non una sinusoide filtrata ideale.

Ogni venti periodi viene aggiunta una pausa di 1 ms per cedere tempo al sistema. Si ripetono 500 periodi e poi si mantiene il codice 128 per un secondo. Le attese esplicite del blocco sonoro sommano **1025 ms**, a cui si aggiunge il tempo di esecuzione: il tono ha interruzioni e jitter, con risultati diversi fra C++ e MicroPython. Non è una sorgente calibrata a 500 Hz. Il silenzio al codice 128 deriva dall’assenza di variazione, non da un’uscita a zero volt; i passaggi possono produrre clic.

Questa versione didattica usa cicli sincroni: durante il blocco non esegue altre attività applicative. Per audio più fedele servono campionamento regolare, buffer e un driver hardware adatto, per esempio DAC con DMA in ESP-IDF oppure I²S con DAC esterno e amplificatore. Il buffer conserva campioni; la cadenza di lettura determina le frequenze riprodotte. File WAV, MP3, parlato e amplificatori non sono implementati in questi esempi.

## Prove e debug

Esegui la melodia PWM in Wokwi e su hardware. L’audio DAC richiede la scheda reale con DAC e un piccolo piezo passivo; la resistenza limita il carico ma il volume può essere basso. Non usare altoparlanti o cuffie direttamente sul DAC. Su hardware confronta forma d’onda e tempi all’oscilloscopio; non aumentare il carico per ottenere volume.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Quanto suona una nota con durata totale 300 ms nell’esempio PWM?**

   - A. 300 ms più 60 ms
   - B. 240 ms, poi 60 ms di silenzio
   - C. 60 ms, poi 240 ms di silenzio
   - D. Sempre un secondo

2. **Otto campioni distanziati idealmente di 250 µs formano quale periodo?**

   - A. 250 µs
   - B. 8 s
   - C. 2 ms
   - D. 500 ms

3. **Tenere il DAC a 128 durante la pausa significa che il pin è a 0 V?**

   - A. Sì
   - B. Solo a 500 Hz
   - C. Solo dopo 500 periodi
   - D. No, è un livello costante intermedio

## Esercizi pratici

1. **Consegna:** Aggiungi una nota LA4 a 440 Hz per 600 ms prima della pausa, aggiornando entrambe le tabelle e il limite dell’indice C++.

   **Risultato atteso:** Nove eventi, ciclo nominale 4000 ms, con pausa finale ancora presente.

2. **Consegna:** Dimezza tutte le durate PWM mantenendo invariato il rapporto 80/20.

   **Risultato atteso:** Melodia due volte più rapida; le frequenze richieste non cambiano.

3. **Consegna:** Nel DAC confronta attese di 250 e 500 µs, misurando con l’oscilloscopio.

   **Risultato atteso:** Il secondo tono è più basso; documenta scarti, interruzioni e costo del runtime anziché assumere frequenze esatte.

## Soluzioni dell’autovalutazione

1. **B.** L’articolazione occupa il 20% della durata già assegnata.
2. **C.** 8 × 250 µs = 2000 µs; il codice reale aggiunge tempo e pause.
3. **D.** L’assenza di oscillazione distingue la pausa dal tono.

## Riferimenti

- [MicroPython: API DAC e limiti dei port](https://docs.micropython.org/en/latest/library/machine.DAC.html).
- [Espressif: conversione DAC continua e DMA](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/dac.html).
- [MicroPython: PWM](https://docs.micropython.org/en/latest/library/machine.PWM.html).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](README.md)
- [⬅️ Guida precedente](03-Buzzer-passivo-e-PWM.md)
- [➡️ Guida successiva](../07-Sensori-e-display-I2C/01-Bus-I2C-e-indirizzi.md)
