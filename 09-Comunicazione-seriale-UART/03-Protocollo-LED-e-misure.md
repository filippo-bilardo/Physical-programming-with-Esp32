# Protocollo testuale per LED e misure

## Obiettivi e prerequisiti

Prerequisiti: guide 01–02 e ADC dell’esercitazione 05. Definirai comandi, risposte, unità e limiti di un semplice dialogo richiesta/risposta, con un client Python sul PC.

## Teoria e collegamento con l'architettura

### Una grammatica condivisa

Il [progetto completo](esempi/03_01-Protocollo-LED-e-ADC/README.md) riusa il ricevitore a righe e aggiunge un potenziometro da 10 kΩ su GPIO 34. Il LED resta sul GPIO 18 con 220 Ω. Non serve I²C o SPI per questa attività.

| Richiesta, seguita da LF | Risposta, seguita da LF | Effetto |
| --- | --- | --- |
| PING | PONG | Verifica del dialogo |
| LED 0 | OK LED 0 | Spegne il LED |
| LED 1 | OK LED 1 | Accende il LED |
| ADC? | ADC=n | Una nuova conversione ADC |
| GET | STATE LED=b ADC=n | Stato LED e una nuova conversione ADC |
| Altro comando valido come riga ASCII | ERR COMMAND | Nessuna modifica |

All'avvio compare una sola riga spontanea `READY`. Non è una risposta a PING. Le righe vuote non producono risposte; i guasti di sintassi del buffer producono gli errori della guida 02.

La lettura n è un codice **0–4095**, non volt. C++ imposta 12 bit; MicroPython riscala `read_u16()` con divisione intera per 16. Non viene riutilizzato un valore memorizzato: GET e ADC? acquisiscono al momento dell'esecuzione del comando. Due richieste successive possono quindi restituire valori diversi.

### Richiesta e risposta, senza carico continuo

Il client invia una riga e aspetta la risposta prima di proseguire. Le scritture UART possono bloccare o risultare incomplete se i buffer si saturano; il firmware didattico non implementa coda di ritrasmissione, numeri di sequenza, CRC o controllo di flusso. Il suo contratto è l'uso interattivo, non un flusso continuo di comandi.

Il programma legge al massimo 32 byte per giro e non aggiunge telemetria periodica sulla stessa UART. Questo rende chiaro a quale richiesta appartiene una risposta. Il timeout di due secondi del client PC è distinto dal timeout fra byte della riga sul dispositivo.

### Il client gira sul computer

`client_uart.py` usa Python del PC e il pacchetto pySerial. Non va copiato sulla scheda MicroPython. Il client mostra PING, accensione LED, GET, ADC? e spegnimento; scarta un eventuale READY iniziale e si ferma se manca una risposta completa. L'adattatore USB-UART a 3,3 V deve essere collegato a UART2; la porta USB integrata della DOIT resta UART0 per upload/REPL.

## Esempi commentati

```cpp
const int raw = analogRead(34);
snprintf(response, sizeof(response), "ADC=%d", raw);
sendLine(response);
```

```python
raw = adc.read_u16() // 16
send_line('ADC=%d' % raw)
```

Dialogo di esempio, con un codice ADC illustrativo:

```text
> PING
PONG
> LED 1
OK LED 1
> GET
STATE LED=1 ADC=2048
> ADC?
ADC=2048
> LED 0
OK LED 0
```

Le frecce `>` indicano il verso nella relazione, non fanno parte dei byte da inviare.

## Buone pratiche e debug

- Chiudi gli altri terminali che occupano la stessa porta del client.
- Verifica prima PING, poi comandi LED e infine misure ADC.
- Riporta il codice e la configurazione ADC; non etichettarlo come tensione calibrata.
- Se il client termina per timeout, il LED conserva l’ultimo comando ricevuto: usa il terminale o riavvia per impostare uno stato noto.
- Un protocollo che modifica uscite reali richiederebbe regole di guasto specifiche; qui il carico è un LED didattico.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Quando viene acquisito il valore ADC nella risposta a GET?**

   - A. Solo all’avvio.
   - B. Durante l’esecuzione di quel comando.
   - C. Ogni volta che il PC stampa una riga.
   - D. Non viene mai acquisito.

2. **Dove si esegue client_uart.py?**

   - A. Dentro il modulo I²C.
   - B. Sul display.
   - C. Sul PC con Python e pySerial.
   - D. Nel bootloader ESP32.

3. **Che cosa significa ADC=2048?**

   - A. 2048 volt.
   - B. Un codice nella scala 0–4095 configurata.
   - C. Una temperatura calibrata.
   - D. Il numero di byte nel buffer.

## Esercizi pratici

1. **Consegna:** Prova il dialogo completo nel monitor Wokwi, con LF.

   **Risultato atteso:** Ogni richiesta nota produce una risposta; GET riflette l’ultimo stato LED e il potenziometro corrente.

2. **Consegna:** Sposta il potenziometro fra due richieste ADC?.

   **Risultato atteso:** La misura successiva cambia in base al nuovo campione; il LED non cambia.

3. **Consegna:** Su hardware installa pySerial in un ambiente virtuale ed esegui il client sulla porta dell’adattatore.

   **Risultato atteso:** Cinque richieste con risposte complete; manca una risposta o un terminatore: il client segnala timeout invece di attendere indefinitamente.

## Soluzioni dell'autovalutazione

1. **B.** GET richiede una conversione nuova e non una telemetria memorizzata.
2. **C.** Il firmware MicroPython è invece nella sottocartella micropython.
3. **B.** Scala e unità del protocollo sono dichiarate e non vanno inventate dal client.

## Riferimenti

- [Espressif: seriale hardware](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/serial.html).
- [pySerial: API del client PC](https://pyserial.readthedocs.io/en/latest/pyserial_api.html).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente disponibile](02-Righe-buffer-e-timeout.md)
- La guida della successiva esercitazione numerica è ancora pianificata; consulta l’indice per i materiali disponibili.
