#define DEBUG 1

typedef struct {
  byte pin;
  const char*  name; 
  parameterizedCallbackFunction clickFunc();
  parameterizedCallbackFunction dClickFunc();
  parameterizedCallbackFunction holdFunc();
} butt;

butt buttons[] = {
  { 5, "Fn",  FnPress(void), fnDClick(void), fnHold(void)},
  { 6, "M", MClick(void), fnClick(void), fnHold(void) },
  { 7, "X" },
  { 8, "click" },
  { 9, "UP" }, 
  { 10, "DOWN" },
  { 11, "RIGHT" },
  { 12, "LEFT" },
};

//byte buttons[]={9,1,2,14,5,7,3,15,4,6};//seperate array from definitions to set up the pins
#define NUMBUTTONS sizeof(buttons)/siezof(button)    //gives size of array *helps for adding buttons



#define KEY_LEFT_CTRL   0x80
#define KEY_LEFT_SHIFT  0x81
#define KEY_LEFT_ALT    0x82
#define KEY_LEFT_GUI    0x83
#define KEY_RIGHT_CTRL  0x84
#define KEY_RIGHT_SHIFT 0x85
#define KEY_RIGHT_ALT   0x86  // AltGr (Right Alt) Key
#define KEY_RIGHT_GUI   0x87

#define KEY_UP_ARROW     0xDA
#define KEY_DOWN_ARROW   0xD9
#define KEY_LEFT_ARROW   0xD8
#define KEY_RIGHT_ARROW  0xD7
#define KEY_MENU         0xED  //  "Keyboard Application" in USB standard
#define KEY_SPACE        0x20
#define KEY_BACKSPACE    0xB2
#define KEY_TAB          0xB3
#define KEY_RETURN       0xB0
#define KEY_ESC          0xB1
#define KEY_INSERT       0xD1
#define KEY_DELETE       0xD4
#define KEY_PAGE_UP      0xD3
#define KEY_PAGE_DOWN    0xD6
#define KEY_HOME         0xD2
#define KEY_END          0xD5
#define KEY_NUM_LOCK     0xDB
#define KEY_CAPS_LOCK    0xC1
#define KEY_F1           0xC2
#define KEY_F2           0xC3
#define KEY_F3           0xC4
#define KEY_F4           0xC5
#define KEY_F5           0xC6
#define KEY_F6           0xC7
#define KEY_F7           0xC8
#define KEY_F8           0xC9
#define KEY_F9           0xCA
#define KEY_F10          0xCB
#define KEY_F11          0xCC
#define KEY_F12          0xCD
#define KEY_F13          0xF0
#define KEY_F14          0xF1
#define KEY_F15          0xF2
#define KEY_F16          0xF3
#define KEY_F17          0xF4
#define KEY_F18          0xF5
#define KEY_F19          0xF6
#define KEY_F20          0xF7
#define KEY_F21          0xF8
#define KEY_F22          0xF9
#define KEY_F23          0xFA
#define KEY_F24          0xFB
#define KEY_PRINT_SCREEN 0xCE
#define KEY_SCROLL_LOCK  0xCF
#define KEY_PAUSE        0xD0

#define LED_NUMLOCK    0x01
#define LED_CAPSLOCK   0x02
#define LED_SCROLLLOCK 0x04
#define LED_COMPOSE    0x08
#define LED_KANA       0x10

// Numeric keypad
#define KEY_KP_SLASH    0xDC
#define KEY_KP_ASTERISK 0xDD
#define KEY_KP_MINUS    0xDE
#define KEY_KP_PLUS     0xDF
#define KEY_KP_ENTER    0xE0
#define KEY_KP_1        0xE1
#define KEY_KP_2        0xE2
#define KEY_KP_3        0xE3
#define KEY_KP_4        0xE4
#define KEY_KP_5        0xE5
#define KEY_KP_6        0xE6
#define KEY_KP_7        0xE7
#define KEY_KP_8        0xE8
#define KEY_KP_9        0xE9
#define KEY_KP_0        0xEA
#define KEY_KP_DOT      0xEB
