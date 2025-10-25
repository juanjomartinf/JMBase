#ifndef JMBase_h
#define JMBase_h

#include <Arduino.h>
#include "JMBaseMQTT.h"
#include "JMBaseOTA.h"
#include "JMBaseWiFi.h"

namespace JMBase {
	extern String HostName;
	
	void setBase(unsigned long baudrate, String hostname);
	void beginSerial(unsigned long baud);
	void setHostName(String hn);
}

#endif
