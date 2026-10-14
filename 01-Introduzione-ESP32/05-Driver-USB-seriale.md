# Installare e verificare il driver USB-seriale

## Obiettivi e prerequisiti

Prerequisiti: nozioni di scheda, USB e porta seriale; computer e DOIT ESP32 DEVKIT V1 con cavo dati. Puoi usare questa guida durante l’[installazione di Arduino IDE](04-Arduino-IDE-e-DOIT-DevKit-V1.md).

Al termine saprai identificare il convertitore, scegliere il driver corretto, riconoscere la porta e distinguere un problema di driver da uno di cavo, permessi o caricamento. Le procedure qui descritte richiedono hardware reale: Wokwi nel browser non richiede un driver USB.

## Teoria e collegamento con l’architettura

Sulla DevKit con ESP32 classico un chip **USB-UART** converte la comunicazione USB del computer nella comunicazione seriale UART del microcontrollore. Il **driver** è il componente del sistema operativo che rende utilizzabile quel chip. Un driver **VCP**, Virtual COM Port, presenta una porta seriale alle applicazioni.

```text
Arduino IDE / Thonny → driver del sistema → USB → convertitore USB-UART → ESP32
```

Il driver gira sul computer, il firmware sulla scheda. Installare il core ESP32 nell’IDE non equivale a installare il driver; installare un driver non carica uno sketch nella Flash. La porta serve sia al caricamento sia ai messaggi della console, usata da una sola applicazione alla volta.

## 1. Identificare il convertitore

1. Scollega la scheda e leggi la sigla del chip vicino al connettore USB, usando se necessario una lente.
2. Controlla la documentazione del produttore della tua scheda. Versioni e cloni possono usare convertitori differenti: la scritta “ESP32 DEVKIT V1” non identifica da sola il driver.
3. Collega con un cavo dati e cerca il dispositivo USB nel sistema operativo; confronta la descrizione con la sigla del chip.
4. Se esiste già una porta funzionante, passa alla verifica finale: non serve reinstallare driver per principio.

| Chip riconosciuto | Famiglia di driver | Fonte del produttore |
| --- | --- | --- |
| CP2102 / CP210x | Silicon Labs CP210x VCP | [Download Silicon Labs](https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers) |
| CH340 / CH341 | WCH CH34x | [Pacchetto Windows WCH](https://www.wch-ic.com/downloads/CH341SER_EXE.html), [pacchetto macOS WCH](https://www.wch-ic.com/downloads/CH341SER_MAC_ZIP.html) |

Se trovi un’altra sigla, usa il driver indicato dal suo produttore; non scegliere CP210x o CH340 a tentativi. Scarica il pacchetto corrispondente al chip e al sistema operativo. Le pagine dei produttori riportano versioni e compatibilità aggiornate.

## 2. Windows

1. Apri **Gestione dispositivi** e osserva “Porte (COM e LPT)”, “Altri dispositivi” e i dispositivi USB prima e dopo il collegamento.
2. Se compare una voce come “Silicon Labs CP210x … (COM7)” senza errori, annota **COM7**: è un esempio di numero, non un valore da imporre a tutte le schede.
3. Se il convertitore è riconosciuto ma il driver manca, scarica il pacchetto ufficiale per Windows.
4. **CP210x:** estrai il pacchetto. Se fornisce un installer, segui le sue istruzioni; se fornisce file `.inf`, scegli sul dispositivo **Aggiorna driver → Cerca i driver nel computer**, indica la cartella estratta e includi le sottocartelle.
5. **CH340/CH341:** usa il pacchetto del produttore e la sua procedura di installazione; la distribuzione `CH341SER.EXE` fornisce un programma di installazione.
6. Accetta soltanto le richieste di installazione del pacchetto scelto. Riavvia il computer se richiesto, poi scollega e ricollega la scheda.
7. Controlla che la voce compaia sotto le porte senza simboli di errore. Seleziona la stessa COM in Arduino IDE.

Se non compare alcun nuovo dispositivo USB, verifica prima cavo, connettore e porta del computer. Il LED di alimentazione acceso dimostra soltanto che arriva energia: un cavo solo ricarica non trasporta i dati.

## 3. macOS

1. Apri **Informazioni di Sistema → USB** e verifica che il convertitore compaia collegando la scheda.
2. Nel Terminale confronta le porte prima e dopo il collegamento:

   ```bash
   ls /dev/cu.*
   ```

3. Se la porta esiste e funziona, usala nell’IDE. Il nome può contenere `SLAB_USBtoUART`, `usbserial` o un’identificazione del produttore; non è obbligatorio che coincida con un esempio trovato online.
4. Se manca il supporto per il chip riconosciuto, scarica dalla pagina Silicon Labs o WCH il pacchetto macOS compatibile con versione del sistema e architettura del computer.
5. Apri il pacchetto ed esegui l’installer seguendo le istruzioni incluse. Se macOS richiede di autorizzare il software del produttore nelle impostazioni di sicurezza, segui quella procedura e riavvia quando richiesto.
6. Ricollega e controlla la nuova porta `/dev/cu.…`, quindi selezionala nell’IDE.

Il [repository ufficiale WCH per macOS](https://github.com/WCHSoftGroup/ch34xser_macos) contiene anche indicazioni di installazione. Non disabilitare globalmente le protezioni del sistema per aggirare un pacchetto incompatibile: verifica prima che sia quello appropriato.

## 4. Linux

I kernel Linux comuni includono già i driver per CP210x e CH340/CH341; la verifica iniziale consiste nel controllare riconoscimento e permessi. Silicon Labs rimanda al [supporto nel kernel Linux](https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers); il driver CH341 è presente nel [sorgente Linux](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/drivers/usb/serial/ch341.c).

1. Collega la scheda e, se disponibile, esegui `lsusb` per controllare la presenza del convertitore. Su Debian/Ubuntu il comando appartiene al pacchetto `usbutils`.
2. Controlla i collegamenti stabili delle porte:

   ```bash
   ls -l /dev/serial/by-id/
   ```

   Il percorso può non esistere se nessun dispositivo seriale è stato enumerato. In questi casi controlla i messaggi del kernel con gli strumenti del sistema e cerca `cp210x`, `ch341` o `ttyUSB`; i permessi di lettura dei log variano fra distribuzioni.

3. Una volta identificata la porta, controlla proprietario e gruppo. Per esempio, **solo se la tua porta è ttyUSB0**:

   ```bash
   ls -l /dev/ttyUSB0
   id -nG
   ```

4. Su Debian/Ubuntu, se la porta appartiene al gruppo `dialout` e l’utente non ne fa parte, un amministratore può aggiungerlo:

   ```bash
   sudo usermod -aG dialout "$USER"
   ```

5. Esci completamente dalla sessione e rientra, poi riapri l’IDE. Su altre distribuzioni usa il gruppo e la procedura indicati dal sistema, non dare per scontato `dialout`.

La [guida Arduino ai permessi seriali Linux](https://support.arduino.cc/hc/en-us/articles/360016495679-Fix-port-access-on-Linux) distingue accesso negato e porta occupata. Non eseguire abitualmente Arduino IDE come root e non usare permessi globali sulla porta per nascondere il problema.

## 5. Verifica finale con Arduino IDE e Thonny

1. Scollega la DOIT: la sua porta deve scomparire. Ricollegala: deve ricomparire; il numero o nome può cambiare.
2. In Arduino IDE scegli DOIT ESP32 DEVKIT V1 e la porta identificata. Carica il [lampeggio completo](esempi/03_01-LED-lampeggiante/README.md) seguendo i suoi collegamenti.
3. Apri il monitor a 115200 baud: il risultato atteso è la sequenza `LED acceso` / `LED spento` con LED coerente.
4. Se usi invece MicroPython già installato, chiudi il monitor Arduino, seleziona la stessa porta in Thonny e verifica la REPL. Il driver USB rimane lo stesso; cambia il software che comunica con la scheda.

### Esempio commentato

Nel firmware Arduino il messaggio arriva alla porta tramite la UART:

```cpp
Serial.begin(115200);          // Configurazione in setup().
Serial.println("LED acceso"); // Messaggio del programma, non del driver.
```

Nella REPL MicroPython, dopo aver installato il firmware appropriato:

```python
print("Collegamento seriale funzionante")
```

Il [primo esempio](esempi/03_01-LED-lampeggiante/README.md) contiene i programmi completi nei due linguaggi. Non occorre creare un altro sketch per provare il driver.

## Buone pratiche e debug

| Sintomo | Possibile causa e controllo |
| --- | --- |
| LED di alimentazione acceso, nessun dispositivo USB | Cavo senza dati, contatto o porta USB |
| Dispositivo USB presente, porta assente | Driver mancante/incompatibile o errore di enumerazione |
| Porta presente, accesso negato | Permessi del sistema operativo |
| Porta presente, risorsa occupata | Un’altra applicazione sta usando la seriale |
| Porta disponibile, upload bloccato | Board selezionata, bootloader e sequenza BOOT/EN; vedi guida 04 |
| Upload riuscito, testo illeggibile | Baud del monitor non coerente col programma |

Non reinstallare il driver come primo rimedio per qualsiasi errore di compilazione: la compilazione avviene prima della comunicazione USB. Non sono state eseguite installazioni di driver sui sistemi degli studenti durante la preparazione di questa guida.

## Autovalutazione

1. **Dove viene installato il driver USB-seriale?**

   - A. Nella resistenza del LED.
   - B. Nel sistema operativo del computer.
   - C. In diagram.json.
   - D. Solo nella RAM dell’ESP32.

2. **Come scegli fra CP210x e CH340?**

   - A. Dal colore del LED.
   - B. Dal numero di funzioni nello sketch.
   - C. Identificando il convertitore presente sulla scheda.
   - D. Installandoli sempre entrambi.

3. **Quale prova identifica la porta della scheda?**

   - A. Osservare quale porta scompare e ricompare scollegandola e ricollegandola.
   - B. Scegliere sempre COM1.
   - C. Cambiare il GPIO del LED.
   - D. Rinominare main.py.

## Esercizi pratici

1. **Consegna:** identifica sigla del chip e pagina del produttore.

   **Risultato atteso:** annotazione del convertitore reale, senza dedurlo soltanto dal nome ESP32.

2. **Consegna:** verifica la porta, installando il driver solo se necessario, e annota sistema operativo e procedura seguita.

   **Risultato atteso:** porta presente e accessibile all’utente normale.

3. **Consegna:** carica il lampeggio e verifica la console; poi chiudi e riapri la connessione.

   **Risultato atteso:** comunicazione ripetibile, senza due applicazioni contemporaneamente sulla stessa porta.

## Soluzioni dell’autovalutazione

1. **B — Nel sistema operativo del computer.** Rende disponibile il convertitore alle applicazioni.
2. **C — Identificando il convertitore presente sulla scheda.** Schede simili possono montare chip diversi.
3. **A — Osservare quale porta scompare e ricompare scollegandola e ricollegandola.** È una verifica pratica del collegamento fisico.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](04-Arduino-IDE-e-DOIT-DevKit-V1.md)
- [➡️ Guida successiva](06-Wokwi-e-Tinkercad.md)
