# Servomotori · Posizione, velocità e controllo con ESP32

Un servomotore per modellismo integra motore, riduttore e circuito di controllo. Un **servo posizionale** interpreta la durata degli impulsi come posizione richiesta; un **servo a rotazione continua** la interpreta come direzione e velocità, con un impulso neutro di arresto.

In questi esempi il periodo è circa **20 ms (50 Hz)** e l’intervallo configurato è **1000–2000 µs**. `write(0..180)` mappa i comandi su questo intervallo; i numeri non garantiscono altrettanti gradi fisici. Verifica limiti e centro del tuo servo, inizialmente senza carico. Il comando non restituisce la posizione reale.

## Libreria e alimentazione

Installa **ESP32Servo** dal gestore librerie di Arduino IDE; ogni sketch include `libraries.txt`. La libreria `Servo` destinata ad altre architetture non è usata in questa raccolta. Apri una cartella alla volta con core **esp32 by Espressif Systems**.

Alimenta i servo con una **sorgente esterna regolata alla tensione prevista dal produttore**, dimensionata per la somma delle correnti di spunto/stallo. Collega GND della sorgente, GND dei servo e GND ESP32. Non alimentare il motore dal GPIO o dal pin 3V3. Porta soltanto il segnale dal GPIO al terminale PWM del servo, verificando che accetti la logica a 3,3 V. Non collegare insieme le uscite positive di due alimentatori.

| Funzione | GPIO |
| --- | --- |
| Segnale servo singolo / base | 18 |
| Segnale secondo servo, braccio 06 | 19 |
| Cursore potenziometro 03 | 34 |
| Moduli LDR sinistro/destro 05 | AO a 34/35 |
| Joystick X/Y 06 | 34/35 |

Potenziometro da 10 kΩ con estremi a 3V3/GND; joystick e moduli LDR con uscite analogiche limitate a 3,3 V. Gli ADC sono impostati a 12 bit, con codici 0–4095. GPIO 34/35 sono ingressi e non hanno pull-up interno.

**Nei diagrammi Wokwi il positivo dei servo è sul VIN della scheda simulata. Sul circuito reale usa l’alimentazione esterna descritta sopra**: il diagramma non valida la capacità di alimentazione della scheda.

## Esempi

| Esempio | Cosa osservare |
| --- | --- |
| [Servo_01_controllo_base](<Servo_01_controllo_base/README.md>) | Comandi 0°, 90°, 180° con attesa di 1 s |
| [Servo_02_rotazione_continua](<Servo_02_rotazione_continua/README.md>) | Servo continuo: 1400, 1500, 1600, 1500 µs |
| [Servo_03_controllo_potenziometro](<Servo_03_controllo_potenziometro/README.md>) | Potenziometro 0–4095 mappato su 0–180 |
| [Servo_04_movimento_fluido](<Servo_04_movimento_fluido/README.md>) | Scansione per passi di un grado ogni 15 ms |
| [Servo_05_inseguimento_solare](<Servo_05_inseguimento_solare/README.md>) | Inseguimento della luce con due LDR e banda morta |
| [Servo_06_braccio_robotico](<Servo_06_braccio_robotico/README.md>) | Due servo con joystick, banda morta e limiti |
| [Servo_07_controllo_seriale](<Servo_07_controllo_seriale/README.md>) | Angolo 0–180 ricevuto come riga seriale |

La 02 richiede un **servo continuo**: calibra il neutro nominale di 1500 µs, che potrebbe non arrestare esattamente il tuo modello. Le direzioni dipendono dal servo e dall’orientamento meccanico. Il componente servo standard di Wokwi visualizza la posizione: non riproduce il comportamento continuo.

La 05 usa moduli LDR il cui **AO diminuisce con l’aumento della luce**, come nel diagramma. La differenza è destra meno sinistra, con soglia 200 codici ADC e un passo ogni 50 ms; se il montaggio si allontana dalla luce inverti il verso di correzione. Con un partitore LDR diverso anche la polarità può cambiare.

La 06 usa centro nominale 2048 e banda morta ±200. Oltre la banda il passo è ±1, oppure ±2 quando lo scostamento supera 1200; le posizioni sono limitate a 0–180. Questi limiti software vanno ristretti se i leveraggi hanno corsa inferiore.

Nella 07 invia per esempio `45` seguito da **LF** o CRLF; prova anche 0 e 180. Le righe negative, non numeriche, troppo lunghe o oltre 180 generano `ERR ANGOLO` senza muovere il servo. Il buffer accetta tre cifre e l’eventuale CR.

Gli sketch controllano `attached()` dopo l’assegnazione della risorsa PWM e segnalano `ERR SERVO` se fallisce. Questo verifica la configurazione software, **non la presenza del servo**. Le attese fra comandi consentono al motore di muoversi ma non verificano che abbia raggiunto la posizione. `detach()` interrompe gli impulsi, non toglie alimentazione.

## Avvio e simulazione

Apri un solo `.ino` dalla cartella omonima in Arduino IDE. Installa **esp32 by Espressif Systems**, seleziona la scheda reale (per esempio DOIT ESP32 DEVKIT V1) e la porta. La seriale, dove usata, è a **115200 baud**. I numeri dei pin sono GPIO, non posizioni del connettore. Questi collegamenti riguardano l’ESP32 classico WROOM-32.

Ogni esempio contiene un `diagram.json`: crea un progetto [Wokwi ESP32](https://docs.wokwi.com/guides/esp32), copia lo sketch nel file principale e il suo diagramma. Copia anche eventuali `.h` e `libraries.txt`. La simulazione aiuta a studiare la logica; correnti, alimentazione e comportamento fisico vanno verificati sul circuito.

## Esercizi

1. Misura o osserva la posizione a 1000, 1500 e 2000 µs e calibra un intervallo senza battute meccaniche.
2. Calibra il neutro del servo continuo e aggiungi un pulsante di arresto.
3. Introduci una rampa temporizzata fra la posizione attuale e quella richiesta via seriale.
4. Misura il centro reale del joystick e confronta due ampiezze della banda morta.
5. Aggiungi al braccio posizioni memorizzate e una sequenza eseguibile senza `delay()`.

## Verifiche

Controlli locali del **24 ottobre 2026** sulle nuove raccolte 007–011: **37 sketch compilati con g++ e API sostituite**, con **66 esecuzioni superate**. Le verifiche comprendono pulsanti e debounce, avvio con tasto premuto, eventi PIR, temporizzazioni e ritorno a zero del timer, ADC e comandi servo, input seriali errati, echi assenti, filtro e fasce di distanza. Per RTTTL sono stati controllati parser, pause, note puntate/alterate, stop e riavvio e **50 melodie del catalogo**; il lettore MicroPython è stato verificato con PWM e clock sostituiti.

Sono stati controllati nomi dei file Arduino, 38 diagrammi JSON, resistenze, partitori Echo e collegamenti Markdown. Il modello temporale usa la larghezza nativa di `unsigned long` del computer: non emula la CPU o i tempi delle periferiche.

**Compilazione con core ESP32 reale, esecuzione Wokwi e collaudo hardware sono da eseguire.** Questi controlli non misurano corrente, qualità del suono, movimento o sensibilità del sensore.

## Riferimenti

- [ESP32Servo: API e compatibilità](https://github.com/madhephaestus/ESP32Servo).
- [Wokwi: servo posizionale](https://docs.wokwi.com/parts/wokwi-servo).

[Indice ESP32-DEVKIT](../README.md) · [Indice generale](../../README.md)
