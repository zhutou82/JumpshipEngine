#pragma once
#include "CommonHeader.h"
#include "SingletonBaseClass.h"
#include <windows.h>
#include <XInput.h>

#define GetInput Singleton<Input>::GetInstance()

enum InputTriggerState : byte
{
	Pressed,
	Released,
	Down
};


class Input : Singleton<Input>
{
public:
	friend class Singleton<Input>;
	//void Setup(int displayWidth, int displayHeight);
	static const int NUMBER_OF_KEYBOARDKEYS = 256;

	bool IsKeyboardKeyDown(char key, bool previousFrame = false) const;
	bool IsMouseKeyDown(char button, bool previousFrame = false) const;

	BYTE m_pCurrKeyboardState[NUMBER_OF_KEYBOARDKEYS],
		 m_pOldKeyboardState[NUMBER_OF_KEYBOARDKEYS],
		 m_pKeyboardState0[NUMBER_OF_KEYBOARDKEYS],
		 m_pKeyboardState1[NUMBER_OF_KEYBOARDKEYS];



private:
	Input() {}
};
