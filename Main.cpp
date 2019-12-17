#include "JumpshipEngine.h"
#include <iostream>
#include "Logger.h"

#include "easy/profiler.h"

#define BUILD_WITH_EASY_PROFILER



int main()
{
	EASY_PROFILER_ENABLE;
	//profiler::startListen();

	logDebug("Set-up Engine");
	JumpshipEngine* jpEngine = new JumpshipEngine();

	logDebug("Set-up profiler");
	EASY_FUNCTION(profiler::colors::Magenta); // Magenta block with name "foo"

	EASY_BLOCK("Calculating sum"); // Begin block with default color == Amber100
	jpEngine->Initialize();
	EASY_END_BLOCK; // End of "Calculating sum" block


	jpEngine->Load();
	jpEngine->Update();
	jpEngine->Unload();
	jpEngine->Release(); 

	profiler::dumpBlocksToFile("test.prof");

}