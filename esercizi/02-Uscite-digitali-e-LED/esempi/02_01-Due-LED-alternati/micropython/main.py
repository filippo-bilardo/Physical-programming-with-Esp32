from machine import Pin
from time import sleep_ms

STEP_MS = 500
led_a = Pin(18, Pin.OUT, value=0)
led_b = Pin(19, Pin.OUT, value=0)

while True:
    led_b.value(0)           # Spegne prima di accendere l'altro LED.
    led_a.value(1)
    print("A")
    sleep_ms(STEP_MS)
    led_a.value(0)
    led_b.value(1)
    print("B")
    sleep_ms(STEP_MS)
