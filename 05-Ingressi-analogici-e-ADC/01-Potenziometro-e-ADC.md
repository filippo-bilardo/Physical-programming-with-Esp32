# Potenziometro e conversione analogico-digitale

## Obiettivi e prerequisiti

Prerequisiti: tensione, GND, GPIO e temporizzazioni dell'esercitazione 04. Imparerai a collegare un potenziometro, distinguere ingresso digitale e analogico e leggere un primo codice ADC.

## Teoria e collegamento con l'architettura

### Dal livello logico a un valore numerico

Un ingresso digitale risponde alla domanda “il livello è LOW oppure HIGH?”. Per conoscere quanto vale una tensione serve un **ADC**, convertitore analogico-digitale. Il circuito acquisisce la tensione del canale selezionato e la rappresenta con uno dei codici disponibili; la CPU legge il risultato e il programma lo elabora.

La conversione non restituisce direttamente una temperatura o una percentuale: produce un numero legato a tensione, configurazione e caratteristiche del convertitore. La RAM conserva campioni e risultati; il codice del programma risiede nella Flash. Gli esempi richiedono una conversione alla volta, tramite polling: non usano DMA o interrupt applicativi.

### Il potenziometro come partitore

Un potenziometro lineare da 10 kΩ ha due estremi collegati a una pista resistiva e un cursore mobile. Fra gli estremi misuri circa 10 kΩ indipendentemente dalla posizione; fra cursore e ciascun estremo misuri una parte di quella resistenza.

| Terminale | Collegamento |
| --- | --- |
| Un estremo, `VCC` in Wokwi | 3V3 della scheda |
| Altro estremo, `GND` | GND |
| Cursore, `SIG` | GPIO 34 |

Nel modello di partitore poco caricato, `V_cursore ≈ 3,3 V × R_verso_GND / R_totale`. A metà pista il valore teorico è circa 1,65 V. Non ne segue che l'ADC reale restituisca metà scala: lo studieremo nella guida 02.

Scambiare i due estremi inverte il verso della regolazione. Non scambiare invece un estremo con il cursore senza ricontrollare il circuito. Identifica i terminali a scheda scollegata, usando il multimetro se necessario.

### Perché GPIO 34 e 35

L'esercitazione usa ingressi dell'ADC1 dell'ESP32 classico: GPIO 34 per il segnale e GPIO 35 nel progetto finale. Sono pin di solo ingresso, senza pull-up interno; non vanno usati per il LED. La scelta evita anche la contesa dell'ADC2 con il Wi-Fi nelle successive attività di rete. Verifica sempre i pin della scheda effettiva.

Mantieni il segnale fra GND e 3V3. Collegare un ingresso a 5 V può danneggiare il chip: selezionare un'attenuazione maggiore non lo rende tollerante a 5 V. Il cursore scollegato diventa un ingresso flottante; una lettura variabile non prova che il potenziometro funzioni.

## Esempi commentati

Dall'[esempio completo](esempi/01_01-Lettura-potenziometro/README.md), configurazione C++:

```cpp
analogReadResolution(12);  // Scala 0..4095 sull'ESP32 classico.
analogSetPinAttenuation(34, ADC_11db);
int raw = analogRead(34);
```

In MicroPython:

```python
from machine import ADC, Pin
adc = ADC(Pin(34), atten=ADC.ATTN_11DB)
adc.width(ADC.WIDTH_12BIT)  # Metodo di compatibilita' specifico ESP32.
raw = adc.read_u16() // 16  # Riporta il risultato alla scala comune 0..4095.
```

`read_u16()` espone una scala da 0 a 65535. La divisione intera per 16 raggruppa quella scala in 4096 codici; non è una conversione in volt. L'hardware resta configurato a 12 bit. I due programmi sono equivalenti nella logica e nella scala scelta, senza garantire letture fisiche identiche su firmware diversi.

Il programma completo stampa un campione ogni 200 ms nominali, con prima lettura dopo 200 ms. Usa il contatore temporale e una breve pausa di 1 ms per giro; non aspetta 200 ms dentro la sezione di acquisizione. Le periferiche lavorano comunque in tempi finiti: si tratta di campionamento software, non di un ritmo hardware garantito.

## Buone pratiche e debug

- Alimenta il potenziometro da 3V3, non da VIN o 5V.
- Controlla il nome del GPIO: nei diagrammi Wokwi compare `D34`, nel codice si usa `34`.
- Se il valore non cambia, controlla cursore, massa comune e attenuazione.
- Se cambia soltanto vicino a un estremo, non modificare subito la formula: verifica prima configurazione e saturazione.
- Wokwi semplifica i circuiti analogici: collega comunque anche VCC e GND. Non usare una simulazione riuscita come verifica del cablaggio reale.

## Autovalutazione

1. **Che cosa restituisce la lettura grezza dell'ADC?**

   - A. Sempre una tensione espressa in volt.
   - B. Un codice digitale associato al segnale e alla configurazione.
   - C. La resistenza totale del potenziometro.
   - D. La temperatura della CPU.

2. **Dove si collega il cursore del primo potenziometro?**

   - A. A VIN.
   - B. A 5V.
   - C. A GPIO 34.
   - D. Al catodo del LED.

3. **Perché non usiamo GPIO 34 per pilotare il LED?**

   - A. Perché sull'ESP32 classico è un pin di solo ingresso.
   - B. Perché tutti i GPIO analogici sono sempre uscite.
   - C. Perché il LED richiede un ADC a 16 bit.
   - D. Perché la seriale usa GPIO 34.

## Esercizi pratici

1. **Consegna:** ruota il potenziometro in cinque posizioni e annota i codici.

   **Risultato atteso:** andamento complessivamente crescente in un verso, con possibili saturazioni o variazioni sul dispositivo reale. Il codice è compreso fra 0 e 4095.

2. **Consegna:** a circuito spento scambia i soli due estremi del potenziometro.

   **Risultato atteso:** la manopola regola nel verso opposto; il cursore resta sullo stesso GPIO.

3. **Consegna:** porta `SAMPLE_MS` a 100 e osserva le righe prodotte.

   **Risultato atteso:** circa 10 letture al secondo invece di 5, senza cambiare risoluzione o intervallo di tensione.

## Soluzioni dell'autovalutazione

1. **B.** La conversione in una grandezza fisica richiede un modello o una calibrazione.
2. **C.** Gli altri due terminali alimentano il partitore.
3. **A.** La capacità di acquisizione analogica non implica una capacità d'uscita.

## Riferimenti

- [Arduino-ESP32: ADC e configurazione](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html).
- [MicroPython ESP32: ADC e pin](https://docs.micropython.org/en/latest/esp32/quickref.html#adc-analog-to-digital-conversion). Per `latest`, verifica la compatibilità con la versione installata.
- [Wokwi: potenziometro](https://docs.wokwi.com/parts/wokwi-potentiometer).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente](../04-Tempo-e-macchine-a-stati/03-Macchine-a-stati-e-semaforo.md)
- [➡️ Guida successiva](02-Risoluzione-attenuazione-e-misura.md)
