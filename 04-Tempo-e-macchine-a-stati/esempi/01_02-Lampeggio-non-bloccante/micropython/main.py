from machine import Pin
from time import sleep_ms, ticks_ms, ticks_diff

INTERVAL_MS = 1000
red = Pin(18, Pin.OUT, value=0)
yellow = Pin(19, Pin.OUT, value=0)
button = Pin(23, Pin.IN, Pin.PULL_UP)
red_on = False
last_toggle = ticks_ms()

while True:
    now = ticks_ms()
    yellow.value(1 if button.value() == 0 else 0)
    if ticks_diff(now, last_toggle) >= INTERVAL_MS:
        last_toggle = now
        red_on = not red_on
        red.value(1 if red_on else 0)
    sleep_ms(1)  # Breve pausa per giro, non un'attesa di 1000 ms.
