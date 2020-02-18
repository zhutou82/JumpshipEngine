#include "Input.h"

Input::Input()
{
    std::fill_n(m_pCurrKeyboardState, NUMBER_OF_KEYBOARDKEYS, true);
}

bool Input::IsKeyboardKeyDown(int8_t key, bool previousFrame) const
{
    return GetKeyState(key) & HIGH_ORDER_BIT; 
    
}

bool Input::IsKeyboardKeyPressed(int8_t key, bool previousFrame)
{
    int16_t state = GetKeyState(key) & HIGH_ORDER_BIT;
	if (m_pCurrKeyboardState[key] && state)
	{
		m_pCurrKeyboardState[key] = false;
		return true;
	}
	else if (!m_pCurrKeyboardState[key] && !state)
	{
		m_pCurrKeyboardState[key] = true;
	}
	return false;
}

bool Input::IsKeyboardKeyToggled(int8_t key, bool previousFrame) const
{
    return GetKeyState(key) & LOW_ORDER_BIT;
}

bool Input::IsMouseKeyDown(int8_t button, bool previousFrame) 
{
     return IsKeyboardKeyPressed(button, previousFrame);
}

