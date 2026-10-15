#pragma once
#include <Arduino.h>

// Una riga ASCII, massimo 32 byte prima di LF (l'eventuale CR conta).
// Dopo un errore scarta fino a LF: non esegue un suffisso come nuovo comando.
class LineReceiver {
 public:
  explicit LineReceiver(HardwareSerial& port) : port_(port) {}

  void poll(unsigned long now, void (*handler)(const char*)) {
    if (length_ > 0 && error_ == nullptr && now - lastByte_ >= 1000) {
      error_ = "ERR TIMEOUT";
    }
    int budget = 32;
    while (budget > 0 && port_.available() > 0) {
      const int value = port_.read();
      if (value < 0) break;
      lastByte_ = now;
      if (value == '\n') {
        if (error_ != nullptr) sendError(error_);
        else {
          if (length_ > 0 && buffer_[length_ - 1] == '\r') length_--;
          bool ascii = true;
          for (int i = 0; i < length_; i++) {
            if (buffer_[i] < 32 || buffer_[i] > 126) ascii = false;
          }
          if (!ascii) sendError("ERR ASCII");
          else if (length_ > 0) {
            buffer_[length_] = '\0';
            handler(buffer_);
          }
        }
        length_ = 0;
        error_ = nullptr;
      } else if (error_ == nullptr) {
        if ((value < 32 && value != '\r') || value > 126) error_ = "ERR ASCII";
        else if (length_ == 32) error_ = "ERR LONG";
        else buffer_[length_++] = char(value);
      }
      budget--;
    }
  }

 private:
  HardwareSerial& port_;
  char buffer_[33];
  int length_ = 0;
  unsigned long lastByte_ = 0;
  const char* error_ = nullptr;
  void sendError(const char* text) {
    port_.print(text);
    port_.write(uint8_t('\n'));
  }
};
