"""Client sul PC: python client_uart.py /dev/ttyUSB1 (oppure COM5)."""
import argparse
import serial


def main():
    parser = argparse.ArgumentParser(description='Prova del protocollo UART2 ESP32')
    parser.add_argument('port', help='Porta dell’adattatore USB-UART a 3,3 V')
    args = parser.parse_args()
    with serial.Serial(args.port, 115200, timeout=2, write_timeout=2) as link:
        link.reset_input_buffer()
        for command in ('PING', 'LED 1', 'GET', 'ADC?', 'LED 0'):
            payload = (command + '\n').encode('ascii')
            if link.write(payload) != len(payload):
                raise OSError('Scrittura seriale incompleta')
            while True:
                reply = link.read_until(b'\n', size=128)
                if not reply.endswith(b'\n'):
                    raise TimeoutError('Risposta mancante o incompleta')
                text = reply.rstrip(b'\r\n').decode('ascii')
                if text != 'READY':
                    break
            print(command, '->', text)


if __name__ == '__main__':
    main()
