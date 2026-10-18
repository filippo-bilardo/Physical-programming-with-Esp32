from machine import ADC, DAC, Pin
from time import ticks_ms, ticks_diff, sleep_ms

adc = ADC(Pin(34), atten=ADC.ATTN_11DB)
adc.width(ADC.WIDTH_12BIT)
dac = DAC(Pin(25))
dac.write(0)
last_sample = ticks_ms()
last_print = ticks_ms()
while True:
    now = ticks_ms()
    if ticks_diff(now, last_sample) >= 20:
        last_sample = now
        raw = adc.read_u16() // 16
        code = raw * 255 // 4095
        dac.write(code)
        if ticks_diff(now, last_print) >= 200:
            last_print = now
            print('ADC=%d DAC=%d' % (raw, code))
    sleep_ms(1)
