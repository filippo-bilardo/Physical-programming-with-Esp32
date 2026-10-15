# Soglia regolabile con isteresi

## Obiettivo e prerequisiti

Confrontare il segnale del primo potenziometro con una soglia regolata dal secondo. Il LED usa una semibanda di 100 codici per mantenere lo stato vicino al centro. Leggi la [guida associata](../../04-Soglia-regolabile-e-isteresi.md) e prepara gli ambienti seguendo la [guida di installazione](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Codice C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Codice MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: framework Arduino-ESP32, `analogReadResolution()` e `analogSetPinAttenuation()`; nessuna libreria esterna.
- MicroPython: firmware per ESP32 classico con `ADC.read_u16()`, costante `ATTN_11DB` e metodo ESP32 `width(ADC.WIDTH_12BIT)`. Quest'ultimo è un metodo di compatibilità specifico del port, non una proprietà universale di tutte le schede MicroPython.
- Non servono pacchetti pip o `libraries.txt`. Registra le versioni effettive usate nelle prove.

## Materiali e collegamenti

ESP32 DOIT ESP32 DEVKIT V1 con modulo ESP32-WROOM-32 o equivalente, cavo USB dati, breadboard e cavetti; due potenziometri lineari da 10 kΩ, un LED rosso e una resistenza da 220 Ω.

Monta a scheda scollegata e identifica il cursore sul componente reale. Usa **3V3**, non VIN o 5 V. Le connessioni VCC/GND vanno realizzate anche se la simulazione analogica semplificata sembra funzionare senza. I numeri nel codice sono GPIO.

| Da | A |
| --- | --- |
| Estremo P1, `VCC` | 3V3 |
| Altro estremo P1, `GND` | GND |
| Cursore P1, `SIG` | GPIO 34 |
| Estremo P2, `VCC` | 3V3 |
| Altro estremo P2, `GND` | GND |
| Cursore P2, `SIG` | GPIO 35 |
| GPIO 18 | Resistenza da 220 Ω → anodo LED rosso |
| Catodo LED rosso | GND |

P1 (`pot1`, in alto a sinistra nel diagramma) simula il segnale; P2 (`pot2`, sotto P1) regola la soglia. Ogni LED deve mantenere la propria resistenza in serie. I pin GPIO 34 e 35 dell'ESP32 classico sono ingressi ADC1; non usarli come uscite e non attivare pull-up. L'attenuazione non protegge da sovratensione.

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

1. Avvia con P1 al minimo e P2 circa a metà: il LED parte spento; il primo controllo avviene dopo circa 20 ms.
2. La console mostra `segnale,soglia,bassa,alta,allarme`, con una riga ogni circa 200 ms. Le letture e il comando LED continuano ogni 20 ms.
3. Mantieni P2 fermo e aumenta P1 fino a raggiungere o superare `alta`: il LED si accende e `allarme` vale 1.
4. Diminuisci P1 fino a entrare fra `bassa` e `alta`: il LED resta acceso. Raggiungi o scendi sotto `bassa` per spegnerlo.
5. Mantieni P1 fermo e sposta P2: i limiti cambiano e possono cambiare lo stato del LED.
6. Prova P2 ai due estremi e controlla che entrambi i limiti restino fra 0 e 4095.
7. Riavvia con il segnale fra i limiti: resta spento. Riavvia con segnale sopra `alta`: si accende alla prima acquisizione.

I cambi del LED possono precedere il riepilogo seriale. Il comparatore usa i campioni grezzi, senza media e senza attesa di stabilità temporale. Non è un circuito di protezione per apparecchiature reali.

| Regolazione ADC grezza P2 | Centro calcolato | Limite basso | Limite alto |
| --- | --- | --- | --- |
| 0 | 100 | 0 | 200 |
| 2048 | 2047 | 1947 | 2147 |
| 4095 | 3995 | 3895 | 4095 |

Sono esempi aritmetici per quei codici; non attribuirli a posizioni fisiche esatte della manopola. La soglia è in codici, non in mV.

## Come funziona e confronto dei linguaggi

L'acquisizione legge prima GPIO 34 e poi GPIO 35: i due canali non sono campionati simultaneamente. La regolazione è trasformata in un centro fra 100 e 3995; i limiti sono centro meno/più 100. Le condizioni inclusive di accensione e spegnimento sono alternative; all'interno della banda il booleano conserva il valore precedente. La stampa usa gli stessi campioni della decisione, senza nuove conversioni.

Entrambe le versioni configurano l'ADC a 12 bit e attenuazione a 11 dB. MicroPython restituisce con `read_u16()` una scala riscalata: `// 16` la riporta ai 4096 codici usati dal corso. Non si ottengono 16 bit fisici. La configurazione è prevista per ESP32 classico; i valori reali dipendono anche dalla toolchain e dalla scheda.

## Modifica autonoma

Prova semibande di 20 e 200 codici, entrambe nell'intervallo ammesso 1–2047. Registra il nuovo centro e i limiti stampati: la mappatura del potenziometro dipende anche dalla semibanda.

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
- [📖 Guida associata](../../04-Soglia-regolabile-e-isteresi.md)
