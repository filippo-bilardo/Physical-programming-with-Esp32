# PIR · Rilevamento del movimento con ESP32

## Introduzione teorica

Un sensore **PIR** (Passive InfraRed) rileva variazioni della radiazione infrarossa nel proprio campo visivo. La lente di Fresnel suddivide il campo in zone: attraversarle può generare un cambiamento rilevabile. Il modulo HC-SR501 elabora il segnale e presenta un’uscita digitale HIGH/LOW.

Il PIR segnala una variazione, non misura distanza o temperatura e non garantisce il rilevamento di una persona ferma. La durata HIGH dipende anche dal temporizzatore e dal retrigger del modulo: il contatore degli esempi conta attivazioni, non persone.

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
