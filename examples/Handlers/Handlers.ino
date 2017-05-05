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

//Stanadalone LCD connected as in comments above
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

/*
 * For LCD shields with integrated keypad
 * 
 * https://nettigo.pl/products/shield-lcd-2x16-z-klawiatura-do-arduino
 * https://nettigo.pl/products/znakowy-shield-lcd-2x16
 */
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


/* For Nettigo Keypad
 *  https://nettigo.pl/products/keypad-odczyt-przez-wejscie-analogowe
 */
NG_Keypad keypad;

/*
 * For LCD shields linked above
 */

 /*
NG_Keypad keypad(
  NG_Keypad::SELECT, 872,
  NG_Keypad::LEFT, 600,
  NG_Keypad::DOWN, 393,
  NG_Keypad::UP, 218,
  NG_Keypad::RIGHT, 65);
*/

//This function will be called when key UP was pressed
//just write more on LCD
void up_was_pressed() {
 lcd.print("it goes UP");
}

void down_was_pressed() {
 lcd.print("it goes DOWN");
}

void left_was_pressed() {
 lcd.print("it goes LEFT");
}

void right_was_pressed() {
 lcd.print("it goes RIGHT");
}

void select_was_pressed() {
 lcd.print("SELECT!");
}
void none_pressed() {
 lcd.print("WAITING...");
}


void setup(){
  lcd.begin(16,2);
  lcd.print("Selected key:");
  //Now register handlers for all keys
  keypad.register_handler(NG_Keypad::UP, up_was_pressed); 
  keypad.register_handler(NG_Keypad::DOWN, down_was_pressed); 
  keypad.register_handler(NG_Keypad::RIGHT, right_was_pressed); 
  keypad.register_handler(NG_Keypad::LEFT, left_was_pressed); 
  keypad.register_handler(NG_Keypad::SELECT, select_was_pressed); 
  keypad.register_handler(NG_Keypad::NONE, none_pressed); 
}

void loop(){
  int rd;
  rd = analogRead(0);
  lcd.setCursor(0,1);
  //check if any handler should be called
  keypad.check_handlers(rd);
 
  lcd.print("          ");
  delay(100);
}
