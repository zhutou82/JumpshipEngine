#include "JumpshipEngine.h"
#include <iostream>
#include "Logger.h"



int main()
{
	MyLogger* logger = new MyLogger();
	JumpshipEngine* jpEngine = new JumpshipEngine(logger);
	

	jpEngine->Initialize();
	jpEngine->Load();
	jpEngine->Update();
	jpEngine->Unload();
	jpEngine->Release();

}