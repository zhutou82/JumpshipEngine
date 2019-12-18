#pragma once
#include "CommonHeader.h"
#include "SingletonBaseClass.h"

#define GetEngine Singleton<JumpshipEngine>::GetInstance()

class JumpshipEngine : public Singleton<JumpshipEngine>
{
public:
	friend class Singleton<JumpshipEngine>;
	void Initialize();
	void Load();
	void Update();
	void Unload();
	void Release();
private:
	JumpshipEngine() {}
};
