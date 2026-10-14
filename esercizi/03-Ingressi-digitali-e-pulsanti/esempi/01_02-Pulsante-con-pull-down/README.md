# Pulsante con pull-down esterno

## Obiettivo e prerequisiti

Confrontare il pull-up interno con un pull-down esterno da 10 kΩ. Leggi prima la [guida associata](../../01-Ingressi-pull-up-e-pull-down.md) e prepara gli ambienti seguendo la [guida di installazione](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Codice C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Codice MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++: framework Arduino-ESP32, API di base; nessuna libreria esterna.
- MicroPython: firmware ESP32_GENERIC per ESP32-WROOM; moduli `machine` e `time` inclusi nel firmware, senza installazioni con pip.
- Configurazione prevista: Arduino IDE 2.x con core ESP32 3.x; MicroPython stabile 1.24 o successivo. Sono riferimenti di compatibilità, non versioni dichiarate collaudate. Registra le versioni effettivamente usate nella tua prova.

## Materiali e collegamenti

ESP32 DevKit con ESP32-WROOM-32, cavo USB dati; 1 LED (rosso), 1 resistenza da 330 Ω, breadboard e cavetti. Un pulsante normalmente aperto a quattro terminali. Una resistenza aggiuntiva da 10 kΩ.

Monta a scheda scollegata. I numeri sono numeri GPIO. Ogni LED ha la propria resistenza e il proprio catodo a massa; non collegare un LED direttamente al GPIO. In un LED comune non tagliato il terminale lungo è l’anodo; verifica comunque il componente. Usa solo livelli logici a 3,3 V.

| Da | A |
| --- | --- |
| GPIO 18 | Resistenza R1 da 330 Ω → anodo A del LED 1 |
| Catodo C del LED 1 | GND |
| GPIO 23 | Contatto 1 del pulsante (`1.l` in Wokwi) |
| Contatto 2 del pulsante (`2.l` in Wokwi) | 3V3 |
| Nodo GPIO 23 / contatto 1 | Resistenza da 10 kΩ → GND |

In Wokwi `1.l` e `1.r` appartengono allo stesso contatto; `2.l` e `2.r` all’altro. La pressione unisce i due contatti. Sulla scheda reale identifica le coppie con il multimetro a circuito scollegato: non affidarti alla sola disposizione visiva. Usa il tasto Q con il circuito Wokwi a fuoco, oppure il mouse.

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

1. Togli alimentazione e realizza la nuova tabella dei collegamenti.
2. Avvia: LED spento a riposo.
3. Premi e rilascia; confronta il comportamento con il pull-up.

**Risultato atteso:** Lo stesso comportamento visibile dell’esempio pull-up, ma lettura 0 a riposo e 1 durante la pressione. La corrente nella resistenza mentre si preme è circa 0,33 mA.

## Come funziona e confronto dei linguaggi

La resistenza da 10 kΩ porta l’ingresso a GND quando il contatto è aperto. La pressione collega il nodo a 3,3 V; `INPUT` / `Pin.IN` non abilita resistenze interne. Il confronto diventa HIGH / 1. Non basta modificare il codice: cambia anche il circuito.

In C++ `setup()` configura le risorse una volta e il framework richiama `loop()` ripetutamente; i tipi sono dichiarati e i blocchi usano parentesi graffe. In MicroPython la configurazione precede `while True`, i blocchi dipendono dall’indentazione e i GPIO sono oggetti `Pin`. Le uscite logiche equivalenti sono HIGH/LOW e 1/0; le attese qui sono sempre espresse in millisecondi.

## Modifica da provare

Aggiungi la stampa del valore numerico dell’ingresso e costruisci una tabella riposo/pressione per entrambi i circuiti.

## Debug

Se la console procede ma il LED non risponde, controlla anodo/catodo, GND e numero del GPIO. Se non compare nulla, controlla porta, velocità e ambiente selezionato; riavvia dopo aver aperto la console. Se la scheda si riavvia continuamente, scollega l’alimentazione e ricontrolla il circuito. Un programma eseguito con Python sul computer non dispone del modulo `machine`: deve girare su MicroPython ESP32 o nel relativo simulatore.

## Stato delle verifiche

Per entrambe le versioni: **Wokwi da verificare; scheda reale da verificare**. I controlli locali e i loro limiti sono descritti nel [rapporto delle verifiche](../../../VERIFICHE.md). I circuiti forniti sono predisposti per la simulazione, non dichiarati collaudati.

## Navigazione del corso

- [📑 Indice generale](../../../../README.md)
- [📂 Indice dell’esercitazione](../../README.md)
- [📖 Guida associata](../../01-Ingressi-pull-up-e-pull-down.md)
