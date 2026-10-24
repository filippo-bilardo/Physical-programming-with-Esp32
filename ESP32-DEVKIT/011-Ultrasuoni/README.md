# Ultrasuoni · Distanza, allarme e scansione con ESP32

## Introduzione teorica

Il modulo **HC-SR04** emette un breve treno di ultrasuoni e misura il tempo necessario a ricevere una riflessione. Il segnale **TRIG**, alto per almeno 10 µs, avvia la misura; la durata HIGH di **ECHO** rappresenta il viaggio di andata e ritorno.

La distanza si ricava da `d = tempo × velocità del suono / 2`. Negli sketch si usa l’approssimazione **distanza in cm = durata in µs / 58**, con risultato intero. Temperatura dell’aria, inclinazione, dimensioni e materiale dell’oggetto influenzano la lettura. L’intervallo nominale del modello standard è circa 2–400 cm: superfici troppo vicine, assorbenti o inclinate possono non produrre un eco utile.

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
