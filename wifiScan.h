
#ifndef wifiScan_h
#define wifiScan_h

#include "ESP8266WiFi.h"

class wifiScan
{
public:
	int idNumber;
	String wifiSSID;
	String wifiRSSI;
	String wifiEncryption;

};


#endif