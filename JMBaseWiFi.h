#ifndef JMBaseWiFi_h
#define JMBaseWiFi_h

#include "JMBase.h"
#include <Arduino.h>

// Selecciona automáticamente la librería WiFi correcta según la placa
#if defined(ARDUINO_ARCH_ESP32)
  #include <WiFiMulti.h>
	namespace JMBaseWiFi {
		//extern String HostName;
		void setupWiFi();
		void reconnect();
	}
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
	
	namespace JMBaseWiFi {
		extern String SSID;
		extern String PASSWORD;
		
		void setupWiFi();
	}
#else
  #error "JMBaseWiFi solo es compatible con ESP32 o ESP8266"
#endif



#endif
