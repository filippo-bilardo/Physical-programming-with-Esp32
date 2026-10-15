# Media a blocchi di otto campioni

## Obiettivo e prerequisiti

Leggere ogni 20 ms nominali, poi pubblicare ultimo valore, media intera, minimo e massimo di ogni blocco di otto campioni non sovrapposti. Leggi la [guida associata](../../03-Campionamento-rumore-e-media.md) e prepara gli ambienti seguendo la [guida di installazione](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

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

1. Avvia e osserva `ultimo,media8,minimo,massimo`. Prima riga dopo circa 160 ms, poi circa 6,25 righe/s.
2. Mantieni fermo il potenziometro: ogni media deve essere compresa fra minimo e massimo del relativo blocco.
3. Cambia nettamente posizione durante l'acquisizione. Il primo blocco può contenere sia il livello precedente sia quello nuovo.
4. Confronta ultimo campione e media, poi attendi un intero blocco con ingresso stabile.

Con otto campioni ideali alternati 1990 e 2010, iniziando da 1990, la riga è `2010,2000,1990,2010`. In Wokwi non è garantito rumore spontaneo: per studiare la variabilità elettrica usa hardware. Non attribuire al simulatore la verifica dell'efficacia contro rumore reale.

## Come funziona e confronto dei linguaggi

Fra un giro e l'altro il programma conserva somma, conteggio, minimo e massimo. Al primo campione del blocco assegna minimo e massimo al dato reale; non li inizializza a zero. Dopo otto letture stampa e azzera somma e conteggio. Il campione successivo apre un nuovo blocco. La divisione intera tronca per difetto e il filtro non corregge offset, saturazione o aliasing già avvenuto.

Entrambe le versioni configurano l'ADC a 12 bit e attenuazione a 11 dB. MicroPython restituisce con `read_u16()` una scala riscalata: `// 16` la riporta ai 4096 codici usati dal corso. Non si ottengono 16 bit fisici. La configurazione è prevista per ESP32 classico; i valori reali dipendono anche dalla toolchain e dalla scheda.

## Modifica autonoma

Porta `SAMPLES` a 4 e modifica l'intestazione in `media4`. La prima media arriva nominalmente dopo 80 ms e le righe diventano circa 12,5 al secondo. Confronta stabilità e ritardo.

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
- [📖 Guida associata](../../03-Campionamento-rumore-e-media.md)
