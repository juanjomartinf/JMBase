#include "JMBase.h"

String JMBase::HostName = "";

void JMBase::setBase(unsigned long baudrate){

	beginSerial(baudrate);
}

void JMBase::setBase(String hostname){
	
	setHostName(hostname);
}

void JMBase::setBase(unsigned long baudrate, String hostname){

	beginSerial(baudrate);
	
	setHostName(hostname);
}

/*************************************************/
void JMBase::beginSerial(unsigned long baud) {
  Serial.begin(baud);
  while (!Serial);
  Serial.println("JMBase iniciado correctamente");
}

void JMBase::setHostName(String hn){
	HostName = hn;
}