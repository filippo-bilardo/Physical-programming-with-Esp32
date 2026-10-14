from machine import Pin
from time import sleep_ms

led = Pin(18, Pin.OUT, value=0)
button = Pin(23, Pin.IN, Pin.PULL_UP)
previous_reading = button.value()
led_on = False
presses = 0

while True:
    reading = button.value()
    # Riconosce il fronte di discesa; NON filtra i rimbalzi.
    if previous_reading == 1 and reading == 0:
        led_on = not led_on
        led.value(1 if led_on else 0)
        presses += 1
        print(presses)
    previous_reading = reading
    sleep_ms(1)
