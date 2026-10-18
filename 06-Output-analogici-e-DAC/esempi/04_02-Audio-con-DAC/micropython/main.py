from machine import DAC, Pin
from time import sleep_us, sleep_ms

# Un periodo approssimato, con centro 128 e ampiezza 64 codici.
samples = (128, 173, 192, 173, 128, 83, 64, 83)
dac = DAC(Pin(25))
dac.write(128)
try:
    while True:
        print('AUDIO DAC: 500 periodi')
        for cycle in range(500):
            for value in samples:
                dac.write(value)
                sleep_us(250)
            if (cycle + 1) % 20 == 0:
                sleep_ms(1)  # Yield ogni blocco di circa 40 ms.
        dac.write(128)
        print('PAUSA DAC')
        sleep_ms(1000)
finally:
    dac.write(128)
