#pragma once
#include <Arduino.h>
#include <Wire.h>

// Driver didattico per la sola temperatura BMP180, secondo il datasheet Bosch.
// Indirizzo fisso 0x77. La conversione richiede una pausa sincrona di 5 ms.
class BMP180Temperature {
 public:
  explicit BMP180Temperature(TwoWire& bus) : bus_(bus) {}

  bool begin() {
    uint8_t id;
    uint8_t data[4];
    if (!readBytes(0xD0, &id, 1) || id != 0x55) return false;
    if (!readBytes(0xB2, data, 4)) return false;
    ac5_ = word(data);
    ac6_ = word(data + 2);
    if (!readBytes(0xBC, data, 4)) return false;
    const uint16_t mc = word(data);
    const uint16_t md = word(data + 2);
    if (!valid(ac5_) || !valid(ac6_) || !valid(mc) || !valid(md)) return false;
    mc_ = mc >= 32768 ? int(mc) - 65536 : int(mc);
    md_ = md >= 32768 ? int(md) - 65536 : int(md);
    return true;
  }

  bool readDeciC(int& temperature) {
    bus_.beginTransmission(0x77);
    bus_.write(0xF4);
    bus_.write(0x2E);
    if (bus_.endTransmission() != 0) return false;
    delay(5);
    uint8_t data[2];
    if (!readBytes(0xF6, data, 2)) return false;
    const int64_t x1 = ((int64_t(word(data)) - ac6_) * ac5_) >> 15;
    const int64_t denominator = x1 + md_;
    if (denominator == 0) return false;
    const int64_t x2 = int64_t(mc_) * 2048 / denominator;
    const int64_t result = (x1 + x2 + 8) >> 4;
    if (result < -400 || result > 850) return false;
    temperature = int(result);  // Decimi di grado Celsius, con segno.
    return true;
  }

 private:
  TwoWire& bus_;
  uint16_t ac5_ = 0, ac6_ = 0;
  int mc_ = 0, md_ = 0;
  static bool valid(uint16_t value) { return value != 0 && value != 65535; }
  static uint16_t word(const uint8_t* data) {
    return (uint16_t(data[0]) << 8) | data[1];
  }
  bool readBytes(uint8_t reg, uint8_t* data, uint8_t length) {
    bus_.beginTransmission(0x77);
    bus_.write(reg);
    if (bus_.endTransmission(false) != 0) return false;
    if (bus_.requestFrom(uint8_t(0x77), length) != length) return false;
    for (int i = 0; i < length; i++) data[i] = bus_.read();
    return true;
  }
};
