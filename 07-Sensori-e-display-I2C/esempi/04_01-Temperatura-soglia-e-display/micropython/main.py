from machine import I2C, Pin, ADC
from time import ticks_ms, ticks_diff, sleep_ms
from bmp180_temperature import BMP180Temperature
from oled12864 import OLED12864

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=100000)
adc = ADC(Pin(34), atten=ADC.ATTN_11DB)
adc.width(ADC.WIDTH_12BIT)
led = Pin(18, Pin.OUT, value=0)
sensor = None
oled = None
alarm_on = False
last_update = ticks_ms()
while True:
    now = ticks_ms()
    if ticks_diff(now, last_update) >= 1000:
        last_update = now
        setting = adc.read_u16() // 16
        threshold = 150 + setting * 200 // 4095
        valid = False
        try:
            if sensor is None:
                sensor = BMP180Temperature(i2c)
            temperature = sensor.read_deci_c()
            valid = True
        except OSError:
            sensor = None
            alarm_on = False
            print('ERR BMP180')
        if valid:
            if not alarm_on and temperature >= threshold + 5:
                alarm_on = True
            elif alarm_on and temperature <= threshold - 5:
                alarm_on = False
            print('T_C=%.1f S_C=%.1f AL=%d' %
                  (temperature / 10, threshold / 10, 1 if alarm_on else 0))
        led.value(1 if alarm_on else 0)
        try:
            if oled is None:
                oled = OLED12864(i2c)
            oled.fill(0)
            oled.text('T: %.1f C' % (temperature / 10) if valid else 'T: ERRORE', 0, 0)
            oled.text('S: %.1f C' % (threshold / 10), 0, 16)
            oled.text('Allarme: ON' if alarm_on else 'Allarme: OFF', 0, 32)
            oled.text('BMP180 + OLED' if valid else 'DATO ASSENTE', 0, 48)
            oled.show()
        except OSError:
            oled = None
            print('ERR OLED')
    sleep_ms(1)
