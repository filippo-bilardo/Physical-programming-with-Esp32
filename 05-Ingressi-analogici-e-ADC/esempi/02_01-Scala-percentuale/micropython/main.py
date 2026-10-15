from machine import ADC, Pin
from time import sleep_ms, ticks_ms, ticks_diff

ADC_MAX = 4095
SAMPLE_MS = 200
adc = ADC(Pin(34), atten=ADC.ATTN_11DB)
adc.width(ADC.WIDTH_12BIT)
print('raw12,percento')
last_sample = ticks_ms()

while True:
    now = ticks_ms()
    if ticks_diff(now, last_sample) >= SAMPLE_MS:
        last_sample = now
        raw = adc.read_u16() // 16
        percent = raw * 100 // ADC_MAX  # Percentuale del codice, non volt.
        print(raw, percent, sep=',')
    sleep_ms(1)
