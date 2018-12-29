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

#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "***********.firebaseio.com"
#define FIREBASE_AUTH "************************"
#define WIFI_SSID "wifi_name"
#define WIFI_PASSWORD "wifi_password"

void setup() {
    Serial.begin(9600);
  //connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // set string value
  Firebase.setString("message from esp", "connected");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
}

int n = 0;
int l = 0;
int d1 = 0,d2 = 0,d3 = 0,d4 = 0,d5 = 0;

void loop() {
  Serial.begin(9600);
  Serial.println("");
  //Serial.println("-----------------------------------------------------");
  
  // set value
  ++l;
  Firebase.setInt("loop", l );
  // handle error
  if (Firebase.failed()) {
     //Serial.print("setting /loop failed:");
     //Serial.println(Firebase.error());  
      return;
  }
   // get value ------------------------------------------------
  d1 = Firebase.getInt("Device_1");
  // handle error
  if (Firebase.failed()) {
    //  Serial.print("getting /Device_1 failed:");
    //  Serial.println(Firebase.error());  
      return;
  }
  if(d1==1){
    Serial.println("11");  
  }else if(d1==0){                   
    Serial.println("10");
  }
  //--------------------------------------------------------------
    d2 = Firebase.getInt("Device_2");
  // handle error
  if (Firebase.failed()) {
    //  Serial.print("getting /Device_2 failed:");
    //  Serial.println(Firebase.error());  
      return;
  }
  if(d2==1){
    Serial.println("21");   
  }else if(d2==0){                   
    Serial.println("20");
  }
  //--------------------------------------------------------------
    d3 = Firebase.getInt("Device_3");
  // handle error
  if (Firebase.failed()) {
    //  Serial.print("getting /Device_3 failed:");
    //  Serial.println(Firebase.error());  
      return;
  }
  if(d3==1){
    Serial.println("31");  
  }else if(d3==0){                   
    Serial.println("30");
  }
  //--------------------------------------------------------------
    d4 = Firebase.getInt("Device_4");
  // handle error
  if (Firebase.failed()) {
    //  Serial.print("getting /Device_4 failed:");
    //  Serial.println(Firebase.error());  
      return;
  }
  if(d4==1){
    Serial.println("41"); 
  }else if(d4==0){                   
    Serial.println("40");
  }
  //--------------------------------------------------------------
    d5 = Firebase.getInt("Device_5");
  // handle error
  if (Firebase.failed()) {
    //  Serial.print("getting /Device_5 failed:");
    //  Serial.println(Firebase.error());  
      return;
  }
  if(d5==1){
    Serial.println("51");
  }else if(d5==0){                   
    Serial.println("50");
  }
  delay(500);
  //--------------------------------------------------------------
  /* 
  // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

  // remove value
  Firebase.remove("number");
  delay(1000);

  // set string value
  Firebase.setString("message", "hello world");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      //Serial.print("setting /truth failed:");
      //Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
  */
}
