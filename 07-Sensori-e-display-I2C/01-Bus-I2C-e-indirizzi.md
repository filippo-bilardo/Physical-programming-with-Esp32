# Bus I²C e indirizzi

## Obiettivi e prerequisiti

Prerequisiti: esercitazioni 01–05, GPIO e massa comune. Imparerai a collegare due dispositivi sullo stesso bus, riconoscere gli indirizzi a 7 bit e interpretare una scansione. La 06 non è necessaria per queste prove.

## Teoria e collegamento con l'architettura

### Due linee condivise

I²C usa **SDA** per i dati e **SCL** per il clock. L'ESP32 avvia le transazioni come controller; i dispositivi rispondono al proprio indirizzo. Nel corso scegliamo SDA = GPIO 21, SCL = GPIO 22 e frequenza nominale 100 kHz. Non sono obbligatori per ogni ESP32: li impostiamo esplicitamente.

Le uscite del bus lavorano con linee aperte verso massa: le resistenze **pull-up** riportano il livello alto. Su hardware scegli moduli con pull-up a **3,3 V**. Se mancano, per questi collegamenti brevi a 100 kHz puoi partire da una resistenza da 4,7 kΩ per linea verso 3V3, verificando i requisiti del bus. Più moduli con resistenze integrate le mettono in parallelo: non aggiungerne altre senza controllare il circuito. Wokwi semplifica questo comportamento elettrico.

| ESP32 | BMP180 | OLED SSD1306 |
| --- | --- | --- |
| GPIO 21 | SDA | SDA |
| GPIO 22 | SCL | SCL |
| 3V3 | VCC del modulo compatibile a 3,3 V | VCC del modulo compatibile a 3,3 V |
| GND | GND | GND |

I collegamenti SDA/SCL sono in parallelo, non incrociati. Non collegare a 5 V le resistenze del bus ESP32.

### Indirizzi e risposte

Il BMP180 usa **0x77**; l'OLED dell'esempio usa **0x3C**. Sono indirizzi a 7 bit. Il bit di lettura/scrittura viene gestito dalla periferica: non passare 0xEE al posto di 0x77. Uno scanner verifica chi risponde con ACK a un indirizzo; non identifica il modello e non dimostra che il sensore produca dati corretti.

La periferica I²C genera i segnali e gestisce i byte, la CPU prepara le transazioni e interpreta i risultati. Due dispositivi con lo stesso indirizzo non sono distinguibili semplicemente cambiando una variabile nel programma: servono una configurazione hardware supportata, un altro bus o un multiplexer.

Lo [scanner completo](esempi/01_01-Scanner-I2C/README.md) esplora gli indirizzi 0x08–0x77 all'avvio e circa ogni 3 s. Una scansione è una sequenza di transazioni sincrone, non un'operazione istantanea.

## Esempi commentati

```cpp
Wire.begin(21, 22, 100000);
Wire.setTimeOut(50);  // Timeout delle transazioni in ms sul core ESP32.
Wire.beginTransmission(0x77);
bool present = Wire.endTransmission() == 0;
```

```python
from machine import I2C, Pin
i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=100000)
addresses = i2c.scan()
```

Nella configurazione prevista la scansione mostra `I2C 0x3C` e `I2C 0x77`. Se nessun dispositivo risponde, il C++ non può distinguere con la sola scansione tutte le cause del mancato ACK; MicroPython può inoltre sollevare `OSError` su un guasto di bus.

## Buone pratiche e debug

- Controlla alimentazione, GND e ordine dei pin prima del codice.
- Non usare GPIO 21/22 per altri carichi mentre sono assegnati al bus.
- Verifica l’indirizzo con lo scanner: alcuni OLED usano 0x3D.
- Un bus bloccato o un corto non viene risolto da tentativi software infiniti; spegni e controlla il montaggio.

## Autovalutazione

Scegli una sola risposta per domanda.

1. **Quali linee devono condividere i due dispositivi?**

   - A. SDA con SDA e SCL con SCL.
   - B. TX con RX.
   - C. Solo VCC, senza GND.
   - D. Due uscite LED.

2. **Che cosa dimostra un ACK nello scanner?**

   - A. La temperatura è corretta.
   - B. Un dispositivo risponde a quell’indirizzo.
   - C. Il cablaggio è certificato per ogni frequenza.
   - D. Il modello del sensore è sicuramente BMP180.

3. **Quale indirizzo si passa alle API per il BMP180?**

   - A. 0xEE.
   - B. 0xEF.
   - C. 0x77.
   - D. 115200.

## Esercizi pratici

1. **Consegna:** Esegui lo scanner con sensore e OLED collegati.

   **Risultato atteso:** Due indirizzi distinti: 0x3C e 0x77 nella configurazione fornita.

2. **Consegna:** Ferma la simulazione, rimuovi il solo OLED e riparti.

   **Risultato atteso:** Resta 0x77. Su hardware modifica il cablaggio soltanto a scheda scollegata.

3. **Consegna:** Cambia l’indirizzo del componente OLED in diagram.json a 0x3D e riparti.

   **Risultato atteso:** Lo scanner rileva 0x3D: modificare l’indirizzo del dispositivo è diverso dal cambiare soltanto quello cercato dal programma.

## Soluzioni dell'autovalutazione

1. **A.** Il bus I²C usa dati e clock condivisi, con massa comune.
2. **B.** L’identificazione richiede ulteriori informazioni, per esempio un registro ID.
3. **C.** Le API ricevono l’indirizzo a 7 bit.

## Riferimenti

- [Espressif: API I²C](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2c.html).
- [MicroPython ESP32: I²C hardware](https://docs.micropython.org/en/latest/esp32/quickref.html#hardware-i2c-bus).

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [📂 Indice dell'esercitazione](README.md)
- [⬅️ Guida precedente disponibile](../05-Ingressi-analogici-e-ADC/04-Soglia-regolabile-e-isteresi.md)
- [➡️ Guida successiva](02-Registri-e-temperatura-BMP180.md)
