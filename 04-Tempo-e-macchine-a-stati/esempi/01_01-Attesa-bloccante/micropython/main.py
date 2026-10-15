from machine import Pin
from time import sleep_ms

red = Pin(18, Pin.OUT, value=0)
yellow = Pin(19, Pin.OUT, value=0)
button = Pin(23, Pin.IN, Pin.PULL_UP)

while True:
    # Una sola lettura ogni circa 2 s: non e' un contatore di pressioni.
    yellow.value(1 if button.value() == 0 else 0)
    red.value(1)
    sleep_ms(1000)
    red.value(0)
    sleep_ms(1000)
