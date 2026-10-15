# Temperatura, soglia e gestione degli errori

## Obiettivi e prerequisiti

Prerequisiti: guide 01–03, ADC e isteresi dell’esercitazione 05. Integrerai sensore, display, potenziometro e LED mantenendo distinti dati validi ed errori.

## Teoria e collegamento con l'architettura

### Due dispositivi sullo stesso bus

Il [progetto completo](esempi/04_01-Temperatura-soglia-e-display/README.md) legge il BMP180 a 0x77 e aggiorna l'OLED a 0x3C. Il potenziometro va all'ADC1 sul GPIO 34, il LED al GPIO 18 con resistenza da 220 Ω. SDA e SCL rimangono sui GPIO 21 e 22.

Il centro della soglia è espresso in decimi di °C:

```text
soglia_dC = 150 + codice_ADC × 200 / 4095
```

La divisione è intera: la regolazione copre 15,0–35,0 °C. L'ADC ha gli stessi limiti studiati nella 05: la manopola non è una misura calibrata di posizione e può saturare vicino agli estremi.

### Stato dell’allarme

La semibanda è di 5 decimi, cioè 0,5 °C. Un allarme spento si accende quando la temperatura raggiunge o supera soglia + 0,5 °C; uno acceso si spegne quando raggiunge o scende sotto soglia − 0,5 °C. Nella banda mantiene il valore precedente. Con soglia visualizzata 25,0 °C, i due limiti sono 24,5 e 25,5 °C.

Il programma acquisisce circa ogni secondo. La lettura sincrona del sensore e l'aggiornamento OLED occupano parte del ciclo: il sistema non promette di rilevare un evento breve fra due campioni.

### Tre informazioni distinte

| Situazione | LED | OLED / seriale |
| --- | --- | --- |
| Misura valida nella zona senza allarme | Spento | Temperatura, soglia e allarme OFF |
| Misura valida con allarme | Acceso | Temperatura, soglia e allarme ON |
| Misura non valida | Spento, per la politica didattica scelta | T: ERRORE / DATO ASSENTE; ERR BMP180 |
| OLED assente, sensore valido | Continua secondo la temperatura | ERR OLED sulla seriale; misura stampata |

Un LED spento da solo non distingue funzionamento normale e guasto. Il progetto dimostra la separazione fra valore e validità; non è un controllo termico di sicurezza. L'ultima temperatura non viene presentata come una misura nuova dopo un errore. Dopo il ripristino, l'allarme riparte da spento e si rivaluta con la nuova misura, secondo le stesse soglie.

## Esempi commentati

```cpp
if (!valid) alarmOn = false;
else if (!alarmOn && temperature >= threshold + 5) alarmOn = true;
else if (alarmOn && temperature <= threshold - 5) alarmOn = false;
```

```python
if not valid:
    alarm_on = False
elif not alarm_on and temperature >= threshold + 5:
    alarm_on = True
elif alarm_on and temperature <= threshold - 5:
    alarm_on = False
```

Nel programma completo il tentativo di acquisizione e quello di visualizzazione sono separati: un problema di display non deve impedire di stampare una misura valida sulla seriale.

## Buone pratiche e debug

- Mantieni le due verifiche di errore separate e prova i dispositivi anche singolarmente.
- Leggi la soglia stampata, non dedurla soltanto dalla posizione della manopola.
- Ripristina la configurazione a 12 bit su entrambi i linguaggi.
- Non toccare il cablaggio sotto alimentazione per simulare guasti: ferma la prova e scollega prima la scheda.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Con soglia 25,0 °C e semibanda 0,5 °C, quando si accende un allarme spento?**

   - A. A 24,5 °C.
   - B. Da 25,5 °C in su.
   - C. A qualunque valore sopra zero.
   - D. Soltanto dopo il riavvio.

2. **Se manca soltanto l’OLED, che cosa fa il progetto?**

   - A. Interrompe tutte le acquisizioni.
   - B. Considera la temperatura zero.
   - C. Continua acquisizione, LED e seriale, segnalando ERR OLED.
   - D. Cancella il firmware.

3. **Un LED spento dimostra che la temperatura sia sicura?**

   - A. No: lo stato di errore va verificato separatamente.
   - B. Sì, sempre.
   - C. Solo con una resistenza da 220 Ω.
   - D. Solo in MicroPython.

## Esercizi pratici

1. **Consegna:** Mantieni la soglia vicina a 25 °C e varia la temperatura attraverso i due limiti.

   **Risultato atteso:** Il LED conserva lo stato nella banda e cambia alle soglie inclusive.

2. **Consegna:** Varia soltanto il potenziometro con temperatura ferma.

   **Risultato atteso:** La regolazione può cambiare il confronto e quindi lo stato del LED.

3. **Consegna:** A prova ferma prepara una configurazione senza BMP180 e una senza OLED.

   **Risultato atteso:** Nei due casi compaiono errori differenti; senza OLED la misura e il LED continuano.

## Soluzioni dell'autovalutazione

1. **B.** L’accensione usa il limite alto incluso.
2. **C.** Acquisizione e visualizzazione hanno gestioni separate.
3. **A.** La politica didattica spegne il LED anche quando la misura non è valida.

## Riferimenti

- [Esercitazione 05: isteresi](../05-Ingressi-analogici-e-ADC/04-Soglia-regolabile-e-isteresi.md).
- [BMP180 in Wokwi](https://docs.wokwi.com/parts/board-bmp180).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente disponibile](03-Display-OLED-e-framebuffer.md)
- La guida della successiva esercitazione numerica è ancora pianificata; consulta l’indice per i materiali disponibili.
