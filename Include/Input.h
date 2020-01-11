#pragma once
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"


#define GetInput Singleton<Input>::GetInstance()
class Input : Singleton<Input>
{
public:
	friend class Singleton<Input>;
  constexpr static const int16_t NUMBER_OF_KEYBOARDKEYS = 0x0100;
  constexpr static const uint8_t MIN_KEYBO8ARD_VALUE = 0x07;
  constexpr static const uint8_t MAX_KEYBOARD_VALUE = 0xFE;
  constexpr static const uint8_t MIN_MOUSE_BUTTON_VALUE = 0x00;
  constexpr static const uint8_t MAX_MOUSE_BUTTON_VALUE = 0x06;
  constexpr static const uint8_t HIGH_ORDER_BIT = 0x80;
  constexpr static const uint8_t LOW_ORDER_BIT = 0x01;


	bool IsKeyboardKeyDown(int8_t key, bool previousFrame = false) const;
  bool IsKeyboardKeyPressed(int8_t key, bool previousFrame = false);
  bool IsKeyboardKeyToggled(int8_t key, bool previousFrame = false) const;
  bool IsMouseKeyDown(int8_t button, bool previousFrame = false);
  //bool IsKeyboardKeyDown_unsafe(char key, bool previousFrame = false) const;

private:
	Input();

  //std::map<std::string, SHORT> m_pCurrKeyboardState;
  bool m_pCurrKeyboardState[NUMBER_OF_KEYBOARDKEYS];
        //m_pOldKeyboardState[NUMBER_OF_KEYBOARDKEYS],
        //m_pKeyboardState0[NUMBER_OF_KEYBOARDKEYS],
        //m_pKeyboardState1[NUMBER_OF_KEYBOARDKEYS];

  bool m_PreviousState = false;

};
