from machine import ADC, Pin
from time import sleep_ms, ticks_ms, ticks_diff

ADC_MAX = 4095
HYSTERESIS = 100  # Semibanda in codici ADC: usare valori da 1 a 2047.
SAMPLE_MS = 20
REPORT_MS = 200
signal_adc = ADC(Pin(34), atten=ADC.ATTN_11DB)
threshold_adc = ADC(Pin(35), atten=ADC.ATTN_11DB)
signal_adc.width(ADC.WIDTH_12BIT)
threshold_adc.width(ADC.WIDTH_12BIT)
led = Pin(18, Pin.OUT, value=0)
alarm_on = False
print('segnale,soglia,bassa,alta,allarme')
last_sample = ticks_ms()
last_report = last_sample

while True:
    now = ticks_ms()
    if ticks_diff(now, last_sample) >= SAMPLE_MS:
        last_sample = now
        signal = signal_adc.read_u16() // 16
        setting = threshold_adc.read_u16() // 16
        # Restringi il centro per mantenere i due limiti entro 0..4095.
        threshold = HYSTERESIS + setting * (ADC_MAX - 2 * HYSTERESIS) // ADC_MAX
        lower = threshold - HYSTERESIS
        upper = threshold + HYSTERESIS

        if not alarm_on and signal >= upper:
            alarm_on = True
        elif alarm_on and signal <= lower:
            alarm_on = False
        led.value(1 if alarm_on else 0)

        if ticks_diff(now, last_report) >= REPORT_MS:
            last_report = now
            print(signal, threshold, lower, upper, 1 if alarm_on else 0, sep=',')
    sleep_ms(1)
