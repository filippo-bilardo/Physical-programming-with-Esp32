# Buzzer passivo e PWM

## Obiettivi e prerequisiti

Prerequisiti: guida 01, frequenza e temporizzazioni. Riprodurrai un tono con un piccolo piezo passivo e distinguerai frequenza, duty cycle e durata del suono.

## Teoria e collegamento con l’architettura

### Scegliere il trasduttore

Un **buzzer attivo** contiene un oscillatore: alimentandolo emette il proprio suono. Un **piezo passivo** richiede un segnale variabile: è adatto a note di frequenza diversa. Negli esempi usiamo un piccolo piezo passivo ad alta impedenza, con una resistenza in serie da **1 kΩ**. Non sostituirlo con un altoparlante da 8 Ω o un buzzer elettromagnetico: richiedono un circuito di pilotaggio diverso.

| Da | A |
| --- | --- |
| GPIO 18 | Resistenza 1 kΩ |
| Altro capo della resistenza | Positivo del piezo |
| Negativo del piezo | GND |

La resistenza limita i transitori di carica del piezo e può ridurre il volume. Non determina una corrente continua costante: il piezo è prevalentemente capacitivo. Verifica il componente reale e non attribuire al circuito una potenza audio non misurata.

### Frequenza, durata e timbro

Il tono dell’[esempio](esempi/03_01-Buzzer-con-PWM/README.md) è a 440 Hz, circa la nota LA4. Il periodo vale `1/440 ≈ 2,27 ms`; con duty vicino al 50% le due semionde durano circa 1,14 ms ciascuna. Il segnale rettangolare contiene armoniche: il timbro non è quello di una sinusoide pura.

Un timer hardware genera le commutazioni. Il programma gestisce soltanto l’alternanza di un secondo di suono e uno di silenzio. Non bisogna alternare digitalWrite() con attese di mezzo periodo: così la CPU resterebbe impegnata nella generazione di ogni ciclo.

### API nei due linguaggi

Gli sketch richiedono **Arduino-ESP32 3.x**: `ledcAttach(pin, frequenza, risoluzione)` configura il pin; `ledcWriteTone(pin, frequenza)` genera il tono. La configurazione viene verificata e un errore produce `ERR PWM`. I vecchi esempi con `ledcSetup()` e `ledcAttachPin()` appartengono all’API 2.x e non vanno mescolati a questi sketch.

```cpp
if (ledcAttach(18, 440, 8)) {
  ledcWriteTone(18, 440);  // Tono al 50%.
}
// Per spegnere il tono:
ledcWriteTone(18, 0);
```

```python
from machine import Pin, PWM
buzzer = PWM(Pin(18), freq=440, duty_u16=0)
buzzer.duty_u16(32768)
# Per il silenzio si mantiene la frequenza valida e si azzera il duty:
buzzer.duty_u16(0)
```

Non passare `freq(0)` a MicroPython: il silenzio viene comandato con duty zero. Il programma completo usa `finally` e `deinit()` per arrestare il PWM anche con Ctrl+C. Frequenza e risoluzione reali dipendono dai timer; altri PWM possono condividere risorse. Qui si usa un solo canale.

## Wokwi e debug

Il componente `wokwi-buzzer` ha terminale **1 negativo** e **2 positivo**. I diagrammi usano GPIO 18 e una resistenza da 1 kΩ, con volume del simulatore inizialmente ridotto. Se non senti audio, controlla audio della scheda del browser, volume, avvio della simulazione e collegamenti. Il volume del browser non misura quello del piezo reale.

Una variazione di duty non è un controllo di volume calibrato: cambia anche lo spettro del segnale. Per iniziare conserva il 50% e modifica la sola frequenza. Per fermare un programma su hardware considera anche il caricamento di uno sketch che disattivi l’uscita o lo scollegamento dell’alimentazione.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Quale componente consente di scegliere le note mediante PWM?**

   - A. Un buzzer attivo qualsiasi
   - B. Un piccolo piezo passivo adatto al circuito
   - C. Un LED
   - D. Un resistore da solo

2. **Come si comanda il silenzio in MicroPython?**

   - A. Con freq(0)
   - B. Con duty_u16(65535)
   - C. Con duty_u16(0)
   - D. Con una stampa sulla seriale

3. **Chi genera i cicli a 440 Hz nell’esempio?**

   - A. Il timer PWM hardware
   - B. La stampante
   - C. Il DAC 25
   - D. Il tester DC

## Esercizi pratici

1. **Consegna:** Confronta 440 Hz e 880 Hz, mantenendo invariati duty e durata.

   **Risultato atteso:** Il secondo tono è un’ottava più alto; non è una prova di volume raddoppiato.

2. **Consegna:** Riduci il suono a 200 ms e lascia 800 ms di pausa usando due durate dipendenti dallo stato.

   **Risultato atteso:** Un ciclo di un secondo, senza un delay(800) che blocchi il programma.

3. **Consegna:** Misura con analizzatore logico periodo e duty sul GPIO 18, prima della resistenza.

   **Risultato atteso:** Circa 2,27 ms e 50% a 440 Hz; indica lo scarto osservato.

## Soluzioni dell’autovalutazione

1. **B.** Il piezo passivo segue l’eccitazione variabile applicata.
2. **C.** Il duty zero ferma le commutazioni mantenendo valida la frequenza.
3. **A.** Il ciclo principale decide quando abilitare il tono.

## Riferimenti

- [Espressif: LEDC e ledcWriteTone](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html).
- [Espressif: migrazione Arduino-ESP32 3.0](https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html#ledc).
- [MicroPython: machine.PWM](https://docs.micropython.org/en/latest/library/machine.PWM.html).
- [Wokwi: buzzer piezoelettrico](https://docs.wokwi.com/parts/wokwi-buzzer).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell’esercitazione](README.md)
- [⬅️ Guida precedente](02-DAC-e-regolazione-della-tensione.md)
- [➡️ Guida successiva](04-Melodie-e-audio-con-DAC.md)
