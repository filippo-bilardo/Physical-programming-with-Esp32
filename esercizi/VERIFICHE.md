# Verifiche delle esercitazioni 01–03

Questo documento distingue i controlli del materiale dalle prove sul dispositivo. Le verifiche sul computer usano sostituti delle API GPIO e del tempo: non simulano la CPU ESP32, il firmware MicroPython, il comportamento elettrico o Wokwi.

## Eseguire i controlli locali

Prerequisiti: **Python 3.10 o successivo** e **g++ con supporto C++17**, disponibili nel PATH. Non sono richiesti pacchetti pip. Su un computer Debian/Ubuntu gli strumenti sono forniti dai pacchetti `python3` e `g++`; usa il gestore pacchetti del tuo sistema se mancano.

Dalla cartella principale del corso:

```bash
python3 strumenti/verifica_esempi.py
```

Lo [script di verifica](../strumenti/verifica_esempi.py) legge soltanto README e materiali delle esercitazioni. Non analizza la cartella `tmp`. I file di compilazione vengono creati in una directory temporanea del sistema e rimossi al termine; gli esempi non vengono modificati.

## Controlli previsti

- Esistenza dei collegamenti relativi nei materiali disponibili e chiusura dei blocchi Markdown. I tredici link del README alle esercitazioni future sono riconosciuti come pianificati, non come cartelle esistenti.
- Sintassi Python dei dieci `main.py`; nome dello sketch C++ coerente con la cartella.
- Lettura dei venti JSON, identificatori univoci, nomi dei pin usati, rami LED con resistenza e collegamenti del pulsante. I circuiti delle due versioni devono coincidere.
- Compilazione dei dieci sketch con g++ e API Arduino sostituite, con avvisi trattati come errori. Questo controllo **non equivale alla compilazione con il core Arduino-ESP32**.
- Esecuzione dei sorgenti Python con API `machine` e `time` sostituite; confronto di uscite e messaggi con le versioni C++ su sequenze di ingresso note.

I nomi dei pin della DevKit simulata sono confrontati con quelli del [componente ufficiale Wokwi](https://github.com/wokwi/wokwi-elements/blob/main/src/esp32-devkit-v1-element.ts); il controllo locale usa soltanto i pin impiegati in questi esempi, non un validatore generale di tutti i componenti Wokwi.

## Scenari comportamentali

| Esempio | Prova locale |
| --- | --- |
| LED lampeggiante | Alternanza 500/500 ms e livello atteso in più istanti |
| Variazione temporizzazione | Alternanza 200/800 ms e periodo nominale |
| LED e resistenza | Permanenza del comando alto |
| Due LED alternati | Combinazioni A/B nel tempo |
| Sequenza tre LED | Ordine 0 → 1 → 2 e ritorno all’inizio |
| Drive strength | Ordine dei quattro livelli, cambio con LED spento, tempi 5 s/1 s e ripartenza; nessun modello elettrico |
| Pull-up / pull-down | Livello LED coerente con pressioni e rilasci, con polarità opposte |
| Rilevamento del fronte | Due pressioni ideali; sovraconteggio su una sequenza di rimbalzi controllata |
| Debounce | Pressioni stabili; rimbalzi alla pressione e al rilascio; ritorno a zero dei tick; impulso di 19 ms scartato; pressione mantenuta; tasto premuto all’avvio; rilascio troppo breve per riarmare il comando |

Per il drive strength i sostituti delle API registrano il livello richiesto e verificano che il cambio avvenga a LED spento. Non modellano tensione, corrente o resistenza interna del GPIO. Le guide di installazione di IDE e driver sono state controllate come documentazione; non sono state eseguite installazioni sui sistemi operativi descritti.

Il modello temporale usa istruzioni istantanee e attese esatte: controlla la logica, non la precisione temporale reale. Per MicroPython si usa un contatore circolare artificiale di 256 tick; per C++ si attraversa il limite di `unsigned long` del compilatore del computer, che può avere dimensione diversa da quella su ESP32. Il collaudo sul target rimane necessario.

## Esito registrato

Verifica locale completata il **14 ottobre 2026**, con **Python 3.10.12** e **g++ 11.4.0** su Linux:

| Controllo | Esito |
| --- | --- |
| Collegamenti e blocchi di codice in 28 documenti | Superato; 13 collegamenti a cartelle future dichiarati separatamente |
| Struttura e collegamenti dei 20 diagrammi | Superato |
| Sintassi dei 10 programmi Python | Superato |
| Compilazione dei 10 sketch con g++ e API sostituite | Superato, senza avvisi |
| 17 scenari per ciascuno dei due linguaggi, 34 prove complessive | Superato; uscite e messaggi delle due implementazioni coincidono nel modello |
| Compilazione con core Arduino-ESP32 | Da eseguire |
| Esecuzione nel runtime MicroPython ESP32 | Da eseguire |
| Simulazione Wokwi e collaudo su scheda reale | Da eseguire per entrambe le versioni |

Nell’ambiente di preparazione è disponibile Arduino CLI, ma non il core ESP32; il tentativo di scaricare il relativo indice è stato impedito dalle restrizioni di rete. Non viene quindi dichiarata una compilazione per il target. Non sono state eseguite prove elettriche o nel simulatore Wokwi.

## Procedura di collaudo da completare

1. Registra data, modello di scheda, versione Arduino IDE/core oppure firmware MicroPython e dipendenze effettive. Gli esempi non richiedono librerie esterne.
2. Per ogni esempio, segui il README e prova entrambe le versioni in Wokwi usando i file forniti. Confronta circuito, console e comportamento atteso.
3. Compila gli sketch per la scheda corretta in Arduino IDE e annota l’esito; esegui i programmi MicroPython sul firmware selezionato.
4. Su hardware controlla i cablaggi a circuito spento; poi verifica LED, resistenze e pulsanti. Confronta le prove del README con quelle osservate.
5. Per il debounce prova pressioni/rilasci di almeno 100 ms, pressione mantenuta per 2 s e avvio con tasto già premuto. Per l’esempio senza filtro, considera possibili i sovraconteggi senza pretendere che avvengano a ogni pressione.
6. Aggiungi l’esito alla tabella seguente, mantenendo distinti ambiente e linguaggio. Una compilazione riuscita non va registrata come prova funzionale conclusa.

| Data | Esempio | Linguaggio | Ambiente e versioni | Procedura | Atteso | Osservato | Esito |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Da compilare durante il collaudo | — | — | — | — | — | — | Da verificare |

## Navigazione

- [Indice generale](../README.md)
- [01 · Introduzione](01-Introduzione-ESP32/README.md)
- [02 · Uscite digitali](02-Uscite-digitali-e-LED/README.md)
- [03 · Ingressi digitali](03-Ingressi-digitali-e-pulsanti/README.md)
