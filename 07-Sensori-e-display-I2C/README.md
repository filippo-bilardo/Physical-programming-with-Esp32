# 07 · Sensori e display I²C

Collega due dispositivi sullo stesso bus, leggi una temperatura e visualizza misura e soglia su un OLED. Il percorso introduce indirizzi, registri, driver e gestione degli errori.

## Prerequisiti e obiettivi

**Prerequisiti:** esercitazioni 01–05: ambiente, GPIO, temporizzazioni, ADC e isteresi. L’esercitazione 06 su output analogici e audio è disponibile, ma non è necessaria per questi esempi I²C.

Al termine saprai:

- Collegare SDA/SCL e verificare indirizzi a 7 bit con uno scanner.
- Distinguere un ACK da un'identificazione e da una misura valida.
- Leggere la temperatura compensata del BMP180 tramite un driver locale.
- Usare un framebuffer e trasferirlo al display SSD1306.
- Visualizzare temperatura, soglia regolabile e stato dell'allarme, segnalando i guasti.

## Materiali e ambienti

DOIT ESP32 DEVKIT V1 con ESP32-WROOM-32, cavo USB dati, breadboard e cavetti; modulo **BMP180**, display **SSD1306 I²C 128×64**, potenziometro lineare da 10 kΩ, LED rosso con resistenza da **220 Ω**. Scegli moduli compatibili con segnali e alimentazione a 3,3 V. Se i moduli non hanno pull-up sul bus, servono due resistenze adeguate, per esempio 4,7 kΩ verso 3V3 per il circuito breve proposto; controlla lo schema reale prima di aggiungerle.

| Funzione | Pin / indirizzo |
| --- | --- |
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| BMP180 | 0x77 |
| OLED | 0x3C, da verificare sul modulo reale |
| Regolazione soglia | GPIO 34, ADC1 |
| LED allarme | GPIO 18 con 220 Ω |

Il BMP180 non è un BMP280. Il driver fornito usa soltanto la temperatura, non la pressione. La simulazione Wokwi consente di cambiare il valore di temperatura del componente; precisione fisica, pull-up e tempi del bus richiedono verifiche sul dispositivo.

## Guide teoriche

1. [Bus I²C e indirizzi](01-Bus-I2C-e-indirizzi.md)
2. [Registri e temperatura del BMP180](02-Registri-e-temperatura-BMP180.md)
3. [Display OLED e framebuffer](03-Display-OLED-e-framebuffer.md)
4. [Temperatura, soglia e gestione degli errori](04-Temperatura-soglia-ed-errori.md)

Ogni guida comprende esempi commentati, autovalutazione con soluzioni ed esercizi progressivi.

## Esempi completi

| Esempio | Guida | Implementazioni |
| --- | --- | --- |
| [Scanner I²C](esempi/01_01-Scanner-I2C/README.md) | 01 | C++ e MicroPython |
| [Temperatura BMP180](esempi/02_01-Temperatura-BMP180/README.md) | 02 | C++ e MicroPython |
| [Testo su OLED](esempi/03_01-Testo-su-OLED/README.md) | 03 | C++ e MicroPython |
| [Temperatura, soglia e display](esempi/04_01-Temperatura-soglia-e-display/README.md) | 04 | C++ e MicroPython |

Gli esempi sono autonomi: ogni sottocartella contiene i moduli necessari. C++ richiede Adafruit SSD1306, Adafruit GFX Library e Adafruit BusIO soltanto per gli esempi OLED; i rispettivi `libraries.txt` sono forniti. Il driver BMP180 è locale. MicroPython include i moduli locali `bmp180_temperature.py` e/o `oled12864.py` secondo l'esempio: copiali insieme a `main.py`. Non servono pacchetti pip sulla scheda.

## Percorso pratico guidato

1. Collega BMP180 e OLED a SDA 21, SCL 22, 3V3 e GND. Verifica i pull-up e l'alimentazione dei moduli reali.
2. Esegui lo scanner: attendi 0x3C e 0x77. Se mancano, risolvi il collegamento prima del driver.
3. Esegui la sola temperatura e cambia il valore del BMP180 in Wokwi. Prova anche una temperatura negativa.
4. Esegui il contatore OLED. Distingui disegno nel buffer e trasferimento al pannello; confronta i font dei due linguaggi.
5. Monta il circuito completo con potenziometro e LED. Leggi la soglia visualizzata e varia la temperatura attraverso i due limiti di isteresi.
6. A prova ferma prepara le varianti senza sensore e senza OLED, poi riavvia. Registra la differenza fra errore di acquisizione ed errore di visualizzazione.
7. Prova entrambi i linguaggi, indicando versioni e risultati osservati. Non attribuire al simulatore un collaudo elettrico o metrologico.

## Attività autonoma conclusiva

**Consegna:** aggiungi un LED giallo sul GPIO 19, con una seconda resistenza da 220 Ω, che indichi dato BMP180 non valido. Deve essere acceso fino alla prima misura valida, riaccendersi a ogni errore e spegnersi al ritorno di una misura valida. Il LED rosso conserva l'isteresi della temperatura.

**Risultato atteso:** il giallo distingue un guasto da un allarme termico spento. Se manca soltanto l'OLED, acquisizione e LED continuano e la seriale segnala `ERR OLED`. Il cablaggio va modificato a scheda scollegata. Consegna i due programmi, circuito e prove di avvio, sensore assente, display assente e ripristino.

## Verifica dell'apprendimento

Spiega perché due dispositivi possono condividere due linee, perché un ACK non basta per validare una misura e perché un trasferimento OLED ha un costo anche se il disegno avviene in RAM. Indica le unità della temperatura e della soglia.

## Stato dei materiali e delle prove

Guide, sorgenti, driver e diagrammi sono disponibili. I controlli locali hanno superato **20 scenari e 80 esecuzioni** dei programmi C++ e Python con API e clock sostituiti: scansione, riferimento Bosch di 15,0 °C, temperature negative, errori e ripristino dei dispositivi, conteggio OLED, soglia e isteresi, anche al ritorno a zero del timer. Gli sketch sono stati compilati sul computer con queste API sostitutive; sintassi Python, collegamenti locali e diagrammi JSON sono stati controllati.

**Compilazione con core ESP32, esecuzione nel runtime MicroPython, prove Wokwi e collaudo hardware: da eseguire.** I controlli locali non provano segnali, temperatura reale, font, tempi effettivi del bus o consegna dei byte al pannello. Ogni esempio contiene una tabella per registrare le prove.

## Navigazione del corso

- [📑 Indice generale](../README.md)
- [⬅️ Esercitazione precedente: 06 · Output analogici e DAC](../06-Output-analogici-e-DAC/README.md)
- [➡️ Esercitazione successiva disponibile: 09](../09-Comunicazione-seriale-UART/README.md)
- L’esercitazione 08 resta pianificata; la numerazione del corso è conservata.
