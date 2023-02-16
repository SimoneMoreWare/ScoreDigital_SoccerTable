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
    delay(1000);
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
    delay(1000);
    digitalWrite(buzzer_pin,LOW);
  }
  redLastState = redCurrentState;
  delay(100);
}
 
void setup()
{
  // set up the LCD's number of columns and rows:
  init_display(); 
  pinMode(blu_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(buzzer_pin, OUTPUT);

}
 
void loop()
{
  blubutton();
  redbutton();
}
