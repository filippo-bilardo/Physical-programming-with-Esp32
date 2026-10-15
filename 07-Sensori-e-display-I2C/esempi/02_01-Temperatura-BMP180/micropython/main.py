from machine import I2C, Pin
from time import ticks_ms, ticks_diff, sleep_ms
from bmp180_temperature import BMP180Temperature

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=100000)
sensor = None
last_sample = ticks_ms()
while True:
    now = ticks_ms()
    if ticks_diff(now, last_sample) >= 1000:
        last_sample = now
        try:
            if sensor is None:
                sensor = BMP180Temperature(i2c)
            temperature = sensor.read_deci_c()
            print('T_C=%.1f' % (temperature / 10))
        except OSError:
            sensor = None
            print('ERR BMP180')
    sleep_ms(1)
