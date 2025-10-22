#include "JMBaseWiFi.h"

#if defined(ARDUINO_ARCH_ESP32)
WiFiMulti wifiMulti;

void JMBaseWiFi::setupWiFi(){
	wifiMulti.addAP("CASA2J", "Mibarbatiene3pelos!");
	wifiMulti.addAP("Villa_Pisin", "JKN_11deJulio");

	WiFi.hostname(JMBase::HostName);
	Serial.print("Connecting...");
	WiFi.mode(WIFI_STA);
	while(wifiMulti.run() != WL_CONNECTED && millis() > 20000){
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("WiFi connected. IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println("[WiFi] Listo. Conexión satisfactoria...");
}
  
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
	
//String JMBaseWiFi::SSID = "CASA2J";
//String JMBaseWiFi::PASSWORD = "Mibarbatiene3pelos!";

String JMBaseWiFi::SSID = "Villa_Pisin";
String JMBaseWiFi::PASSWORD = "JKN_11deJulio";


void JMBaseWiFi::setupWiFi(){
  WiFi.hostname(JMBase::HostName);
  Serial.print("Connecting...");
  WiFi.mode(WIFI_STA);
	WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED && millis() < 20000) {
    Serial.print(".");
    delay(500);
  }
  //WiFi.setAutoReconnect(true);
  //WiFi.persistent(true);
	Serial.println("");
	Serial.print("WiFi connected. IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println("[WiFi] Listo. Conexión satisfactoria...");
}
	
#else
  #error "JMBaseWiFi solo es compatible con ESP32 o ESP8266"
#endif

