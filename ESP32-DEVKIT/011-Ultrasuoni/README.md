# Ultrasuoni · Distanza, allarme e scansione con ESP32

## Introduzione teorica

Il modulo **HC-SR04** emette un breve treno di ultrasuoni e misura il tempo necessario a ricevere una riflessione. Il segnale **TRIG**, alto per almeno 10 µs, avvia la misura; la durata HIGH di **ECHO** rappresenta il viaggio di andata e ritorno.

La distanza si ricava da `d = tempo × velocità del suono / 2`. Negli sketch si usa l’approssimazione **distanza in cm = durata in µs / 58**, con risultato intero. Temperatura dell’aria, inclinazione, dimensioni e materiale dell’oggetto influenzano la lettura. L’intervallo nominale del modello standard è circa 2–400 cm: superfici troppo vicine, assorbenti o inclinate possono non produrre un eco utile.

### Dall’emissione al tempo di volo

Il trasmettitore converte un impulso elettrico in un breve treno acustico; il ricevitore rileva l’energia riflessa da una superficie. Nel modulo HC-SR04 il treno emesso comprende otto cicli a circa 40 kHz. Il breve impulso TRIG è un comando di avvio: la durata da convertire in distanza è quella del segnale ECHO generato dal modulo. [Datasheet HC-SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf).

La riflessione deve compiere due tratte: sensore → oggetto e oggetto → sensore. Se `t` è il tempo complessivo e `c` la velocità del suono:

```text
2 × distanza = c × t
distanza = c × t / 2
```

Con `c ≈ 343 m/s`, un oggetto a 1 m produce un tempo di andata e ritorno di circa `2/343 s = 5,83 ms`. Convertendo i metri in centimetri e i secondi in microsecondi si ricava `d_cm ≈ t_us/58,3`; il divisore 58 degli sketch è un’approssimazione pratica.

### Geometria del bersaglio e zona cieca

Il sensore copre una regione angolare, non un raggio geometrico infinitamente sottile. Un oggetto laterale può contribuire all’eco e una superficie obliqua può riflettere l’energia lontano dal ricevitore. Tessuti, superfici porose e oggetti piccoli possono restituire meno energia rispetto a una superficie ampia e favorevolmente orientata.

A distanza molto breve il sistema può non separare bene emissione, vibrazioni residue ed eco: da qui la distanza minima specificata. Una lettura numerica sotto l’intervallo nominale richiede quindi valutazione. Il timeout intercetta un eco incompleto o assente; non valida automaticamente tutte le distanze numeriche ricevute.

Riflessioni multiple possono far arrivare un percorso più lungo di quello diretto. Con più sensori vicini, un ricevitore potrebbe inoltre rilevare l’emissione dell’altro. La sequenza di attivazione e l’intervallo fra misure diventano parte del progetto.

### Velocità del suono e incertezza

La velocità del suono nell’aria dipende dalle condizioni ambientali, in particolare dalla temperatura. Se il programma usa una velocità ipotizzata diversa da quella effettiva, la distanza calcolata presenta un errore di scala. Dalla formula segue:

```text
distanza_calcolata / distanza_reale = c_usata / c_reale
```

Usare una velocità più bassa di quella reale porta a sottostimare la distanza. Una compensazione richiederebbe un sensore ambientale e un modello appropriato; non è presente negli sketch della raccolta.

Vanno distinti **risoluzione**, **ripetibilità** e **accuratezza**. La risoluzione è il passo con cui il dato viene rappresentato: qui la divisione intera produce centimetri interi. La ripetibilità descrive quanto si disperdono letture ripetute nelle stesse condizioni. L’accuratezza richiede il confronto con un riferimento: una lettura molto stabile può comunque avere un errore sistematico.

### Timeout e significato di una misura mancante

`pulseIn()` attende l’impulso e ne restituisce la durata, oppure zero se non completa la lettura entro il timeout previsto. Un’attesa massima di 30 ms limita il blocco del programma; con 343 m/s quel tempo corrisponderebbe idealmente a circa 5,1 m di percorso di sola andata ricavato dal tempo totale. Non estende però la portata nominale del modulo a 5,1 m.

Una misura mancante può dipendere da oggetto fuori portata, riflessione sfavorevole o problema nel collegamento. Il programma deve conservarne la **validità** insieme al valore. Usare zero come distanza farebbe scattare erroneamente l’allarme massimo; riutilizzare senza indicazione una vecchia misura nasconderebbe il problema. Gli esempi usano quindi `ERR ECO` o -1.

### Media mobile: stabilità e ritardo

Per una finestra di `N` campioni validi la media è `media = somma/N`. All’avvio il denominatore deve essere il numero di campioni realmente disponibili; includere posizioni ancora vuote come zeri abbasserebbe artificialmente il risultato.

La media riduce alcune oscillazioni, ma distribuisce nel tempo una variazione reale. Con cinque campioni ideali equidistanti di 100 ms, i dati della finestra coprono 400 ms e la loro età media è circa 200 ms. È un esempio di ritardo del filtro; il periodo effettivo degli sketch comprende anche misura e altre istruzioni.

Un singolo eco anomalo influenza più risultati finché rimane nella finestra. Una mediana, un controllo dell’intervallo nominale o una soglia sulla variazione sono possibili estensioni, ognuna con effetti sui dati accettati. La 02, in caso di eco mancante, azzera la storia e riparte dai nuovi campioni validi.

### Allarme e scansione: leggere il dato nel tempo

Vicino a una soglia il rumore può far cambiare ripetutamente fascia. L’**isteresi** può definire due distanze: una per entrare nella fascia vicina e una maggiore per uscirne. Il ritardo totale di risposta comprende scansione, misura, filtro e segnalazioni bloccanti; la frequenza della CPU da sola non lo descrive.

Nello scanner il campione va associato all’angolo richiesto al momento della misura. Il servo richiede tempo per muoversi e il fascio ha una propria apertura; passi di 5° non garantiscono risoluzione angolare di 5° né una misura della posizione meccanica effettiva. Per tracciare il grafico, un valore -1 deve restare un campione non valido e le distanze oltre scala vanno interpretate secondo la convenzione indicata dallo sketch.

## Materiale e collegamenti

ESP32 WROOM-32, HC-SR04 standard a 5 V, resistenze da **10 kΩ e 15 kΩ** per Echo; per la 03 LED con **220 Ω** e piezo passivo con **1 kΩ**; per la 04 servo posizionale.

| HC-SR04 | ESP32 / circuito |
| --- | --- |
| VCC | Alimentazione 5 V adeguata |
| GND | GND comune |
| TRIG | GPIO 25 |
| ECHO | Resistenza 10 kΩ → nodo → GPIO 26; dal nodo 15 kΩ verso GND |

**Non collegare direttamente Echo a un GPIO ESP32**: sul modulo standard è un segnale a 5 V. Il partitore porta nominalmente 5 V a `5 × 15 / (10 + 15) = 3 V`. La resistenza da 10 kΩ è fra Echo e nodo; quella da 15 kΩ fra nodo e GND. Verifica valori e collegamento prima di alimentare. Il comando TRIG a 3,3 V è normalmente accettato dai moduli con ingresso TTL; verifica il tuo modello o usa un adattatore di livello appropriato.

Nella 03: GPIO **18 → 220 Ω → anodo LED**, catodo GND; GPIO **27 → 1 kΩ → positivo piezo**, negativo GND. Usa un piezo passivo adatto, non un altoparlante a bassa impedenza.

Nella 04 il segnale servo è sul GPIO **18**. Alimenta il servo con sorgente esterna adeguata alla corrente di spunto/stallo, con GND comune; **non dal GPIO o dal 3V3**. Nei diagrammi Wokwi il VIN serve soltanto ad alimentare il modello simulato; per il montaggio reale segui la guida dei [servomotori](../010-Servomotori/README.md).

## Esempi

| Esempio | Cosa osservare |
| --- | --- |
| [Ultrasuoni_01_misurazione_base](<Ultrasuoni_01_misurazione_base/README.md>) | Misura singola ogni 500 ms e stampa in cm |
| [Ultrasuoni_02_media_mobile](<Ultrasuoni_02_media_mobile/README.md>) | Media mobile degli ultimi cinque campioni validi |
| [Ultrasuoni_03_allarme_prossimita](<Ultrasuoni_03_allarme_prossimita/README.md>) | Segnalazione con LED e buzzer in quattro fasce |
| [Ultrasuoni_04_radar](<Ultrasuoni_04_radar/README.md>) | Scansione con servo e righe angolo,distanza |

### Eco assente e filtro

Ogni chiamata usa `pulseIn(ECHO_PIN, HIGH, 30000UL)`: attende al massimo circa **30 ms** per l’impulso. Il codice resta bloccato durante la lettura, ma non indefinitamente. Un ritorno zero indica timeout o impulso non completato: non rappresenta un oggetto a distanza zero. Gli sketch 01–03 stampano `ERR ECO`; la 04 trasmette **-1** nel campo distanza.

La 02 calcola la media sui campioni effettivamente raccolti, fino a cinque: la prima lettura non viene divisa per cinque. Dopo un eco mancante svuota il filtro, così una vecchia media non viene presentata come distanza attuale. Il filtro riduce le oscillazioni ma aggiunge ritardo e non rende valido un eco errato. Gli intervalli fra letture sono almeno 100 ms, quindi superiori ai 60 ms comunemente usati per separare le misure.

### Allarme di prossimità

| Distanza | Segnalazione 03 |
| --- | --- |
| oltre 150 cm | LED e buzzer spenti |
| oltre 80 e fino a 150 cm | LED lampeggiante, 500 ms acceso e 500 ms spento |
| oltre 40 e fino a 80 cm | LED e tono 500 Hz per 200 ms, poi 200 ms spenti (più 100 ms finali) |
| fino a 40 cm | LED acceso e tono continuo 1000 Hz |
| eco assente | `ERR ECO`, LED e buzzer spenti |

La 03 usa attese bloccanti per le segnalazioni: un oggetto che si avvicina viene rivalutato alla misura successiva, con ritardo dipendente dalla fascia precedente. Una nuova lettura valida interrompe prima il tono precedente per evitare che resti attivo passando alla zona più lontana.

### Scansione con servo

La 04 richiede **ESP32Servo**; è fornito `libraries.txt`. Usa impulsi a 50 Hz, intervallo 1000–2000 µs, e scansione **15–165°** a passi di 5°, con 100 ms di attesa prima di ciascuna misura. Il formato seriale è `angolo,distanza`, per esempio `90,37`; `90,-1` significa eco assente. Le distanze valide oltre **200 cm** sono limitate a 200 per la visualizzazione; non vengono confuse con -1.

Il comando al servo e l’attesa non costituiscono una misura dell’angolo effettivo. Questo è uno scanner didattico a ultrasuoni: per rappresentarlo su un grafico esterno converti separatamente angolo e distanza e scarta -1. `ERR SERVO` indica un errore di configurazione PWM, non rileva un motore scollegato.

## Avvio e simulazione

Apri un solo `.ino` dalla cartella omonima in Arduino IDE. Installa **esp32 by Espressif Systems**, seleziona la scheda reale (per esempio DOIT ESP32 DEVKIT V1) e la porta. La seriale, dove usata, è a **115200 baud**. I numeri dei pin sono GPIO, non posizioni del connettore. Questi collegamenti riguardano l’ESP32 classico WROOM-32.

Ogni esempio contiene un `diagram.json`: crea un progetto [Wokwi ESP32](https://docs.wokwi.com/guides/esp32), copia lo sketch nel file principale e il suo diagramma. Copia anche eventuali `.h` e `libraries.txt`. La simulazione aiuta a studiare la logica; correnti, alimentazione e comportamento fisico vanno verificati sul circuito.

Nel simulatore seleziona HC-SR04 e varia la distanza. Prova 40, 80, 150 cm e valori appena superiori per verificare i confini delle fasce. Il partitore documenta il cablaggio reale: la simulazione non certifica i livelli elettrici o il comportamento di un ostacolo fisico.

## Esercizi

1. Confronta dieci letture con un righello a 10, 50 e 100 cm; annota errori ed echi assenti.
2. Confronta la risposta al movimento con filtro da uno, cinque e dieci campioni.
3. Sostituisci i lampeggi bloccanti con una macchina a stati basata su `millis()`.
4. Aggiungi isteresi alle soglie per ridurre commutazioni vicino a 40, 80 e 150 cm.
5. Disegna i punti dello scanner su un grafico e visualizza gli echi mancanti senza trasformarli in distanza zero.

## Verifiche

Controlli locali del **24 ottobre 2026** sulle nuove raccolte 007–011: **37 sketch compilati con g++ e API sostituite**, con **66 esecuzioni superate**. Le verifiche comprendono pulsanti e debounce, avvio con tasto premuto, eventi PIR, temporizzazioni e ritorno a zero del timer, ADC e comandi servo, input seriali errati, echi assenti, filtro e fasce di distanza. Per RTTTL sono stati controllati parser, pause, note puntate/alterate, stop e riavvio e **50 melodie del catalogo**; il lettore MicroPython è stato verificato con PWM e clock sostituiti.

Sono stati controllati nomi dei file Arduino, 38 diagrammi JSON, resistenze, partitori Echo e collegamenti Markdown. Il modello temporale usa la larghezza nativa di `unsigned long` del computer: non emula la CPU o i tempi delle periferiche.

**Compilazione con core ESP32 reale, esecuzione Wokwi e collaudo hardware sono da eseguire.** Questi controlli non misurano corrente, qualità del suono, movimento o sensibilità del sensore.

## Riferimenti

- [Wokwi: HC-SR04, piedini e misura](https://docs.wokwi.com/parts/wokwi-hc-sr04).
- [ESP32Servo](https://github.com/madhephaestus/ESP32Servo).
- [Espressif: GPIO](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html).

[Indice ESP32-DEVKIT](../README.md) · [Indice generale](../../README.md)
