#ifndef JMBaseOTA_h
#define JMBaseOTA_h

#include "JMBase.h"
#include <Arduino.h>


// Selección automática de la librería WiFi correcta según la placa
#if defined(ARDUINO_ARCH_ESP32)
  #include <ESPmDNS.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266mDNS.h>	
#else
  #error "Esta librería solo es compatible con ESP32 o ESP8266"
#endif	
	
  #include <WiFiUdp.h>
  #include <ArduinoOTA.h>
	namespace JMBaseOTA {
		void setupOTA();
		void loopOTA();
	}

#endif
