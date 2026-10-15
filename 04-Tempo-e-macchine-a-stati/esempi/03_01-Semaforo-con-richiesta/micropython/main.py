from machine import Pin
from time import sleep_ms, ticks_ms, ticks_diff

DEBOUNCE_MS = 30
GREEN_MIN_MS = 5000
YELLOW_MS = 2000
PEDESTRIAN_MS = 4000
RED_PAUSE_MS = 1000
AUTO_VERDE = 'AUTO_VERDE'
AUTO_GIALLO = 'AUTO_GIALLO'
PEDONI_VERDE = 'PEDONI_VERDE'
PAUSA_ROSSA = 'PAUSA_ROSSA'

red = Pin(18, Pin.OUT, value=0)
yellow = Pin(19, Pin.OUT, value=0)
green = Pin(21, Pin.OUT, value=0)
pedestrian = Pin(22, Pin.OUT, value=0)
button = Pin(23, Pin.IN, Pin.PULL_UP)


def enter_state(next_state, now):
    global state, entered_at, green_ready
    state = next_state
    entered_at = now  # Il riferimento cambia solo entrando nello stato.
    red.value(0)
    yellow.value(0)
    green.value(0)
    pedestrian.value(0)
    if state == AUTO_VERDE:
        green_ready = False
        green.value(1)
    elif state == AUTO_GIALLO:
        yellow.value(1)
    elif state == PEDONI_VERDE:
        red.value(1)
        pedestrian.value(1)
    elif state == PAUSA_ROSSA:
        red.value(1)
    print(state)


last_raw = button.value()
stable_state = last_raw  # Un tasto gia' premuto non genera un evento.
last_change = ticks_ms()
request_pending = False
enter_state(AUTO_VERDE, last_change)

while True:
    raw = button.value()
    now = ticks_ms()
    # Il filtro continua ad aggiornarsi anche quando la richiesta e' ignorata.
    if raw != last_raw:
        last_raw = raw
        last_change = now
    if raw != stable_state and ticks_diff(now, last_change) >= DEBOUNCE_MS:
        stable_state = raw
        if stable_state == 0 and state == AUTO_VERDE and not request_pending:
            request_pending = True
            print('Richiesta accettata')

    if state == AUTO_VERDE:
        # Non confrontare tick ormai lontani dopo una lunga attesa nel verde.
        if not green_ready and ticks_diff(now, entered_at) >= GREEN_MIN_MS:
            green_ready = True
        if request_pending and green_ready:
            request_pending = False
            enter_state(AUTO_GIALLO, now)
    elif state == AUTO_GIALLO:
        if ticks_diff(now, entered_at) >= YELLOW_MS:
            enter_state(PEDONI_VERDE, now)
    elif state == PEDONI_VERDE:
        if ticks_diff(now, entered_at) >= PEDESTRIAN_MS:
            enter_state(PAUSA_ROSSA, now)
    elif state == PAUSA_ROSSA:
        if ticks_diff(now, entered_at) >= RED_PAUSE_MS:
            enter_state(AUTO_VERDE, now)
    sleep_ms(1)
