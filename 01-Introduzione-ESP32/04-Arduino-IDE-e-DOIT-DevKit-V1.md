# Installare Arduino IDE e la board DOIT ESP32 DEVKIT V1

## Obiettivi e prerequisiti

Prerequisiti: saper installare un’applicazione e riconoscere file e cartelle; aver letto le guide 01 e 02. Questa guida approfondisce la preparazione dell’ambiente: puoi consultarla prima di eseguire il primo programma della guida 03.

Al termine saprai installare Arduino IDE, aggiungere il supporto ESP32, selezionare la DOIT ESP32 DEVKIT V1 e distinguere compilazione, caricamento e monitor seriale. Il collaudo completo richiede una scheda reale; la sola compilazione può essere eseguita senza collegarla.

## Teoria e collegamento con l’architettura

Un **IDE**, ambiente di sviluppo integrato, riunisce editor, compilazione, caricamento e strumenti di diagnostica. Il **core Arduino-ESP32** aggiunge compilatore, librerie e definizioni delle schede ESP32. Installare Arduino IDE non installa automaticamente ogni core disponibile.

La **board** selezionata determina il target di compilazione e le impostazioni di caricamento. La **porta** identifica invece il dispositivo collegato al computer. Scegliere una porta non seleziona sempre automaticamente la scheda: un convertitore USB-seriale può essere condiviso da modelli diversi.

```text
Sketch C++ → compilatore per ESP32 → firmware → USB del computer
                                               ↓
                                    convertitore USB-UART
                                               ↓
                                   bootloader ESP32 → Flash
```

La CPU esegue il firmware dalla piattaforma ESP32; il convertitore USB-UART trasferisce dati, non compila lo sketch. Per driver e riconoscimento della porta usa la [guida USB-seriale](05-Driver-USB-seriale.md).

## 1. Identificare la scheda e preparare il materiale

Usiamo come esempio una **DOIT ESP32 DEVKIT V1 con ESP32 classico e modulo WROOM**. Leggi le sigle sulla scheda e sul modulo: un prodotto dal nome simile con ESP32-C3 o S3 non usa automaticamente questa configurazione. Il modello della porta USB non basta a identificare il microcontrollore.

Servono computer, connessione Internet per scaricare gli strumenti, scheda e **cavo USB dati** compatibile con il suo connettore. Per la prova LED aggiungi breadboard, LED rosso, resistenza da 330 Ω e cavetti. Durante l’installazione iniziale puoi lasciare scollegato il circuito esterno.

## 2. Installare Arduino IDE

Apri la [pagina software Arduino](https://www.arduino.cc/en/software) e scegli una release stabile di **Arduino IDE 2** per il tuo sistema. Controlla i requisiti e segui la [procedura ufficiale](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE):

| Sistema | Procedura essenziale |
| --- | --- |
| Windows | Scarica l’installer compatibile, avvialo e completa la procedura guidata; apri Arduino IDE dal menu Start. |
| macOS | Apri il file `.dmg`, trascina Arduino IDE in Applicazioni e avvialo. |
| Linux | Se usi AppImage, rendi il file eseguibile dalle proprietà e avvialo; in caso di errore FUSE consulta la procedura ufficiale per le dipendenze del sistema. |

Verifica che l’editor si apra e annota la versione dal menu delle informazioni sull’applicazione. I nomi dei menu possono essere tradotti o variare fra sistemi; non occorre installare il Cloud Agent per usare l’IDE desktop.

## 3. Aggiungere il core ESP32

1. Apri le preferenze dell’IDE, generalmente **File → Preferenze** oppure il menu dell’applicazione su macOS.
2. Individua **URL aggiuntive per il Gestore schede** e aggiungi l’indice stabile, conservando eventuali altri URL già presenti:

   ```text
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

3. Conferma e apri il **Gestore schede / Boards Manager** dalla barra laterale o dal menu Strumenti.
4. Cerca `esp32` e installa **esp32 by Espressif Systems**, release stabile del ramo 3.x usato come riferimento nel corso.
5. Attendi la conclusione del download e annota la versione del pacchetto. Se l’installazione fallisce, leggi l’errore relativo a rete, spazio o permessi prima di riprovare.

L’URL e il flusso di installazione sono riportati nella [documentazione Espressif](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html). Il gestore **schede** installa il supporto del microcontrollore; il gestore **librerie** aggiunge altre librerie e non lo sostituisce.

## 4. Selezionare DOIT ESP32 DEVKIT V1

1. Nel selettore della scheda o in **Strumenti → Scheda → esp32** cerca **DOIT ESP32 DEVKIT V1**.
2. Seleziona esattamente quel profilo per la DOIT usata nella prova. La definizione è presente nel [file delle board del core Espressif](https://github.com/espressif/arduino-esp32/blob/master/boards.txt); l’identificatore per Arduino CLI è `esp32:esp32:esp32doit-devkit-v1`.
3. Mantieni inizialmente le opzioni predefinite del profilo, salvo diversa indicazione della documentazione della tua scheda. Non abilitare PSRAM o modificare partizioni per tentativi.
4. Collega la scheda e seleziona la porta che compare. Se non compare, segui la [guida al driver USB-seriale](05-Driver-USB-seriale.md).

Se il profilo non appare, controlla che il pacchetto Espressif sia effettivamente installato e che la ricerca non abbia filtri residui. Un profilo generico ESP32 Dev Module è un’altra scelta da configurare consapevolmente, non la board usata per questa procedura.

## 5. Compilare e caricare il primo esempio

1. Apri [cpp/cpp.ino del lampeggio](esempi/03_01-LED-lampeggiante/cpp/cpp.ino). Mantieni il file nella cartella `cpp`: lo sketch Arduino deve avere il nome base della cartella.
2. Premi **Verifica**. Il risultato atteso è una compilazione senza errori; questa fase può riuscire anche senza una porta selezionata.
3. A scheda scollegata realizza il circuito del [README del lampeggio](esempi/03_01-LED-lampeggiante/README.md): GPIO 18 → 330 Ω → anodo LED; catodo → GND.
4. Collega la scheda, verifica board e porta, chiudi le altre applicazioni seriali e premi **Carica**.
5. Attendi l’esito di caricamento. Apri il **Monitor seriale** a **115200 baud** e premi EN/RESET per osservare la ripartenza.
6. Verifica LED acceso/spento ogni circa mezzo secondo e messaggi corrispondenti. Non usare il LED integrato come sostituto implicito del circuito esterno.

Il caricamento scrive firmware nella Flash: se la scheda eseguiva MicroPython, salva prima i suoi file e considera necessaria la reinstallazione del firmware per tornarvi.

### Se il caricamento resta su Connecting

Per una scheda che non entra automaticamente nel bootloader, prova la sequenza manuale: tieni premuto **BOOT**, premi e rilascia **EN/RESET**, avvia il caricamento e rilascia BOOT quando inizia la scrittura. Dopo il caricamento rilascia tutti i pulsanti e premi EN se necessario. BOOT controlla la condizione di avvio; EN riavvia il chip. La [documentazione esptool](https://docs.espressif.com/projects/esptool/en/latest/esp32/advanced-topics/boot-mode-selection.html) spiega il meccanismo.

Non confondere velocità di upload e baud del monitor: sono impostazioni differenti. Se la comunicazione di upload è instabile, prova un altro cavo dati e una velocità di upload più bassa, ad esempio 115200, senza cambiare il codice.

## Esempi commentati

Nel programma completo la console è configurata una volta:

```cpp
void setup() {
  Serial.begin(115200);     // Baud del monitor seriale.
  pinMode(LED_PIN, OUTPUT); // LED_PIN vale 18 nell'esempio completo.
  digitalWrite(LED_PIN, LOW);
}
```

Questo è un frammento del [progetto completo](esempi/03_01-LED-lampeggiante/README.md): non incollarlo in aggiunta a un’altra `setup()`. Modifica `ON_MS` e `OFF_MS` per provare tempi differenti, poi ricompila e ricarica.

## Buone pratiche e debug

| Sintomo | Cosa controllare |
| --- | --- |
| Il profilo DOIT manca | Installazione del core **Espressif**, non di una libreria omonima |
| Compilazione riuscita, upload fallito | Porta, driver, cavo dati, disponibilità della porta e modalità BOOT |
| Porta presente ma occupata | Chiudi Thonny, altre istanze IDE o terminali seriali |
| Testo illeggibile | Baud del monitor uguale a quello in `Serial.begin` |
| LED fermo ma messaggi corretti | Circuito, polarità e GPIO 18 |

Registra modello, versione del core, porta, impostazioni modificate e risultato di compilazione/upload. Le procedure sono documentate ma non dichiarate collaudate su una DOIT reale in questa sessione.

## Autovalutazione

1. **Quale pacchetto aggiunge le board ESP32 all’IDE?**

   - A. Una libreria LED qualsiasi.
   - B. esp32 by Espressif Systems nel Gestore schede.
   - C. Il solo driver CP210x.
   - D. Il file diagram.json.

2. **Cosa identifica la porta seriale?**

   - A. Il dispositivo di comunicazione collegato al computer.
   - B. Il linguaggio usato nello sketch.
   - C. La resistenza del LED.
   - D. Il nome della funzione loop.

3. **La compilazione riesce senza scheda collegata: cosa significa?**

   - A. Il circuito è già stato collaudato.
   - B. Il driver USB è sicuramente installato.
   - C. Il programma è stato tradotto per il target selezionato.
   - D. Il firmware è già nella Flash della scheda.

## Esercizi pratici

1. **Consegna:** installa IDE e core, seleziona DOIT ESP32 DEVKIT V1 e compila l’esempio.

   **Risultato atteso:** compilazione conclusa e versioni annotate; non serve la scheda per questa fase.

2. **Consegna:** identifica la porta scollegando e ricollegando la DOIT, poi carica il lampeggio.

   **Risultato atteso:** upload riuscito, LED e console coerenti. Richiede hardware.

3. **Consegna:** cambia entrambe le attese da 500 a 250 ms, ricompila e ricarica.

   **Risultato atteso:** periodo nominale dimezzato, da 1 s a 0,5 s; distingue salvataggio del file e aggiornamento del firmware.

## Soluzioni dell’autovalutazione

1. **B — esp32 by Espressif Systems nel Gestore schede.** Include il supporto per compilare e caricare sugli ESP32.
2. **A — Il dispositivo di comunicazione collegato al computer.** Il target di compilazione si sceglie separatamente tramite la board.
3. **C — Il programma è stato tradotto per il target selezionato.** Il trasferimento e il collaudo richiedono altri passaggi.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](03-Primo-programma.md)
- [➡️ Guida successiva](05-Driver-USB-seriale.md)
