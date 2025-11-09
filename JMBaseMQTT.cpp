#include "JMBaseMQTT.h"
#include "JMBase.h"

/******************************************** Timer MQTT **************************************************/
#define TiempoMQTT        10  
#define TiempoSignal       60

unsigned long int TIEMPO_WIFI = 0;

int timerMQTT = 0, timerSignal = 0;

void JMBaseMQTT::loopTimerWiFi(){
  if(millis() - TIEMPO_WIFI >= 1000) {
    if(timerMQTT > 0){
      timerMQTT--;
			#ifdef PrintTimerMQTT
			Serial.print("[WiFi] Reconnecting in ... "); Serial.println(timerMQTT);
			#endif
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
String JMBaseMQTT::server_MQTT;
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

void JMBaseMQTT::subMQTT(String topic){
  char top[50];
  topic.toCharArray(top, 50);
  mqttclient.subscribe(top);
}

void JMBaseMQTT::callBack(char* topic, byte* payload, unsigned int length) {
	String mensaje="";
  for (int i=0;i<length;i++) {
    mensaje.concat((char)payload[i]);
  }
  //Serial.print("REC ");Serial.print(topic);Serial.print(" = ");Serial.println(mensaje);
	
	if(String(topic) == Topic + "/_Debug"){
    if(mensaje == "TIME"){
      JMBaseMQTT::pubMQTT("_Debug/Time", String(millis()/1000));
    }
    else if(mensaje == "RESET"){
      ESP.restart();
    }
  }
	else{
		recibirMensaje(String(topic), mensaje);
	}
}

void JMBaseMQTT::setupMQTT(String user_mqtt, String pass_mqtt, String server_mqtt, String topic){
	
	user_MQTT = user_mqtt;
	pass_MQTT = pass_mqtt;
	server_MQTT = server_mqtt;
	
	mqttclient.setServer(server_MQTT.c_str(), 1883);
	
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
        timerSignal = TiempoSignal;
      }
    }
    else{                                               // NO hay MQTT
			JMBase::setLED(false);
      if(timerMQTT == 0){
        Serial.print("[MQTT] Connecting...");
        if(mqttclient.connect(JMBase::HostName.c_str(), user_MQTT.c_str(), pass_MQTT.c_str(), String("/_Debug/Status").c_str(), 2, true, "Offline")){
					Serial.print("connected to ");
					Serial.println(server_MQTT);
          JMBase::setLED(true);
					timerMQTT = 0;
          //Pub-Sub SYSTEM
          subMQTT("_Debug");
          pubMQTT("_Debug/Status", "Online");
          pubMQTT("_Debug/IP", String(WiFi.localIP().toString().c_str()));
          pubMQTT("_Debug/Signal", String(WiFi.RSSI()));
          pubMQTT("_Debug/Time", "Ready");
					//Pub-Sub_PROJECT
          if(pubSub_Project){ 
						pubSub_Project();
					}
					Serial.println("[MQTT] Ready. Subscriptions and publications made.");
        }
        else{
					JMBase::setLED(false);
          timerMQTT = TiempoMQTT;
          Serial.println("Error to connect!");
          Serial.println("[WiFi] Next reconnection in "+String(TiempoMQTT)+" seconds...");
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