#pragma once
#include <iostream>
#include "Logger.h"

class JumpshipEngine
{

public:
	JumpshipEngine(MyLogger* logger) : m_logger(logger){}
	~JumpshipEngine() {
		delete m_logger;
	};
	void Initialize();
	void Load();
	void Update();
	void Unload();
	void Release();
private:

	MyLogger* m_logger = NULL;

};
