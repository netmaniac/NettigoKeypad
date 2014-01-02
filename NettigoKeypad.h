//Nettigo Keypad library
//Published on MIT licence
// (c) 2011-2013 Nettigo.pl

#ifndef _NG_Keypad_h_
#define _NG_Keypad_h_

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define NG_KEYPAD_SIZE  6

class NG_Keypad
{
  public:
	static const byte NONE    = 0;
	static const byte SELECT  = 1;
	static const byte LEFT    = 2;
	static const byte  DOWN    = 3;
	static const byte UP      = 4;
	static const byte RIGHT   = 5;

	//should we do debounce?
	bool debounce;


	NG_Keypad(void);  

	//which key was pressed? Takes analog input value and returns constant
	//describing which key was pressed.
	byte key_pressed(int rd);
	//debounce keys?
	void setDebounce(bool);
	bool getDebounce(void);

	//Register handler to be called when key pressed
	// takes two args
	// key - which key should be used
	// userF - which function should be called when key pressed
	int register_handler( byte key, void (*userF)(void) );

	//Check for handlers to be called. Takes as argument analogRead result.
	void check_handlers(int rd);

	//return current debounce delay
	unsigned int getDebounceDelay( void );

	//set new debounce delay
	void setDebounceDelay (unsigned int);

	//assign custom values as boundaries in voltage divider
	void setBoundaries( int * );
	private:
	void  (*_functions[NG_KEYPAD_SIZE])(void);

	/*
	 *  Nettigo Keypad has keys in following order:
	 * 
	 * NG_Keypad::RIGHT
	 * NG_Keypad::UP
	 * NG_Keypad::DOWN 
	 * NG_Keypad::LEFT 
	 * NG_Keypad::SELECT
	 * NG_Keypad::NONE
	 * 
	 * Boundary values has to be in ascending order in array, if order on Your
	 * keypad is different You has to write some wrapper to change values. Do not
	 * change order of values or keypad will be not working properly.
	 * 	 */
	int boundaries[5] = { 250, 380, 490, 550, 690 };

	//default debounce timeout
	unsigned int debounceDelay;

	//what last key was pressed and when (millis)
	byte lastKey;
	unsigned long lastKeyTime;

};

#endif