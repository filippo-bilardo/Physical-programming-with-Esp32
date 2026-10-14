# GPIO e uscite digitali

## Obiettivi e prerequisiti

Prerequisiti: circuito LED e legge di Ohm della guida 01. Obiettivi: configurare più uscite, interpretare HIGH/LOW e pianificare transizioni fra combinazioni di LED.

## Teoria e collegamento con l’architettura

### Livelli elettrici e significato applicativo

Un’uscita digitale comanda un livello basso o alto. Nel circuito con anodo verso il GPIO e catodo a GND, HIGH accende il LED: lo chiamiamo collegamento **attivo alto**. Questa relazione dipende dal cablaggio; non significa che qualsiasi LED in qualsiasi circuito si accenda sempre con HIGH.

In C++ `pinMode` configura la direzione e `digitalWrite` imposta il livello. In MicroPython la creazione di `Pin` specifica la direzione; `value` permette di impostare 0 o 1. Una **API** associa a un’operazione hardware una funzione utilizzabile dal programma. I nomi cambiano fra ambienti, mentre l’effetto richiesto al pin è lo stesso.

### Scegliere i pin

Usiamo GPIO 18, 19 e 21 come uscite e riserviamo GPIO 23 al pulsante dell’esercitazione seguente. Sull’ESP32 classico GPIO 34–39 sono soltanto ingressi; alcuni altri GPIO servono a Flash, comunicazione seriale o configurazione dell’avvio. I pin di **strapping** vengono letti all’avvio per selezionare funzioni della scheda. Non sostituire i pin arbitrariamente: consulta la [tabella Espressif](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html).

Un numero come 18 identifica il GPIO, non il diciottesimo contatto del connettore. Sulle DevKit la scritta può essere `18` o `D18`: fa fede lo schema della scheda. Ogni esempio dichiara la corrispondenza precisa.

### Due uscite indipendenti

Due LED richiedono due rami in parallelo rispetto alla massa, ciascuno con la propria resistenza. Non si mette una sola resistenza sul ritorno comune: i rami devono mantenere una limitazione di corrente indipendente.

| Fase | GPIO 18, LED A | GPIO 19, LED B |
| --- | --- | --- |
| Inizializzazione | LOW | LOW |
| A | HIGH | LOW |
| B | LOW | HIGH |

La sequenza delle scritture conta. Per passare da A a B spegni A prima di accendere B. Le istruzioni non vengono eseguite simultaneamente: esiste un piccolo intervallo con entrambi spenti. Nel nostro esercizio è accettabile e impedisce sovrapposizioni intenzionali.

### Collegamento con l’architettura

I registri della periferica conservano la configurazione e il livello d’uscita. Le variabili del programma rappresentano scelte e tempi, ma il pin continua a mantenere l’ultimo comando mentre la CPU esegue altro. Durante reset e avvio, prima che il programma configuri i pin, non si deve presumere lo stesso stato operativo: questo diventerà importante con carichi più complessi.

Configurare le uscite in `setup()` o prima del ciclo rende esplicita la fase iniziale. Un programma leggibile separa numeri dei pin, durata delle fasi e sequenza di azioni.

## Esempi commentati

Dall’[esempio dei due LED](esempi/02_01-Due-LED-alternati/README.md):

```cpp
digitalWrite(LED_A, LOW);   // Termina la fase A.
digitalWrite(LED_B, HIGH);  // Inizia la fase B.
delay(STEP_MS);
```

```python
led_a.value(0)
led_b.value(1)
sleep_ms(STEP_MS)
```

Confronta la tabella degli stati con il codice completo: ogni fase deve assegnare tutti i livelli necessari, senza fare affidamento su uno stato casuale.

## Buone pratiche e debug

Assegna nomi comprensibili ai pin e inizializza tutte le uscite. Se entrambi i LED restano accesi, verifica che ogni fase spenga quello precedente e che i fili non uniscano i due GPIO. Non collegare direttamente due uscite fra loro.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Perché ogni LED ha una propria resistenza?**

   - A. Per cambiare la sintassi del programma
   - B. Per limitare indipendentemente la corrente di ogni ramo
   - C. Per raddoppiare la RAM
   - D. Per sostituire GND

2. **Per passare da A acceso a B acceso senza sovrapporli, cosa si fa?**

   - A. Si spegne prima A, poi si accende B
   - B. Si accende B e si elimina la resistenza
   - C. Si cambia la porta USB
   - D. Si collega A a B

3. **Quale pin non è adatto come uscita sull’ESP32 classico?**

   - A. GPIO 18
   - B. GPIO 19
   - C. GPIO 21
   - D. GPIO 34

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Esegui A/B e associa ogni messaggio al GPIO acceso.

   **Risultato atteso:** Alternanza coerente con la tabella degli stati.

2. **Consegna:** Inserisci 200 ms con entrambi spenti fra A e B e fra B e A.

   **Risultato atteso:** Periodo nominale 500 + 200 + 500 + 200 = 1400 ms.

3. **Consegna:** Progetta la sequenza entrambi spenti → solo A → entrambi accesi → solo B, 500 ms per fase.

   **Risultato atteso:** Quattro combinazioni distinte e periodo nominale di 2 s, con due resistenze separate.

## Soluzioni dell’autovalutazione

1. **B — Per limitare indipendentemente la corrente di ogni ramo.** Ogni ramo ha una corrente da limitare.

2. **A — Si spegne prima A, poi si accende B.** L’ordine produce un breve intervallo spento invece di uno con entrambi accesi.

3. **D — GPIO 34.** GPIO 34 appartiene al gruppo di pin utilizzabili solo come ingressi.

## Riferimenti

[GPIO Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html), [vincoli dei pin ESP32](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html).

## Navigazione del corso

- [📑 Indice generale](../../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](01-Circuiti-LED-e-resistenze.md)
- [➡️ Guida successiva](03-Funzioni-cicli-e-sequenze.md)
