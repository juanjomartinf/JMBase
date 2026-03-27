#ifndef JMBase_h
#define JMBase_h

#include <Arduino.h>
#include "JMBaseMQTT.h"
#include "JMBaseWiFi.h"

namespace JMBase {
	extern String HostName;
	extern bool Logic;
	
	void setBase(String hostname);
	void setBase(String hostname, bool logic);
	void setBase(unsigned long baudrate, String hostname);
	void setBase(unsigned long baudrate, String hostname, bool logic);
	
	void setHostName(String hn);
	void beginSerial(unsigned long baud);
	void setLED(bool est);
}

#endif