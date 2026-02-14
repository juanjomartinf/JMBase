#ifndef JMBaseMQTT_h
#define JMBaseMQTT_h


// Selección automática de la librería WiFi correcta según la placa
#if defined(ARDUINO_ARCH_ESP32)
  #include "WiFiClient.h"
	#include <HTTPClient.h>
	#include <HTTPUpdate.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>	
#else
  #error "JMBaseMQTT solo es compatible con ESP32 o ESP8266"
#endif	
	
	
	#include <PubSubClient.h>
	
	namespace JMBaseMQTT {
		extern String user_MQTT;
		extern String pass_MQTT;
		extern String Topic;
		extern String TopicSub;
		
		typedef void (*OnReceiveMessage_CallBack)(const String &topic, const String &payload);
		typedef void (*pubSubProject_Callback)();
	
		// 3️.Función interna que invoca al callback (la llamará tu código MQTT)
		void callBack(char* topic, byte* payload, unsigned int length);
		
		// --- tus funciones ya existentes ---
		void setupMQTT(String user_mqtt, String pass_mqtt, String topic);
		void setCallBacks(void (*callbackConectar)(), void (*callbackMensaje)(const String&, const String&));
		void pubMQTT(String topic, String mensaje);
		void subMQTT(String topic);
		void subMQTT_ext(String topic);
		void loopTimerWiFi();
		void loopMQTT();
		void HTTP_OTA();
	}

#endif