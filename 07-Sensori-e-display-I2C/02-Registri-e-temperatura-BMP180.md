# Registri e temperatura del BMP180

## Obiettivi e prerequisiti

Prerequisiti: guida 01 e scala delle misure. Imparerai a distinguere indirizzo del dispositivo e registro, avviare una conversione e usare i coefficienti di calibrazione.

## Teoria e collegamento con l'architettura

### Un indirizzo seleziona il dispositivo, un registro seleziona il dato

Il BMP180 è un sensore di pressione che misura anche la temperatura del proprio chip. Qui usiamo soltanto la temperatura; il riscaldamento della scheda e il montaggio possono influenzarla. Non è il BMP280: pur avendo un nome simile, registri e driver non sono intercambiabili.

| Registro BMP180 | Uso nel driver |
| --- | --- |
| 0xD0 | Identificativo atteso 0x55 |
| 0xB2–0xB5 | Coefficienti AC5 e AC6, senza segno |
| 0xBC–0xBF | Coefficienti MC e MD, con segno |
| 0xF4 | Comando 0x2E per iniziare la temperatura |
| 0xF6–0xF7 | Risultato grezzo UT, byte alto prima |

Per una lettura di registro, il controller comunica prima quale registro vuole leggere e poi acquisisce i byte. Un indirizzo o una dimensione errati possono restituire byte senza il significato desiderato.

### Dal dato grezzo alla temperatura compensata

UT non è una temperatura in gradi. Il driver locale applica la compensazione Bosch usando i coefficienti del singolo sensore. La divisione intera con valori negativi richiede attenzione: C++ tronca verso zero, mentre `//` in Python arrotonda verso il basso. Il modulo Python riproduce esplicitamente il comportamento del calcolo C++.

I file `bmp180_temperature.h` e `bmp180_temperature.py` sono forniti negli esempi: puoi usare l'interfaccia prima di studiarne tutti i passaggi. Non serve installare una libreria BMP085/BMP180 esterna. Il driver legge ID e coefficienti, avvia la conversione, attende **5 ms** e restituisce un intero in decimi di °C. Questa piccola attesa è sincrona; il polling a un secondo non rende ogni operazione non bloccante.

### Errore e validità del dato

Nell'[esempio completo](esempi/02_01-Temperatura-BMP180/README.md), un NACK, una lettura incompleta, un ID inatteso, coefficienti nulli/non validi o un risultato fuori intervallo producono `ERR BMP180`. Non si stampa una temperatura fittizia di zero. Il ciclo seguente ritenta l'inizializzazione; questa strategia non ripara un guasto elettrico e non garantisce il recupero di un bus in corto.

## Esempi commentati

```cpp
int temperature;
if (ready && sensor.readDeciC(temperature)) {
  Serial.println(temperature / 10.0, 1);
} else {
  ready = false;
  Serial.println("ERR BMP180");
}
```

```python
try:
    temperature = sensor.read_deci_c()
    print('%.1f' % (temperature / 10))
except OSError:
    sensor = None  # Il programma completo lo ricrea alla prova successiva.
    print('ERR BMP180')
```

Il risultato 237 significa 23,7 °C; −55 significa −5,5 °C. La prima prova di acquisizione avviene circa un secondo dopo l'avvio, più il tempo di conversione e comunicazione.

## Buone pratiche e debug

- Non sostituire i coefficienti letti dal sensore con valori presi da un esempio.
- Mantieni il modulo locale nella stessa cartella di main.py o dello sketch.
- In Wokwi varia la temperatura dalle proprietà del sensore: non stai provando l’accuratezza fisica.
- Su hardware confronta dopo stabilizzazione con un termometro di riferimento, indicando i limiti del confronto.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Il valore UT può essere stampato direttamente come gradi Celsius?**

   - A. Sì, senza trasformazioni.
   - B. Solo se vale 0.
   - C. No: va compensato con i coefficienti del sensore.
   - D. Solo con un OLED.

2. **Che cosa significa temperatura = 237 nel driver?**

   - A. 237 V.
   - B. 23,7 °C.
   - C. 237 dispositivi.
   - D. 2,37 kHz.

3. **Come tratta il programma una lettura fallita?**

   - A. La presenta come 0 °C.
   - B. Conserva il vecchio dato come nuovo.
   - C. La ignora sempre.
   - D. Segnala ERR BMP180 e ritenta al ciclo successivo.

## Esercizi pratici

1. **Consegna:** Imposta nel simulatore 15,0 °C, poi 30,0 °C, lasciando alcuni secondi fra le modifiche.

   **Risultato atteso:** Le letture seguono la temperatura con la quantizzazione del driver; annota eventuali scarti del simulatore.

2. **Consegna:** Prova un valore sotto zero supportato dal componente.

   **Risultato atteso:** Il segno deve essere conservato; non devono apparire grandi interi senza segno.

3. **Consegna:** A simulazione ferma scollega il sensore e riavvia, poi ripristina il circuito e riavvia.

   **Risultato atteso:** Il guasto è segnalato come errore. Non dichiarare il recupero a caldo senza provarlo su hardware e nel simulatore.

## Soluzioni dell'autovalutazione

1. **C.** Dato grezzo e grandezza fisica sono distinti.
2. **B.** Il driver restituisce decimi di grado con segno.
3. **D.** La validità della misura viene mantenuta distinta dal suo valore.

## Riferimenti

- [Bosch: datasheet BMP180, sezioni 3.5 e 4](https://cdn-shop.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf).
- [Wokwi: BMP180](https://docs.wokwi.com/parts/board-bmp180).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente disponibile](01-Bus-I2C-e-indirizzi.md)
- [➡️ Guida successiva](03-Display-OLED-e-framebuffer.md)
