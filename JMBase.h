#ifndef JMBase_h
#define JMBase_h

#include <Arduino.h>
#include "JMBaseGPIO.h"
#include "JMBaseMQTT.h"
#include "JMBaseOTA.h"
#include "JMBaseWiFi.h"

namespace JMBase {
  void beginSerial(unsigned long baud = 115200);
  void log(const String &msg);
  float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
  String millisToString(unsigned long ms);
}

#endif
