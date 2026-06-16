#include "JMBase.h"

String JMBase::HostName = "";
bool JMBase::Logic;

void JMBase::setBase(String hostname){
	beginSerial(115200);
	setHostName(hostname);
	Logic = true;
	//pinMode(LED_BUILTIN, OUTPUT);
	//setLED(false);
}

void JMBase::setBase(String hostname, bool logic){
	beginSerial(115200);
	setHostName(hostname);
	Logic = logic;
	//pinMode(LED_BUILTIN, OUTPUT);
	//setLED(false);
}

void JMBase::setBase(unsigned long baudrate, String hostname){
	beginSerial(baudrate);
	setHostName(hostname);
	Logic = true;
	//pinMode(LED_BUILTIN, OUTPUT);
	//setLED(false);
}

void JMBase::setBase(unsigned long baudrate, String hostname, bool logic){
	beginSerial(baudrate);
	setHostName(hostname);
	Logic = logic;
	//pinMode(LED_BUILTIN, OUTPUT);
	//setLED(false);
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

void JMBase::setLED(bool est){ //cuando CONEXION es OK -> setLED(true)
/*
	if(Logic){			//logica positiva
		if(est){
			digitalWrite(LED_BUILTIN, LOW);
		}
		else{
			digitalWrite(LED_BUILTIN, HIGH);
		}
	}
	else{						//logica negativa
		if(est){
			digitalWrite(LED_BUILTIN, HIGH);
		}
		else{
			digitalWrite(LED_BUILTIN, LOW);
		}
	}
*/
}