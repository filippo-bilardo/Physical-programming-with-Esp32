# Soglia regolabile e isteresi

## Obiettivi e prerequisiti

Prerequisiti: guide 01–03 e stato booleano dell'esercitazione 04. Imparerai a confrontare due ingressi analogici e a mantenere uno stato all'interno di una banda di isteresi.

## Teoria e collegamento con l'architettura

### Il primo potenziometro simula un sensore

Nell'[esempio completo](esempi/04_01-Soglia-regolabile-con-isteresi/README.md) un potenziometro sul GPIO 34 produce il segnale da controllare. Il secondo, sul GPIO 35, regola il centro della soglia. Il LED sul GPIO 18 indica l'allarme; la sua resistenza da 220 Ω resta necessaria.

Il confronto è fatto in **codici ADC**, non in volt, gradi o altre unità fisiche. I due canali vengono letti uno dopo l'altro, non simultaneamente. Per una misura strumentale servirebbe anche caratterizzare la risposta dei singoli canali.

### Perché una sola soglia può far commutare continuamente

La regola semplice `allarme = segnale >= soglia` cambia stato a ogni passaggio attorno allo stesso valore. Con una soglia di 2000, una sequenza 1999, 2001, 1998, 2002 può alternare il LED senza una variazione significativa del fenomeno osservato.

L'**isteresi** usa due limiti: uno alto per accendere e uno basso per spegnere. Fra i limiti si mantiene lo stato precedente. Non è una media e non attende che il segnale resti stabile per un certo tempo: è un filtro della decisione basato su una banda e sulla memoria dello stato.

| Stato attuale | Condizione sul campione | Nuovo stato |
| --- | --- | --- |
| Spento | `segnale >= alta` | Acceso |
| Spento | `segnale < alta` | Spento |
| Acceso | `segnale <= bassa` | Spento |
| Acceso | `segnale > bassa` | Acceso |

Con centro 2000 e **semibanda H = 100 codici**, il limite basso è 1900 e quello alto è 2100. La banda totale è larga 200 codici. Non sono 200 mV: la trasformazione in tensione richiederebbe il modello di misura.

```text
Segnale:       1800  2050  2100  2050  1900
Stato LED:        0     0     1     1     0
```

### Mantenere raggiungibili entrambi i limiti

Se il potenziometro regolasse il centro da 0 a 4095, aggiungere e sottrarre 100 potrebbe portare i limiti fuori dalla scala disponibile. Negli esempi trasformiamo quindi la regolazione grezza in un centro compreso fra 100 e 3995:

```text
centro = H + regolazione × (4095 − 2 × H) / 4095
bassa  = centro − H
alta   = centro + H
```

La divisione è intera per difetto. Con regolazione 0, centro 100 e limiti 0/200; con regolazione 4095, centro 3995 e limiti 3895/4095. Entrambi i passaggi restano raggiungibili nella scala dei codici. Nell'esempio modifica H soltanto nell'intervallo **1–2047**.

La soglia visualizzata è il centro trasformato, non il valore grezzo del secondo potenziometro. Muovere quel potenziometro può cambiare lo stato del LED anche se il segnale resta fermo: è il comportamento voluto di una soglia regolabile.

## Esempi commentati

In C++, dopo le due letture e il calcolo dei limiti:

```cpp
if (!alarmOn && signal >= upper) {
  alarmOn = true;
} else if (alarmOn && signal <= lower) {
  alarmOn = false;
}
digitalWrite(18, alarmOn ? HIGH : LOW);
```

In MicroPython:

```python
if not alarm_on and signal >= upper:
    alarm_on = True
elif alarm_on and signal <= lower:
    alarm_on = False
led.value(1 if alarm_on else 0)
```

I due casi sono alternativi. Dentro la banda non si assegna un nuovo valore all'allarme; la RAM conserva quello precedente. È una macchina a due stati. Il riavvio parte spento; alla prima lettura, dopo circa 20 ms, un segnale già oltre il limite alto lo accende, mentre un segnale nella banda mantiene lo stato iniziale.

Il ciclo acquisisce i due ingressi ogni 20 ms nominali e stampa un riepilogo ogni 200 ms, senza acquisizioni aggiuntive per la stampa. Il LED può quindi cambiare prima che compaia la successiva riga seriale. Un impulso interamente fra due campioni può non essere rilevato.

## Buone pratiche e debug

- Leggi i limiti stampati, invece di usare la sola posizione della manopola per prevedere il cambio.
- Confronta i valori nella stessa scala: non usare 32768 come soglia di codici a 12 bit.
- Il rumore più grande della banda può ancora produrre commutazioni. Isteresi, media e debounce risolvono problemi diversi.
- Se il segnale rimane nella banda dopo il riavvio, LED spento è il comportamento definito.
- Per confrontare con il caso senza isteresi, sostituisci la decisione con un solo confronto al centro; non impostare H a zero lasciando invariati i due confronti inclusivi.

## Autovalutazione

1. **L'allarme è acceso e il segnale si trova strettamente fra i due limiti. Che cosa accade?**

   - A. Si spegne sempre.
   - B. Mantiene lo stato acceso.
   - C. Lampeggia a 50 Hz.
   - D. Si riavvia il programma.

2. **Con H = 100 codici, la banda totale è larga:**

   - A. 100 V.
   - B. 100 codici.
   - C. 200 codici.
   - D. 4095 codici in ogni caso.

3. **Perché il centro è limitato a 100–3995?**

   - A. Per mantenere i due limiti dentro 0–4095.
   - B. Per cambiare l'alimentazione del potenziometro.
   - C. Per ottenere un ADC a 16 bit.
   - D. Per eliminare la resistenza del LED.

## Esercizi pratici

1. **Consegna:** fissa la soglia, sali oltre il limite alto e poi torna nella banda senza superare quello basso.

   **Risultato atteso:** il LED si accende e resta acceso nella banda; si spegne soltanto raggiungendo o scendendo sotto il limite basso.

2. **Consegna:** riavvia con il segnale nella banda, poi con segnale sopra il limite alto.

   **Risultato atteso:** nel primo caso resta spento; nel secondo si accende alla prima acquisizione utile.

3. **Consegna:** confronta H = 20, 100 e 200, regolando nuovamente il centro dopo ogni modifica.

   **Risultato atteso:** bande rispettivamente di 40, 200 e 400 codici. Aumenta l'escursione necessaria per tornare allo stato precedente; non stai filtrando temporalmente il segnale.

## Soluzioni dell'autovalutazione

1. **B.** Nella banda la decisione dipende dalla memoria dello stato.
2. **C.** La semibanda si estende da entrambi i lati del centro.
3. **A.** Gli estremi restano raggiungibili con i campioni della scala comune.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente](03-Campionamento-rumore-e-media.md)
- La guida successiva appartiene all'esercitazione 06, ancora pianificata.
