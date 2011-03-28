//Nettigo Keypad library
//Published on MIT licence
// (c) 2011 Nettigo

#define NG_KEYPAD_SIZE  6

class NG_Keypad
{
  public:
  static const int NONE    = 0;
  static const int SELECT  = 1;
  static const int LEFT    = 2;
  static const int DOWN    = 3;
  static const int UP      = 4;
  static const int RIGHT   = 5;

  

  NG_Keypad(void);  
  //which key was pressed? Takes analog input value and returns constant
  //describing which key was pressed.
  int key_pressed(int rd);

  //Register handler to be called when key pressed
  // takes two args
  // key - which key should be used
  // userF - which function should be called when key pressed
  int register_handler( int key, void (*userF)(void) );
  
  //Check for handlers to be called
  void check_handlers(int rd);
  private:
  void  (*_functions[NG_KEYPAD_SIZE])(void);
  
  
};

