#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <ESP8266HTTPClient.h>

const char* ssid = "mkS!ngh";
const char* password = "manish@6588";
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED){//Check WiFi connection status
    
    HTTPClient http;  //Declare an object of class HTTPClient
    HTTPClient http2;
    
    http.begin("http://homeautomation-env.48fi6jjnfj.ap-south-1.elasticbeanstalk.com/Arduino/1/1");
    http2.begin("http://homeautomation-env.48fi6jjnfj.ap-south-1.elasticbeanstalk.com/Arduino/1/2");
    
    int httpCode = http.GET();
    int httpCode2 = http2.GET();
    
    //Send the request
    if (httpCode > 0) {
      String payload = http.getString(); 
      if(payload.equals("1")){
        Serial.println("1");
        //digitalWrite(LED_BUILTIN, LOW);
      }else{
        Serial.println("0");  
      }
    }
    http.end();   //Close connection

  if (httpCode2 > 0) {
      String payload2 = http2.getString(); 
      if(payload2.equals("1")){
        Serial.println("2");
      }else{
        Serial.println("3");  
      }
    }
    http2.end();   //Close connection
  }
  delay(250);    //Send a request every 30 seconds
}
