/*
Example how to read selected key from Nettigo Keypad.

Uses:
 - Arduino
 - LCD Kit from Nettigo (but could be any LCD display compatible with LiquidCrystal library)
 - Nettigo Keypad
 
 Connect:
 LCD:
 1 - GND
 2 - +5V
 3 - 10k pot output
 4 - D2 on Arduino
 5 - GND
 6 - D3 on Arduino
 7 - 10 - not connected
 11 - 14 - D4-D7 on Arduino
 15 - +5V (backlight)
 16 - GND
 
 Nettigo Keypad:
 AD1:
  1 (marked with square pad) - +5V
  2 - A0 on Arduino
  3 - GND
*/
#include <NettigoKeypad.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

NG_Keypad keypad;

char* keys[] = { "NONE", "SELECT", "LEFT", "DOWN", "UP", "RIGHT" };

void up_was_pressed() {
 lcd.print("it goes UP ");
}

void setup(){
  lcd.begin(16,2);
  lcd.print("Selected key:");
  keypad.register_handler(NG_Keypad::UP, up_was_pressed); 
}

void loop(){
  int rd;
  rd = analogRead(0);
  lcd.setCursor(0,1);
  keypad.check_handlers(rd);
  lcd.print( keys[ keypad.key_pressed(rd) ] );
  lcd.print("           ");
  delay(100);
}
