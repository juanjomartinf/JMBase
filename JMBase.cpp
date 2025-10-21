#include "JMBase.h"

void JMBase::beginSerial(unsigned long baud) {
  Serial.begin(baud);
  while (!Serial);
  log("JMBase iniciado correctamente");
}

void JMBase::log(const String &msg) {
  Serial.println("[JMBase] " + msg);
}

float JMBase::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

String JMBase::millisToString(unsigned long ms) {
  unsigned long seconds = ms / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours   = minutes / 60;
  seconds %= 60;
  minutes %= 60;
  char buffer[20];
  sprintf(buffer, "%02lu:%02lu:%02lu", hours, minutes, seconds);
  return String(buffer);
}
