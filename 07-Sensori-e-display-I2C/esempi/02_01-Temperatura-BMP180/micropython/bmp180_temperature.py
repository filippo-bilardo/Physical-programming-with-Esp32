from time import sleep_ms


class BMP180Temperature:
    """Sola temperatura BMP180; compensazione dal datasheet Bosch."""

    def __init__(self, i2c):
        self.i2c = i2c
        if self._read(0xD0, 1)[0] != 0x55:
            raise OSError('Identificativo BMP180 non valido')
        data = self._read(0xB2, 4) + self._read(0xBC, 4)
        words = [(data[i] << 8) | data[i + 1] for i in range(0, 8, 2)]
        if any(value in (0, 65535) for value in words):
            raise OSError('Calibrazione BMP180 non valida')
        self.ac5, self.ac6 = words[:2]
        self.mc = words[2] - 65536 if words[2] >= 32768 else words[2]
        self.md = words[3] - 65536 if words[3] >= 32768 else words[3]

    def _read(self, register, size):
        data = self.i2c.readfrom_mem(0x77, register, size)
        if len(data) != size:
            raise OSError('Lettura BMP180 incompleta')
        return data

    def read_deci_c(self):
        self.i2c.writeto_mem(0x77, 0xF4, b'\x2e')
        sleep_ms(5)  # Conversione sincrona: non e' una lettura istantanea.
        data = self._read(0xF6, 2)
        ut = (data[0] << 8) | data[1]
        x1 = ((ut - self.ac6) * self.ac5) >> 15
        denominator = x1 + self.md
        if denominator == 0:
            raise OSError('Compensazione BMP180 non valida')
        numerator = self.mc * 2048
        # Divisione verso zero, come gli interi C++; // da solo arrotonda in basso.
        x2 = abs(numerator) // abs(denominator)
        if (numerator < 0) != (denominator < 0):
            x2 = -x2
        result = (x1 + x2 + 8) >> 4
        if not -400 <= result <= 850:
            raise OSError('Temperatura BMP180 fuori intervallo')
        return result
