//Nettigo Keypad library
//Published on MIT licence
// (c) 2011 Nettigo

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
  //which key was pressed?
  int key_pressed(int rd);
  
  
};

