#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <LiquidCrystal.h>

// Create An LCD Object. Signals: [ RS=13, EN=12, D4=25, D5=26, D6=27, D7=14]
#define blu_button 18
#define red_button 19
#define buzzer_pin 22
int bluLastState = HIGH; // the previous state from the input pin
int bluCurrentState;     // the current reading from the input pin
int redLastState = HIGH;
int redCurrentState;
int red_score=0;
int blu_score=0;
LiquidCrystal lcd(13, 12, 25, 26, 27, 14);
const char* ssid = "CEUR Mollino";
const char* password = "";

void OTAupload();
void init_display();
void blubutton();
void redbutton();

void setup() {
  OTAupload();
  init_display(); 
  pinMode(blu_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  ArduinoOTA.handle();
  blubutton();
  redbutton();
}

void OTAupload(){
  //Serial.begin(115200);
  //Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    //Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);
  // Hostname defaults to esp3232-[MAC]
  // ArduinoOTA.setHostname("myesp32");
  // No authentication by default
  // ArduinoOTA.setPassword("admin");
  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  ArduinoOTA
  .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      //Serial.println("Start updating " + type);
    });
    //.onEnd([]() {
    //Serial.println("\nEnd");
    //})
    //.onProgress([](unsigned int progress, unsigned int total) {
    //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    //})
    /*.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });*/
  ArduinoOTA.begin();
  //Serial.println("Ready");
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
}

void init_display(){
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rosso");
  lcd.setCursor(7,0);
  lcd.print("|");
  lcd.setCursor(8,0);
  lcd.print("Blu");
  lcd.setCursor(0,1);
  lcd.print(red_score);
  lcd.setCursor(7,1);
  lcd.print("|");
  lcd.setCursor(8,1);
  lcd.print(blu_score);
}

void blubutton(){
  bluCurrentState = digitalRead(blu_button);
  if(bluLastState == LOW && bluCurrentState == HIGH){
    if(blu_score==0) blu_score=10;
    lcd.setCursor(8,1);
    lcd.print(--blu_score);
    digitalWrite(buzzer_pin,HIGH);
    delay(600 );
    digitalWrite(buzzer_pin,LOW);
  }
  bluLastState = bluCurrentState;
  delay(100);
}

void redbutton(){
  redCurrentState = digitalRead(red_button);
  if(redLastState == LOW && redCurrentState == HIGH){
    if(red_score==0) red_score=10;
    lcd.setCursor(0,1);
    lcd.print(--red_score);
    digitalWrite(buzzer_pin,HIGH);
    delay(600);
    digitalWrite(buzzer_pin,LOW);
  }
  redLastState = redCurrentState;
  delay(100);
}
