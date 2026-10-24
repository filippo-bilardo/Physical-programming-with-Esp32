# Buzzer · Toni, Morse e melodie con ESP32

## Introduzione teorica

Un **buzzer attivo** contiene un oscillatore: alimentandolo alla tensione prevista emette una frequenza sostanzialmente fissa. Un **piezo passivo** richiede invece un segnale alternato: `tone(pin, frequenza)` genera l’onda e `noTone(pin)` la interrompe. La frequenza determina l’altezza della nota; la durata determina il ritmo. Un altoparlante da 8 Ω non può sostituire direttamente il piezo sul GPIO.

### Dalla deformazione del piezo al suono

Nel piezo passivo un elemento piezoelettrico cambia leggermente forma quando varia il campo elettrico applicato. La deformazione fa vibrare il diaframma, che mette in movimento l’aria. La geometria del diaframma e dell’involucro determina una risposta in frequenza con zone di risonanza: due note comandate con la stessa ampiezza elettrica possono avere intensità sonore diverse. Il buzzer attivo aggiunge il circuito che genera l’oscillazione. [Murata: principio di funzionamento dei componenti piezoelettrici](https://www.murata.com.cn/products/sound/library/basic/mechanism).

Un piezo presenta anche un comportamento capacitivo: la corrente si concentra durante le variazioni del segnale. Il valore della resistenza in serie influisce sul pilotaggio e va letto insieme alle caratteristiche del componente. I collegamenti proposti riguardano piccoli piezo adatti alla logica; la corrente di un buzzer attivo o di un trasduttore magnetico richiede una valutazione distinta.

### Frequenza, periodo e timbro

La frequenza indica quante oscillazioni si ripetono in un secondo. Per un tono da 1000 Hz il periodo è `T = 1/f = 1 ms`; a duty 50% si hanno circa 0,5 ms alto e 0,5 ms basso. Aumentando la frequenza cresce normalmente l’altezza percepita della nota.

L’onda quadra contiene, oltre alla fondamentale, componenti armoniche che contribuiscono al **timbro**. Il piezo e il suo involucro filtrano queste componenti. Perciò il suono prodotto non coincide con quello di uno strumento acustico anche quando la frequenza fondamentale è la stessa.

A duty 0% e 100% l’uscita è costante: dopo il transitorio non c’è l’oscillazione richiesta per un tono continuo sul piezo passivo. Variando il duty cambia anche il contenuto armonico; il risultato non è una scala lineare del volume. Questo chiarisce il comportamento dell’esperimento PWM della raccolta.

### Note musicali e rapporti di frequenza

Nel temperamento equabile un’ottava raddoppia la frequenza e ogni semitono moltiplica per `2^(1/12)`. Indicando con `n` il numero della nota secondo la convenzione MIDI, la frequenza si può calcolare come:

```text
f(n) = 440 × 2^((n − 69) / 12) Hz
n = 69 → La4 = 440 Hz
n = 81 → La5 = 880 Hz
n = 60 → Do4 ≈ 261,6 Hz
```

È una corrispondenza matematica fra note e frequenze, indipendente dal protocollo usato per richiederle. Ricevere il testo `12` sulla seriale non costituisce la ricezione di un messaggio MIDI. L’arrotondamento a hertz interi introduce una piccola approssimazione, cui si aggiunge quella del generatore hardware.

### Ritmo, durata e articolazione

Il tempo in BPM conta i battiti al minuto; negli esempi RTTTL si assume come battito la semiminima. A 120 BPM una semiminima dura `60000/120 = 500 ms`. Se `d` è il denominatore della durata, si usa:

```text
durata della nota = 240000 / (BPM × d) ms
```

| Valore a 120 BPM | Denominatore | Durata |
| --- | --- | --- |
| Semibreve | 1 | 2000 ms |
| Minima | 2 | 1000 ms |
| Semiminima | 4 | 500 ms |
| Croma | 8 | 250 ms |
| Croma puntata | 8, con punto | 375 ms |

Il punto aggiunge metà della durata. Una pausa occupa tempo senza suono; una breve interruzione fra note migliora l’articolazione. Il lettore locale mantiene circa il 90% della durata come suono e il resto come separazione, conservando il tempo complessivo dell’evento. I calcoli interi in millisecondi possono arrotondare le durate.

### Riproduzione bloccante e macchina a stati

Una melodia può essere rappresentata come sequenza di coppie frequenza/durata. Con un ciclo e `delay()` ogni nota impedisce al flusso principale di gestire altri comandi fino alla fine dell’attesa. La periferica può continuare a generare il segnale, ma il programma non legge automaticamente un pulsante di stop.

Un lettore aggiornato a ogni giro conserva nota corrente, istante iniziale, durata e fase suono/pausa. Quando scade il tempo cambia fase e restituisce il controllo. La scansione del loop deve essere abbastanza frequente rispetto alla nota più breve: chiamate molto tardive a `update()` possono allungare le durate. Il metodo non bloccante evita l’attesa esplicita, ma la regolarità dipende da tutte le altre attività del programma.

### RTTTL come linguaggio di dati

La stringa RTTTL separa nome, impostazioni e lista degli eventi. Il parser converte simboli come `8c#6.` in durata, altezza e alterazione; la riproduzione usa poi i valori numerici. Validare denominatori, ottave e BPM evita divisioni per zero e interpretazioni fuori intervallo.

Con un solo generatore si riproduce una linea melodica alla volta. La polifonia richiederebbe più voci e un metodo di combinazione del segnale; sommare richieste a `tone()` non mescola automaticamente le frequenze. Questa distinzione è utile quando si collega il buzzer al pianoforte touch o a un selettore di note.

## Materiale e collegamenti

- ESP32 WROOM-32, piezo passivo adatto al pilotaggio logico e resistenza in serie da **1 kΩ**: GPIO **27 → 1 kΩ → positivo piezo**, negativo a GND.
- LED negli esempi 05/11: GPIO **18 → 220 Ω → anodo**, catodo a GND.
- PIR nella 05: OUT a **23**, GND comune, alimentazione del modulo HC-SR501 tipicamente 5 V; verifica che OUT sia compatibile con 3,3 V.
- HC-SR04 nella 07: TRIG **25**, Echo **26** attraverso il partitore descritto negli [ultrasuoni](../011-Ultrasuoni/README.md), VCC 5 V e GND comune.

Per il buzzer **attivo** della 01 usa un modulo con ingresso di comando compatibile con 3,3 V e alimentazione adeguata. Per un dispositivo a due terminali che richiede più corrente usa un transistor: per esempio GPIO 27 → 1 kΩ → base NPN, emettitore a GND, collettore al negativo del buzzer, positivo all’alimentazione prevista e masse comuni; dimensiona il circuito rispetto alla corrente e al tipo di carico. Il GPIO fornisce il comando, non l’alimentazione del buzzer. Nel diagramma 01 un analizzatore logico mostra soltanto HIGH/LOW: il buzzer passivo di Wokwi non simula l’oscillatore di uno attivo.

## Esempi

| Esempio | Cosa osservare |
| --- | --- |
| [Buzzer_01_buzzer_attivo](<Buzzer_01_buzzer_attivo/README.md>) | Comando attivo: 1 s acceso, 1 s spento |
| [Buzzer_02_buzzer_passivo](<Buzzer_02_buzzer_passivo/README.md>) | Tre note e modulazione della frequenza, una volta in setup |
| [Buzzer_03_melodia_semplice](<Buzzer_03_melodia_semplice/README.md>) | Scala ripetuta e pause tra le note |
| [Buzzer_04_controllo_volume_pwm](<Buzzer_04_controllo_volume_pwm/README.md>) | PWM a 1 kHz: esplorazione del duty cycle |
| [Buzzer_05_sistema_allarme_pir](<Buzzer_05_sistema_allarme_pir/README.md>) | PIR: stabilizzazione 60 s, sirena non bloccante di 3 s |
| [Buzzer_06_codice_morse](<Buzzer_06_codice_morse/README.md>) | Testo seriale ASCII trasformato in Morse |
| [Buzzer_07_theremin_digitale](<Buzzer_07_theremin_digitale/README.md>) | Distanza trasformata in frequenza |
| [Buzzer_08_sintetizzatore_midi](<Buzzer_08_sintetizzatore_midi/README.md>) | Selezione seriale di una delle 24 note |
| [Buzzer_09_play_rtttl](<Buzzer_09_play_rtttl/README.md>) | Melodie RTTTL con esecuzione bloccante |
| [Buzzer_10_play_rttt](<Buzzer_10_play_rttt/README.md>) | Lettore RTTTL in MicroPython |
| [Buzzer_11_play_rtttl_nonblocking](<Buzzer_11_play_rtttl_nonblocking/README.md>) | RTTTL con update e LED indipendente |

### PWM e intensità sonora

La 04 conserva il nome `controllo_volume_pwm`, ma **variare il duty non è un controllo calibrato del volume**. La frequenza resta 1 kHz, il duty varia 0–255 con risoluzione a 8 bit. Gli estremi sono livelli costanti: un piezo passivo non produce un tono continuo a duty 0 o 255. Risonanza e circuito influenzano il suono; non aspettarti una crescita monotona del volume.

### Morse e selettore di note

Nella 06 invia lettere A–Z, cifre 0–9 e spazi con terminazione **LF** o CRLF. Il buffer accetta 64 byte prima di LF, quindi con CRLF restano 63 caratteri di testo. I caratteri non supportati e le righe troppo lunghe producono un errore. Un punto dura 200 ms, una linea 600 ms; separazione fra simboli 200 ms, fra lettere 600 ms e fra parole 1400 ms. La trasmissione è bloccante: attendi `FINE MORSE` prima di inviare altro testo.

Nella 08 invia un numero **1–24** con LF/CRLF: la nota dura 500 ms. Il nome `sintetizzatore_midi` descrive la corrispondenza delle note, **il programma riceve numeri testuali via seriale** e non implementa il protocollo MIDI.

### RTTTL e attività concorrenti

La struttura è `nome:d=4,o=5,b=120:c,d,e,p,2g`. `d` è il denominatore della durata (potenze di due da 1 a 64), `o` l’ottava 3–7 e `b` il tempo 25–900 BPM. Sono riconosciuti C–B, H come B, pause `p`, diesis `#`, bemolli `b` e un punto di valore prima o dopo l’ottava. Per esempio `8c#6.` dura una croma puntata. Le impostazioni omesse assumono 4, 5 e 120.

Le prove 09/11 includono `Melodie.h` e un lettore locale `RtttlPlayer.h`: copia entrambi insieme allo sketch. `play()` attende la fine; `startPlay()` avvia la melodia e richiede `update()` a ogni giro. `stop()` interrompe e `hasError()` segnala sintassi non valida. La nota suona per circa il 90% della durata; il resto separa le note. Il parser C++ controlla ogni evento quando lo raggiunge: un errore tardivo può seguire note già riprodotte. Una chiamata tardiva a `update()` ritarda l’esecuzione: evita lunghe attese nel loop.

La 11 riproduce tre melodie con pause di un secondo; il LED cambia stato ogni 250 ms anche durante la musica e continua dopo `FINE MELODIE`. La 05 ricomincia una nuova sirena dopo 3 s se il PIR rimane alto.

## Avvio e simulazione

Apri un solo `.ino` dalla cartella omonima in Arduino IDE. Installa **esp32 by Espressif Systems**, seleziona la scheda reale (per esempio DOIT ESP32 DEVKIT V1) e la porta. La seriale, dove usata, è a **115200 baud**. I numeri dei pin sono GPIO, non posizioni del connettore. Questi collegamenti riguardano l’ESP32 classico WROOM-32.

Ogni esempio contiene un `diagram.json`: crea un progetto [Wokwi ESP32](https://docs.wokwi.com/guides/esp32), copia lo sketch nel file principale e il suo diagramma. Copia anche eventuali `.h` e `libraries.txt`. La simulazione aiuta a studiare la logica; correnti, alimentazione e comportamento fisico vanno verificati sul circuito.

Per la 10 installa MicroPython sull’ESP32 e usa per esempio Thonny. Copia **entrambi** `Buzzer_10_play_rttt.py` e `main.py` sulla scheda; `main.py` avvia il lettore. Non caricarli come sketch Arduino. Il codice usa `machine.PWM` sul GPIO 27, duty al 50% durante le note e spegnimento/deinizializzazione in `finally`. Il parser controlla l’intera melodia prima di riprodurla e solleva `ValueError` per dati errati.

## Esercizi

1. Cambia tempo e ottava di una breve melodia RTTTL e calcola la durata di una nota puntata.
2. Verifica il silenzio per una pausa e per un Echo assente nel theremin.
3. Riscrivi la trasmissione Morse con `millis()` per mantenere attivo un pulsante di stop.
4. Aggiungi alla 11 un pulsante con debounce per interrompere e riavviare la musica.
5. Confronta il duty al 25%, 50%, 75% e 100% descrivendo ciò che senti senza attribuirgli un volume percentuale.

## Verifiche

Controlli locali del **24 ottobre 2026** sulle nuove raccolte 007–011: **37 sketch compilati con g++ e API sostituite**, con **66 esecuzioni superate**. Le verifiche comprendono pulsanti e debounce, avvio con tasto premuto, eventi PIR, temporizzazioni e ritorno a zero del timer, ADC e comandi servo, input seriali errati, echi assenti, filtro e fasce di distanza. Per RTTTL sono stati controllati parser, pause, note puntate/alterate, stop e riavvio e **50 melodie del catalogo**; il lettore MicroPython è stato verificato con PWM e clock sostituiti.

Sono stati controllati nomi dei file Arduino, 38 diagrammi JSON, resistenze, partitori Echo e collegamenti Markdown. Il modello temporale usa la larghezza nativa di `unsigned long` del computer: non emula la CPU o i tempi delle periferiche.

**Compilazione con core ESP32 reale, esecuzione Wokwi e collaudo hardware sono da eseguire.** Questi controlli non misurano corrente, qualità del suono, movimento o sensibilità del sensore.

## Riferimenti

- [MicroPython: PWM su ESP32](https://docs.micropython.org/en/latest/esp32/quickref.html#pwm-pulse-width-modulation).
- [Wokwi: buzzer passivo](https://docs.wokwi.com/parts/wokwi-buzzer).

[Indice ESP32-DEVKIT](../README.md) · [Indice generale](../../README.md)
