# Pulsanti · Livelli, eventi e debounce con ESP32

## Introduzione teorica

Un pulsante normalmente aperto chiude un contatto durante la pressione. Con `INPUT_PULLUP` il GPIO è alto a riposo e diventa basso quando il pulsante lo collega a GND. Un ingresso senza riferimento può risultare flottante; un pulsante a quattro piedini contiene due coppie già collegate internamente: usa contatti appartenenti alle due coppie diverse.

Il **livello** indica se il contatto è premuto; un **fronte** è il cambiamento di livello; un **click** richiede una pressione e un rilascio. I contatti meccanici possono rimbalzare, producendo più cambiamenti ravvicinati. Il filtro temporale accetta un nuovo stato soltanto dopo almeno **50 ms di stabilità**: non basta aggiungere un ritardo e chiamarlo debounce.

## Collegamenti

Scheda ESP32 classico WROOM-32, per esempio DOIT ESP32 DEVKIT V1; pulsanti normalmente aperti, LED esterni, resistenze da **220 Ω** e, per l’esempio 05, potenziometro da 10 kΩ.

| Componente | Collegamento |
| --- | --- |
| Pulsante principale | GPIO 23 ↔ pulsante ↔ GND, `INPUT_PULLUP` |
| Reset, esempio 06 | GPIO 22 ↔ pulsante ↔ GND, `INPUT_PULLUP` |
| LED principale | GPIO 18 → 220 Ω → anodo; catodo a GND |
| Tre LED, esempio 07 | Rosso 18, verde 19, blu 21, una resistenza da 220 Ω per LED |
| Potenziometro, esempio 05 | Estremi a 3V3/GND, cursore a GPIO 34 |

Usa logica a **3,3 V**, senza pull-up esterni a 5 V. Collega a scheda scollegata. GPIO 34 non dispone di pull-up interno e viene usato qui soltanto come ingresso ADC. I numeri indicano GPIO, non posizioni fisiche dei terminali.

## Sketch

Ogni `.ino` si trova nella propria cartella Arduino omonima, direttamente sotto `007-Pulsanti`. Non mettere insieme più sketch nella stessa cartella.

| Sketch | Risultato atteso |
| --- | --- |
| [01 · Lettura semplice](Pulsanti_01_lettura_semplice/Pulsanti_01_lettura_semplice.ino) | Stampa il livello ogni 100 ms; pressione mantenuta produce più righe, non più click |
| [02 · Controllo LED](Pulsanti_02_controllo_led/Pulsanti_02_controllo_led.ino) | Il LED segue il livello: acceso durante la pressione, spento al rilascio |
| [03 · Debouncing](Pulsanti_03_debouncing/Pulsanti_03_debouncing.ino) | Una commutazione del LED per ogni pressione filtrata |
| [04 · Click e doppio click](Pulsanti_04_click_doppio_click/Pulsanti_04_click_doppio_click.ino) | Conta i rilasci filtrati; singolo inverte il LED, doppio produce cinque lampeggi |
| [05 · Attività concorrenti](Pulsanti_05_non_bloccante/Pulsanti_05_non_bloccante.ino) | Pulsante filtrato e lettura ADC del potenziometro ogni 2 s |
| [06 · Contatore](Pulsanti_06_contatore/Pulsanti_06_contatore.ino) | Incremento per pressione filtrata e azzeramento con un secondo pulsante |
| [07 · Macchina a stati](Pulsanti_07_macchina_stati/Pulsanti_07_macchina_stati.ino) | OFF → rosso → verde → blu → OFF, un passaggio per pressione |
| [08 · Classe Pulsante](Pulsanti_08_classe_pulsante/Pulsanti_08_classe_pulsante.ino) | Stessa commutazione filtrata, incapsulata in una classe |

Le prove 01/02 leggono direttamente il contatto e non filtrano i rimbalzi. Nelle prove 03–08 lo stato iniziale viene letto dall’hardware: **tenere premuto all’avvio non genera una nuova pressione**. Occorre rilasciare stabilmente e premere di nuovo. Nella 04 anche il rilascio iniziale di un tasto già premuto non viene contato come click.

### Click: finestra e attese

La prova 04 attende più di **250 ms dall’ultimo rilascio filtrato** per classificare la sequenza: un rilascio è un singolo click, due sono un doppio, tre o più producono `Sequenza multipla ignorata`. La finestra riparte a ogni rilascio. Il singolo non viene quindi segnalato subito alla pressione.

Il doppio click produce cinque cicli da 100 ms acceso e 100 ms spento, poi ripristina lo stato memorizzato. **Questa animazione è bloccante per un secondo:** durante il lampeggio non si leggono i pulsanti e tocchi brevi possono andare persi. La prova 05 mostra invece come gestire attività periodiche senza lunghe attese; la sua lettura analogica è un codice ADC 0–4095, non una temperatura inventata a partire dal potenziometro.

Nella 06 i due ingressi sono filtrati separatamente; il reset è elaborato dopo l’incremento. Se entrambe le pressioni diventano valide nello stesso giro, il risultato finale è zero. Il contatore è `unsigned long` e non viene salvato in Flash.

### Classe Pulsante

`begin()` configura il pin e legge lo stato iniziale; il costruttore non accede all’hardware. Chiama `update()` **una volta per giro**, poi usa:

- `press()`: livello filtrato, vero per tutta la pressione.
- `pressDebounce()`: evento di nuova pressione filtrata.
- `click()`: evento di rilascio di una pressione iniziata dopo l’avvio.

Gli eventi sono conservati fino al successivo `update()`, quindi due letture nello stesso giro non li consumano. Nessun metodo aspetta il rilascio con un ciclo bloccante.

## Esecuzione

1. Installa il core **esp32 by Espressif Systems**, seleziona la scheda reale e apri uno sketch dalla sua sottocartella. Non servono librerie esterne.
2. Collega pulsante e LED secondo la tabella; carica e usa la seriale a **115200 baud** dove prevista.
3. Prova riposo, pressione breve, pressione mantenuta, rilascio e dieci pressioni consecutive.
4. Per il debounce usa pressioni e rilasci di almeno 100 ms; un impulso più breve di 50 ms deve essere ignorato.
5. Riavvia tenendo premuto, poi rilascia e premi di nuovo: verifica la politica iniziale.

Ogni cartella comprende un `diagram.json` per [Wokwi ESP32](https://docs.wokwi.com/guides/esp32). Copia lo sketch nel file principale del modello e il relativo diagramma. Il pulsante simulato può generare rimbalzi: confronta 02 e 03. In hardware verifica contatti e polarità; la simulazione non misura correnti o disturbi reali.

## Esercizi

1. Sostituisci il pull-up con un pull-down esterno da 10 kΩ verso GND e un pulsante verso 3V3. Aggiorna la logica e confronta i livelli.
2. Confronta debounce da 10, 30 e 50 ms, registrando eventi persi e falsi eventi.
3. Riscrivi l’animazione del doppio click con `millis()` e specifica come trattare i nuovi click durante la sequenza.
4. Aggiungi saturazione del contatore a 999 e una pressione lunga per azzerarlo.
5. Usa due oggetti `Pulsante` con gli stessi criteri di avvio e verifica pressioni contemporanee.
6. Controlla una pagina degli [esempi OLED](../003-Oled/README.md) con la macchina a stati, limitando i ridisegni per non ritardare la scansione.

## Verifiche

Controlli locali del **24 ottobre 2026** sulle nuove raccolte 007–011: **37 sketch compilati con g++ e API sostituite**, con **66 esecuzioni superate**. Le verifiche comprendono pulsanti e debounce, avvio con tasto premuto, eventi PIR, temporizzazioni e ritorno a zero del timer, ADC e comandi servo, input seriali errati, echi assenti, filtro e fasce di distanza. Per RTTTL sono stati controllati parser, pause, note puntate/alterate, stop e riavvio e **50 melodie del catalogo**; il lettore MicroPython è stato verificato con PWM e clock sostituiti.

Sono stati controllati nomi dei file Arduino, 38 diagrammi JSON, resistenze, partitori Echo e collegamenti Markdown. Il modello temporale usa la larghezza nativa di `unsigned long` del computer: non emula la CPU o i tempi delle periferiche.

**Compilazione con core ESP32 reale, esecuzione Wokwi e collaudo hardware sono da eseguire.** Questi controlli non misurano corrente, qualità del suono, movimento o sensibilità del sensore.

## Riferimenti

- [Espressif: GPIO](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html).
- [Approfondimento su ingressi digitali e pulsanti](../../03-Ingressi-digitali-e-pulsanti/README.md).
- [Indice ESP32-DEVKIT](../README.md).
- [Indice generale](../../README.md).
