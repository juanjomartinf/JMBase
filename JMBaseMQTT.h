#ifndef JMBaseMQTT_h
#define JMBaseMQTT_h


// Selección automática de la librería WiFi correcta según la placa
#if defined(ARDUINO_ARCH_ESP32)
  #include "WiFiClient.h"
	#include <PubSubClient.h>
	
	namespace JMBaseMQTT {
		extern String Topic;
		extern String TopicSub;
		
		typedef void (*RecibirMensajeCallback)(const String &topic, const String &payload);
		typedef void (*OnMQTTConnectCallback)();
	
		// 3️.Función interna que invoca al callback (la llamará tu código MQTT)
		void procesarMensaje(char* topic, byte* payload, unsigned int length);
		
		// --- tus funciones ya existentes ---
		void setupMQTT(String topic, void (*callbackConectar)(), void (*callbackMensaje)(const String&, const String&));
		void pubMQTT(String topic, String mensaje);
		void subMQTT(String topic);
		void loopTimerWiFi();
		void loopMQTT();
		
		void pubMQTT(String topic, String mensaje);
		void subMQTT(String topic);
		
	}
	
	
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
	#include <PubSubClient.h>
	
	
#else
  #error "JMBaseMQTT solo es compatible con ESP32 o ESP8266"
#endif





#endif

