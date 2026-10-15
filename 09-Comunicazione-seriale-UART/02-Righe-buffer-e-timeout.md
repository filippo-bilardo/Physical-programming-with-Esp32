# Righe, buffer e timeout

## Obiettivi e prerequisiti

Prerequisiti: guida 01, stringhe e stato in RAM. Imparerai a ricomporre un comando arrivato in più parti, limitare l’occupazione del buffer e riprendere dopo una riga errata.

## Teoria e collegamento con l'architettura

### I byte non arrivano necessariamente tutti insieme

Una scrittura del terminale può essere letta in più parti; due scritture possono essere già accodate nello stesso buffer. Non usare una singola `read()` come se fosse automaticamente un messaggio completo. Il [ricevitore a righe](esempi/02_01-Comandi-LED/README.md) accumula byte fino a **LF**, ASCII 10, rappresentato da `\n`.

Accettiamo anche un unico CR immediatamente prima di LF, cioè CRLF. Un CR all'interno della riga è un errore, non uno spazio da cancellare. Sono ammessi caratteri ASCII stampabili, con comandi maiuscoli e spazi esatti. Le righe vuote vengono ignorate.

### Un buffer con un limite dichiarato

La riga può contenere al massimo **32 byte prima di LF**, incluso l'eventuale CR. Il C++ riserva 33 byte per aggiungere il terminatore di stringa NUL, che non viene trasmesso. MicroPython mantiene un bytearray della stessa lunghezza massima. Non si accumulano stringhe senza limite.

La CPU riceve in polling al massimo 32 byte per giro; la periferica UART e i buffer del driver possono conservare altri byte fino alla loro capacità. Il limite applicativo non impedisce un overflow del driver se il mittente trasmette più velocemente di quanto il sistema riesca a elaborare.

| Caso | Risposta al successivo LF | Ripresa |
| --- | --- | --- |
| Riga valida | Risposta al comando | Riga successiva |
| Più di 32 byte prima di LF | ERR LONG | Dopo quel LF |
| Byte non ASCII stampabile, escluso CR finale | ERR ASCII | Dopo quel LF |
| Riga parziale senza byte per almeno 1000 ms | ERR TIMEOUT | Dopo il LF che conclude la riga scartata |

### Perché scartare fino al terminatore

Dopo un errore, il ricevitore non esegue la coda come un altro comando. Se una riga troppo lunga termina con `LED 1`, quel suffisso non deve accendere il LED. Il primo errore rilevato resta associato alla riga fino a LF; lì viene inviata una sola risposta e il parser si ripristina.

Il timeout misura l'inattività fra byte di una riga parziale. Non si usa un lungo delay di un secondo. Allo scadere il parser marca la riga da scartare; **l'errore è trasmesso quando arriva LF**, non appena scade il tempo. Se non arriva mai LF, non arriva neppure la risposta e il ricevitore rimane in scarto. Per risincronizzare invia LF, attendi l'errore e poi invia un nuovo comando.

I file locali `line_receiver.h` e `line_receiver.py` implementano queste regole. Puoi iniziare dal main, che riceve soltanto righe complete già validate.

## Esempi commentati

```cpp
// Il parser richiama handleCommand soltanto per una riga valida e completa.
receiver.poll(millis(), handleCommand);
```

```python
receiver.poll(ticks_ms())
```

Esempio di comando nel programma completo:

```python
if line == 'LED 1':
    led.value(1)
    send_line('OK LED 1')
```

`LED 1` seguito da LF accende; `led 1`, `LED  1` o `LED 1 ` producono `ERR COMMAND`. Un messaggio errato non modifica lo stato del LED.

## Buone pratiche e debug

- Configura il monitor Wokwi con newline lf oppure crlf; con solo cr manca il terminatore richiesto.
- Per provare il timeout imposta temporaneamente newline none, invia un frammento, attendi oltre un secondo e poi invia LF.
- Non usare strip() indiscriminatamente se vuoi mantenere una grammatica esatta.
- Invia un comando e aspetta la risposta prima del successivo nelle prove reali: non è un test di carico.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Una read() restituisce soltanto LE. Che cosa deve fare il parser?**

   - A. Eseguire subito LED 1.
   - B. Scartare sempre ogni frammento.
   - C. Conservare i byte e attendere il terminatore.
   - D. Riavviare la UART.

2. **Dopo overflow, perché si scarta fino a LF?**

   - A. Per evitare che un suffisso diventi un comando valido.
   - B. Per aumentare la RAM.
   - C. Per cambiare baud rate.
   - D. Per abilitare la REPL.

3. **Quando arriva ERR TIMEOUT nel ricevitore fornito?**

   - A. Sempre all’avvio.
   - B. Al LF che conclude la riga marcata dopo almeno un secondo di inattività.
   - C. Prima del primo byte.
   - D. Esattamente ogni secondo anche senza dati.

## Esercizi pratici

1. **Consegna:** Invia LED 1 e GET, prima con LF e poi con CRLF.

   **Risultato atteso:** OK LED 1 e LED=1 in entrambi i casi; il LED cambia solo al completamento del comando.

2. **Consegna:** Invia almeno 33 caratteri seguiti da LED 1 sulla stessa riga, poi LF; invia GET su una nuova riga.

   **Risultato atteso:** ERR LONG, poi stato del LED invariato. Il suffisso della riga lunga non viene eseguito.

3. **Consegna:** Invia LED senza terminatore, attendi più di 1 s, completa con 1 e LF, quindi invia LED 1 su una riga nuova.

   **Risultato atteso:** Prima ERR TIMEOUT con stato invariato, poi OK LED 1. Registra la configurazione dei terminatori.

## Soluzioni dell'autovalutazione

1. **C.** Il confine dei messaggi è LF, non il confine della lettura.
2. **A.** Il recupero deve mantenere la separazione fra righe.
3. **B.** Il timeout invalida la riga; il terminatore produce la risposta e risincronizza.

## Riferimenti

- [MicroPython: letture e scritture UART](https://docs.micropython.org/en/latest/library/machine.UART.html).
- [Wokwi: terminatori del monitor](https://docs.wokwi.com/guides/serial-monitor).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente disponibile](01-UART-collegamenti-e-loopback.md)
- [➡️ Guida successiva](03-Protocollo-LED-e-misure.md)
