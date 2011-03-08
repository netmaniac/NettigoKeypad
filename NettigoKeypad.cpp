//Nettigo Keypad library
//Published on MIT licence
// (c) 2011 Nettigo

#include "WProgram.h"
#include "NettigoKeypad.h"

NG_Keypad::NG_Keypad(void) {};

int NG_Keypad::key_pressed(int rd) {
  if (rd < 250) return RIGHT;
  if (rd < 590) return UP;
  if (rd < 749) return DOWN;
  if (rd < 792) return LEFT;
  if (rd < 912) return SELECT;
  return NONE;
};

