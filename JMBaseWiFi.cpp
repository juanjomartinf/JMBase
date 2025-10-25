#include "JMBaseWiFi.h"

#if defined(ARDUINO_ARCH_ESP32)
WiFiMulti wifiMulti;

void JMBaseWiFi::setupWiFi(){
	wifiMulti.addAP("CASA2J", "Mibarbatiene3pelos!");
	wifiMulti.addAP("Villa_Pisin", "JKN_11deJulio");

	WiFi.hostname(JMBase::HostName);
	Serial.print("[WiFi] Connecting...");
	WiFi.mode(WIFI_STA);
	while(wifiMulti.run() != WL_CONNECTED && millis() > 20000){
		delay(500);
		Serial.print(".");
	}
	
	if(WiFi.status() == WL_CONNECTED){
		Serial.println("");
		Serial.print("[WiFi] Listo. Conexión satisfactoria. IP address: ");
		Serial.println(WiFi.localIP());
	}
	else{
		Serial.print("[WiFi] Error al conectar.");
	}
}

void JMBaseWiFi::reconnect(){
  WiFi.mode(WIFI_OFF);
  delay(200);
  WiFi.disconnect();
	
	Serial.println("[WiFi] WiFi is disconnected  **");
	
	wifiMulti.addAP("CASA2J", "Mibarbatiene3pelos!");
	wifiMulti.addAP("Villa_Pisin", "JKN_11deJulio");

	WiFi.hostname(JMBase::HostName);
	Serial.print("[WiFi] Connecting...");
	WiFi.mode(WIFI_STA);
	unsigned long startAttempt = millis();
	while (wifiMulti.run() != WL_CONNECTED && millis() - startAttempt < 10000) {
		delay(500);
		Serial.print(".");
	}
	
	if(WiFi.status() == WL_CONNECTED){
		Serial.println("");
		Serial.print("[WiFi] Listo. Conexión satisfactoria. IP address: ");
		Serial.println(WiFi.localIP());
	}
	else{
		Serial.print("[WiFi] Error al conectar.");
	}
}

  
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
	
//String JMBaseWiFi::SSID = "CASA2J";
//String JMBaseWiFi::PASSWORD = "Mibarbatiene3pelos!";

String JMBaseWiFi::SSID = "Villa_Pisin";
String JMBaseWiFi::PASSWORD = "JKN_11deJulio";


void JMBaseWiFi::setupWiFi(){
  WiFi.hostname(JMBase::HostName);
  Serial.print("[WiFi] Connecting...");
  WiFi.mode(WIFI_STA);
	WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED && millis() < 20000) {
    Serial.print(".");
    delay(500);
  }
  //WiFi.setAutoReconnect(true);
  //WiFi.persistent(true);
	Serial.println("");
	Serial.print("[WiFi] Listo. Conexión satisfactoria. IP address: ");
	Serial.println(WiFi.localIP());
}
	
#else
  #error "JMBaseWiFi solo es compatible con ESP32 o ESP8266"
#endif

