# Ingressi digitali, pull-up e pull-down

## Obiettivi e prerequisiti

Prerequisiti: esercitazioni 01 e 02. Obiettivi: leggere un pulsante, evitare ingressi flottanti e confrontare collegamenti attivi bassi e attivi alti.

## Teoria e collegamento con l’architettura

### Un ingresso osserva una tensione

Un GPIO configurato come ingresso rileva un livello senza imporlo come farebbe un’uscita. La sua **alta impedenza** significa che assorbe poca corrente. Questo è utile per non alterare troppo il circuito osservato, ma un ingresso scollegato può assumere tensioni variabili per effetto di disturbi: è un ingresso **flottante**.

Un contatto aperto, da solo, non stabilisce necessariamente uno zero logico. Occorre una resistenza che dia al nodo un livello definito quando il pulsante non collega altro.

### Pull-up: riposo alto, pressione bassa

Una resistenza di **pull-up** collega debolmente il nodo all’alimentazione logica. Nel primo esempio abilitiamo quella interna al GPIO 23 e colleghiamo il pulsante fra GPIO e GND. A riposo si legge 1; premendo si legge 0. Diciamo che il pulsante è **attivo basso**.

La resistenza è importante anche quando il contatto si chiude: limita la corrente nel percorso fra alimentazione e massa. Non sostituirla con un filo diretto. In questi esempi il GPIO del pulsante deve restare un ingresso, mai un’uscita alta collegata a massa dal tasto.

### Pull-down: riposo basso, pressione alta

Una resistenza di **pull-down** collega il nodo a massa. Nel secondo esempio usiamo una resistenza esterna da 10 kΩ fra GPIO 23 e GND; il pulsante collega il nodo a 3V3 quando premuto. L’ingresso è configurato senza pull interno: riposo 0, pressione 1, comportamento **attivo alto**.

| Circuito | Configurazione | Rilasciato | Premuto | Condizione applicativa |
| --- | --- | --- | --- | --- |
| Pull-up interno | INPUT_PULLUP / Pin.PULL_UP | 1 | 0 | lettura == 0 |
| Pull-down esterno 10 kΩ | INPUT / Pin.IN | 0 | 1 | lettura == 1 |

Il LED deve accendersi durante la pressione in entrambi i casi. Per ottenere lo stesso risultato visibile occorre cambiare sia collegamenti sia interpretazione della lettura.

### I quattro terminali del pulsante

Il pulsante Wokwi ha due contatti, ciascuno riportato su due terminali: `1.l`/`1.r` e `2.l`/`2.r`. La pressione unisce il gruppo 1 al gruppo 2. Usa un terminale per ciascun gruppo; collegarne due dello stesso gruppo produrrebbe una connessione permanente. Il [riferimento Wokwi](https://docs.wokwi.com/parts/wokwi-pushbutton) mostra pin e attributi. Sul componente reale individua le coppie con una prova di continuità a circuito scollegato.

### Collegamento con l’architettura

La periferica GPIO campiona la tensione e presenta un valore logico al software. La CPU legge quel valore e decide l’uscita. La resistenza di pull è parte del circuito elettrico: non è una variabile che “ricorda” l’ultima pressione.

Sul GPIO 23 della scheda di riferimento possiamo usare il pull-up interno. Non tutti i GPIO hanno le stesse capacità: i pin 34–39 dell’ESP32 classico non dispongono di pull-up/pull-down interni, come indicato nei [vincoli Espressif](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html).

## Esempi commentati

Nel [pulsante con pull-up](esempi/01_01-Pulsante-con-pull-up/README.md):

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);       // Configurazione iniziale.
const bool pressed = (digitalRead(BUTTON_PIN) == LOW);
digitalWrite(LED_PIN, pressed ? HIGH : LOW);
```

```python
button = Pin(23, Pin.IN, Pin.PULL_UP)
pressed = (button.value() == 0)
led.value(1 if pressed else 0)
```

`bool` indica un valore vero/falso. L’espressione condizionale C++ `condizione ? a : b` sceglie `a` se la condizione è vera e `b` altrimenti; in Python si scrive `a if condizione else b`. Il [pull-down completo](esempi/01_02-Pulsante-con-pull-down/README.md) usa la condizione opposta e include la resistenza esterna.

## Buone pratiche e debug

Non collegare il pulsante a 5 V. Se risulta sempre premuto, controlla la coppia di terminali e il confronto con 0/1. Se la lettura varia senza toccare nulla, verifica massa, resistenza e configurazione dell’ingresso. Un simulatore può non rendere evidenti tutti i disturbi di un ingresso flottante.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Con pull-up e pulsante verso GND, cosa si legge premendo?**

   - A. 1
   - B. 0
   - C. Sempre un numero casuale
   - D. Il numero del GPIO

2. **A cosa serve una resistenza di pull?**

   - A. A definire il livello del nodo quando il contatto è aperto
   - B. A compilare il programma
   - C. A filtrare automaticamente ogni rimbalzo
   - D. A far diventare un ingresso un’uscita

3. **Nel pulsante Wokwi quali terminali sono sempre collegati?**

   - A. 1.l e 2.l
   - B. 1.r e 2.r
   - C. 1.l e 1.r
   - D. Tutti e quattro

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Esegui il pull-up e annota livello e stato del LED a riposo e premuto.

   **Risultato atteso:** Riposo 1/spento; pressione 0/acceso.

2. **Consegna:** Scollega l’alimentazione e passa al pull-down usando tabella e codice del secondo esempio.

   **Risultato atteso:** Stesso effetto sul LED, con valori elettrici opposti.

3. **Consegna:** Modifica il programma per mantenere il LED acceso soltanto a riposo in entrambi i circuiti.

   **Risultato atteso:** La condizione applicativa cambia coerentemente senza eliminare le resistenze di pull.

## Soluzioni dell’autovalutazione

1. **B — 0.** Il contatto porta il nodo a massa.

2. **A — A definire il livello del nodo quando il contatto è aperto.** Il pull evita che il nodo resti flottante; non è un filtro completo dei rimbalzi.

3. **C — 1.l e 1.r.** I due terminali del contatto 1 sono collegati anche a riposo.

## Riferimenti

[Ingressi Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html), [pulsante Wokwi](https://docs.wokwi.com/parts/wokwi-pushbutton).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](../02-Uscite-digitali-e-LED/04-Drive-strength-dei-GPIO.md)
- [➡️ Guida successiva](02-Polling-stato-e-fronti.md)
