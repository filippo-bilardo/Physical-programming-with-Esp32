import framebuf


class OLED12864(framebuf.FrameBuffer):
    """Driver didattico I2C per SSD1306 128x64, non per SH1106."""

    def __init__(self, i2c, address=0x3C):
        self.i2c = i2c
        self.address = address
        self.buffer = bytearray(128 * 64 // 8)
        super().__init__(self.buffer, 128, 64, framebuf.MONO_VLSB)
        # Comandi di configurazione dal datasheet SSD1306, charge pump interna.
        commands = (0xAE, 0x20, 0x00, 0x40, 0xA1, 0xA8, 0x3F,
                    0xC8, 0xD3, 0x00, 0xDA, 0x12, 0xD5, 0x80,
                    0xD9, 0xF1, 0xDB, 0x30, 0x81, 0xFF, 0xA4,
                    0xA6, 0x8D, 0x14)
        for command in commands:
            self._command(command)
        self.fill(0)
        self.show()
        self._command(0xAF)

    def _command(self, value):
        if self.i2c.writeto(self.address, bytes((0x80, value))) != 2:
            raise OSError('Comando OLED incompleto')

    def show(self):
        for command in (0x21, 0, 127, 0x22, 0, 7):
            self._command(command)
        packet = b'\x40' + self.buffer
        if self.i2c.writeto(self.address, packet) != len(packet):
            raise OSError('Trasferimento OLED incompleto')
