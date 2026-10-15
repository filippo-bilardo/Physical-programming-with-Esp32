from machine import ADC, Pin
from time import sleep_ms, ticks_ms, ticks_diff

SAMPLES = 8
SAMPLE_MS = 20
adc = ADC(Pin(34), atten=ADC.ATTN_11DB)
adc.width(ADC.WIDTH_12BIT)
total = 0
count = 0
print('ultimo,media8,minimo,massimo')
last_sample = ticks_ms()

while True:
    now = ticks_ms()
    if ticks_diff(now, last_sample) >= SAMPLE_MS:
        last_sample = now
        raw = adc.read_u16() // 16
        if count == 0:
            minimum = raw
            maximum = raw
        if raw < minimum:
            minimum = raw
        if raw > maximum:
            maximum = raw
        total += raw
        count += 1

        if count == SAMPLES:
            average = total // SAMPLES
            print(raw, average, minimum, maximum, sep=',')
            total = 0
            count = 0  # Blocchi consecutivi di otto letture, senza sovrapposizione.
    sleep_ms(1)
