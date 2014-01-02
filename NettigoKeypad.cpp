//Nettigo Keypad library
//Published on MIT licence
// (c) 2011 Nettigo

#include "NettigoKeypad.h"

NG_Keypad::NG_Keypad(void) {
  for (int i=0; i++; i< NG_KEYPAD_SIZE) { _functions[i] = NULL; }
  //store current time and set last pressed key to none
  lastKey = NONE;
  lastKeyTime = millis();
  debounce = true;
  debounceDelay = 50;

};

byte NG_Keypad::key_pressed(int rd) {
  static byte ret;
  
  if (rd < boundaries[0])		{ ret = RIGHT;}
  else if (rd < boundaries[1]) 	{ ret = UP; }
  else if (rd < boundaries[2]) 	{ ret = DOWN; }
  else if (rd < boundaries[3]) 	{ ret = LEFT; }
  else if (rd < boundaries[4]) 	{ ret = SELECT; }
  else { ret = NONE; }
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

