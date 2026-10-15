# Scala percentuale del codice ADC

## Obiettivo e prerequisiti

Affiancare al codice grezzo una percentuale intera della scala ADC. La percentuale non è una misura calibrata della tensione o dell'angolo della manopola. Leggi la [guida associata](../../02-Risoluzione-attenuazione-e-misura.md) e prepara gli ambienti seguendo la [guida di installazione](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Codice C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Codice MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: framework Arduino-ESP32, `analogReadResolution()` e `analogSetPinAttenuation()`; nessuna libreria esterna.
- MicroPython: firmware per ESP32 classico con `ADC.read_u16()`, costante `ATTN_11DB` e metodo ESP32 `width(ADC.WIDTH_12BIT)`. Quest'ultimo è un metodo di compatibilità specifico del port, non una proprietà universale di tutte le schede MicroPython.
- Non servono pacchetti pip o `libraries.txt`. Registra le versioni effettive usate nelle prove.

## Materiali e collegamenti

ESP32 DOIT ESP32 DEVKIT V1 con modulo ESP32-WROOM-32 o equivalente, cavo USB dati, breadboard e cavetti; un potenziometro lineare da 10 kΩ.

Monta a scheda scollegata e identifica il cursore sul componente reale. Usa **3V3**, non VIN o 5 V. Le connessioni VCC/GND vanno realizzate anche se la simulazione analogica semplificata sembra funzionare senza. I numeri nel codice sono GPIO.

| Da | A |
| --- | --- |
| Estremo P1, `VCC` | 3V3 |
| Altro estremo P1, `GND` | GND |
| Cursore P1, `SIG` | GPIO 34 |

I pin GPIO 34 e 35 dell'ESP32 classico sono ingressi ADC1; non usarli come uscite e non attivare pull-up. L'attenuazione non protegge da sovratensione.

## Esecuzione in Wokwi

1. Apri un progetto Arduino ESP32 oppure MicroPython ESP32 dalla [guida ufficiale](https://docs.wokwi.com/guides/esp32).
2. Per C++ sostituisci il contenuto di `sketch.ino` con `cpp/cpp.ino`; per MicroPython sostituisci `main.py` con quello fornito.
3. Sostituisci `diagram.json` con quello della stessa sottocartella. Non mantenere due sketch contenenti le stesse funzioni.
4. Avvia la simulazione e apri la console. Seleziona la manopola per modificarla con mouse o tastiera: frecce per piccoli spostamenti, Home/End per gli estremi. Vedi il [riferimento Wokwi del potenziometro](https://docs.wokwi.com/parts/wokwi-potentiometer).
5. Esegui la prova guidata. L'attributo iniziale `value` del componente Wokwi usa 0–1023: è la posizione del controllo, **non** la scala ADC del programma.

## Esecuzione su scheda reale

1. Controlla collegamenti, alimentazione a 3,3 V e massa comune prima di collegare l'USB.
2. **C++:** apri `cpp/cpp.ino`, seleziona DOIT ESP32 DEVKIT V1, porta e core ESP32 installato in Arduino IDE. Compila, carica e apri il monitor seriale a **115200 baud**. Mantieni il nome `cpp.ino` dentro la cartella `cpp`.
3. **MicroPython:** in Thonny seleziona l'interprete ESP32 e la porta; salva il programma sulla scheda come `/main.py` e riavvia. Interrompi con Ctrl+C per tornare alla REPL.
4. Per la prova elettrica facoltativa misura la tensione fra cursore e GND con il multimetro in volt continua. Non considerare il codice una lettura calibrata di tensione.

## Prova guidata e risultato atteso

1. Avvia e osserva l'intestazione `raw12,percento`. Le righe numeriche iniziano dopo circa 200 ms.
2. Ruota il potenziometro e verifica che la percentuale resti fra 0 e 100.
3. Controlla una riga facendo `raw12 × 100 / 4095`, con divisione intera per difetto.
4. Su hardware confronta alcune posizioni con la tensione misurata al cursore. Una percentuale di codice non dimostra una corrispondente percentuale dell'alimentazione.

Esempi di calcolo: `0,0`; `1024,25`; `2047,49`; `2048,50`; `3072,75`; `4095,100`. Queste sono coppie numeriche attese per quei codici, non posizioni garantite della manopola.

## Come funziona e confronto dei linguaggi

Il campione è acquisito una sola volta per riga. C++ usa `raw * 100L / ADC_MAX`; MicroPython usa `raw * 100 // ADC_MAX`. I due risultati sono uguali a parità di codice in ingresso. La moltiplicazione viene prima della divisione: dividere prima per 4095 perderebbe la parte frazionaria quasi ovunque.

Entrambe le versioni configurano l'ADC a 12 bit e attenuazione a 11 dB. MicroPython restituisce con `read_u16()` una scala riscalata: `// 16` la riporta ai 4096 codici usati dal corso. Non si ottengono 16 bit fisici. La configurazione è prevista per ESP32 classico; i valori reali dipendono anche dalla toolchain e dalla scheda.

## Modifica autonoma

Aggiungi una colonna con una scala 0–255 mediante `raw × 255 / 4095`, usando divisione intera. È solo una riscalatura numerica: il programma non genera PWM e non cambia la risoluzione dell'ADC.

## Debug e stato delle prove

Se la lettura è fissa, controlla GPIO, cursore e attenuazione. Un ingresso lasciato aperto può fluttuare; un codice al massimo può indicare saturazione. Se un metodo ADC non è disponibile, verifica port e versione MicroPython, senza continuare con una configurazione diversa non documentata. Non eseguire `main.py` con Python del computer.

**Compilazione con core ESP32, Wokwi e hardware: da verificare per entrambe le versioni dove applicabile.** I controlli locali della logica con API sostituite non riproducono conversione elettrica, rumore, calibrazione o precisione temporale del dispositivo.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell'esercitazione](../../README.md)
- [📖 Guida associata](../../02-Risoluzione-attenuazione-e-misura.md)
