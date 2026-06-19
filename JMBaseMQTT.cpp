#include "JMBaseMQTT.h"
#include "JMBase.h"

/******************************************** Timer MQTT **************************************************/
#define TiempoMQTT        10  
#define TiempoSignal      60

unsigned long int TIEMPO_WIFI = 0;

int timerMQTT = 0, timerSignal = 0;

void JMBaseMQTT::loopTimerWiFi(){
  if(millis() - TIEMPO_WIFI >= 1000) {
    if(timerMQTT > 0){
      timerMQTT--;
			//Serial.print("[WiFi] Reconnecting in ... "); Serial.println(timerMQTT);
    }

    if(timerSignal > 0){
      timerSignal--;
    }

    TIEMPO_WIFI = millis();
  }
}
/******************************************** Timer MQTT **************************************************/


/******************************************** MQTT ********************************************************/
WiFiClient wifiClient;
PubSubClient mqttclient(wifiClient);

String JMBaseMQTT::user_MQTT;
String JMBaseMQTT::pass_MQTT;
String JMBaseMQTT::Topic;
String JMBaseMQTT::TopicSub;
	
static JMBaseMQTT::pubSubProject_Callback pubSub_Project = nullptr;
static JMBaseMQTT::OnReceiveMessage_CallBack recibirMensaje = nullptr;


void JMBaseMQTT::pubMQTT(String topic, String mensaje){
  if(WiFi.status() == WL_CONNECTED && mqttclient.connected()){
    //char top[50], msg[50];
    //mensaje.toCharArray(msg, 50);
    //topic.toCharArray(top, 50);
    mqttclient.publish((Topic + "/" + topic).c_str(), mensaje.c_str(), true);
  }
}

void JMBaseMQTT::pubMQTT(String topic, String mensaje, bool retained){
  if(WiFi.status() == WL_CONNECTED && mqttclient.connected()){
    //char top[50], msg[50];
    //mensaje.toCharArray(msg, 50);
    //topic.toCharArray(top, 50);
    mqttclient.publish((Topic + "/" + topic).c_str(), mensaje.c_str(), retained);
  }
}

void JMBaseMQTT::subMQTT(String topic){
  //char top[50];
  //topic.toCharArray(top, 50);
  mqttclient.subscribe((Topic + "/" + topic).c_str());
}
void JMBaseMQTT::subMQTT_ext(String topic){
  //char top[50];
  //topic.toCharArray(top, 50);
  mqttclient.subscribe((topic).c_str());
}

void JMBaseMQTT::callBack(char* topic, byte* payload, unsigned int length) {
	String mensaje="";
  for (int i=0;i<length;i++) {
    mensaje.concat((char)payload[i]);
  }
  //Serial.print("REC ");Serial.print(topic);Serial.print(" = ");Serial.println(mensaje);
	
	if(String(topic).endsWith("/_Debug")){
    if(mensaje == "TIME"){
      pubMQTT("_Debug/Time", String(millis()/1000));
    }
    else if(mensaje == "RESET"){
      ESP.restart();
    }
		else if(mensaje == "UPDATE"){
			HTTP_OTA();
		}
  }
	else{
		recibirMensaje(String(topic), mensaje);
	}
}

void JMBaseMQTT::setupMQTT(String user_mqtt, String pass_mqtt, String topic){
	
	user_MQTT = user_mqtt;
	pass_MQTT = pass_mqtt;
	
	mqttclient.setServer(JMBaseWiFi::MQTTServer, 1883);
	
	Topic = topic;
	TopicSub = topic + "/_Set";
}
void JMBaseMQTT::setCallBacks(pubSubProject_Callback oc, OnReceiveMessage_CallBack rm){
	pubSub_Project = oc;
	recibirMensaje = rm;
  mqttclient.setCallback(callBack);
}

void JMBaseMQTT::loopMQTT(){
  loopTimerWiFi();
  
  if(WiFi.status() == WL_CONNECTED){                  // hay WIFI
    if(mqttclient.connected()){                         // hay MQTT
      mqttclient.loop();
			JMBase::setLED(true);
      if(timerSignal == 0){
        pubMQTT("_Debug/Signal", String(WiFi.RSSI()));
		#if defined(ARDUINO_ARCH_ESP32)
		float tempC = (temprature_sens_read() - 32) / 1.8;
		pubMQTT("_Debug/Temperature", String(tempC));
		#endif
        timerSignal = TiempoSignal;
      }
    }
    else{                                               // NO hay MQTT
			JMBase::setLED(false);
      if(timerMQTT == 0){
        Serial.print("[MQTT] Connecting...");
        if(mqttclient.connect(JMBase::HostName.c_str(), user_MQTT.c_str(), pass_MQTT.c_str(), String(Topic + "/_Debug/Status").c_str(), 2, true, "Offline")){
					Serial.print("connected to ");
					Serial.println(JMBaseWiFi::MQTTServer);
          JMBase::setLED(true);
					timerMQTT = 0;
          //Pub-Sub SYSTEM
          subMQTT("_Debug");
          pubMQTT("_Debug/Status", "Online");
					pubMQTT("_Debug/Update_status", "OK");
          pubMQTT("_Debug/IP", String(WiFi.localIP().toString().c_str()));
          pubMQTT("_Debug/Signal", String(WiFi.RSSI()));
          pubMQTT("_Debug/Time", "Ready");
					//Pub-Sub_PROJECT
          if(pubSub_Project){ 
						pubSub_Project();
					}
					Serial.println("[MQTT] Ready. Subscriptions and publications are made.");
        }
        else{
					JMBase::setLED(false);
          timerMQTT = TiempoMQTT;
          Serial.println("Error to connect!");
          Serial.println("[MQTT] Next reconnection in "+String(TiempoMQTT)+" seconds...");
        }
      }
    }
  }
  else{                                               // NO hay WIFI
		JMBase::setLED(false);
    if(timerMQTT == 0){
			JMBaseWiFi::reconnect();
			
      if(WiFi.status() == WL_CONNECTED){
        timerMQTT = 0;
				Serial.println("connected!");
				Serial.print("[WiFi] SSID: ");
				Serial.println(WiFi.SSID());
				Serial.print("[WiFi] IP address: ");
				Serial.println(WiFi.localIP());
      }
	  else{
        timerMQTT = TiempoMQTT;
				Serial.println("Error to connect!");
				Serial.println("[WiFi] Next reconnection in "+String(TiempoMQTT)+" seconds...");
      }
    }
  }
}
/******************************************** HTTP OTA ********************************************************/

void JMBaseMQTT::HTTP_OTA() {
	
  Serial.println(String("[HTTP_OTA] => Starting update"));
  pubMQTT("_Debug/Update_status", "downloading...");
  Serial.println(String("[HTTP_OTA] => downloading..."));
	
  delay(1000);
  #if defined(ARDUINO_ARCH_ESP32)
    // Opcional: tiempo de espera
    httpUpdate.rebootOnUpdate(true); // si OK, reinicia automáticamente
    httpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	String url = "http://";
	url.concat(JMBaseWiFi::HAServer.toString());
	url.concat(":8123/local/firmware/0.bin");
	
	Serial.println(url);

	t_httpUpdate_return ret = httpUpdate.update(wifiClient, url);
	
	switch (ret) {
      case HTTP_UPDATE_FAILED:
        pubMQTT("_Debug/Update_status", String("fail: ") + httpUpdate.getLastErrorString());
      break;

      case HTTP_UPDATE_NO_UPDATES:
        pubMQTT("_Debug/Update_status", "no_update");
      break;

      case HTTP_UPDATE_OK:
        // Si rebootOnUpdate(true), normalmente no llega aquí (reinicia).
        pubMQTT("_Debug/Update_status", "ok");
      break;
	}
	
  #elif defined(ARDUINO_ARCH_ESP8266)
    ESPhttpUpdate.rebootOnUpdate(true);
    ESPhttpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	String url = "http://";
	url.concat(JMBaseWiFi::HAServer.toString());
	url.concat(":8123/local/firmware/0.bin");
	
	Serial.println(url);	
	
	
	t_httpUpdate_return ret = ESPhttpUpdate.update(wifiClient, url);
	
	switch (ret) {
      case HTTP_UPDATE_FAILED:
        pubMQTT("_Debug/Update_status", String("fail: ") + ESPhttpUpdate.getLastErrorString());
      break;

      case HTTP_UPDATE_NO_UPDATES:
        pubMQTT("_Debug/Update_status", "no_update");
      break;

      case HTTP_UPDATE_OK:
        // Si rebootOnUpdate(true), normalmente no llega aquí (reinicia).
        pubMQTT("_Debug/Update_status", "ok");
      break;
	}

  #endif
}
