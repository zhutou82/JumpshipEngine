#include "CommonHeader.h"
#include "Input.h"

bool Input::IsKeyboardKeyDown(char key, bool previousFrame) const
{

  //keybaord key range
  if (key > Input::MIN_KEYBOARD_VALUE &&  key <= Input::MAX_KEYBOARD_VALUE)
	{
    return GetKeyState(key) & 0x8000;
	}
	return false;
}

bool Input::IsKeyboardKeyPressed(char key, bool previousFrame) const
{
  static bool s = true;
  //keybaord key range
  if (key > Input::MIN_KEYBOARD_VALUE &&  key <= Input::MAX_KEYBOARD_VALUE)
  {
    //m_pCurrKeyboardState["123"] = GetKeyState(key);
    //if (    && s)
    //{
    //  s = false;
    //  return true;
    //}
    //if (!(m_pCurrKeyboardState[GetKeyState(key)] & 0xF000) && !s)
    //{
    //  s = true;
    //}
  }
  return false;
}

bool Input::IsKeyboardKeyToggled(char key, bool previousFrame) const
{
  //keybaord key range
   //return GetKeyState(key) & 0x8000;
  return false;
}

bool Input::IsMouseKeyDown(char button, bool previousFrame) const
{
  //mouse key range
	if (button >= Input::MIN_MOUSE_BUTTON_VALUE && 
      button <= Input::MAX_MOUSE_BUTTON_VALUE)
	{
    return true;
	}
	return false;
}

