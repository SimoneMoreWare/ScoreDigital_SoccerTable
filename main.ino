#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>

#define buzzer_pin 33
#define photoresistore_red_pin 32
#define photoresistore_blu_pin 35
#define soglia 2000

const char* ssid = "OPPO A52";
const char* password = "internet";

String ServerName = "https://studyroompoli.altervista.org/balilla/getdata.php?token=MullinB&goal=";

void checkgoal_red();
void checkgoal_blu();
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
  }
  delay(1);
}

void checkgoal_blu(){
  int analogValue = analogRead(photoresistore_blu_pin);
  if(analogValue<soglia){
    digitalWrite(buzzer_pin,HIGH);
    httpget(1);
    digitalWrite(buzzer_pin,LOW);
  }  
}

void httpget(int team){
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    String NameRequest = ServerName + String(team);
    http.begin(NameRequest); //Specify the URL
    int httpCode = http.GET();                                        //Make the requesT
    http.end(); //Free the resources
  }
}
