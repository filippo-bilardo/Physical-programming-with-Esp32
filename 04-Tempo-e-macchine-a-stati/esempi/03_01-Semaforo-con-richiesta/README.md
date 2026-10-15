# Semaforo con richiesta pedonale

## Obiettivo e prerequisiti

Integrare quattro stati temporizzati, una prenotazione e un pulsante con debounce di 30 ms. È un modello didattico: LED verde pedoni spento significa che non si attraversa. Leggi la [guida associata](../../03-Macchine-a-stati-e-semaforo.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Programma C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Programma MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: core Arduino-ESP32 e API Arduino di base, nessuna libreria esterna.
- MicroPython: firmware per ESP32-WROOM-32, moduli `machine` e `time` inclusi; nessun pacchetto pip.

## Materiali e collegamenti

ESP32 DOIT ESP32 DEVKIT V1 o DevKit equivalente con ESP32-WROOM-32, cavo USB dati, 4 LED e **4 resistenze da 220 Ω**, breadboard e cavetti. Un pulsante normalmente aperto.

Monta a scheda scollegata. I numeri sono GPIO, non posizioni fisiche dei terminali. Ogni LED ha una propria resistenza; usa logica a 3,3 V e massa comune.

| Da | A |
| --- | --- |
| GPIO 18 | R1 da 220 Ω → anodo LED rosso auto |
| Catodo LED rosso auto | GND |
| GPIO 19 | R2 da 220 Ω → anodo LED giallo auto |
| Catodo LED giallo auto | GND |
| GPIO 21 | R3 da 220 Ω → anodo LED verde auto |
| Catodo LED verde auto | GND |
| GPIO 22 | R4 da 220 Ω → anodo LED verde pedoni |
| Catodo LED verde pedoni | GND |
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
2. **C++:** apri `cpp/cpp.ino` in Arduino IDE; seleziona **DOIT ESP32 DEVKIT V1** per la scheda di riferimento, porta e core ESP32 installato. Compila e carica mantenendo lo sketch nella cartella `cpp`. Apri il monitor seriale a **115200 baud**.
3. **MicroPython:** seleziona l'interprete ESP32 e la porta in Thonny; salva il programma come `/main.py` sulla scheda e riavvia. Ctrl+C interrompe il ciclo e restituisce la console.
4. Registra le versioni effettive di core o firmware. I programmi usano API di base; la compilazione sul computer con sostituti delle API non equivale a quella per ESP32.

## Prova guidata e risultato atteso

1. Avvia senza premere e attendi almeno 8 s: resta `AUTO_VERDE`.
2. Riavvia, premi nel primo secondo per almeno 100 ms e rilascia per almeno 100 ms. Compare `Richiesta accettata`, ma il giallo arriva soltanto al termine dei 5 s minimi di verde.
3. Osserva `AUTO_GIALLO` per 2 s, `PEDONI_VERDE` per 4 s, `PAUSA_ROSSA` per 1 s, quindi `AUTO_VERDE`.
4. Attendi oltre i 5 s del nuovo verde e premi: il giallo inizia alla pressione stabilizzata, senza aspettare altri 5 s.
5. Ripeti con più pressioni nel verde: al massimo una richiesta rimane prenotata; il tempo non viene prolungato.
6. Premi e rilascia durante giallo o attraversamento: non viene prenotato un secondo ciclo.
7. Mantieni premuto dalla prima richiesta fino al ritorno al verde: non parte un secondo ciclo. Rilascia stabilmente e premi di nuovo per generarlo.
8. Riavvia con il tasto già premuto: nessuna richiesta fino al rilascio stabile e a una nuova pressione.
9. Prova un impulso sotto 30 ms e una sequenza di rimbalzi: il filtro richiede un nuovo livello stabile per 30 ms, sia alla pressione sia al rilascio.

Le durate decorrono dall'ingresso nello stato. I messaggi compaiono soltanto alle transizioni e alla prima prenotazione. A parità di ingressi, i due programmi seguono le stesse regole.

| Stato | Uscite accese | Condizione di uscita |
| --- | --- | --- |
| `AUTO_VERDE` | Verde auto | Richiesta e almeno 5000 ms nel verde |
| `AUTO_GIALLO` | Giallo auto | 2000 ms |
| `PEDONI_VERDE` | Rosso auto e verde pedoni | 4000 ms |
| `PAUSA_ROSSA` | Rosso auto | 1000 ms |

Il verde può durare indefinitamente senza richieste. In ogni stato il programma continua a leggere il pulsante; le pressioni fuori dal verde vengono ignorate, non accodate.

## Come funziona e confronto dei linguaggi

C++ rappresenta lo stato con `enum` e valuta un `switch`; MicroPython usa costanti stringa e `if` / `elif`. `enterState()` / `enter_state()` aggiorna uscite e riferimento temporale. Il filtro funziona in tutte le fasi. Le nuove richieste sono accettate soltanto in verde; quando parte il giallo la prenotazione viene consumata. `greenReady` / `green_ready` memorizza il raggiungimento dei 5 s, così una lunga permanenza in verde non richiede di confrontare tick troppo distanti. Lo stato è in RAM e non sopravvive a un riavvio.

## Modifica autonoma

Porta `PEDESTRIAN_MS` da 4000 a 6000. Con una richiesta nel primo secondo, il ritorno al verde avviene nominalmente a 14 s dall'avvio, invece che a 12 s. Aggiorna anche la tabella temporale nella tua relazione.

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
- [📖 Guida associata](../../03-Macchine-a-stati-e-semaforo.md)
