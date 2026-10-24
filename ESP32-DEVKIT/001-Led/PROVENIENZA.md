# Provenienza degli sketch LED

I dieci sketch `LED_01`–`LED_10` derivano da [filippo-bilardo/ROBOTICA, cartella Led](https://github.com/filippo-bilardo/ROBOTICA/tree/main/Led).

La sorgente consultata è la copia locale `/ws/ROBOTICA`, revisione **`be14c4db788f02186c714e241a8c2fa19b975b7d`**, con cartella `Led` senza modifiche locali al momento dell’importazione. Non è stato verificato che coincida con l’ultimo stato online. Adattamento per ESP32 WROOM-32: **24 ottobre 2026**.

La [licenza GNU AGPLv3](../../LICENSE) del repository di destinazione è identica, byte per byte, al file `LICENSE` della copia sorgente. Le intestazioni originarie sono conservate e ogni sketch importato indica origine e adattamento. Lo sketch preesistente `01-LedBlink` e `LedBlink.png` sono stati conservati.

## Corrispondenza dei file

| File sorgente sotto Led/ | Sketch locale | SHA-256 del file sorgente |
| --- | --- | --- |
| `LED_01_lampeggio_semplice.ino` | [LED_01_lampeggio_semplice](LED_01_lampeggio_semplice/LED_01_lampeggio_semplice.ino) | `f9c368fd3ddc2cbdb125d4191e4b4385737d275116336b3087acc8d4c0d64981` |
| `LED_02_controllo_pulsante.ino` | [LED_02_controllo_pulsante](LED_02_controllo_pulsante/LED_02_controllo_pulsante.ino) | `f97cd5e138f40920261fb81eeccf4837c5e6aadea6d749371b4afa9917f664fe` |
| `LED_03_luminosita_variabile.ino` | [LED_03_luminosita_variabile](LED_03_luminosita_variabile/LED_03_luminosita_variabile.ino) | `9ec5898a42f52008683c778540f98d404d0113e471f06c73e2e14f46ea94551a` |
| `LED_04_effetto_respiro.ino` | [LED_04_effetto_respiro](LED_04_effetto_respiro/LED_04_effetto_respiro.ino) | `99d6f0fe90d92eaa24c44c5eaa855f456dcd55ae4d7b88a8c3441f0b4921125b` |
| `LED_05_semaforo.ino` | [LED_05_semaforo](LED_05_semaforo/LED_05_semaforo.ino) | `00b280cde75ef69bf49a247d977927b0a5f50495f97efdf96c8f7777d3bf4168` |
| `LED_06_led_rgb.ino` | [LED_06_led_rgb](LED_06_led_rgb/LED_06_led_rgb.ino) | `c8fd14a029b108c5b6119a08945e4550adb8f8785eeab954277eed186b279478` |
| `LED_07_knight_rider.ino` | [LED_07_knight_rider](LED_07_knight_rider/LED_07_knight_rider.ino) | `87c6dbaf967eed254faf618d9f3a7c15b7b302bf4a99fe47454e936b96336fc3` |
| `LED_08_classe_led.ino` | [LED_08_classe_led](LED_08_classe_led/LED_08_classe_led.ino) | `0e9e49aed4f15e68d8d7d0adce90b1a274b5cb0232ae8ecd0ba7d0129e5f60bc` |
| `LED_09_led_non_bloccante.ino` | [LED_09_led_non_bloccante](LED_09_led_non_bloccante/LED_09_led_non_bloccante.ino) | `2b3c462ea62496c01141abb122c55ffe4c9793bb93225960201e5f3850936f75` |
| `LED_10_led_seriale.ino` | [LED_10_led_seriale](LED_10_led_seriale/LED_10_led_seriale.ino) | `35012540737e284f7727218f855c9a84757bf53a456802905aa7f4d2f87bd4f7` |

## Adattamenti rispetto ai sorgenti

- GPIO compatibili con l’ESP32 classico, LED esterni con 220 Ω e diagrammi dedicati; nessun uso dei GPIO 6–11 per i LED.
- PWM a 8 bit e 5 kHz negli esempi che usano analogWrite; i metodi della classe e i comandi seriali conservano lo stesso tipo di uscita, evitando di alternare digitalWrite e PWM sullo stesso pin.
- RGB a catodo comune: 0 spegne il colore, 255 corrisponde al duty massimo; corretto il commento originario invertito.
- Knight Rider su un array esplicito di GPIO, senza supporre pin consecutivi.
- Classe LED: il costruttore memorizza lo stato, begin() configura l’hardware da setup().
- Esempio 09: timer inizializzato in setup(), intervallo unsigned e breve pausa cooperativa di 1 ms; seriale a 115200 baud.
- Esempio 10: ricevitore di righe con buffer limitato, LF o CRLF, cifre controllate e recupero dopo righe troppo lunghe. Il lampeggio resta bloccante e al termine ripristina il valore PWM precedente, non soltanto lo stato acceso/spento. Nessun timeout sulle righe parziali: attende LF.

I risultati dei controlli e le procedure sono nel [README](README.md).
