#ifndef JMBaseMQTT_h
#define JMBaseMQTT_h

#include <Arduino.h>

// Selección automática de la librería WiFi correcta según la placa
#if defined(ARDUINO_ARCH_ESP32)
  #include <WiFi.h>
	
	
	
	
	
	
	
	
	
	
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
#else
  #error "JMBaseMQTT solo es compatible con ESP32 o ESP8266"
#endif

#include <PubSubClient.h>

namespace JMBaseMQTT {
  void begin(const char* server, uint16_t port);
  void loop();
  void publish(const char* topic, const char* payload);
  void subscribe(const char* topic);
  void setCallback(MQTT_CALLBACK_SIGNATURE);
}

#endif

