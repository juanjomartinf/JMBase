#ifndef JMBaseGPIO_h
#define JMBaseGPIO_h

#include <Arduino.h>

namespace JMBaseGPIO {
  void blink(uint8_t pin, int times = 1, int delayMs = 200);
  void digitalToggle(uint8_t pin);
}

#endif
