# PIR · Rilevamento del movimento con ESP32

## Introduzione teorica

Un sensore **PIR** (Passive InfraRed) rileva variazioni della radiazione infrarossa nel proprio campo visivo. La lente di Fresnel suddivide il campo in zone: attraversarle può generare un cambiamento rilevabile. Il modulo HC-SR501 elabora il segnale e presenta un’uscita digitale HIGH/LOW.

Il PIR segnala una variazione, non misura distanza o temperatura e non garantisce il rilevamento di una persona ferma. La durata HIGH dipende anche dal temporizzatore e dal retrigger del modulo: il contatore degli esempi conta attivazioni, non persone.

### Effetto piroelettrico e segnale differenziale

Gli oggetti emettono radiazione infrarossa in funzione della loro temperatura. Il materiale piroelettrico del sensore produce un segnale quando cambia la radiazione che lo raggiunge. Nei comuni sensori a doppio elemento si confrontano due zone sensibili: una variazione che investe prima una zona e poi l’altra produce un segnale differenziale riconoscibile. Una variazione uniforme può avere un effetto diverso da un attraversamento del campo. [Adafruit: principio del sensore PIR](https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/how-pirs-work).

Il segnale originario è debole e variabile; il modulo contiene amplificazione ed elaborazione che lo trasformano in un’uscita digitale. L’ESP32 legge quindi una decisione già elaborata. Dal solo HIGH/LOW non può ricostruire forma, temperatura o percorso della sorgente infrarossa.

### Lente di Fresnel e movimento nel campo visivo

La copertura bianca non è soltanto una protezione: le sue zone ottiche convogliano la radiazione sul sensore. Muoversi trasversalmente attraversa più zone e può produrre variazioni più nette rispetto ad avvicinarsi lungo una sola direzione. Posizione, altezza e orientamento del montaggio influenzano quindi la risposta.

La probabilità di rilevamento dipende anche dal contrasto termico fra oggetto e sfondo. Se l’ambiente cambia, una prova riuscita con una mano a breve distanza non garantisce lo stesso esito con una persona lontana o quasi ferma. Il sensore rileva variazioni nel proprio campo, senza fornire una misura geometrica della posizione.

### Temporizzazione interna e retrigger

Dopo un’attivazione il modulo mantiene OUT alto per un intervallo. Nella modalità **retrigger** ulteriori rilevamenti possono prolungare l’uscita; nella modalità senza retrigger l’impulso segue la propria temporizzazione. Può essere presente anche un intervallo di inibizione dopo il ritorno basso. Jumper e trimmer del modello reale determinano questi comportamenti. [Adafruit: retrigger e tempi del modulo PIR](https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/testing-a-pir).

Il programma osserva quindi una successione già filtrata nel tempo. Se OUT rimane alto per più movimenti, il contatore a fronti registra una sola attivazione. Se il modulo torna basso e poi alto mentre la stessa persona continua a muoversi, può contarne più di una. **Attivazioni del sensore e persone presenti non sono grandezze equivalenti.**

### Tre tempi da distinguere

| Tempo | Chi lo determina | Significato |
| --- | --- | --- |
| Stabilizzazione iniziale | Modulo e attesa del programma | Periodo in cui l’uscita può essere instabile |
| Mantenimento di OUT | Circuito PIR e configurazione | Durata del segnale digitale dopo un rilevamento |
| Spegnimento della luce | Programma ESP32 | Tempo aggiuntivo scelto per l’applicazione |

Esempio di calcolo: l’ultimo movimento rilevabile avviene a 2 s, il modulo mantiene HIGH fino a 7 s e il programma spegne il LED 10 s dopo l’ultimo campione HIGH. La luce si spegnerà intorno a 17 s, con l’approssimazione della scansione. I dieci secondi software non partono necessariamente dall’ultimo gesto fisico.

Anche la durata HIGH misurata dagli esempi descrive il segnale del modulo. È utile per analizzarne la temporizzazione, ma non costituisce la durata esatta di un movimento umano.

### Fronti, polling e contatori indipendenti

Il fronte LOW → HIGH segnala l’inizio di un’attivazione; HIGH → LOW ne segnala la fine. Il programma deve conservare il livello precedente per distinguerli da un HIGH mantenuto. Stampare “movimento” a ogni lettura alta è corretto come indicazione di livello, ma produce molte righe per la stessa attivazione.

Ogni zona richiede una propria memoria del livello precedente e un proprio contatore. Condividere lo stesso stato fra tre sensori può confondere un rilascio in una zona con una nuova attivazione in un’altra. La scansione deve inoltre proseguire con regolarità: una lunga attesa può nascondere un’intera sequenza alto/basso.

### Dal sensore allo stato dell’applicazione

La macchina a stati dell’allarme conserva un’informazione distinta dal PIR. Disarmato, armato e scattato descrivono la politica dell’applicazione; il sensore fornisce soltanto il livello di ingresso. Un allarme memorizzato può rimanere scattato anche dopo il ritorno LOW, finché arriva un comando di disarmo.

Per valutare il sistema conviene provare attraversamento laterale, avvicinamento, immobilità e uscita dal campo, registrando tempi e livello. Cambia una sola regolazione per volta. In questo modo si distinguono effetti del modulo, decisioni del programma e condizioni del montaggio.

## Collegamenti

| Componente | Collegamento |
| --- | --- |
| HC-SR501 | VCC all’alimentazione prevista, tipicamente 5 V; GND comune; OUT a GPIO 23 |
| LED principale | GPIO 18 → 220 Ω → anodo; catodo a GND |
| Pulsante allarme 06 | GPIO 22 ↔ pulsante ↔ GND, pull-up interno |
| LED allarme 06 | Rosso 18, verde 19; una resistenza da 220 Ω per LED |
| Piezo passivo 06 | GPIO 27 → 1 kΩ → positivo; negativo a GND |
| Tre zone 07 | OUT a 23, 22, 21; LED rispettivamente a 18, 19, 25 |

Controlla la piedinatura del tuo modulo: può cambiare con l’orientamento della lente. L’uscita dei comuni HC-SR501 è tipicamente a 3,3 V anche con alimentazione a 5 V; **verifica il modulo prima di collegarlo**. I GPIO ESP32 non accettano 5 V. Regola sensibilità e tempo di mantenimento in hardware; il software non imposta i trimmer.

Dopo l’avvio tutti gli sketch attendono **60 secondi** con `delay()`: è un periodo di stabilizzazione, durante il quale non vengono elaborati eventi. Le condizioni ambientali possono richiedere ulteriore attesa. Nella 06 il LED verde indica lo stato disarmato anche durante l’attesa; attendi `Sistema pronto!` prima di usare il pulsante.

## Esempi

| Esempio | Cosa osservare |
| --- | --- |
| [PIR_01_rilevamento_semplice](<PIR_01_rilevamento_semplice/README.md>) | Livello del sensore ogni 500 ms |
| [PIR_02_controllo_led](<PIR_02_controllo_led/README.md>) | LED acceso mentre OUT è HIGH |
| [PIR_03_rilevamento_eventi](<PIR_03_rilevamento_eventi/README.md>) | Fronti di salita/discesa e durata del livello HIGH |
| [PIR_04_contatore](<PIR_04_contatore/README.md>) | Un incremento per fronte LOW → HIGH |
| [PIR_05_illuminazione_automatica](<PIR_05_illuminazione_automatica/README.md>) | LED acceso fino a 10 s dall’ultimo campione HIGH |
| [PIR_06_sistema_allarme](<PIR_06_sistema_allarme/README.md>) | Pulsante con debounce, stati disarmato/armato/scattato e beep |
| [PIR_07_multi_sensore](<PIR_07_multi_sensore/README.md>) | Tre sensori con LED e contatori indipendenti |
| [PIR_08_classe_sensore](<PIR_08_classe_sensore/README.md>) | Classe SensorePIR con eventi, durata e contatore |

Nelle prove 03/04/08 un HIGH presente alla fine della stabilizzazione viene considerato una prima attivazione. Le letture avvengono tramite polling: impulsi più brevi dell’intervallo di scansione possono sfuggire.

La 05 rinnova il timer mentre OUT è alto: i dieci secondi iniziano dall’ultimo campione alto, non dal primo movimento. La 06 rileva anche un HIGH già presente quando viene armata; dopo lo scatto resta in allarme finché il pulsante non la disarma. Il beep da 200 ms acceso e 100 ms spento usa `millis()` così il pulsante resta leggibile. Tenere il pulsante premuto alla fine della stabilizzazione non genera un nuovo comando: rilascia e premi di nuovo.

### Classe SensorePIR

Il costruttore memorizza il pin. `inizializza()` configura l’ingresso e attende la stabilizzazione; `update()` acquisisce il sensore una volta per giro. Dopo l’aggiornamento:

- `leggiStato()` restituisce il livello acquisito.
- `movimentoRilevato()` e `movimentoTerminato()` segnalano i due fronti fino al successivo `update()`; leggerli non li consuma.
- `getContatore()` restituisce le attivazioni; `resetContatore()` le azzera.
- `getDurataUltimoMovimento()` indica la durata dell’ultimo HIGH completato; `getTempoDallUltimoCambio()` il tempo trascorso dall’ultimo fronte.

## Avvio e simulazione

Apri un solo `.ino` dalla cartella omonima in Arduino IDE. Installa **esp32 by Espressif Systems**, seleziona la scheda reale (per esempio DOIT ESP32 DEVKIT V1) e la porta. La seriale, dove usata, è a **115200 baud**. I numeri dei pin sono GPIO, non posizioni del connettore. Questi collegamenti riguardano l’ESP32 classico WROOM-32.

Ogni esempio contiene un `diagram.json`: crea un progetto [Wokwi ESP32](https://docs.wokwi.com/guides/esp32), copia lo sketch nel file principale e il suo diagramma. Copia anche eventuali `.h` e `libraries.txt`. La simulazione aiuta a studiare la logica; correnti, alimentazione e comportamento fisico vanno verificati sul circuito.

Per generare un evento in Wokwi seleziona il PIR e usa **Simulate Motion**. Attendi prima i 60 s iniziali; ripeti con e senza retrigger e osserva che il tempo HIGH non coincide necessariamente con il tempo del gesto reale. Nella 07 attiva le zone separatamente e insieme.

## Esercizi

1. Confronta durata HIGH e numero di attivazioni variando i trimmer e il jumper H/L del modulo reale.
2. Aggiungi un contatore al programma 05 senza contare ripetutamente una pressione HIGH mantenuta.
3. Introduci un ritardo di uscita non bloccante prima di armare l’allarme.
4. Usa gli eventi della classe per visualizzare lo stato su un [OLED](../003-Oled/README.md).
5. Aggiungi una temporizzazione indipendente a ciascuna delle tre zone.

## Verifiche

Controlli locali del **24 ottobre 2026** sulle nuove raccolte 007–011: **37 sketch compilati con g++ e API sostituite**, con **66 esecuzioni superate**. Le verifiche comprendono pulsanti e debounce, avvio con tasto premuto, eventi PIR, temporizzazioni e ritorno a zero del timer, ADC e comandi servo, input seriali errati, echi assenti, filtro e fasce di distanza. Per RTTTL sono stati controllati parser, pause, note puntate/alterate, stop e riavvio e **50 melodie del catalogo**; il lettore MicroPython è stato verificato con PWM e clock sostituiti.

Sono stati controllati nomi dei file Arduino, 38 diagrammi JSON, resistenze, partitori Echo e collegamenti Markdown. Il modello temporale usa la larghezza nativa di `unsigned long` del computer: non emula la CPU o i tempi delle periferiche.

**Compilazione con core ESP32 reale, esecuzione Wokwi e collaudo hardware sono da eseguire.** Questi controlli non misurano corrente, qualità del suono, movimento o sensibilità del sensore.

## Riferimenti

- [Wokwi: PIR e temporizzazioni](https://docs.wokwi.com/parts/wokwi-pir-motion-sensor).
- [Espressif: GPIO](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html).

[Indice ESP32-DEVKIT](../README.md) · [Indice generale](../../README.md)
