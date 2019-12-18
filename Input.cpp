#include "Input.h"

bool Input::IsKeyboardKeyDown(char key, bool previousFrame) const
{
	if (key > 0x07 && key <= 0xFE)
	{

	}
	return false;
}

bool Input::IsMouseKeyDown(char button, bool previousFrame) const
{
	if (button >= 0x01 && button <= 0x06)
	{

	}
	return false;
}

