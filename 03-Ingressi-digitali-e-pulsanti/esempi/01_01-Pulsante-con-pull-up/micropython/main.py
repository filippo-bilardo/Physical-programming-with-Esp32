from machine import Pin
from time import sleep_ms

led = Pin(18, Pin.OUT, value=0)
button = Pin(23, Pin.IN, Pin.PULL_UP)
previous_reading = -1        # Forza la stampa della prima lettura.

while True:
    reading = button.value()
    pressed = (reading == 0)  # Pulsante attivo basso.
    led.value(1 if pressed else 0)
    if reading != previous_reading:
        print("Premuto" if pressed else "Rilasciato")
        previous_reading = reading
    sleep_ms(10)             # Lettura periodica; non e' un debounce.
