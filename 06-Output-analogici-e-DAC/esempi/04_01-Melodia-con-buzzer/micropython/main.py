from machine import PWM, Pin
from time import ticks_ms, ticks_diff, sleep_ms

# Ogni durata comprende suono (80%) e articolazione silenziosa (20%).
notes = (262, 294, 330, 262, 330, 349, 392, 0)
durations = (300, 300, 300, 300, 300, 300, 600, 1000)
buzzer = PWM(Pin(18), freq=440, duty_u16=0)
note_index = 0
sounding = False


def start_note():
    global sounding
    frequency = notes[note_index]
    sounding = frequency > 0
    buzzer.duty_u16(0)
    if sounding:
        buzzer.freq(frequency)
        buzzer.duty_u16(32768)
    print('NOTE=%d MS=%d' % (frequency, durations[note_index]))


try:
    start_note()
    note_started = ticks_ms()
    while True:
        now = ticks_ms()
        elapsed = ticks_diff(now, note_started)
        duration = durations[note_index]
        if elapsed >= duration:
            note_index = (note_index + 1) % len(notes)
            note_started = now
            start_note()
        elif sounding and elapsed >= duration * 4 // 5:
            buzzer.duty_u16(0)
            sounding = False
        sleep_ms(1)
finally:
    buzzer.deinit()
