from machine import I2C, Pin
from time import ticks_ms, ticks_diff, sleep_ms

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=100000)


def scan_bus():
    try:
        addresses = i2c.scan()
        for address in addresses:
            print('I2C 0x%02X' % address)
        if not addresses:
            print('Nessun dispositivo')
    except OSError:
        print('ERR I2C')


scan_bus()
last_scan = ticks_ms()
while True:
    now = ticks_ms()
    if ticks_diff(now, last_scan) >= 3000:
        last_scan = now
        scan_bus()
    sleep_ms(1)
