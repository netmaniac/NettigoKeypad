//Nettigo Keypad library
//Published on MIT licence
// (c) 2011-2017 Nettigo

#include "NettigoKeypad.h"



NG_Keypad::NG_Keypad(void) {
  for (int i=0; i++; i< NG_KEYPAD_SIZE) { _functions[i] = NULL; }
  //store current time and set last pressed key to none
  lastKey = NONE;
  lastKeyTime = millis();
  debounce = true;
  debounceDelay = 50;

};

NG_Keypad::	NG_Keypad(
  byte k0, unsigned b0, 
  byte k1, unsigned b1, 
  byte k2, unsigned b2, 
  byte k3, unsigned b3, 
  byte k4, unsigned b4
  ) {
  NG_Keypad::NG_Keypad();
  NG_Keypad::setOrder(k0, k1, k2, k3, k4);
  NG_Keypad::setBoundaries(b0, b1, b2, b3, b4);
  
}


byte NG_Keypad::key_pressed(int rd) {
  static byte ret;
  ret = NONE;
  for (byte i=0; i <5; i++) {
    if( rd < boundaries[i] ) { 
      Serial.print("key_pressed");
      Serial.print(i);
      Serial.print(",");
      Serial.print(boundaries[i]);
      Serial.print(",");
      Serial.println(order[i]);
      ret = order[i];}
  }
  //return result at once if no debouncing enabled
  if (!debounce)
	return ret;
  //no change since last time or timeout for debouncing not passed - do nothing 	
  if (ret == lastKey || millis() - lastKeyTime < debounceDelay) {
  	return NONE;
  } else  {
    lastKey = ret;
    lastKeyTime = millis();
    return ret;
  }

};

void NG_Keypad::check_handlers(int rd) {
  byte key =  key_pressed(rd);
  if (_functions[key] != NULL) 
  {
	_functions[key]();
  };
  return;
}


int NG_Keypad::register_handler( byte key, void (*userF)(void) ) {
  if(key >= NG_KEYPAD_SIZE)
	return -1;
  _functions[key] = userF;
};

unsigned int NG_Keypad::getDebounceDelay( void ){
  return debounceDelay;
};

void NG_Keypad::setDebounceDelay (unsigned int d){
  debounceDelay = d;
};

bool NG_Keypad::getDebounce( void ){
  return debounce;
};

void NG_Keypad::setDebounce (bool d){
  debounce = d;
};

void NG_Keypad::setBoundaries( int *b) {
  for (byte i=0; i < 5; i++) { boundaries[i] = b[i];}
};  

void NG_Keypad::setOrder( byte const *b) {
  for (byte i=0; i < 5; i++) { order[i] = b[i];}
};  

void NG_Keypad::setOrder( byte b0, byte b1, byte b2, byte b3, byte b4) {
  order[0] = b0;
  order[1] = b1;
  order[2] = b2;
  order[3] = b3;
  order[4] = b4;
  
};  

void NG_Keypad::setBoundaries( int b0, int b1, int b2, int b3, int b4) {
  boundaries[0] = b0;
  boundaries[1] = b1;
  boundaries[2] = b2;
  boundaries[3] = b3;
  boundaries[4] = b4;
  
};  
