#ifndef JMBaseWiFi_h
#define JMBaseWiFi_h

#include <Arduino.h>

// Selecciona automáticamente la librería WiFi correcta según la placa
#if defined(ARDUINO_ARCH_ESP32)
  #include <WiFi.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
#else
  #error "JMBaseWiFi solo es compatible con ESP32 o ESP8266"
#endif

namespace JMBaseWiFi {
  void connect(const char* ssid, const char* password);
  bool isConnected();
  String getIP();
}

#endif
