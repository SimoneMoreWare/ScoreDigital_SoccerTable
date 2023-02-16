#include <LiquidCrystal.h>
 
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal lcd(13, 12, 25, 26, 27, 14);
 
void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rosso");
  lcd.setCursor(7,0);
  lcd.print("|");
  lcd.setCursor(8,0);
  lcd.print("Blu");
  lcd.setCursor(0,1);
  lcd.print(0);
  lcd.setCursor(7,1);
  lcd.print("|");
  lcd.setCursor(8,1);
  lcd.print(0);
}
 
void loop()
{
  
}
