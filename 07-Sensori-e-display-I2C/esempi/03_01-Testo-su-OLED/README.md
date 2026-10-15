# Testo e contatore su OLED

## Obiettivo e prerequisiti

Disegnare quattro righe in un framebuffer e trasferirle a un SSD1306 I²C 128×64, con un aggiornamento al secondo nominale. Leggi la [guida associata](../../03-Display-OLED-e-framebuffer.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++ aggiuntivi: [libraries.txt](cpp/libraries.txt).
- MicroPython aggiuntivi: [oled12864.py](micropython/oled12864.py).

C++ richiede **Adafruit SSD1306**, **Adafruit GFX Library** e **Adafruit BusIO**, elencate in libraries.txt. In Arduino IDE installale dal gestore librerie, accettando le dipendenze. Per MicroPython il modulo OLED locale è incluso: non installare un pacchetto con pip sulla scheda. Registra versioni di core, firmware e librerie usate. La scheda prevista è ESP32 classico WROOM-32, per esempio DOIT ESP32 DEVKIT V1.

## Materiali e collegamenti

ESP32, cavo USB dati, breadboard e cavetti; OLED SSD1306 I²C 128×64 a 0x3C.

Monta a scheda scollegata. Usa moduli compatibili con alimentazione e segnali a **3,3 V**, con pull-up I²C verso 3V3. Se assenti, aggiungi pull-up adeguati come spiegato nella guida 01. Non collegare pull-up a 5 V. I numeri del codice sono GPIO, non posizioni fisiche dei terminali.

| Da | A |
| --- | --- |
| OLED SSD1306 VCC | 3V3 |
| OLED SSD1306 GND | GND |
| OLED SSD1306 SDA | GPIO 21 |
| OLED SSD1306 SCL | GPIO 22 |

Il diagramma di questo esempio comprende soltanto il display. Sul modulo reale verifica lo schema della specifica scheda, l'indirizzo e la compatibilità con 3,3 V.

## Esecuzione in Wokwi

1. Apri il modello Arduino ESP32 o MicroPython ESP32 dalla [guida Wokwi](https://docs.wokwi.com/guides/esp32).
2. C++: copia cpp.ino in sketch.ino e aggiungi tutti gli altri file della cartella cpp, mantenendo i nomi degli header. Copia anche libraries.txt o installa le tre librerie dal gestore Wokwi.
3. MicroPython: copia main.py e **tutti i moduli .py** della sottocartella micropython nel progetto. Un file mancante provoca ImportError.
4. Sostituisci diagram.json con quello della stessa versione, avvia e apri la console UART0.
5. Segui la prova guidata; non considerare la simulazione una misura di precisione o un collaudo elettrico.

## Esecuzione su scheda reale

1. Controlla alimentazione, pull-up e collegamenti prima di connettere l'USB.
2. C++: apri cpp/cpp.ino, seleziona DOIT ESP32 DEVKIT V1 e porta in Arduino IDE; installa le librerie, compila e carica. Apri il monitor seriale a 115200 baud. Mantieni lo sketch nella cartella cpp con gli header forniti.
3. MicroPython: seleziona interprete ESP32 e porta in Thonny, copia main.py e tutti i moduli della sua sottocartella nella radice della scheda e riavvia. Ctrl+C interrompe il programma.
4. Per le verifiche elettriche documenta strumenti e condizioni. Non scollegare componenti alimentati per provocare un guasto.

## Prova guidata e risultato atteso

1. Avvia: dopo circa 1 s compaiono ESP32 I2C, OLED 128x64, indirizzo e conteggio 0.
2. Il numero aumenta soltanto dopo un aggiornamento senza errore rilevato e torna a 0 dopo 9999.
3. Sostituisci una scritta con una più corta e riparti: la pulizia del buffer evita caratteri residui.
4. A prova ferma rimuovi il display e riparti: compare `ERR OLED` nella console.
5. Ripristina, riavvia e confronta i due linguaggi: font diversi sono previsti; contenuto e posizioni delle quattro righe restano equivalenti.

## Come funziona e limiti

C++ usa Adafruit SSD1306/GFX; MicroPython usa oled12864.py e framebuf. Il framebuffer da 1024 byte viene ripulito e trasferito una volta per aggiornamento. Il contatore conta fotogrammi riusciti secondo i controlli disponibili, non secondi precisi.

Il driver MicroPython verifica le scritture e può sollevare OSError. La libreria OLED C++ non conferma la consegna di ogni fotogramma: la verifica di presenza precedente non rileva tutti i guasti durante display(). I riferimenti temporali vengono aggiornati al tempo osservato; non si recuperano gli aggiornamenti saltati con raffiche di operazioni.

## Modifica autonoma

Modifica il periodo di aggiornamento e spiega quale costo del bus rimane invariato. Aggiorna la tabella delle prove dopo la modifica.

## Stato delle prove

Compilazione con core ESP32, simulazione Wokwi e collaudo reale sono **da eseguire**. I controlli locali con API sostituite riguardano codice e logica, non periferiche fisiche o accuratezza dei dispositivi.

| Data | Linguaggio | Ambiente, scheda e versioni | Prova | Osservato | Esito |
| --- | --- | --- | --- | --- | --- |
| Da compilare | C++ | — | Prova guidata | — | Da verificare |
| Da compilare | MicroPython | — | Prova guidata | — | Da verificare |

## Navigazione del corso

- [📑 Indice generale](../../../README.md)
- [📂 Indice dell'esercitazione](../../README.md)
- [📖 Guida associata](../../03-Display-OLED-e-framebuffer.md)
