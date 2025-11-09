#include "JMBase.h"

String JMBase::HostName = "";

void JMBase::setBase(String hostname){
	setHostName(hostname);
	setLED(false);
}

void JMBase::setBase(unsigned long baudrate){
	beginSerial(baudrate);
	setLED(false);
}

void JMBase::setBase(unsigned long baudrate, String hostname){
	beginSerial(baudrate);
	setHostName(hostname);
	setLED(false);
}

/*************************************************/
void JMBase::setHostName(String hn){
	HostName = hn;
}

void JMBase::beginSerial(unsigned long baud) {
  Serial.begin(baud);
  while (!Serial);
  Serial.println("JMBase iniciado correctamente");
}

void JMBase::setLED(bool est){
	pinMode(LED_BUILTIN, OUTPUT);
	
	#ifdef Negative_Logic
	if(est){
		digitalWrite(LED_BUILTIN, LOW);
	}
	else{
		digitalWrite(LED_BUILTIN, HIGH);
	}
	#else
	if(est){
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else{
		digitalWrite(LED_BUILTIN, LOW);
	}
	#endif
}