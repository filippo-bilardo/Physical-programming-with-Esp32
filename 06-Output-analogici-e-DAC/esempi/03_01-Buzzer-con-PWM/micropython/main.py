from machine import PWM, Pin
from time import ticks_ms, ticks_diff, sleep_ms

buzzer = PWM(Pin(18), freq=440, duty_u16=0)
sounding = True
try:
    buzzer.duty_u16(32768)  # Circa 50%.
    print('TONE=440')
    last_change = ticks_ms()
    while True:
        now = ticks_ms()
        if ticks_diff(now, last_change) >= 1000:
            last_change = now
            sounding = not sounding
            buzzer.duty_u16(32768 if sounding else 0)
            print('TONE=440' if sounding else 'TONE=0')
        sleep_ms(1)
finally:
    buzzer.deinit()  # Anche quando Ctrl+C interrompe il programma.
