from machine import Pin
from time import sleep_ms

LED_PIN = 18
DRIVE_LEVELS = (Pin.DRIVE_0, Pin.DRIVE_1, Pin.DRIVE_2, Pin.DRIVE_3)
LABELS = ("DRIVE_0", "DRIVE_1", "DRIVE_2", "DRIVE_3")
ON_MS = 5000
OFF_MS = 1000
led = Pin(LED_PIN, Pin.OUT, value=0)

while True:
    for i in range(len(DRIVE_LEVELS)):
        led.value(0)           # Cambia configurazione a LED spento.
        led.init(drive=DRIVE_LEVELS[i])  # Conserva modo e livello del pin.
        print(LABELS[i])        # Impostazione richiesta, non corrente misurata.
        led.value(1)
        sleep_ms(ON_MS)         # Tempo per leggere il multimetro.
        led.value(0)
        sleep_ms(OFF_MS)
