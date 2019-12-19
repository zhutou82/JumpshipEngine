#include "CommonHeader.h"
#include "Input.h"

Input::Input()
{
	for (int i = 0; i < NUMBER_OF_KEYBOARDKEYS; ++i) m_pCurrKeyboardState[i] = true;
}

inline bool Input::IsKeyboardKeyDown(char key, bool previousFrame) const
{
  return GetKeyState(key) & 0x8000;
}

inline bool Input::IsKeyboardKeyPressed(char key, bool previousFrame)
{
	SHORT state = GetKeyState(key);
	if (m_pCurrKeyboardState[key] && (state & 0xF0))
	{
		m_pCurrKeyboardState[key] = false;
		return true;
	}
	else if (!m_pCurrKeyboardState[key] && !(state & 0xF0))
	{
		m_pCurrKeyboardState[key] = true;
	}
	return false;
}

inline bool Input::IsKeyboardKeyToggled(char key, bool previousFrame) const
{
  return GetKeyState(key) & 0x01;
}

inline bool Input::IsMouseKeyDown(char button, bool previousFrame) 
{
	SHORT state = GetKeyState(button);
	if (m_pCurrKeyboardState[button] && (state & 0xF0))
	{
		m_pCurrKeyboardState[button] = false;
		return true;
	}
	else if (!m_pCurrKeyboardState[button] && !(state & 0xF0))
	{
		m_pCurrKeyboardState[button] = true;
	}
	return false;
}

