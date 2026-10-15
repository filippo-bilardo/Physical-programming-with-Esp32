from machine import UART, Pin
from time import sleep_ms

uart = UART(2, baudrate=115200, bits=8, parity=None, stop=1,
            rx=Pin(16), tx=Pin(17), timeout=0, timeout_char=0)
uart.write(b'READY UART2\n')
while True:
    data = uart.read(32)
    if data:
        uart.write(data)  # Restituisce i byte, senza interpretarli come comandi.
    sleep_ms(1)
