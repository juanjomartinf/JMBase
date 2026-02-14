#ifndef JMBaseWiFi_h
#define JMBaseWiFi_h

#include "JMBase.h"
#include <Arduino.h>

// Selección automática de la librería WiFi correcta según la placa
#if defined(ARDUINO_ARCH_ESP32)
	#include <WiFi.h>
  #include <WiFiMulti.h>
	
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
	#include <ESP8266WiFiMulti.h>	
	
#else
  #error "JMBaseWiFi solo es compatible con ESP32 o ESP8266"
#endif	

	namespace JMBaseWiFi {
		extern IPAddress MQTTServer;
		extern IPAddress HAServer;
		
		void addNetwork(const char* ssid, const char* password);
		void setupWiFi();
		void reconnect();
		void calcularServers();
	}
	
#endif
