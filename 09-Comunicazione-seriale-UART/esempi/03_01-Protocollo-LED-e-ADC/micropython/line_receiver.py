from time import ticks_diff


class LineReceiver:
    """Righe ASCII limitate a 32 byte prima di LF; CR finale opzionale."""

    def __init__(self, uart, handler):
        self.uart = uart
        self.handler = handler
        self.buffer = bytearray()
        self.error = None
        self.last_byte = 0

    def poll(self, now):
        if self.buffer and self.error is None and ticks_diff(now, self.last_byte) >= 1000:
            self.error = 'ERR TIMEOUT'
        data = self.uart.read(32)
        if not data:
            return
        for value in data:
            self.last_byte = now
            if value == 10:
                if self.error is not None:
                    self.uart.write((self.error + '\n').encode('ascii'))
                else:
                    if self.buffer and self.buffer[-1] == 13:
                        self.buffer.pop()
                    if any(byte < 32 or byte > 126 for byte in self.buffer):
                        self.uart.write(b'ERR ASCII\n')
                    elif self.buffer:
                        self.handler(self.buffer.decode('ascii'))
                self.buffer = bytearray()
                self.error = None
            elif self.error is None:
                if (value < 32 and value != 13) or value > 126:
                    self.error = 'ERR ASCII'
                elif len(self.buffer) == 32:
                    self.error = 'ERR LONG'
                else:
                    self.buffer.append(value)
