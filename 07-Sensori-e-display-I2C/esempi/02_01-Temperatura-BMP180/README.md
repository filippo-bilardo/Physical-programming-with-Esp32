# Temperatura dal BMP180

## Obiettivo e prerequisiti

Leggere la temperatura compensata in decimi di °C e segnalarne l’assenza senza trasformare l’errore in una temperatura falsa. Leggi la [guida associata](../../02-Registri-e-temperatura-BMP180.md) e la [guida agli ambienti](../../../01-Introduzione-ESP32/02-Ambienti-di-sviluppo.md).

## File e dipendenze

- [Sketch C++](cpp/cpp.ino) e [circuito C++](cpp/diagram.json).
- [Main MicroPython](micropython/main.py) e [circuito MicroPython](micropython/diagram.json).
- C++ aggiuntivi: [bmp180_temperature.h](cpp/bmp180_temperature.h).
- MicroPython aggiuntivi: [bmp180_temperature.py](micropython/bmp180_temperature.py).

C++ richiede soltanto Wire, incluso in Arduino-ESP32. MicroPython usa machine e time, inclusi nel firmware. Non servono librerie esterne. Registra versioni di core, firmware e librerie usate. La scheda prevista è ESP32 classico WROOM-32, per esempio DOIT ESP32 DEVKIT V1.

## Materiali e collegamenti

ESP32, cavo USB dati, breadboard e cavetti; modulo BMP180.

Monta a scheda scollegata. Usa moduli compatibili con alimentazione e segnali a **3,3 V**, con pull-up I²C verso 3V3. Se assenti, aggiungi pull-up adeguati come spiegato nella guida 01. Non collegare pull-up a 5 V. I numeri del codice sono GPIO, non posizioni fisiche dei terminali.

| Da | A |
| --- | --- |
| BMP180 VCC | 3V3 |
| BMP180 GND | GND |
| BMP180 SDA | GPIO 21 |
| BMP180 SCL | GPIO 22 |

I dispositivi condividono SDA e SCL in parallelo. Sul BMP180 simulato si usa VCC; il terminale aggiuntivo etichettato 3.3V resta scollegato. Sul modulo reale verifica lo schema della specifica scheda. BMP180 e BMP280 non usano lo stesso driver.

## Esecuzione in Wokwi

1. Apri il modello Arduino ESP32 o MicroPython ESP32 dalla [guida Wokwi](https://docs.wokwi.com/guides/esp32).
2. C++: copia cpp.ino in sketch.ino e aggiungi tutti gli altri file della cartella cpp, mantenendo i nomi degli header. Wire è integrato e non richiede libraries.txt.
3. MicroPython: copia main.py e **tutti i moduli .py** della sottocartella micropython nel progetto. Un file mancante provoca ImportError.
4. Sostituisci diagram.json con quello della stessa versione, avvia e apri la console UART0.
5. Clicca BMP180 per cambiare la temperatura; la pressione non viene usata da questi programmi. Segui la prova guidata; non considerare la simulazione una misura di precisione o un collaudo elettrico.

## Esecuzione su scheda reale

1. Controlla alimentazione, pull-up e collegamenti prima di connettere l'USB.
2. C++: apri cpp/cpp.ino, seleziona DOIT ESP32 DEVKIT V1 e porta in Arduino IDE; compila e carica. Apri il monitor seriale a 115200 baud. Mantieni lo sketch nella cartella cpp con gli header forniti.
3. MicroPython: seleziona interprete ESP32 e porta in Thonny, copia main.py e tutti i moduli della sua sottocartella nella radice della scheda e riavvia. Ctrl+C interrompe il programma.
4. Per il confronto elettrico e della temperatura, documenta strumenti e condizioni. Non scollegare componenti alimentati per provocare un guasto.

## Prova guidata e risultato atteso

1. Avvia con il sensore a 24 °C: la prima lettura arriva dopo circa 1 s più conversione e I/O.
2. Modifica la temperatura del componente Wokwi a 15 e 30 °C, attendendo alcuni secondi fra le prove.
3. Prova un valore negativo consentito dal sensore.
4. A prova ferma prepara un circuito senza sensore e riavvia: compare `ERR BMP180`.
5. Ripristina e riavvia: le misure riprendono. Il programma ritenta anche ogni secondo dopo un errore, ma il recupero elettrico a caldo resta da collaudare.

## Come funziona e limiti

Il modulo locale legge ID e coefficienti e applica la compensazione Bosch. La conversione include una pausa sincrona di 5 ms. Su errore si invalida il driver e si riprova all’aggiornamento successivo. È implementata soltanto la temperatura, non la pressione.

I riferimenti temporali vengono aggiornati al tempo osservato; non si recuperano gli aggiornamenti saltati con raffiche di operazioni.

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
- [📖 Guida associata](../../02-Registri-e-temperatura-BMP180.md)
