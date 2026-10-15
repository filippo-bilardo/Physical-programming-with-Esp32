# Lampeggio senza lunghe attese

## Obiettivo e prerequisiti

Conservare il lampeggio da 1 s per fase mentre il giallo segue continuamente il pulsante. Usa lo stesso circuito dell'esempio bloccante. Leggi la [guida associata](../../01-Attese-e-tempo-trascorso.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Programma C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Programma MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: core Arduino-ESP32 e API Arduino di base, nessuna libreria esterna.
- MicroPython: firmware per ESP32-WROOM-32, moduli `machine` e `time` inclusi; nessun pacchetto pip.

## Materiali e collegamenti

ESP32 DOIT ESP32 DEVKIT V1 o DevKit equivalente con ESP32-WROOM-32, cavo USB dati, 2 LED e **2 resistenze da 220 Ω**, breadboard e cavetti. Un pulsante normalmente aperto.

Monta a scheda scollegata. I numeri sono GPIO, non posizioni fisiche dei terminali. Ogni LED ha una propria resistenza; usa logica a 3,3 V e massa comune.

| Da | A |
| --- | --- |
| GPIO 18 | R1 da 220 Ω → anodo LED rosso |
| Catodo LED rosso | GND |
| GPIO 19 | R2 da 220 Ω → anodo LED giallo |
| Catodo LED giallo | GND |
| GPIO 23, `INPUT_PULLUP` / `Pin.PULL_UP` | Contatto `1.l` del pulsante |
| Contatto `2.l` del pulsante | GND |

Il pulsante è attivo basso: rilasciato legge 1, premuto legge 0. In Wokwi `1.l` e `1.r` sono lo stesso contatto, `2.l` e `2.r` l'altro; usa un terminale di ciascuna coppia. Su hardware identifica i contatti a circuito scollegato. Premi con il mouse oppure con Q, dando il fuoco al circuito. I rimbalzi restano attivi; consulta il [riferimento del pulsante Wokwi](https://docs.wokwi.com/parts/wokwi-pushbutton).

## Esecuzione in Wokwi

1. Apri un progetto Arduino ESP32 o MicroPython ESP32 dalla [guida ufficiale](https://docs.wokwi.com/guides/esp32).
2. Per C++ sostituisci `sketch.ino` con il contenuto di `cpp/cpp.ino`; per MicroPython sostituisci `main.py` con quello fornito.
3. Sostituisci `diagram.json` con quello della stessa sottocartella. Non mantenere due sketch con le stesse funzioni.
4. Avvia e segui la prova guidata. Non servono `libraries.txt` o moduli aggiuntivi.

## Esecuzione su scheda reale

1. Controlla collegamenti, resistenze e polarità prima di collegare l'USB.
2. **C++:** apri `cpp/cpp.ino` in Arduino IDE; seleziona **DOIT ESP32 DEVKIT V1** per la scheda di riferimento, porta e core ESP32 installato. Compila e carica mantenendo lo sketch nella cartella `cpp`. L'esempio non stampa sulla seriale: osserva i LED.
3. **MicroPython:** seleziona l'interprete ESP32 e la porta in Thonny; salva il programma come `/main.py` sulla scheda e riavvia. Ctrl+C interrompe il ciclo e restituisce la console.
4. Registra le versioni effettive di core o firmware. I programmi usano API di base; la compilazione sul computer con sostituti delle API non equivale a quella per ESP32.

## Prova guidata e risultato atteso

1. Avvia con il pulsante rilasciato: entrambi i LED partono spenti.
2. Il rosso si accende dopo circa 1 s, si spegne dopo circa 2 s e continua.
3. Premi per almeno 100 ms durante entrambe le fasi del rosso: il giallo segue la pressione senza aspettare il cambio del rosso.
4. Mantieni premuto per 3 s e rilascia: il rosso continua a lampeggiare.

La fase iniziale è diversa dall'esempio bloccante: qui il rosso parte spento. Il periodo completo resta nominalmente di 2 s. Il giallo mostra il livello grezzo del pulsante; non conta eventi e non applica debounce.

## Come funziona e confronto dei linguaggi

Ogni giro legge l'ingresso e controlla il tempo trascorso dal precedente cambio del rosso. C++ usa sottrazione unsigned; MicroPython usa `ticks_diff()`. Il riferimento viene aggiornato al momento del cambio, senza recuperare i cambi persi. La pausa di 1 ms per giro non è un'attesa dell'intero secondo; il polling non ha una latenza rigidamente garantita.

## Modifica autonoma

Porta `INTERVAL_MS` a 200: il periodo completo del rosso passa a 400 ms. Il comportamento del pulsante rimane indipendente.

## Debug e stato delle prove

Se il LED non si accende, controlla GPIO, polarità, resistenza e GND. Se il pulsante non cambia livello, controlla i due contatti e il pull-up; non collegarlo a 5 V. Non eseguire `main.py` con Python del computer: richiede MicroPython ESP32.

**Wokwi e scheda reale: da verificare separatamente per C++ e MicroPython.** Un controllo della logica con GPIO e tempo simulati sul computer non prova montaggio o precisione temporale sul dispositivo.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Risultato osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell'esercitazione](../../README.md)
- [📖 Guida associata](../../01-Attese-e-tempo-trascorso.md)
