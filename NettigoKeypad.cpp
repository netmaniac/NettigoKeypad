//Nettigo Keypad library
//Published on MIT licence
// (c) 2011 Nettigo

#include "WProgram.h"
#include "NettigoKeypad.h"

NG_Keypad::NG_Keypad(void) {
 for (int i=0; i++; i< NG_KEYPAD_SIZE) { _functions[i] = NULL; }
};

int NG_Keypad::key_pressed(int rd) {
  if (rd < 250) return RIGHT;
  if (rd < 590) return UP;
  if (rd < 749) return DOWN;
  if (rd < 792) return LEFT;
  if (rd < 912) return SELECT;
  return NONE;
};

void NG_Keypad::check_handlers(int rd) {
  if (_functions[key_pressed(rd)] != NULL) 
  {
    _functions[key_pressed(rd)]();
  };
  return;
}


int NG_Keypad::register_handler( int key, void (*userF)(void) ) {
  if(key >= NG_KEYPAD_SIZE)
    return -1;
    _functions[key] = userF;
};

