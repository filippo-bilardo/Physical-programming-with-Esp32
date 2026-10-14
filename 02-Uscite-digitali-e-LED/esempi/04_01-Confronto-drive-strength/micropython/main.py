from machine import Pin
from time import sleep_ms

LED_PIN = 18
DRIVE_LEVELS = (Pin.DRIVE_0, Pin.DRIVE_1, Pin.DRIVE_2, Pin.DRIVE_3)
# Collega sempre una resistenza da 220 ohm in serie al LED, anche su hardware.
# Le correnti indicate sono stime con 3.3 V, LED rosso da circa 2 V e drive interno approssimato.
LABELS = (
    'Drive 5 mA; I LED circa 3.7 mA stimata con R=220 ohm',
    'Drive 10 mA; I LED circa 4.6 mA stimata con R=220 ohm',
    'Drive 20 mA; I LED circa 5.2 mA stimata con R=220 ohm',
    'Drive 40 mA; I LED circa 5.5 mA stimata con R=220 ohm',
)
ON_MS = 5000
OFF_MS = 1000
led = Pin(LED_PIN, Pin.OUT, value=0)

while True:
    for i in range(len(DRIVE_LEVELS)):
        led.value(0)           # Cambia configurazione a LED spento.
        led.init(drive=DRIVE_LEVELS[i])  # Conserva modo e livello del pin.
        print(LABELS[i])        # La corrente effettiva non viene misurata.
        led.value(1)
        sleep_ms(ON_MS)         # Durata virtuale di questa fase.
        led.value(0)
        sleep_ms(OFF_MS)
