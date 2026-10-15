# Lettura del potenziometro

## Obiettivo e prerequisiti

Acquisire il cursore del potenziometro su GPIO 34 e stampare un codice nella scala comune 0–4095 ogni 200 ms nominali. Leggi la [guida associata](../../01-Potenziometro-e-ADC.md) e prepara gli ambienti seguendo la [guida di installazione](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

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

1. Avvia: la prima riga arriva dopo circa 200 ms, poi circa cinque righe al secondo.
2. Ruota lentamente fra i due estremi e annota minimo, massimo e tre valori intermedi.
3. Mantieni ferma la manopola per alcuni secondi: su hardware possono esserci piccole variazioni, nel simulatore il valore può essere stabile.
4. Confronta i due linguaggi mantenendo la stessa posizione iniziale. Confronta l'andamento e la scala, senza pretendere la stessa risposta fisica di core e firmware diversi.

Ogni riga contiene un solo intero. Non rappresenta volt. Vicino agli estremi l'ADC reale può saturare: non aspettarti una relazione lineare su tutta la corsa.

## Come funziona e confronto dei linguaggi

C++ imposta 12 bit e legge `analogRead(34)`. MicroPython imposta 12 bit, legge `read_u16()` e divide per 16 per ottenere la scala 0–4095. Entrambe le versioni controllano un riferimento temporale e fanno una breve pausa di 1 ms per giro. Non sono usate acquisizioni continue hardware.

Entrambe le versioni configurano l'ADC a 12 bit e attenuazione a 11 dB. MicroPython restituisce con `read_u16()` una scala riscalata: `// 16` la riporta ai 4096 codici usati dal corso. Non si ottengono 16 bit fisici. La configurazione è prevista per ESP32 classico; i valori reali dipendono anche dalla toolchain e dalla scheda.

## Modifica autonoma

Porta `SAMPLE_MS` a 100 e poi a 500: la frequenza nominale passa a 10 e 2 campioni/s. Risoluzione e attenuazione restano invariate.

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
- [📖 Guida associata](../../01-Potenziometro-e-ADC.md)
