from machine import UART, Pin
from time import ticks_ms, sleep_ms
from line_receiver import LineReceiver

uart = UART(2, baudrate=115200, bits=8, parity=None, stop=1,
            rx=Pin(16), tx=Pin(17), timeout=0, timeout_char=0)
led = Pin(18, Pin.OUT, value=0)
led_on = False


def send_line(text):
    uart.write((text + '\n').encode('ascii'))


def handle_command(line):
    global led_on
    if line == 'LED 0' or line == 'LED 1':
        led_on = line[4] == '1'
        led.value(1 if led_on else 0)
        send_line('OK LED 1' if led_on else 'OK LED 0')
    elif line == 'GET':
        send_line('LED=1' if led_on else 'LED=0')
    else:
        send_line('ERR COMMAND')


receiver = LineReceiver(uart, handle_command)
send_line('READY')
while True:
    receiver.poll(ticks_ms())
    sleep_ms(1)
