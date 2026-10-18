from machine import DAC, Pin
from time import ticks_ms, ticks_diff, sleep_ms

dac = DAC(Pin(25))
levels = (0, 64, 128, 192, 255)
index_level = 0


def show_level():
    code = levels[index_level]
    dac.write(code)
    print('DAC=%d' % code)  # Codice, non tensione misurata.


show_level()
last_change = ticks_ms()
while True:
    now = ticks_ms()
    if ticks_diff(now, last_change) >= 2000:
        last_change = now
        index_level = (index_level + 1) % len(levels)
        show_level()
    sleep_ms(1)
