#include "Common/CommonHeader.h"
#include "Graphics.h"
int CALLBACK WinMain(
                    _In_ HINSTANCE hInstance,
                    _In_opt_ HINSTANCE hPrevInstance,
                    _In_ LPSTR     lpCmdLine,
                    _In_ int       nCmdShow 
                    )
{
  //allocate console at the beginning of the engine
  GetGraphicsEngine.AllocateConsole();

  LogDebug("Set-up profiler");
  EASY_PROFILER_ENABLE
	//EASY_FUNCTION(profiler::colors::Magenta);
	EASY_BLOCK("Whole Engine Run time"); 
	if(GLOBAL::JSPFAILED == GetEngine.Initialize(hInstance, lpCmdLine, nCmdShow))
  {
    return 0;
  }
	GetEngine.Load();
	GetEngine.Update();
	GetEngine.Unload();
	GetEngine.Release();
	EASY_END_BLOCK
	//testing profiler
	
  //system("pause");

  // Main message loop:
  return 1;
}