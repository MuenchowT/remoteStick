#include <SoftReset.h>

// uses libraries fromddggfgftt3
// https://github.com/r89m/PushButton
// https://github.com/r89m/Button
// https://github.com/thomasfredericks/Bounce2
// #define CONFIG_TINYUSB_HID_ENABLED 1
#include <Keyboard.h>
#include <Button.h>
#include <ButtonEventCallback.h>
#include <PushButton.h>
#include <Bounce2.h>

#include "OneButton.h"
// Version
#define VERSION "3.0_USB"

// Pin Assignments
//const int LED_Pin = 02;

const int Up_Pin = 2 ;       // UP         (Joystick Up)
const int Down_Pin = 4;     // Down       (Joystick Down)
const int Left_Pin = 5;     // Left       (Joystick Left)
const int Right_Pin = 3 ;    // Right      (Joystick Right)
const int Center_Pin = 6;   // Enter      (Joystick Press)
const int Fn_Pin = 9;     // Fn 
const int Menu_Pin = 14;       // Menu 
const int Cancel_Pin = 15;    // X          (Button 5)


// Button's keys
const char Up_Press_Key = KEY_UP_ARROW;
const char Down_Press_Key = KEY_DOWN_ARROW;
const char Left_Press_Key = KEY_LEFT_ARROW;
const char Right_Press_Key = KEY_RIGHT_ARROW;

const char Fn_Press_Key = KEY_F4;    // Flarm Traffic, , im Pan Mode: Zoom In 
const char Fn_DClick_Key = 'M';      // Vario-UnterMenu 
const char Fn_Hold_Key = KEY_F3;      // Checkliste

const char Menu_Press_Key = KEY_F6;    // F6=Alternativen, im Pan Mode: Zoom Out
const char Menu_DClick_Key = KEY_F1;    //  F1=Quickmenu
const char Menu_Hold_Key = 'L';    // Mark Location

const char Cancel_Press_Key = KEY_ESC;
const char Cancel_Hold_Key = 'T';     // Task beenden / Wiederaufnehmen
// Cancel_doubleClick:   KEY_LEFT_ALT + KEY_TAB (context switch)


// Joystick Control:
const int Joy_Rebounce_Interval = 3;
const int Joy_Rebounce_Threshold = 20;

// max so viele clicks hintereinander
const int Joy_Active_Threshold = 100;

const int Button_Hold_Threshold = 500;
const int Button_Rebounce_Interval = 500;
const int Reset_Threshold = 5000;
const int Joy_Hold_Threshold = 1;

// PushButton's instances
PushButton Up = PushButton(Up_Pin);
PushButton Down = PushButton(Down_Pin);
PushButton Left = PushButton(Left_Pin);
PushButton Right = PushButton(Right_Pin);

// Setup a new OneButton on pin PIN_INPUT
// The 2. parameter activeLOW is true, because external wiring sets the button to LOW when pressed.
OneButton center_button(Center_Pin, true, true);
OneButton cancel_button(Cancel_Pin, true, true);
OneButton fn_button(Fn_Pin, true, true);
OneButton m_button(Menu_Pin, true, true);


// save the millis when a press has started.
unsigned long HoldCenterTime;

// Variables
int bt_first_connected = false;
boolean Joy_Inactive = true;
int Joy_Active_Counter = 0;

// current Cruise_Climb (Joy Center) state, staring with LOW (0)
int Cruise_Climb = LOW;
int Cruise_ClimbOpto = LOW;
int OptoPin=33;

void inline keyboardPress(char key)
{
 #if DEBUG==1
 char buf[16] = "key pressed: ";
  buf[13] = key;
  buf[14] = '\0';
  Serial.println(buf);
#endif

  Keyboard.press(key);
}

void inline KeybRelease(void)
{
  Keyboard.releaseAll();
}

void FnPress(void)
{
  keyboardPress(Fn_Press_Key);
  KeybRelease();
}

void fnDClick(void)
{
  keyboardPress(Fn_DClick_Key);
  KeybRelease();
}

void FnHold(void)
{
  keyboardPress(Fn_Hold_Key);
//  KeybRelease();
}

 void MenuPress(void)
 {
  keyboardPress(Menu_Press_Key);
  KeybRelease();
 
 }
 
  void MenuDClick(void)
  {
   keyboardPress(Menu_DClick_Key);
  KeybRelease();
  }

  void MenuHold(void)
  {
     keyboardPress(Menu_Hold_Key);
  }

void CancelClick(void)
{
  keyboardPress(Cancel_Press_Key);
  KeybRelease();
}
  
void cancelDoubleClick()
{
  keyboardPress(KEY_LEFT_ALT);
  keyboardPress(KEY_TAB);
  KeybRelease();
}


// Joystick control
void Joy_onHoldRepeat(Button &btn, uint16_t duration, uint16_t repeat_count)
{
  if (btn.isPressed() && Joy_Active_Counter == 5)
  {
    if (btn.is(Up))
      keyboardPress(Up_Press_Key);
    if (btn.is(Down))
      keyboardPress(Down_Press_Key);
    if (btn.is(Left))
      keyboardPress(Left_Press_Key);
    if (btn.is(Right))
      keyboardPress(Right_Press_Key);
    KeybRelease();
  }
  if (Joy_Inactive && ++Joy_Active_Counter > Joy_Active_Threshold)
  {
    Joy_Active_Counter = 0;
    Joy_Inactive = false;
  }
  if (!Joy_Inactive && Joy_Active_Counter > Joy_Rebounce_Threshold)
    Joy_Active_Counter = 0;
}
void inline Joy_onRelease(Button &btn, uint16_t duration)
{
  Joy_Active_Counter = 0;
  Joy_Inactive = true;
}

// this function will be called when the Joy center button is pressed 1 time only
void CenterSingleClick()
{ 
  Keyboard.write(KEY_RETURN);
 #if DEBUG==1
  Serial.println("CenterSingleClick() detected.");
 #endif
 
  KeybRelease();
} // CenterSingleClick

// this function will be called when the Joy center button was pressed 2 times in a short timeframe.
void CenterDoubleClick()
{ 
#if DEBUG==1
Serial.println("CenterDoubleClick() detected.");
#endif
if (Cruise_Climb == LOW)
  {
    Keyboard.print("V");
    Serial.println("Vario");
    //digitalWrite(OptoPin, LOW);
  }
  else
  {
    Keyboard.print("S");
    Serial.println("Speed to fly");
  }
  Cruise_Climb = !Cruise_Climb; // reverse the Cruise_Climb
  KeybRelease();
} // DoubleClick

// this function will be called when the Joy center button is held down for 0.5 second or more.
void HoldCenter()
{ 
  Keyboard.print("P");
#if DEBUG==1
  Serial.println("PAN()");
 #endif
 
  HoldCenterTime = millis() - 500; // as set in setPressTicks()
//  KeybRelease();
} // HoldCenter()


void CancelHold(void)
{ // this function will be called when the Cancel button is held down for a longer time
      keyboardPress(Cancel_Hold_Key);
//      KeybRelease();
}

void setup()
{

  pinMode(Up_Pin, INPUT_PULLUP);
  pinMode(Down_Pin, INPUT_PULLUP);
  pinMode(Left_Pin, INPUT_PULLUP);
  pinMode(Right_Pin, INPUT_PULLUP);
  pinMode(Center_Pin, INPUT_PULLUP);
  pinMode(Fn_Pin, INPUT_PULLUP);
  pinMode(Menu_Pin, INPUT_PULLUP);
  pinMode(Cancel_Pin, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("Version: " VERSION);

  // link the click functions to be called on xxxclick event.
  center_button.attachClick(CenterSingleClick);
  center_button.attachDoubleClick(CenterDoubleClick);
  center_button.setPressMs(800); // that is the time when LongHoldCenter is called
  center_button.attachLongPressStart(HoldCenter);
  center_button.attachDuringLongPress(KeybRelease);
  center_button.attachLongPressStop(KeybRelease);

  cancel_button.attachClick(CancelClick);
  cancel_button.attachDoubleClick(cancelDoubleClick);
  cancel_button.setPressMs(800); 
  cancel_button.attachLongPressStart(CancelHold);
  cancel_button.attachDuringLongPress(KeybRelease);
  cancel_button.attachLongPressStop(KeybRelease);
  
//      Cancel.onRelease(0, Button_Hold_Threshold - 1, Button_onRelease);
//    Cancel.onHoldRepeat(Button_Hold_Threshold, Button_Rebounce_Interval, Button_onHoldRepeat);



  fn_button.attachClick(FnPress);
  fn_button.attachDoubleClick(fnDClick);
  fn_button.attachLongPressStart(FnHold);
  fn_button.attachDuringLongPress(KeybRelease);
  fn_button.attachLongPressStop(KeybRelease);
  fn_button.setPressMs(800); 

  m_button.attachClick(MenuPress);
  m_button.attachDoubleClick(MenuDClick);
  m_button.attachLongPressStart(MenuHold);
  m_button.attachDuringLongPress(KeybRelease);
  m_button.attachLongPressStop(KeybRelease);
  m_button.setPressMs(800); 
  
  // pinMode(LED_Pin, OUTPUT);
  Keyboard.begin();
//  USB.begin();
  delay(1000);
    Serial.println("Starting USB work!");

    Up.onRelease(Joy_onRelease);
    Down.onRelease(Joy_onRelease);
    Left.onRelease(Joy_onRelease);
    Right.onRelease(Joy_onRelease);

    Up.onHoldRepeat(Joy_Hold_Threshold, Joy_Rebounce_Interval, Joy_onHoldRepeat);
    Down.onHoldRepeat(Joy_Hold_Threshold, Joy_Rebounce_Interval, Joy_onHoldRepeat);
    Left.onHoldRepeat(Joy_Hold_Threshold, Joy_Rebounce_Interval, Joy_onHoldRepeat);
    Right.onHoldRepeat(Joy_Hold_Threshold, Joy_Rebounce_Interval, Joy_onHoldRepeat);

    Joy_Active_Counter = 0;
  }

void loop()


  {
  // keep watching the push button:
 
  center_button.tick();
  cancel_button.tick();
  fn_button.tick();
  m_button.tick();
      if (not bt_first_connected)
      {
        bt_first_connected = true;
        Serial.println("usb connected");
        delay(2000);
      }
  Up.update();
  Down.update();
  Left.update();
  Right.update();
}
