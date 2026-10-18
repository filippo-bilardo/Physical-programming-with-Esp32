# Uscite analogiche, PWM e DAC

## Obiettivi e prerequisiti

Prerequisiti: esercitazioni 01–05, tensione, GPIO e ADC. Distinguerai un livello digitale, un segnale PWM e una tensione prodotta dal DAC, scegliendo lo strumento con cui osservarli.

## Teoria e collegamento con l’architettura

### Tre uscite diverse

| Metodo | Che cosa esce dal pin | Parametro principale | Osservazione utile |
| --- | --- | --- | --- |
| GPIO digitale | Livello basso o alto | Stato 0/1 | Tester o analizzatore logico |
| PWM | Commutazioni periodiche basso/alto | Frequenza e duty cycle | Oscilloscopio o analizzatore logico |
| DAC | Livello analogico selezionato da un codice | Codice numerico | Tester DC, oscilloscopio per variazioni rapide |

Un duty cycle del 50% significa che il segnale rimane alto per metà periodo. Sul filo continuano a esserci commutazioni: il valore medio ideale di circa 1,65 V non descrive la forma d’onda. Un filtro passa-basso può ridurre l’ondulazione del PWM, introducendo ritardo; un tester può mostrare un valore medio senza dimostrare che l’uscita sia continua.

Il DAC effettua la conversione opposta all’ADC: la CPU scrive un numero e la periferica imposta un livello. Sull’**ESP32 classico WROOM-32** ci sono due uscite DAC a **8 bit**, GPIO **25** e **26**, con codici **0–255**. Gli esempi usano GPIO 25. Una tensione mantenuta dal DAC non richiede che il programma ripeta continuamente la scrittura.

### Risoluzione e carico

256 codici non significano 256 tensioni esatte né accuratezza di otto bit. Alimentazione, conversione reale e corrente assorbita dal carico influenzano il risultato. Per i conti di questa guida usiamo la scala didattica `V_ideale ≈ 3,3 × codice / 255`, includendo gli estremi ideali: non è una curva di calibrazione del chip. Il passo è circa 13 mV; alcune convenzioni descrivono invece l’LSB con 3,3/256. Misura la scheda prima di usare il DAC come riferimento.

| Codice | Tensione nella scala didattica |
| --- | --- |
| 0 | 0,00 V |
| 64 | 0,83 V |
| 128 | 1,66 V |
| 192 | 2,48 V |
| 255 | 3,30 V |

Il DAC è un’uscita di segnale: non alimenta un altoparlante da 8 Ω, un motore o un buzzer di potenza. Per le prime misure collega soltanto un multimetro ad alta impedenza fra GPIO 25 e GND. Non usare come carico un LED privo della propria resistenza.

## Esempi commentati

```cpp
// Arduino-ESP32: una vera uscita DAC sull'ESP32 classico.
dacWrite(25, 128);
```

```python
from machine import DAC, Pin
output = DAC(Pin(25))
output.write(128)
```

L’[esempio dei cinque livelli](esempi/01_01-Livelli-DAC/README.md) mantiene ogni codice per due secondi e stampa il codice richiesto. La scritta `DAC=128` non è una misura di 1,66 V.

## Ambiente e debug

La scheda di riferimento resta DOIT ESP32 DEVKIT V1. Le varianti ESP32-C3 e S3 non forniscono questo DAC integrato: cambiare soltanto il numero del pin non risolve l’assenza della periferica. `analogWrite()` nel core ESP32 genera PWM; per questa attività usa esplicitamente `dacWrite()`.

Wokwi documenta il PWM LEDC; la sua tabella di supporto ESP32 non dichiara il DAC. I diagrammi DAC forniti sono una traccia del cablaggio, con una nota per il tester, e non dimostrano una conversione simulata. Le misure DAC vanno eseguite sulla scheda reale. Una sonda logica non misura i livelli intermedi analogici.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Quale uscita può mantenere un livello intermedio senza PWM?**

   - A. Il solo GPIO digitale
   - B. Il DAC
   - C. La UART
   - D. Il pin GND

2. **Che cosa prova DAC=128 sulla seriale?**

   - A. Che il tester ha misurato 1,66 V
   - B. Che la corrente è 128 mA
   - C. Che il programma ha richiesto il codice 128
   - D. Che è attivo il PWM

3. **Un PWM al 50% produce sul filo una tensione costante di 1,65 V?**

   - A. Sì, sempre
   - B. Sì, se la CPU è veloce
   - C. Solo su GPIO 25
   - D. No, il segnale commuta fra due livelli

## Esercizi pratici

1. **Consegna:** Esegui i cinque livelli e annota tensione ideale e misurata, lasciando il tester in modalità DC.

   **Risultato atteso:** Cinque misure associate ai rispettivi codici, senza sostituire la misura con la formula.

2. **Consegna:** Aggiungi i codici 32 e 224 e aggiorna il numero di elementi nel ciclo C++.

   **Risultato atteso:** Sette livelli; entrambi i programmi ritornano al primo senza leggere fuori dall’array.

3. **Consegna:** Confronta un PWM al 50% e un DAC a metà scala usando un oscilloscopio, se disponibile.

   **Risultato atteso:** Il primo commuta, il secondo mantiene un livello con gli errori e il rumore del circuito.

## Soluzioni dell’autovalutazione

1. **B.** Il DAC converte un codice in un livello analogico.
2. **C.** Un comando non è una misura del circuito.
3. **D.** Valore medio e forma d’onda sono grandezze diverse.

## Riferimenti

- [Espressif: DAC Arduino](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/dac.html).
- [Espressif: DAC ESP32](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/dac.html).
- [Wokwi: periferiche ESP32](https://docs.wokwi.com/guides/esp32#simulation-features).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](README.md)
- [⬅️ Guida precedente](../05-Ingressi-analogici-e-ADC/04-Soglia-regolabile-e-isteresi.md)
- [➡️ Guida successiva](02-DAC-e-regolazione-della-tensione.md)
