#pragma once
#include <iostream>
#include "Logger.h"

class JumpshipEngine
{

public:
	JumpshipEngine() {}
	~JumpshipEngine() {};
	void Initialize();
	void Load();
	void Update();
	void Unload();
	void Release();
private:
};
