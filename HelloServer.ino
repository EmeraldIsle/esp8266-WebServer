#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index.h"
#include "sConfig.h"
#include "wifiScan.h"


const char* ssid = "SSID HERE";
const char* password = "PASSWORD HERE";

ESP8266WebServer server(9000);

const int led = 13;

void blinkLed()
{
	digitalWrite(D1, HIGH);
	delay(1000);
	digitalWrite(D1, LOW);
	delay(1000);
	digitalWrite(D1, HIGH);
	delay(1000);
	digitalWrite(D1, LOW);
}

wifiScan handleWifiSetup()
{

	/*String index = Conf_page;

	server.send(200, "text/html", index);*/

	wifiScan scanner = new wifiScan();

	int n = WiFi.scanNetworks();
	Serial.println("scan done");
	if (n == 0)
		Serial.println("no networks found");
	else
	{
		
		
		Serial.print(n);
		Serial.println(" networks found");
		for (int i = 0; i < n; ++i)
		{
			// Print SSID and RSSI for each network found
			scanner.idNumber += (i + 1);
			scanner.wifiSSID += (WiFi.SSID(i));
			//scanner.wifiRSSI = (WiFi.RSSI(i));
			scanner.wifiEncryption += ((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
			/*Serial.print(i + 1);
			Serial.print(": ");
			Serial.print(WiFi.SSID(i));
			Serial.print(" (");
			Serial.print(WiFi.RSSI(i));
			Serial.print(")");
			Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");*/
			delay(10);
		}
	}
	jsonEncode();
	return scanner;
}
String jsonEncode()
{
	
	
	// Encodes JSON
	String encode;
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	root["sensor"] = "gps";
	root["time"] = 1351824120;

	JsonArray& data = root.createNestedArray("data");
	data.add(48.56, 6); //6 is number of decimals
	data.add(2.302038, 6);
	root.printTo(encode);
	return encode;
}
void handleApi()
{
	
		StaticJsonBuffer<200> newBuffer;
		JsonObject& newjson = newBuffer.parseObject(server.arg("plain"));
		
		bool LedState = newjson["led1"];
		bool FlashLed = newjson["flash"];


		if (LedState == true) {
			digitalWrite(D1, HIGH);
		}
		else
		{
			digitalWrite(D1, LOW);
		}


		server.send(200, "text/html", "LED STATE " + String(LedState));
	
}

void handleRoot() {

	String index = MAIN_page;
	server.send(200, "text/html", index);


}


void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
	message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(D1, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);


  //WiFi.begin(ssid, password);


  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
	Serial.println("MDNS responder started");
  }
  /*
  * URI Handling 
  *
  */
  server.on("/", handleRoot);

  server.on("/inline", [](){
	server.send(200, "text/plain", "this works as well");
  });
  // api URI
  server.on("/api/", HTTP_POST, []() {
	  handleApi(); 
  });
  
  server.on("/setup", HTTP_GET, []() {
	wifiScan scanned = handleWifiSetup();
	 /* String index = Conf_page;
	  server.send(200, "text/html", index);*/
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
