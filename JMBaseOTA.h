#ifndef JMBaseOTA_h
#define JMBaseOTA_h

#include <Arduino.h>

//Incluir cabeceras según la arquitectura

#if defined(ARDUINO_ARCH_ESP32)
  #include <ESPmDNS.h>
  #include <WiFiUdp.h>
  #include <ArduinoOTA.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266mDNS.h>
  #include <WiFiUdp.h>
  #include <ArduinoOTA.h>
#else
  #error "Esta librería solo es compatible con ESP32 o ESP8266"
#endif

namespace JMBaseOTA {
  void setupOTA(const char* host_name);
  void loopOTA();
}

#endif
