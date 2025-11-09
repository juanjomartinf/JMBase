#include "JMBaseWiFi.h"

#if defined(ARDUINO_ARCH_ESP32)
WiFiMulti wifiMulti;

void JMBaseWiFi::addNetwork(const char* ssid, const char* password) {
	wifiMulti.addAP(ssid, password);
}

void JMBaseWiFi::setupWiFi(){
	WiFi.mode(WIFI_STA);
	WiFi.hostname(JMBase::HostName);
  Serial.print("[WiFi] Connecting...");
  wifiMulti.run();
  while(WiFi.status() != WL_CONNECTED && millis() < 20000) {
    delay(500);
    Serial.print(".");
  }
	
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("connected!");
    Serial.print("[WiFi] SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("[WiFi] IP address: ");
    Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("error to connect!");
  }
}

void JMBaseWiFi::reconnect(){
  WiFi.mode(WIFI_OFF);
  delay(200);
  WiFi.disconnect();
	
	Serial.println("[WiFi] WiFi disconnected!");
	WiFi.hostname(JMBase::HostName);
	Serial.print("[WiFi] Reconnecting... ");
	WiFi.mode(WIFI_STA);
	wifiMulti.run();
	delay(100);
}

  
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
	
//String JMBaseWiFi::SSID = "CASA2J";
//String JMBaseWiFi::PASSWORD = "Mibarbatiene3pelos!";

//String JMBaseWiFi::SSID = "Villa_Pisin";
//String JMBaseWiFi::PASSWORD = "JKN_11deJulio";


void JMBaseWiFi::setupWiFi(){
	WiFi.mode(WIFI_STA);
  WiFi.hostname(JMBase::HostName);
  Serial.print("[WiFi] Connecting...");
	WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED && millis() < 20000) {
    Serial.print(".");
    delay(500);
  }
	if(WiFi.status() == WL_CONNECTED){
		Serial.println("connected!");
		Serial.print("[WiFi] SSID: ");
		Serial.println(WiFi.SSID());
		Serial.print("[WiFi] IP address: ");
		Serial.println(WiFi.localIP());
	}
	else{
		Serial.println("Error to connect!");
	}
}
	
#else
  #error "JMBaseWiFi solo es compatible con ESP32 o ESP8266"
#endif

