#pragma once
#include "CommonHeader.h"
#include "SingletonBaseClass.h"


#define GetInput Singleton<Input>::GetInstance()
class Input : Singleton<Input>
{
public:
	friend class Singleton<Input>;
  static const int NUMBER_OF_KEYBOARDKEYS = 256;
  static const int MIN_KEYBOARD_VALUE = 0x07;
  static const int MAX_KEYBOARD_VALUE = 0xFE;
  static const int MIN_MOUSE_BUTTON_VALUE = 0x00;
  static const int MAX_MOUSE_BUTTON_VALUE = 0x06;

	bool IsKeyboardKeyDown(char key, bool previousFrame = false) const;
  bool IsKeyboardKeyPressed(char key, bool previousFrame = false) const;
  bool IsKeyboardKeyToggled(char key, bool previousFrame = false) const;

  bool IsMouseKeyDown(char button, bool previousFrame = false) const;
  bool IsKeyboardKeyDown_unsafe(char key, bool previousFrame = false) const;

private:
	Input() {}

  std::map<std::string, SHORT> m_pCurrKeyboardState;
        //m_pOldKeyboardState[NUMBER_OF_KEYBOARDKEYS],
        //m_pKeyboardState0[NUMBER_OF_KEYBOARDKEYS],
        //m_pKeyboardState1[NUMBER_OF_KEYBOARDKEYS];

  bool m_PreviousState = false;

};
