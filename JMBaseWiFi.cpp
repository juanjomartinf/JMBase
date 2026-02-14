#include "JMBaseWiFi.h"

// Selección automática de la librería WiFi correcta según la placa
#if defined(ARDUINO_ARCH_ESP32)
WiFiMulti wifiMulti;
#elif defined(ARDUINO_ARCH_ESP8266)
ESP8266WiFiMulti wifiMulti;
#else
  #error "JMBaseWiFi solo es compatible con ESP32 o ESP8266"
#endif

IPAddress JMBaseWiFi::MQTTServer;
IPAddress JMBaseWiFi::HAServer;


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
		calcularServers();
		Serial.print("[WiFi] IP MQTTServer: ");
    Serial.println(MQTTServer.toString());
		Serial.print("[WiFi] IP HAServer: ");
    Serial.println(HAServer.toString());
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

void JMBaseWiFi::calcularServers(){
	IPAddress gw = WiFi.gatewayIP();                // Ej: 192.168.X.1
  MQTTServer = IPAddress(gw[0], gw[1], gw[2], 2);  // -> 192.168.X.2
	HAServer = IPAddress(gw[0], gw[1], gw[2], 5);  // -> 192.168.X.5
}