# Display OLED e framebuffer

## Obiettivi e prerequisiti

Prerequisiti: guide 01–02. Imparerai a distinguere il disegno in RAM dal trasferimento al display, installare le dipendenze C++ e usare il modulo MicroPython fornito.

## Teoria e collegamento con l'architettura

### Un’immagine monocromatica in RAM

Il display SSD1306 scelto ha 128 × 64 pixel a un bit per pixel. Il solo framebuffer occupa `128 × 64 / 8 = 1024 byte`, oltre agli oggetti e agli altri dati del programma. Cancellare o scrivere testo nel buffer non modifica automaticamente il pannello: serve il trasferimento esplicito.

C++ usa Adafruit SSD1306 con Adafruit GFX e Adafruit BusIO. MicroPython usa il modulo locale **oled12864.py**, basato su `framebuf`, già incluso nel firmware. Questo driver didattico supporta SSD1306 I²C 128×64; non è un driver generico per SH1106, display SPI o pannelli 128×32.

### Aggiornare un fotogramma

| Passo | C++ | MicroPython |
| --- | --- | --- |
| Pulisci il buffer | `clearDisplay()` | `fill(0)` |
| Posiziona/scrivi | `setCursor()` e `print()` | `text()` |
| Trasferisci | `display()` | `show()` |

Nell'[esempio completo](esempi/03_01-Testo-su-OLED/README.md) si ridisegnano quattro righe ogni secondo. Il contatore parte da zero e torna a zero dopo 9999: conta aggiornamenti riusciti, non misura secondi esatti. Il font C++ e quello MicroPython possono differire; usiamo testo ASCII breve, con al massimo 16 caratteri per riga.

### Il costo della comunicazione

Con 1024 byte e almeno nove impulsi di clock per byte, il solo contenuto richiede circa 92 ms a 100 kHz, più indirizzi e comandi. Un aggiornamento sincrono non è istantaneo. Non trasferire l'intero buffer in ogni giro del ciclo principale: qui un aggiornamento al secondo è sufficiente.

Il programma verifica la presenza del dispositivo. La libreria C++ `display()` non restituisce una conferma dell'immagine visualizzata: un ACK prima del trasferimento non prova che ogni byte successivo sia arrivato. Il driver MicroPython controlla le scritture e solleva `OSError`; nessuna delle due prove software sostituisce l'osservazione del pannello.

## Esempi commentati

```cpp
// Dentro il programma completo, dopo begin() riuscito:
oled.clearDisplay();
oled.setTextSize(1);
oled.setTextColor(SSD1306_WHITE);
oled.setCursor(0, 0);
oled.print("ESP32 I2C");
oled.display();
```

```python
from oled12864 import OLED12864
oled = OLED12864(i2c)
oled.fill(0)
oled.text('ESP32 I2C', 0, 0)
oled.show()
```

Il trasferimento successivo deve sostituire anche i pixel del testo precedente: ripulire il buffer evita cifre residue quando una scritta diventa più corta.

## Buone pratiche e debug

- Installa le tre librerie elencate in libraries.txt per C++; copia oled12864.py per MicroPython.
- Verifica 0x3C con lo scanner; se il modulo usa 0x3D, aggiorna coerentemente codice e circuito.
- Se il display è riconosciuto ma vuoto, controlla modello, risoluzione e chiamata di trasferimento.
- Il cablaggio dei quattro pin deve corrispondere alle etichette del modulo reale, non al solo ordine della figura.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Quanta RAM occupa il solo framebuffer monocromatico 128×64?**

   - A. 128 byte.
   - B. 64 byte.
   - C. 1024 byte.
   - D. 8192 byte.

2. **Quale chiamata trasferisce il buffer MicroPython al pannello?**

   - A. fill(0).
   - B. text().
   - C. scan().
   - D. show().

3. **Il contatore visualizzato è un orologio preciso?**

   - A. No, conta aggiornamenti riusciti con costi e ritardi.
   - B. Sì, perché il testo dice conteggio.
   - C. Sì, perché I²C ha un clock.
   - D. Solo se il font è grande.

## Esercizi pratici

1. **Consegna:** Esegui il contatore con entrambi i linguaggi.

   **Risultato atteso:** Testo e numero coerenti, anche con font differenti.

2. **Consegna:** Cambia una riga con una scritta più corta mantenendo la pulizia del buffer.

   **Risultato atteso:** Nessun carattere residuo dal fotogramma precedente.

3. **Consegna:** Porta l’intervallo a 500 ms e confronta la reattività del programma.

   **Risultato atteso:** Aggiornamenti più frequenti ma costo maggiore sul bus; non dimezza il tempo necessario al trasferimento di un fotogramma.

## Soluzioni dell'autovalutazione

1. **C.** Un bit per pixel dà 8192 bit, cioè 1024 byte.
2. **D.** Il disegno in RAM e la comunicazione sono passaggi distinti.
3. **A.** La temporizzazione cooperativa non garantisce un secondo esatto per fotogramma.

## Riferimenti

- [Adafruit: API SSD1306](https://github.com/adafruit/Adafruit_SSD1306).
- [MicroPython: framebuf](https://docs.micropython.org/en/latest/library/framebuf.html).
- [SSD1306: datasheet del controller](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente disponibile](02-Registri-e-temperatura-BMP180.md)
- [➡️ Guida successiva](04-Temperatura-soglia-ed-errori.md)
