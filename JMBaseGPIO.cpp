#include "JMBaseGPIO.h"

void JMBaseGPIO::blink(uint8_t pin, int times, int delayMs) {
  pinMode(pin, OUTPUT);
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(delayMs);
    digitalWrite(pin, LOW);
    delay(delayMs);
  }
}

void JMBaseGPIO::digitalToggle(uint8_t pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, !digitalRead(pin));
}
