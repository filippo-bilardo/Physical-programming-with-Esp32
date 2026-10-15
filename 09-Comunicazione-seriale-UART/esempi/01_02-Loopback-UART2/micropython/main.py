from machine import UART, Pin
from time import ticks_ms, ticks_diff, sleep_ms

uart = UART(2, baudrate=115200, bits=8, parity=None, stop=1,
            rx=Pin(16), tx=Pin(17), timeout=0, timeout_char=0)
last_send = ticks_ms()
sent_at = last_send
waiting = False
while True:
    now = ticks_ms()
    data = uart.read(32)
    if data:
        for value in data:
            if value == 65 and waiting:  # 65 e' il codice ASCII di A.
                waiting = False
                print('RX: A')
            else:
                print('RX inatteso')
    if waiting and ticks_diff(now, sent_at) >= 200:
        waiting = False
        print('ERR TIMEOUT')
    if not waiting and ticks_diff(now, last_send) >= 1000:
        last_send = now
        sent_at = now
        waiting = True
        uart.write(b'A')
        print('TX: A')
    sleep_ms(1)
