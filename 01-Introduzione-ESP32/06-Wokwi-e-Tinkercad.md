# Wokwi: simulare ESP32, con un’introduzione a Tinkercad

## Obiettivi e prerequisiti

Prerequisiti: guide 01 e 02, nozioni di LED, resistenza e GPIO. Questa guida approfondisce la simulazione e può essere consultata durante la preparazione del primo programma della guida 03.

Al termine saprai creare progetti ESP32 Arduino e MicroPython in Wokwi, usare diagramma e console, trasferire gli esempi del corso e distinguere simulazione e collaudo reale. Conoscerai anche l’impiego introduttivo di Tinkercad Circuits. Per le attività di questa guida bastano browser e connessione Internet.

## Teoria e collegamento con l’architettura

Un **simulatore** riproduce in software alcuni comportamenti di una scheda e dei suoi componenti. Il programma osserva GPIO e periferiche virtuali: il circuito disegnato descrive le connessioni che la simulazione deve rappresentare.

Un progetto Wokwi contiene due parti da mantenere coerenti: programma e circuito. Modificare `LED_PIN` nel codice non sposta automaticamente il filo; modificare un collegamento non aggiorna automaticamente il programma.

| File | Funzione |
| --- | --- |
| `sketch.ino` nel modello Arduino | Sorgente C++ da compilare nel servizio di simulazione |
| `main.py` nel modello MicroPython | Programma eseguito dal firmware MicroPython simulato |
| `diagram.json` | Componenti, attributi e collegamenti del circuito |
| `libraries.txt`, quando necessario | Librerie Arduino aggiuntive richieste dal progetto Wokwi |

Negli esempi locali del corso il file Arduino si chiama `cpp/cpp.ino`, per rispettare la convenzione dell’IDE desktop. Nel modello online ne copiamo il contenuto in `sketch.ino`. Gli esempi iniziali non richiedono librerie esterne.

Il supporto ESP32 e i modelli Arduino/MicroPython sono descritti nella [guida Wokwi ESP32](https://docs.wokwi.com/guides/esp32). Il runtime online può differire da quello installato sul computer: annota ambiente e data della prova.

## 1. Orientarsi nell’interfaccia

1. Apri la guida Wokwi ESP32 e scegli il modello **Arduino-ESP32** collegato nella sezione iniziale.
2. Individua l’editor del codice, la scheda del circuito e il comando di avvio/arresto della simulazione.
3. Individua il monitor seriale, che mostra i messaggi del programma. Avvia e arresta il modello per riconoscere questi elementi.
4. Per conservare il lavoro usa la funzione di salvataggio o copia del progetto e, se richiesto dal servizio, accedi al tuo account. Le etichette dell’interfaccia possono cambiare: verifica che la copia salvata si riapra con codice e circuito corretti.

Non occorre collegare una scheda USB o installare driver per questa simulazione nel browser. Le estensioni per editor locali e gli strumenti da riga di comando costituiscono altri flussi di lavoro e non sono necessari per iniziare.

## 2. Importare l’esempio C++ del corso

1. Apri il [README del lampeggio](esempi/03_01-LED-lampeggiante/README.md).
2. Copia tutto il contenuto del [codice C++](esempi/03_01-LED-lampeggiante/cpp/cpp.ino) nel `sketch.ino` del modello, sostituendo il testo precedente. Non aggiungere un secondo file con altre funzioni `setup()` e `loop()`.
3. Apri la scheda `diagram.json` nell’editor Wokwi e sostituiscila con il [diagramma fornito](esempi/03_01-LED-lampeggiante/cpp/diagram.json).
4. Controlla che compaiano ESP32 DevKit v1, LED e resistenza. Segui il filo da D18 alla resistenza e al LED, poi a GND.
5. Avvia: attendi la compilazione, osserva il LED e leggi la console. Il risultato atteso è 500 ms acceso e 500 ms spento, con messaggi corrispondenti.
6. Ferma, cambia `ON_MS` a 200 e `OFF_MS` a 800, poi riavvia. Il periodo nominale resta 1 s; cambia la durata del lampo.

## 3. Importare la versione MicroPython

1. Crea un altro progetto dal modello **MicroPython ESP32**, senza riutilizzare il progetto Arduino come se bastasse cambiare estensione.
2. Sostituisci `main.py` con il [programma MicroPython](esempi/03_01-LED-lampeggiante/micropython/main.py).
3. Sostituisci `diagram.json` con il [diagramma MicroPython](esempi/03_01-LED-lampeggiante/micropython/diagram.json).
4. Avvia e confronta LED, messaggi e tempi con il C++.
5. Per tornare alla console interattiva, porta il fuoco sul terminale e premi Ctrl+C. Puoi interrogare l’interprete e riavviare la simulazione per ripartire dall’inizio.

La [guida MicroPython di Wokwi](https://docs.wokwi.com/guides/micropython) descrive la gestione del codice e della console. Un modulo presente nel firmware simulato non è automaticamente installato su qualsiasi scheda reale.

## 4. Leggere e modificare il circuito

Ogni componente ha un identificatore, ad esempio `esp`, `r1` o `led1`. Una connessione identifica componente e terminale separati da `:`. La [specifica diagram.json](https://docs.wokwi.com/diagram-format) descrive il formato.

Questo estratto del diagramma unisce il GPIO del modello DevKit v1 alla resistenza; i componenti devono essere già definiti nella sezione `parts` del file completo:

```json
["esp:D18", "r1:1", "green", []]
```

Nel programma il numero del GPIO è **18**; per questo modello Wokwi il terminale del diagramma si chiama **D18**. Il nome del terminale dipende dal componente simulato, non da una regola universale per tutte le schede.

Per cambiare un montaggio, arresta la simulazione, modifica i fili nell’editor o il JSON e verifica la corrispondenza col codice. I file forniti nel corso costituiscono un punto di partenza riproducibile: conserva una copia prima di sperimentare.

## Esempi commentati

Nel [lampeggio C++](esempi/03_01-LED-lampeggiante/cpp/cpp.ino):

```cpp
const int LED_PIN = 18;   // Deve corrispondere al GPIO collegato nel diagramma.
```

Nella [versione MicroPython](esempi/03_01-LED-lampeggiante/micropython/main.py):

```python
led = Pin(LED_PIN, Pin.OUT, value=0)  # Parte spento nel circuito attivo alto.
```

Per esercitarti con un ingresso puoi poi usare il [pulsante con pull-up](../03-Ingressi-digitali-e-pulsanti/esempi/01_01-Pulsante-con-pull-up/README.md), dopo aver studiato l’esercitazione 03: il diagramma associa il tasto Q al pulsante. La pressione virtuale modifica il segnale letto dal programma.

## 5. Accenni a Tinkercad Circuits

**Tinkercad** è un ambiente Autodesk che comprende anche **Circuits**, dedicato all’esplorazione di circuiti e programmazione introduttiva. I [materiali ufficiali](https://www.tinkercad.com/learn/circuits) includono progetti Arduino e micro:bit; la [presentazione Autodesk](https://www.autodesk.com/solutions/circuit-design-software) ne descrive l’uso per circuiti Arduino e breadboard.

| Aspetto | Wokwi nel corso | Tinkercad Circuits come introduzione |
| --- | --- | --- |
| Obiettivo della prova | Eseguire gli esempi ESP32 Arduino e MicroPython forniti | Familiarizzare con montaggi, LED e circuiti didattici |
| Punto di partenza | Modello ESP32 e file del corso | Esercizi e modelli disponibili nella sezione Circuits |
| Programma | C++ o MicroPython secondo il modello | Ambiente di programmazione del componente scelto, con attività anche a blocchi |
| Trasferimento del progetto | Codice e diagramma Wokwi coerenti | Ricostruzione del circuito e adattamento al modello usato |

Nel percorso ESP32 usiamo Wokwi. Un esercizio Tinkercad basato su Arduino Uno può insegnare lo stesso concetto di lampeggio, ma non dimostra che il firmware ESP32 compili o funzioni: cambiano microcontrollore, piedinatura, livelli elettrici e API disponibili. Non importare `diagram.json` o `main.py` aspettandoti un progetto equivalente.

Per una prima esplorazione apri la sezione Circuits di Tinkercad, scegli un’attività introduttiva Arduino con LED, avviane la simulazione e confronta componenti e codice con Wokwi. Non trasferire fisicamente collegamenti a 5 V verso i GPIO a 3,3 V dell’ESP32. Il confronto è concettuale, non un collaudo della stessa scheda.

## Limiti della simulazione e debug

Wokwi permette di studiare il programma e le periferiche supportate, ma il comportamento analogico, le tolleranze, l’alimentazione e i consumi richiedono prove reali. In particolare il [drive strength](../02-Uscite-digitali-e-LED/04-Drive-strength-dei-GPIO.md) non va valutato dalla sola luminosità simulata.

| Sintomo | Controllo |
| --- | --- |
| Due definizioni di setup o loop | Hai aggiunto il sorgente senza sostituire quello del modello |
| Circuito assente o errore JSON | Controlla sintassi, `parts`, `connections` e identificatori |
| Console corretta, LED fermo | Verifica GPIO nel codice, nome del terminale e polarità del LED |
| Python trattato come C++ | Ricrea il progetto dal modello MicroPython |
| Nuovo codice non osservabile | Arresta e riavvia, poi controlla di aver modificato il progetto giusto |

Consulta la [tabella delle periferiche supportate](https://docs.wokwi.com/guides/esp32#simulation-features) per i limiti aggiornati. Le procedure e i circuiti sono predisposti; l’esecuzione effettiva nel browser non è stata effettuata durante la preparazione di questi materiali.

## Autovalutazione

1. **Quali file devi mantenere coerenti per il lampeggio?**

   - A. Soltanto il nome del browser.
   - B. Programma e diagram.json.
   - C. Il driver USB e il wallpaper.
   - D. Solo il numero della porta COM.

2. **Serve il driver USB per avviare Wokwi nel browser senza scheda collegata?**

   - A. Sì, sempre CP210x.
   - B. Sì, sempre CH340.
   - C. No, la simulazione usa un dispositivo virtuale.
   - D. Soltanto per spegnere il LED.

3. **Un lampeggio Arduino Uno in Tinkercad dimostra il funzionamento dello stesso firmware su ESP32?**

   - A. No: è un modello diverso e il trasferimento richiede adattamenti e verifiche.
   - B. Sì, tutti i GPIO hanno le stesse tensioni.
   - C. Sì, qualunque sketch è indipendente dalla board.
   - D. Sì, diagram.json è un formato universale.

## Esercizi pratici

1. **Consegna:** prepara e salva una copia Wokwi del lampeggio C++ e una MicroPython.

   **Risultato atteso:** stesso circuito, stessi messaggi e stessa temporizzazione nei due progetti.

2. **Consegna:** copia la variante 200/800 ms, annota il periodo previsto e confrontalo con la simulazione.

   **Risultato atteso:** circa un lampo al secondo, acceso per una frazione minore del ciclo.

3. **Consegna:** esplora un’attività LED Arduino in Tinkercad e confrontala con il progetto Wokwi.

   **Risultato atteso:** breve tabella con board, linguaggio, pin del LED, componenti e almeno due adattamenti necessari per passare a ESP32. Non dichiarare collaudato un firmware che non hai eseguito sul relativo target.

## Soluzioni dell’autovalutazione

1. **B — Programma e diagram.json.** Il codice usa i GPIO che il circuito collega ai componenti.
2. **C — No, la simulazione usa un dispositivo virtuale.** Il driver serve alla comunicazione con l’hardware USB reale.
3. **A — No: è un modello diverso e il trasferimento richiede adattamenti e verifiche.** Il concetto didattico può essere comune, la piattaforma resta distinta.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](05-Driver-USB-seriale.md)
- [➡️ Guida successiva](../02-Uscite-digitali-e-LED/01-Circuiti-LED-e-resistenze.md)
