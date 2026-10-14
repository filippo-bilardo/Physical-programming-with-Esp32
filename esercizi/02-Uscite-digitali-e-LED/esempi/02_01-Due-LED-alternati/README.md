# Due LED alternati

## Obiettivo e prerequisiti

Gestire due uscite indipendenti e prevedere l’effetto dell’ordine delle istruzioni. Leggi prima la [guida associata](../../02-GPIO-e-uscite-digitali.md) e prepara gli ambienti seguendo la [guida di installazione](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Codice C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Codice MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: framework Arduino-ESP32, API di base; nessuna libreria esterna.
- MicroPython: firmware ESP32_GENERIC per ESP32-WROOM; moduli `machine` e `time` inclusi nel firmware, senza installazioni con pip.
- Configurazione prevista: Arduino IDE 2.x con core ESP32 3.x; MicroPython stabile 1.24 o successivo. Sono riferimenti di compatibilità, non versioni dichiarate collaudate. Registra le versioni effettivamente usate nella tua prova.

## Materiali e collegamenti

ESP32 DevKit con ESP32-WROOM-32, cavo USB dati; 2 LED (rosso, giallo), 2 resistenze da 330 Ω, breadboard e cavetti.

Monta a scheda scollegata. I numeri sono numeri GPIO. Ogni LED ha la propria resistenza e il proprio catodo a massa; non collegare un LED direttamente al GPIO. In un LED comune non tagliato il terminale lungo è l’anodo; verifica comunque il componente. Usa solo livelli logici a 3,3 V.

| Da | A |
| --- | --- |
| GPIO 18 | Resistenza R1 da 330 Ω → anodo A del LED 1 |
| Catodo C del LED 1 | GND |
| GPIO 19 | Resistenza R2 da 330 Ω → anodo A del LED 2 |
| Catodo C del LED 2 | GND |

## Esecuzione in Wokwi

1. Apri il modello Arduino ESP32 oppure MicroPython ESP32 dalla [pagina ufficiale](https://docs.wokwi.com/guides/esp32).
2. Per C++ copia tutto `cpp/cpp.ino` nel file `sketch.ino` del modello, sostituendone il contenuto. Per MicroPython sostituisci `main.py` con il file fornito.
3. Sostituisci anche `diagram.json` con quello della stessa sottocartella. Non aggiungere un secondo file `.ino` contenente lo stesso codice.
4. Avvia la simulazione e osserva il monitor seriale. Non servono librerie aggiuntive né `libraries.txt`.
5. Segui le prove elencate sotto. Salva una copia del progetto se vuoi conservare le modifiche.

## Esecuzione su scheda reale

1. Verifica i collegamenti della tabella e collega l’USB solo dopo il controllo del circuito.
2. **C++:** apri `cpp/cpp.ino` in Arduino IDE, seleziona la scheda appropriata (per una DevKit WROOM generica: ESP32 Dev Module) e la porta. Verifica, carica e apri il monitor seriale a **115200 baud**. La cartella `cpp` e lo sketch `cpp.ino` devono mantenere lo stesso nome base.
3. **MicroPython:** dopo l’installazione del firmware, seleziona in Thonny l’interprete MicroPython (ESP32) e la porta. Salva il file sulla scheda come `/main.py`; riavvia per eseguirlo. Interrompi con Ctrl+C per tornare alla console.
4. Chiudi gli altri programmi che usano la porta seriale. Per cambiare ambiente salva prima i file: il caricamento di uno sketch Arduino sostituisce il firmware MicroPython.

## Prova guidata e comportamento atteso

1. Osserva l’alternanza e i messaggi A/B.
2. Verifica che i catodi condividano GND e non una resistenza.
3. Porta `STEP_MS` a 1000 e misura la durata del ciclo A–B.

**Risultato atteso:** A acceso per circa 500 ms, poi B acceso per circa 500 ms. Nessuna fase intenzionale con entrambi accesi; ciclo nominale 1 s.

## Come funziona e confronto dei linguaggi

Ogni LED ha un proprio ramo e una propria resistenza. Prima si spegne il LED precedente, poi si accende il successivo: le scritture sono sequenziali, quindi può esserci un brevissimo intervallo con entrambi spenti.

In C++ `setup()` configura le risorse una volta e il framework richiama `loop()` ripetutamente; i tipi sono dichiarati e i blocchi usano parentesi graffe. In MicroPython la configurazione precede `while True`, i blocchi dipendono dall’indentazione e i GPIO sono oggetti `Pin`. Le uscite logiche equivalenti sono HIGH/LOW e 1/0; le attese qui sono sempre espresse in millisecondi.

## Modifica da provare

Aggiungi una pausa di 200 ms con entrambi spenti fra le fasi. Il ciclo completo deve diventare circa 1,4 s.

## Debug

Se la console procede ma il LED non risponde, controlla anodo/catodo, GND e numero del GPIO. Se non compare nulla, controlla porta, velocità e ambiente selezionato; riavvia dopo aver aperto la console. Se la scheda si riavvia continuamente, scollega l’alimentazione e ricontrolla il circuito. Un programma eseguito con Python sul computer non dispone del modulo `machine`: deve girare su MicroPython ESP32 o nel relativo simulatore.

## Stato delle verifiche

Per entrambe le versioni: **Wokwi da verificare; scheda reale da verificare**. I controlli locali e i loro limiti sono descritti nel [rapporto delle verifiche](../../../VERIFICHE.md). I circuiti forniti sono predisposti per la simulazione, non dichiarati collaudati.

## Navigazione del corso

- [📑 Indice generale](../../../../README.md)
- [📂 Indice dell’esercitazione](../../README.md)
- [📖 Guida associata](../../02-GPIO-e-uscite-digitali.md)
