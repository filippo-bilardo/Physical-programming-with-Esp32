from machine import Pin
from time import sleep_ms

LED_PINS = (18, 19, 21)
STEP_MS = 300
leds = [Pin(number, Pin.OUT, value=0) for number in LED_PINS]


def show_only(selected):
    # Prima spegne tutti: evita sovrapposizioni nel cambio di fase.
    for led in leds:
        led.value(0)
    leds[selected].value(1)


while True:
    for i in range(len(leds)):
        show_only(i)
        print(i)
        sleep_ms(STEP_MS)
