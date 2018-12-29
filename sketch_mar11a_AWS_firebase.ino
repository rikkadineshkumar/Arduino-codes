#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#define dht_apin D2

// ssid and pass to connect WiFi AccessPoint 
const char* ssid = "wifi_name";
const char* password = "wifi_password";
// Server details
const int httpsPort = 443;
const char* host = "***********.firebaseio.com";
const char* user_id = "********************";
// WiFiClientSecure class to create TLS connection
WiFiClientSecure client;
// Json to store fetched data
StaticJsonBuffer<500> jsonBuffer;
StaticJsonBuffer<70> jsonBuffer_sensors;
//devices
boolean d0,d1,d2,d3;
//device on time off time
String strD0on, strD0off, strD1on, strD1off, strD2on, strD2off, strD3on, strD3off;
//device name
String d0_name,d1_name,d2_name,d3_name;
//sensors
int temp = 33, humi = 33, gas = 33;
//smoke sensor variables
int smokeA0 = A0;
//temperature sensor variables
dht DHT;
void setup() {
  //for Smoke sensor input from A0
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
  digitalWrite(D8,HIGH);
  
  pinMode(smokeA0, INPUT);
  pinMode(dht_apin,INPUT);
  Serial.begin(9600);
//  Serial.println();
//  Serial.print("connecting to ");
//  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  Serial.println("\nWiFi connected\nIP address local IP: ");
  Serial.println(WiFi.localIP());
  //gas sensor reading
  gas = analogRead(smokeA0);
  DHT.read11(dht_apin);
  temp=DHT.temperature;
  humi=DHT.humidity;
//  Serial.print("temp ::");Serial.println(temp);
//  Serial.print("humi ::");Serial.println(humi);
//  Serial.print("gas ::");Serial.println(gas);
}

void loop() {
  jsonBuffer.clear();
  jsonBuffer_sensors.clear();
  
  String strSensorJson = "";  
  JsonObject& sensors_json = jsonBuffer_sensors.createObject();
    sensors_json["temp"] = temp;
    sensors_json["humi"] = humi;
    sensors_json["gas"] = gas;
  sensors_json.printTo(strSensorJson);  
  
//  if (!client.connect(host, httpsPort)) {
//    //Serial.println("connection failed");
//    //Serial.println(host);
//    return;
//  }else{
//    //Serial.print("connected to host::")+
//    //Serial.println(host);  
//  }

  //d1 = getDeviceStatus(0);
  //d2 = getDeviceStatus(1);
  //Serial.println(strSensorJson);
  setSensorStatus(strSensorJson);
  //delay(500);
  getAllDeviceStatus();
  //setOnOffTime(2,strD3on,strD3off);
  
  //Data for arduino
  JsonObject& root = jsonBuffer.createObject();
  //root["d0"] = d0;
  root["t1"] = strD0on;
  root["t2"] = strD0off;
//  root["d0_name"] = d0_name;
//  
//  root["d1"] = d1;
//  root["d1OnTime"] = strD1on;
//  root["d1OffTime"] = strD1off;
//  root["d1_name"] = d1_name;
//
//  root["d2"] = d2;
//  root["d2OnTime"] = strD2on;
//  root["d2OffTime"] = strD2off;
//  root["d2_name"] = d2_name;
//
//  root["d3"] = d3;
//  root["d3OnTime"] = strD3on;
//  root["d3OffTime"] = strD3off;
//  root["d3_name"] = d3_name;
//  
  root["g"] = gas;
  root["t"] = temp;
  root["h"] = humi;
//  Serial.println(d0);
//  Serial.println(d1);
//  Serial.println(d2);
//  Serial.println(d3);
  root.printTo(Serial);
  delay(500);
  if(d0==false){
    digitalWrite(D5,HIGH);
  }else{
    digitalWrite(D5,LOW);;  
  }
  if(d1==false){
    digitalWrite(D6,HIGH);;
  }else{
    digitalWrite(D6,LOW);;  
  }
  if(d2==false){
    digitalWrite(D7,HIGH);;
  }else{
    digitalWrite(D7,LOW);;  
  }
  if(d3==false){
    digitalWrite(D8,HIGH);
  }else{
    digitalWrite(D8,LOW);  
  }
    
  //gas sensor reading
  gas = analogRead(smokeA0);
  //dht11 sensor reading
  DHT.read11(dht_apin);
  temp=DHT.temperature;
  humi=DHT.humidity;
}

//boolean getDeviceStatus(int i){
//    client.connect(host, httpsPort);
//    String line="";
//    client.print(String("GET ") + "/arduino/" + user_id + "/devices/"+i+"/onORoff.json" + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "User-Agent: BuildFailureDetectorESP8266\r\n" +
//               "Connection: close\r\n\r\n");
//    line = client.readStringUntil('\n');
//    while (client.connected()) {
//      String line = client.readStringUntil('\n');
//      if (line == "\r") {
//        //Serial.println("headers received");
//        break;
//      }
//    }
//    line = client.readStringUntil('\n');
//    //Serial.println(line);
//    if(line.equals("true")){
//        return true;
//     }else if(line.equals("false")){
//        return false; 
//     }
//}
void getAllDeviceStatus(){
  char charArr[250];
    StaticJsonBuffer<250> jsonBuffer;
    int s=0,p1,p2,p3,e;
    String s0,s1,s2,s3;
    HTTPClient http;
    http.begin("http://default-environment.b*****et.ap-south-1.elasticbeanstalk.com/HA/getAllDeviceStatus/Gj****************gHlJu1");
    int httpCode = http.GET();
    if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String line = http.getString();
            }
      } else {
//             USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
    http.end();

    p1 = line.indexOf("},{");
    p2 = line.indexOf("},{",p1+2);
    p3 = line.indexOf("},{",p2+2);
    e = line.indexOf("}]",p3);

//    Serial.println(p1);
//    Serial.println(p2);
//    Serial.println(p3);
//    Serial.println(e);

    s0 = line.substring(s+1,p1+1);
    s1 = line.substring(p1+2,p2+1);
    s2 = line.substring(p2+2,p3+1);
    s3 = line.substring(p3+2,e+1);

//    Serial.println(s0);
//    Serial.println(s1);
//    Serial.println(s2);
//    Serial.println(s3);

    line = "";
 
    s0.toCharArray(charArr,250);
    s0="";
    JsonObject& r = jsonBuffer.parseObject(charArr);
    jsonBuffer.clear();
//    r.prettyPrintTo(Serial);
    d0_name="";strD0on="";strD0off="";
    r["name"].printTo(d0_name);
    r["start_time"].printTo(strD0on);
    r["stop_time"].printTo(strD0off);
    d0 = r["onORoff"];

    s1.toCharArray(charArr,250);
    s1="";
    JsonObject& rr = jsonBuffer.parseObject(charArr);
    jsonBuffer.clear();
//    rr.prettyPrintTo(Serial);
   d1_name="";strD1on="";strD1off="";
    rr["name"].printTo(d1_name);
    rr["start_time"].printTo(strD1on);
    rr["stop_time"].printTo(strD1off);
    d1 = rr["onORoff"];

    s2.toCharArray(charArr,250);
    s2="";
    JsonObject& rrr = jsonBuffer.parseObject(charArr);
    jsonBuffer.clear();
//    rrr.prettyPrintTo(Serial);
   d2_name="";strD2on="";strD2off="";
    rrr["name"].printTo(d2_name);
    rrr["start_time"].printTo(strD2on);
    rrr["stop_time"].printTo(strD2off);
    d2 = rrr["onORoff"];

    s3.toCharArray(charArr,250);
    s3="";
    JsonObject& rrrr = jsonBuffer.parseObject(charArr);
    jsonBuffer.clear();
//    rrrr.prettyPrintTo(Serial);
    d3_name="";strD3on="";strD3off="";
    rrrr["name"].printTo(d3_name);
    rrrr["start_time"].printTo(strD3on);
    rrrr["stop_time"].printTo(strD3off);
    d3 = rrrr["onORoff"];
  }

void setSensorStatus(String v){
//    client.connect(host, httpsPort);
//    String line_put = "";
//    int content_length = v.length();
//    client.print(String("PUT") + " /Sensors.json" + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "Content-Type: application/json\r\n" +
//               "Cache-Control: no-cache\r\n" + 
//               "Content-Length: "+ content_length + "\r\n" +
//               //"Postman-Token: 311be439-6e12-6157-e145-0bdbcaf37b75\r\n"+
//               "\r\n"+v);
//    line_put = client.readString();
//    Serial.println(line_put);
//*********************************************
    HTTPClient http;
    http.begin("http://default-environment.bm******et.ap-south-1.elasticbeanstalk.com/HA/setSensorStatus");
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
    int httpCode = http.POST(v); 
//    if(httpCode > 0) {
//            // HTTP header has been send and Server response header has been handled
//            // file found at server
//            if(httpCode == HTTP_CODE_OK) {
//                String line = http.getString();
//            }
//      } else {
//             USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//      }
    http.end();
  }
 
//void setOnOffTime(int i,String &on_time,String &off_time){
//  client.connect(host, httpsPort);
//  String line="";
//  client.print(String("GET ") + "/arduino/" + user_id + "/devices/"+i+".json" + " HTTP/1.1\r\n" +
//             "Host: " + host + "\r\n" +
//             "User-Agent: BuildFailureDetectorESP8266\r\n" +
//             "Connection: close\r\n\r\n");
//  line = client.readStringUntil('\n');
//  while (client.connected()) {
//    String line = client.readStringUntil('\n');
//    if (line == "\r") {
//      //Serial.println("headers received");
//      break;
//    }
//  }
//  line = client.readStringUntil('\n');
//  char charArr[150] ;
//  line.toCharArray(charArr,150);
//  StaticJsonBuffer<150> jsonBuffer;
//  JsonObject& r = jsonBuffer.parseObject(charArr);
//  on_time="";
//  off_time="";
//  r["start_time"].printTo(on_time);
//  r["stop_time"].printTo(off_time);
//  jsonBuffer.clear();
//  }

