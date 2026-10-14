# Ambienti di sviluppo e primo collegamento

## Obiettivi e prerequisiti

Prerequisiti: guida 01 e capacità di installare applicazioni. Obiettivi: creare un progetto Wokwi, preparare Arduino IDE, installare MicroPython e distinguere compilazione, caricamento ed esecuzione.

## Teoria e collegamento con l’architettura

### Tre operazioni diverse

Un **editor** modifica il testo del programma. Un **compilatore** traduce il C++ in codice per la CPU. Il **caricamento** trasferisce il firmware sulla scheda; la **console seriale** mostra messaggi e, con MicroPython, consente anche una sessione interattiva chiamata REPL. Il pulsante “Verifica” di Arduino IDE controlla la compilazione: non dimostra da solo che il circuito funzioni.

Wokwi simula un microcontrollore e dispositivi collegati. Un progetto comprende codice e `diagram.json`, il file che descrive componenti e connessioni. Il file JSON non viene caricato sulla scheda reale: rappresenta il montaggio da riprodurre.

Per istruzioni più dettagliate consulta [Arduino IDE e DOIT ESP32 DEVKIT V1](04-Arduino-IDE-e-DOIT-DevKit-V1.md), [driver USB-seriale](05-Driver-USB-seriale.md) e [Wokwi e Tinkercad](06-Wokwi-e-Tinkercad.md).

### Wokwi: preparazione senza hardware

1. Apri la [guida ESP32](https://docs.wokwi.com/guides/esp32) e, sotto “Getting Started”, apri il modello Arduino-ESP32.
2. Apri il [primo esempio](esempi/03_01-LED-lampeggiante/README.md). Copia `cpp/cpp.ino` nel `sketch.ino` del modello, sostituendo tutto il contenuto.
3. Sostituisci `diagram.json` con `cpp/diagram.json` dello stesso esempio. Avvia la simulazione e individua monitor seriale, scheda e LED.
4. Crea un secondo progetto usando il modello MicroPython ESP32 della stessa pagina. Sostituisci `main.py` e `diagram.json` con i file della cartella `micropython/`.
5. Avvia e confronta i due progetti. Per interagire con la REPL, interrompi il programma MicroPython con Ctrl+C nella console.

I modelli impostano l’ambiente corretto. Non basta rinominare un file Python dentro un progetto Arduino. Le istruzioni ufficiali descrivono l’[uso di MicroPython in Wokwi](https://docs.wokwi.com/guides/micropython).

### Arduino IDE: dalla compilazione alla Flash

1. Installa [Arduino IDE](https://www.arduino.cc/en/software), ramo 2.x.
2. Nelle preferenze aggiungi all’elenco degli URL per il gestore schede l’indice stabile: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`.
3. Apri il gestore delle schede e installa **esp32 by Espressif Systems**, ramo 3.x. Annota la versione scelta.
4. Collega la DevKit con un cavo USB dati. Seleziona il modello appropriato; per la DOIT usata nella guida di installazione scegli **DOIT ESP32 DEVKIT V1**; per un’altra DevKit WROOM verifica il profilo appropriato. Seleziona la porta comparsa collegando la scheda.
5. Apri `cpp/cpp.ino` del primo esempio. Il file `.ino` e la cartella che lo contiene devono avere lo stesso nome base.
6. Premi “Verifica”, poi “Carica”. Apri il monitor seriale a 115200 baud e riavvia se vuoi vedere i messaggi iniziali.

La procedura di installazione è descritta nella [documentazione Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html). Nessuno degli esempi delle prime tre esercitazioni richiede librerie aggiuntive.

### MicroPython: firmware, REPL e main.py

1. Installa [Thonny](https://thonny.org/) e collega la scheda. La [guida MicroPython di Thonny](https://github.com/thonny/thonny/wiki/MicroPython) descrive la configurazione dell’interprete. Chiudi Arduino IDE o almeno il suo monitor seriale per liberare la porta.
2. Apri le impostazioni dell’interprete in Thonny e scegli **MicroPython (ESP32)** e la porta del dispositivo.
3. Usa la funzione di installazione/aggiornamento MicroPython del dialogo dell’interprete. Seleziona ESP32 generico, variante compatibile con il modulo WROOM e una release stabile. Le etichette del dialogo possono cambiare con la versione di Thonny.
4. Controlla la corrispondenza con la [pagina ufficiale ESP32_GENERIC](https://micropython.org/download/ESP32_GENERIC/). Per una DevKit WROOM con almeno 4 MiB di Flash usa il firmware generico standard; non selezionare C3/S3. Se il dialogo non supporta il dispositivo, segui la procedura di installazione riportata in quella pagina usando il firmware esatto.
5. Salva sul computer eventuali file già presenti prima di cancellare la Flash. Installa il firmware, poi riconnetti l’interprete alla porta.
6. Nella console esegui `print("Ciao ESP32")`: deve apparire il messaggio seguito dal prompt `>>>`.
7. Apri il file dell’esempio in Thonny e salvalo **sul dispositivo MicroPython**, nella cartella principale, con il nome `main.py`. Riavvia con il pulsante EN/RESET della scheda per controllare l’avvio automatico.
8. Interrompi con Ctrl+C prima di sostituire il file; salva e riavvia nuovamente.

`main.py` resta nel filesystem della Flash e viene eseguito all’avvio. Il firmware e gli oggetti in RAM hanno ruoli distinti: trasferire il sorgente non equivale a ricompilare tutto il firmware. Gli esempi usano API disponibili nelle release MicroPython 1.24 o successive; queste sono versioni di riferimento, non una dichiarazione di collaudo su tutte le release.

### Registrare l’ambiente

Annota modello della scheda, versione IDE, versione core o firmware, nome dell’esempio e tipo di prova (simulazione o hardware). In MicroPython `import sys; print(sys.implementation)` aiuta a identificare il runtime. In Arduino IDE il gestore schede mostra la versione del pacchetto installato. Per Wokwi annota data, modello di progetto e versione mostrata nel log, se disponibile; non dedurla dalla versione installata sul computer.

## Esempi commentati

Una prova della console non richiede un circuito esterno:

```python
print("Ciao ESP32")  # Scrivi questa riga nella REPL MicroPython.
```

Nel [programma C++ completo](esempi/03_01-LED-lampeggiante/cpp/cpp.ino), la console si prepara una volta:

```cpp
Serial.begin(115200);       // Dentro setup().
Serial.println("Avvio");   // Invia una riga al monitor seriale.
```

Il [README dell’esempio](esempi/03_01-LED-lampeggiante/README.md) contiene i file da copiare e il risultato atteso.

## Buone pratiche e debug

| Sintomo | Controllo utile |
| --- | --- |
| Nessuna porta disponibile | Cavo dati, porta USB, eventuale driver del convertitore e permessi seriali del sistema |
| Porta occupata | Chiudi console e programmi concorrenti |
| Caricamento fermo su Connecting | Verifica scheda e porta; se necessario segui la procedura BOOT/EN del modello |
| Testo illeggibile | Imposta 115200 baud e controlla il dispositivo selezionato |
| `No module named machine` | Stai usando Python sul computer anziché MicroPython sul dispositivo |
| Programma assente dopo riavvio | Controlla che `main.py` sia stato salvato sulla scheda, non soltanto sul PC |

Passando da Arduino a MicroPython occorre reinstallare il firmware MicroPython; non presumere che file e configurazioni della Flash restino intatti.

## Autovalutazione

Per ogni domanda scegli una sola risposta. Le soluzioni sono dopo gli esercizi pratici.

1. **Quale file descrive il circuito Wokwi?**

   - A. main.py
   - B. diagram.json
   - C. cpp.ino
   - D. Il nome della porta seriale

2. **Dove va salvato main.py per l’avvio automatico sulla scheda?**

   - A. Solo sul desktop del PC
   - B. Nel monitor seriale
   - C. Nel filesystem della scheda, alla radice
   - D. Nel gestore schede Arduino

3. **Cosa dimostra una compilazione riuscita?**

   - A. Che la traduzione del programma per il target è riuscita
   - B. Che la polarità del LED è corretta
   - C. Che il GPIO non supera mai i limiti elettrici
   - D. Che ogni prova su hardware è conclusa

## Esercizi pratici

Le attività sul codice e sulla logica sono eseguibili in Wokwi; montaggio, misure elettriche e collaudo fisico richiedono la scheda reale quando indicato.

1. **Consegna:** Esegui il messaggio di saluto nella REPL.

   **Risultato atteso:** La console risponde e torna al prompt.

2. **Consegna:** Prepara i due progetti Wokwi del lampeggio.

   **Risultato atteso:** Stesso circuito e stesso comportamento usando i due ambienti.

3. **Consegna:** Compila/carica il primo esempio su una scheda, se disponibile, e compila una scheda di prova con le versioni.

   **Risultato atteso:** Una procedura riproducibile; se manca hardware, annota esplicitamente “da verificare su scheda”.

## Soluzioni dell’autovalutazione

1. **B — diagram.json.** diagram.json contiene componenti, attributi e connessioni.

2. **C — Nel filesystem della scheda, alla radice.** Il firmware avvia il file presente sul dispositivo.

3. **A — Che la traduzione del programma per il target è riuscita.** Il montaggio e il comportamento richiedono verifiche separate.

## Riferimenti

[Installazione Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html), [firmware ESP32_GENERIC](https://micropython.org/download/ESP32_GENERIC/), [progetti Wokwi](https://docs.wokwi.com/guides/esp32).

## Navigazione del corso

- [📑 Indice generale](../../README.md)
- [📂 Indice dell’esercitazione](./README.md)
- [⬅️ Guida precedente](01-Architettura-ESP32.md)
- [➡️ Guida successiva](03-Primo-programma.md)
