from machine import Pin
from time import sleep_ms, ticks_ms, ticks_diff

RED_INTERVAL_MS = 250
YELLOW_INTERVAL_MS = 700
red = Pin(18, Pin.OUT, value=0)
yellow = Pin(19, Pin.OUT, value=0)
red_on = False
yellow_on = False
last_red = ticks_ms()
last_yellow = last_red

while True:
    now = ticks_ms()
    if ticks_diff(now, last_red) >= RED_INTERVAL_MS:
        last_red = now
        red_on = not red_on
        red.value(1 if red_on else 0)
    # Non usare elif: il giallo ha una temporizzazione indipendente.
    if ticks_diff(now, last_yellow) >= YELLOW_INTERVAL_MS:
        last_yellow = now
        yellow_on = not yellow_on
        yellow.value(1 if yellow_on else 0)
    sleep_ms(1)
