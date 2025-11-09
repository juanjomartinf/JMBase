#ifndef JMBase_h
#define JMBase_h

#include <Arduino.h>
#include "JMBaseMQTT.h"
#include "JMBaseOTA.h"
#include "JMBaseWiFi.h"

namespace JMBase {
	extern String HostName;
	
	void setBase(String hostname);
	void setBase(unsigned long baudrate);
	void setBase(unsigned long baudrate, String hostname);
	
	void setHostName(String hn);
	void beginSerial(unsigned long baud);
	void setLED(bool est);
}

#endif
