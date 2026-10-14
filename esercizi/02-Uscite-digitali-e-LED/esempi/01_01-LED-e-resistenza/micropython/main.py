from machine import Pin
from time import sleep_ms

LED_PIN = 18
led = Pin(LED_PIN, Pin.OUT, value=1)
print("LED acceso in modo continuo")

while True:
    sleep_ms(1000)             # Il GPIO conserva il suo stato.
