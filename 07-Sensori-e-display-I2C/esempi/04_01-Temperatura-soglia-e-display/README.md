# Temperatura, soglia e display

## Obiettivo e prerequisiti

Visualizzare temperatura e soglia regolabile 15–35 °C e comandare un LED con semibanda di isteresi 0,5 °C, mantenendo separati gli errori dei dispositivi. Leggi la [guida associata](../../04-Temperatura-soglia-ed-errori.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++ aggiuntivi: [bmp180_temperature.h](cpp/bmp180_temperature.h), [libraries.txt](cpp/libraries.txt).
- MicroPython aggiuntivi: [bmp180_temperature.py](micropython/bmp180_temperature.py), [oled12864.py](micropython/oled12864.py).

C++ richiede **Adafruit SSD1306**, **Adafruit GFX Library** e **Adafruit BusIO**, elencate in libraries.txt. In Arduino IDE installale dal gestore librerie, accettando le dipendenze. Per MicroPython il modulo OLED locale è incluso: non installare un pacchetto con pip sulla scheda. Registra versioni di core, firmware e librerie usate. La scheda prevista è ESP32 classico WROOM-32, per esempio DOIT ESP32 DEVKIT V1.

## Materiali e collegamenti

ESP32, cavo USB dati, breadboard e cavetti; modulo BMP180 e OLED SSD1306 I²C 128×64 a 0x3C; potenziometro lineare 10 kΩ, LED e resistenza 220 Ω.

Monta a scheda scollegata. Usa moduli compatibili con alimentazione e segnali a **3,3 V**, con pull-up I²C verso 3V3. Se assenti, aggiungi pull-up adeguati come spiegato nella guida 01. Non collegare pull-up a 5 V. I numeri del codice sono GPIO, non posizioni fisiche dei terminali.

| Da | A |
| --- | --- |
| BMP180 VCC | 3V3 |
| BMP180 GND | GND |
| BMP180 SDA | GPIO 21 |
| BMP180 SCL | GPIO 22 |
| OLED SSD1306 VCC | 3V3 |
| OLED SSD1306 GND | GND |
| OLED SSD1306 SDA | GPIO 21 |
| OLED SSD1306 SCL | GPIO 22 |
| Potenziometro estremi VCC/GND | 3V3 / GND |
| Potenziometro cursore SIG | GPIO 34 |
| GPIO 18 | 220 Ω → anodo LED rosso |
| Catodo LED | GND |

I dispositivi condividono SDA e SCL in parallelo. Sul BMP180 simulato si usa VCC; il terminale aggiuntivo etichettato 3.3V resta scollegato. Sul modulo reale verifica lo schema della specifica scheda. BMP180 e BMP280 non usano lo stesso driver.

## Esecuzione in Wokwi

1. Apri il modello Arduino ESP32 o MicroPython ESP32 dalla [guida Wokwi](https://docs.wokwi.com/guides/esp32).
2. C++: copia cpp.ino in sketch.ino e aggiungi tutti gli altri file della cartella cpp, mantenendo i nomi degli header. Copia anche libraries.txt o installa le tre librerie dal gestore Wokwi.
3. MicroPython: copia main.py e **tutti i moduli .py** della sottocartella micropython nel progetto. Un file mancante provoca ImportError.
4. Sostituisci diagram.json con quello della stessa versione, avvia e apri la console UART0.
5. Clicca BMP180 per cambiare la temperatura; la pressione non viene usata da questi programmi. Segui la prova guidata; non considerare la simulazione una misura di precisione o un collaudo elettrico.

## Esecuzione su scheda reale

1. Controlla alimentazione, pull-up e collegamenti prima di connettere l'USB.
2. C++: apri cpp/cpp.ino, seleziona DOIT ESP32 DEVKIT V1 e porta in Arduino IDE; installa le librerie, compila e carica. Apri il monitor seriale a 115200 baud. Mantieni lo sketch nella cartella cpp con gli header forniti.
3. MicroPython: seleziona interprete ESP32 e porta in Thonny, copia main.py e tutti i moduli della sua sottocartella nella radice della scheda e riavvia. Ctrl+C interrompe il programma.
4. Per il confronto elettrico e della temperatura, documenta strumenti e condizioni. Non scollegare componenti alimentati per provocare un guasto.

## Prova guidata e risultato atteso

1. Avvia con sensore a 24 °C e potenziometro circa a metà; leggi la soglia effettiva visualizzata.
2. Imposta la temperatura sotto il limite basso, poi sopra il limite alto, aspettando almeno due aggiornamenti.
3. Con soglia visualizzata 25,0 °C: accensione da 25,5 °C, spegnimento da 24,5 °C in giù; nella banda conserva lo stato.
4. Varia soltanto il potenziometro e osserva soglia, LED e messaggi seriali.
5. A prova ferma prepara la variante senza sensore: LED spento, T: ERRORE, DATO ASSENTE ed ERR BMP180.
6. Prepara la variante senza OLED: temperatura e LED continuano, con ERR OLED in seriale.
7. Ripristina i collegamenti e riavvia. Il recupero a caldo e i guasti durante un trasferimento richiedono prove dedicate su hardware.

## Come funziona e limiti

Ogni secondo nominale legge ADC e BMP180, aggiorna l’isteresi e infine prova l’OLED. I moduli si inizializzano di nuovo dopo gli errori rilevati. Con dato non valido l’allarme viene azzerato e l’errore è distinto dal valore. Le transazioni sono sincrone: il trasferimento del framebuffer può richiedere circa un decimo di secondo a 100 kHz.

Il driver MicroPython verifica le scritture e può sollevare OSError. La libreria OLED C++ non conferma la consegna di ogni fotogramma: la verifica di presenza precedente non rileva tutti i guasti durante display(). I riferimenti temporali vengono aggiornati al tempo osservato; non si recuperano gli aggiornamenti saltati con raffiche di operazioni.

## Modifica autonoma

Porta l’intervallo a 2000 ms e registra il ritardo di risposta al cambio di temperatura. Aggiorna la tabella delle prove dopo la modifica.

## Stato delle prove

Compilazione con core ESP32, simulazione Wokwi e collaudo reale sono **da eseguire**. I controlli locali con API sostituite riguardano codice e logica, non periferiche fisiche o accuratezza dei dispositivi.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell'esercitazione](../../README.md)
- [📖 Guida associata](../../04-Temperatura-soglia-ed-errori.md)
