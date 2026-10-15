from machine import ADC, Pin
from time import sleep_ms, ticks_ms, ticks_diff

SAMPLE_MS = 200
adc = ADC(Pin(34), atten=ADC.ATTN_11DB)
adc.width(ADC.WIDTH_12BIT)  # Configurazione specifica del port ESP32.
last_sample = ticks_ms()

while True:
    now = ticks_ms()
    if ticks_diff(now, last_sample) >= SAMPLE_MS:
        last_sample = now
        # read_u16() restituisce una scala 0..65535, non 16 bit hardware.
        raw = adc.read_u16() // 16  # Scala comune 0..4095.
        print(raw)
    sleep_ms(1)
