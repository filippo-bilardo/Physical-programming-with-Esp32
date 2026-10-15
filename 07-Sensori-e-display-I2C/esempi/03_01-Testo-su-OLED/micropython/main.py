from machine import I2C, Pin
from time import ticks_ms, ticks_diff, sleep_ms
from oled12864 import OLED12864

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=100000)
oled = None
counter = 0
last_update = ticks_ms()
while True:
    now = ticks_ms()
    if ticks_diff(now, last_update) >= 1000:
        last_update = now
        try:
            if oled is None:
                oled = OLED12864(i2c)
            oled.fill(0)
            oled.text('ESP32 I2C', 0, 0)
            oled.text('OLED 128x64', 0, 16)
            oled.text('Addr 0x3C', 0, 32)
            oled.text('Conteggio: %d' % counter, 0, 48)
            oled.show()
            print('Conteggio: %d' % counter)
            counter = (counter + 1) % 10000
        except OSError:
            oled = None
            print('ERR OLED')
    sleep_ms(1)
