//Nettigo Keypad library
//Published on MIT licence
// (c) 2011 Nettigo

#include "NettigoKeypad.h"

NG_Keypad::NG_Keypad(void) {
 for (int i=0; i++; i< NG_KEYPAD_SIZE) { _functions[i] = NULL; }
 //store current time and set last pressed key to none
 lastKey = NONE;
 lastKeyTime = millis();
 debounceDelay = 50;
};

int NG_Keypad::key_pressed(int rd) {
  static int ret;
	
  if (rd < 250)		{ ret = RIGHT;}
  else if (rd < 590) 	{ ret = UP; }
  else if (rd < 749) 	{ ret = DOWN; }
  else if (rd < 792) 	{ ret = LEFT; }
  else if (rd < 912) 	{ ret = SELECT; }
  else { ret = NONE; }
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
  int key =  key_pressed(rd);
  if (_functions[key] != NULL) 
  {
    _functions[key]();
  };
  return;
}


int NG_Keypad::register_handler( int key, void (*userF)(void) ) {
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


