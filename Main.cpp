#include "JumpshipEngine.h"
#include "CommonHeader.h"

//#include "gainput/gainput.h"

int main()
{
	LogDebug("Set-up profiler");
	GetProfiler.Init();

	//EASY_FUNCTION(profiler::colors::Magenta);
	EASY_BLOCK("Whole Engine Run time"); 
	GetEngine.Initialize();
	GetEngine.Load();
	GetEngine.Update();
	GetEngine.Unload();
	GetEngine.Release();
	EASY_END_BLOCK
	//testing profiler
	GetProfiler.DumpblockToFile("test.prof");

}