#include "JMBase.h"

String JMBase::HostName = "";
bool JMBase::Logic;

void JMBase::setBase(String hostname, bool logic){
	setHostName(hostname);
	Logic = logic;
	pinMode(LED_BUILTIN, OUTPUT);
	setLED(false);
}

void JMBase::setBase(unsigned long baudrate, bool logic){
	beginSerial(baudrate);
	Logic = logic;
	pinMode(LED_BUILTIN, OUTPUT);
	setLED(false);
}

void JMBase::setBase(unsigned long baudrate, String hostname, bool logic){
	beginSerial(baudrate);
	setHostName(hostname);
	Logic = logic;
	pinMode(LED_BUILTIN, OUTPUT);
	setLED(false);
}

/*************************************************/
void JMBase::setHostName(String hn){
	HostName = hn;
}

void JMBase::beginSerial(unsigned long baud) {
  Serial.begin(baud);
  while (!Serial);
  Serial.println("\n\nJMBase iniciado correctamente");
}

void JMBase::setLED(bool est){
	if(Logic){			//logica positiva
		if(est){
			digitalWrite(LED_BUILTIN, HIGH);
		}
		else{
			digitalWrite(LED_BUILTIN, LOW);
		}
	}
	else{						//logica negativa
		if(est){
			digitalWrite(LED_BUILTIN, LOW);
		}
		else{
			digitalWrite(LED_BUILTIN, HIGH);
		}
	}
}