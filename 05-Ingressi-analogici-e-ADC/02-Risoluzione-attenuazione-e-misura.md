# Risoluzione, attenuazione e misura

## Obiettivi e prerequisiti

Prerequisiti: guida 01, proporzioni e divisione intera. Distinguerai quantità di codici, intervallo di tensione, accuratezza e calibrazione; convertirai il codice in una percentuale dichiarandone il significato.

## Teoria e collegamento con l'architettura

### Risoluzione: quanti codici posso rappresentare?

Con N bit si rappresentano `2^N` codici, da 0 a `2^N − 1`. Un ADC a 12 bit dispone quindi di 4096 codici, da 0 a 4095. Un'uscita software larga 16 bit non dimostra che l'hardware distingua 65536 livelli fisici.

| Grandezza | Esempio | Significato |
| --- | --- | --- |
| Risoluzione hardware impostata | 12 bit | Quantizzazione della conversione |
| Scala comune del corso | 0–4095 | Codice usato nei confronti |
| Risultato `read_u16()` | 0–65535 | Rappresentazione riscalata dell'API |
| Percentuale del codice | 0–100 | Trasformazione numerica per l'interfaccia |
| Tensione | mV o V | Grandezza fisica da misurare o calibrare |

Per un convertitore **ideale** con intervallo di 3,3 V, un passo a 12 bit sarebbe circa `3,3 / 4096 ≈ 0,806 mV`. È un esempio teorico di quantizzazione, non una specifica di accuratezza dell'ESP32. Rumore, non linearità e variazioni del riferimento possono incidere più di un singolo codice.

### Attenuazione: quale intervallo posso acquisire?

L'attenuazione riduce il segnale visto dallo stadio di conversione. Negli esempi selezioniamo 11 dB: `ADC_11db` in Arduino-ESP32 e `ADC.ATTN_11DB` in MicroPython. Le due opzioni indicano la configurazione, non un fattore da applicare come semplice moltiplicazione ai codici.

L'intervallo utilizzabile dipende da chip, firmware e condizioni di misura; non coincide automaticamente con 0–3,3 V. Vicino agli estremi possono comparire zone poco lineari e saturazione. Le documentazioni Arduino e MicroPython riportano intervalli caratterizzati diversi: usa il riferimento della toolchain effettiva e verifica il comportamento reale. Non assumere `4095 = 3,3 V` e non usare `raw * 3.3 / 4095` come voltmetro calibrato.

L'alimentazione a 3V3 mantiene il potenziometro entro il livello previsto dal circuito, ma non garantisce che l'ADC misuri linearmente tutta la corsa. Un codice fermo al massimo mentre il multimetro mostra ancora variazioni è un indizio di saturazione.

## Esempi commentati

Nell'[esempio di scala percentuale](esempi/02_01-Scala-percentuale/README.md):

```cpp
const int percent = raw * 100L / 4095;
```

```python
percent = raw * 100 // 4095
```

La moltiplicazione precede la divisione. I valori non negativi vengono troncati per difetto nei due linguaggi: 0 produce 0%, 2048 produce 50%, 4095 produce 100%. `100L` rende esplicito il calcolo con un intero lungo in C++; i valori di questo esempio restano entro i limiti dell'ESP32.

La percentuale descrive **la scala digitale**, non necessariamente la posizione fisica della manopola o la percentuale di 3,3 V. Anche uno schermo che mostra “100%” potrebbe ricevere un ADC già saturo.

### Passare a una misura di tensione

Per una prova aggiuntiva su hardware, Arduino-ESP32 offre `analogReadMilliVolts(34)`; MicroPython ESP32 offre `adc.read_uv()` e la divisione per 1000 per ottenere mV. Queste API applicano la calibrazione supportata dalla piattaforma: mantengono limiti di validità e non sostituiscono un multimetro di riferimento.

```cpp
// Prova opzionale separata, con attenuazione gia' configurata.
uint32_t millivolts = analogReadMilliVolts(34);
```

```python
millivolts = adc.read_uv() // 1000
```

Sono conversioni ulteriori rispetto alla precedente lettura grezza: non attribuire necessariamente i due risultati allo stesso istante. Queste chiamate non sono richieste dai programmi Wokwi forniti; se il firmware non le supporta, registra il limite senza sostituirle con una formula presentata come calibrata.

## Prova con multimetro e debug

Misura la tensione **fra cursore e GND**, usando la portata volt continua. Il puntale non deve cortocircuitare terminali vicini. Non impostare il multimetro in misura di corrente per questa prova.

| Posizione indicativa | Tensione misurata al cursore (V) | Codice 0–4095 | Percentuale del codice | Note |
| --- | --- | --- | --- | --- |
| Minimo | Da misurare | — | — | — |
| Circa 1/4 | Da misurare | — | — | — |
| Circa metà | Da misurare | — | — | — |
| Circa 3/4 | Da misurare | — | — | — |
| Massimo | Da misurare | — | — | — |

Se due tensioni diverse danno lo stesso codice alto, controlla saturazione e attenuazione prima di aumentare i bit. Conserva nella relazione modello della scheda, firmware, configurazione e risoluzione dello strumento.

## Autovalutazione

1. **Quanti codici contiene una scala a 12 bit?**

   - A. 12.
   - B. 4095.
   - C. 4096.
   - D. 65536.

2. **`read_u16()` implica un ADC fisico a 16 bit?**

   - A. Sì, su qualsiasi scheda.
   - B. No: la scala restituita dall'API può essere una riscalatura.
   - C. Sì, purché si stampi un numero decimale.
   - D. Solo se il potenziometro è da 10 kΩ.

3. **Il codice è 2048. La percentuale intera dell'esempio vale:**

   - A. 50%, riferita alla scala del codice.
   - B. 50 V.
   - C. Una misura garantita di 1,65 V.
   - D. 2048%.

## Esercizi pratici

1. **Consegna:** calcola a mano la percentuale per 1024, 2047 e 3072.

   **Risultato atteso:** 25%, 49% e 75%; si tronca e non si arrotonda al più vicino.

2. **Consegna:** compila la tabella con il multimetro su scheda reale.

   **Risultato atteso:** cinque coppie di misure, senza inventare una corrispondenza ideale. Annota eventuale saturazione.

3. **Consegna:** confronta, dove disponibile, la lettura calibrata in mV con il multimetro in tre punti intermedi.

   **Risultato atteso:** differenze documentate con unità e condizioni; nessuna garanzia di uguaglianza perfetta. Non usare i soli estremi per valutare la calibrazione.

## Soluzioni dell'autovalutazione

1. **C.** Il valore massimo è 4095 perché la numerazione comincia da zero.
2. **B.** La rappresentazione dell'API non aumenta da sola la risoluzione fisica.
3. **A.** L'espressione calcola una percentuale del codice, non una tensione.

## Riferimenti

- [Espressif: risoluzione, attenuazione e lettura calibrata](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html).
- [MicroPython ESP32: configurazione e read_uv()](https://docs.micropython.org/en/latest/esp32/quickref.html#adc-analog-to-digital-conversion).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente](01-Potenziometro-e-ADC.md)
- [➡️ Guida successiva](03-Campionamento-rumore-e-media.md)
