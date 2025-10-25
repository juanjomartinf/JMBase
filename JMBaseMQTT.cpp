#include "JMBaseMQTT.h"
#include "JMBase.h"

#if defined(ARDUINO_ARCH_ESP32)

#elif defined(ARDUINO_ARCH_ESP8266)

#else
  #error "JMBaseWiFi solo es compatible con ESP32 o ESP8266"
#endif

WiFiClient wifiClient;
PubSubClient mqttclient(wifiClient);

const char* MQTTServer = "domotica2j.duckdns.org";

String JMBaseMQTT::Topic = "";

#define TiempoMQTT        600  
#define TiempoSignal       60

unsigned long int TIEMPO_WIFI = 0;

int timerMQTT = 0, timerSignal = 0;
	
	
static JMBaseMQTT::OnMQTTConnectCallback onConnectUser = nullptr;
static JMBaseMQTT::RecibirMensajeCallback recibirMensajeUsuario = nullptr;

// --- 2️.Función que ejecuta el callback cuando llega un mensaje MQTT ---
void JMBaseMQTT::procesarMensaje(char* topic, byte* payload, unsigned int length) {
  String mensaje="";
  for (int i=0;i<length;i++) {
    mensaje.concat((char)payload[i]);
  }
  //Serial.print("REC ");Serial.print(topic);Serial.print(" = ");Serial.println(mensaje);
	
	if(String(topic) == Topic + "/_Debug"){
    if(mensaje == "TIME"){
      JMBaseMQTT::pubMQTT(String(Topic + "/_Debug/Time"), String(millis()/1000));
    }
    else if(mensaje == "RESET"){
      ESP.restart();
    }
  }
	else{
		recibirMensajeUsuario(String(topic), mensaje);
	}
}



// --- tu código existente ---

void JMBaseMQTT::setupMQTT(String topic, OnMQTTConnectCallback oc, RecibirMensajeCallback rm){
  mqttclient.setServer(MQTTServer, 1883);
	
	onConnectUser = oc;
	
	recibirMensajeUsuario = rm;
  mqttclient.setCallback(procesarMensaje);
	
	Topic = topic;
}

void JMBaseMQTT::pubMQTT(String topic, String mensaje){
  if(WiFi.status() == WL_CONNECTED && mqttclient.connected()){
    char top[50], msg[50];
    mensaje.toCharArray(msg, 50);
    topic.toCharArray(top, 50);
    mqttclient.publish(top, msg, true);
  }
}

void JMBaseMQTT::subMQTT(String topic){
  char top[50];
  topic.toCharArray(top, 50);
  mqttclient.subscribe(top);
}

void JMBaseMQTT::loopTimerWiFi(){
  if(millis() - TIEMPO_WIFI >= 1000) {
    if(timerMQTT > 0){
      timerMQTT--;
    }

    if(timerSignal > 0){
      timerSignal--;
    }

    TIEMPO_WIFI = millis();
  }
}


void JMBaseMQTT::loopMQTT(){
  loopTimerWiFi();
  
  if(WiFi.status() == WL_CONNECTED){                  // hay WIFI
    if(mqttclient.connected()){                         // hay MQTT
      mqttclient.loop();
      if(timerSignal == 0){
        pubMQTT(String(Topic + "/_Debug/Signal"), String(WiFi.RSSI()));
        timerSignal = TiempoSignal;
      }
    }
    else{                                               // NO hay MQTT
      if(timerMQTT == 0){
        Serial.print("\n[MQTT] Conectando...");
        if(mqttclient.connect(JMBase::HostName.c_str(), "Juanjo", "sudoKaiser", String(Topic + "/_Debug/Status").c_str(), 2, true, "Offline")){
          timerMQTT = 0;
          //Pub-Sub SYSTEM
          subMQTT(Topic + "/_Debug");
          pubMQTT(Topic + "/_Debug/Status", "Online");
          pubMQTT(Topic + "/_Debug/IP", String(WiFi.localIP().toString().c_str()));
          pubMQTT(Topic + "/_Debug/Signal", String(WiFi.RSSI()));
          pubMQTT(Topic + "/_Debug/Time", "Ready");
					//Pub-Sub PROJECT
          if (onConnectUser){ 
						onConnectUser();
					}
					Serial.println("[MQTT] Listo. Suscripciones y Publicaciones realizadas.");
        }
        else{
          Serial.println("[MQTT] Error to connect!");
          timerMQTT = TiempoMQTT;
        }
      }
    }
  }
  else{                                               // NO hay WIFI
    if(timerMQTT == 0){
			JMBaseWiFi::reconnect();
			
      if(WiFi.status() == WL_CONNECTED){
        timerMQTT = 0;
      }
      else{
        timerMQTT = TiempoMQTT;
      }
    }
  }
}