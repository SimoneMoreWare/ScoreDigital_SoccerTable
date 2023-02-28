#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>

#define buzzer_pin 33
#define photoresistore_blu_pin 32
#define photoresistore_red_pin 34
#define soglia 2000

const char* ssid = "OPPO A52";
const char* password = "internet";
                
String ServerName = "http://ec2-34-250-23-168.eu-west-1.compute.amazonaws.com/increment/";

void checkgoal_blu();
void checkgoal_red();
void checkconnection();
void httpget(int team);

void setup() {
  checkconnection();
  pinMode(buzzer_pin,OUTPUT);
}

void loop() {
  checkgoal_red();
  checkgoal_blu();
  delay(1);
}

void checkconnection(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(1000);  
}

void checkgoal_red(){
  int analogValue = analogRead(photoresistore_red_pin);
  if(analogValue<soglia){
    digitalWrite(buzzer_pin,HIGH);
    httpget(0);
    digitalWrite(buzzer_pin,LOW);
    delay(3500);
  }  

}

void checkgoal_blu(){
  int analogValue = analogRead(photoresistore_blu_pin);
  if(analogValue<soglia){
    digitalWrite(buzzer_pin,HIGH);
    httpget(1);
    digitalWrite(buzzer_pin,LOW);
    delay(3500); 
  }  

}

void httpget(int team){
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    String NameRequest = ServerName + String(team) + String("/eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9");
    http.begin(NameRequest); //Specify the URL
    int httpCode = http.GET();                                        //Make the requesT
    http.end(); //Free the resources
  }
}
