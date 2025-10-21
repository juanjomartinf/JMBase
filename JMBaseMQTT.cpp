#include "JMBaseMQTT.h"

static WiFiClient wifiClient;
static PubSubClient mqttClient(wifiClient);
static String mqttServer;
static uint16_t mqttPort;

void JMBaseMQTT::begin(const char* server, uint16_t port) {
  mqttServer = server;
  mqttPort = port;
  mqttClient.setServer(server, port);
}

void JMBaseMQTT::loop() {
  if (!mqttClient.connected()) {
    Serial.println("[MQTT] Intentando reconectar...");
    if (mqttClient.connect("JMBaseClient")) {
      Serial.println("[MQTT] Conectado al broker");
    } else {
      delay(5000);
      return;
    }
  }
  mqttClient.loop();
}

void JMBaseMQTT::publish(const char* topic, const char* payload) {
  mqttClient.publish(topic, payload);
}

void JMBaseMQTT::subscribe(const char* topic) {
  mqttClient.subscribe(topic);
}

void JMBaseMQTT::setCallback(MQTT_CALLBACK_SIGNATURE) {
  mqttClient.setCallback(callback);
}
