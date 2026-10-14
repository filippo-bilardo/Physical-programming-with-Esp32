from machine import Pin
from time import sleep_ms

LED_PIN = 18
ON_MS = 500
OFF_MS = 500
led = Pin(LED_PIN, Pin.OUT, value=0)

while True:
    led.value(1)
    print("LED acceso")
    sleep_ms(ON_MS)           # Attesa in millisecondi.
    led.value(0)
    print("LED spento")
    sleep_ms(OFF_MS)
