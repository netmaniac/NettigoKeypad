#include <NettigoKeypad.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

NG_Keypad keypad;

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("hello, world!");
  
}

void loop(){
  int rd;
  rd = analogRead(0);
  Serial.println(rd , DEC);
  lcd.setCursor(0,1);
  lcd.print(keypad.key_pressed(rd),DEC);
  lcd.print("    ");
  delay(1000);
}
