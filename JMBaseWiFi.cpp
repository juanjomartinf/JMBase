#include "JMBaseWiFi.h"

void JMBaseWiFi::connect(const char* ssid, const char* password) {
  Serial.print("[WiFi] Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(500);
    Serial.print(".");
    retries++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WiFi] Conectado. IP: " + WiFi.localIP().toString());
  } else {
    Serial.println("\n[WiFi] Error al conectar.");
  }
}

bool JMBaseWiFi::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

String JMBaseWiFi::getIP() {
  return WiFi.localIP().toString();
}
