from machine import Pin
from time import sleep_ms, ticks_ms, ticks_diff

DEBOUNCE_MS = 30
led = Pin(18, Pin.OUT, value=0)
button = Pin(23, Pin.IN, Pin.PULL_UP)
last_raw = button.value()
stable_state = last_raw       # Il livello iniziale non e' una pressione.
last_change = ticks_ms()
led_on = False
presses = 0

while True:
    raw = button.value()
    now = ticks_ms()
    if raw != last_raw:
        last_raw = raw
        last_change = now    # Ogni cambiamento riavvia la finestra.
    # ticks_diff gestisce il ritorno a zero del contatore temporale.
    if raw != stable_state and ticks_diff(now, last_change) >= DEBOUNCE_MS:
        stable_state = raw
        if stable_state == 0:
            led_on = not led_on
            led.value(1 if led_on else 0)
            presses += 1
            print(presses)
    sleep_ms(1)
