#include "Common/CommonHeader.h"
#include "Graphics.h"
int CALLBACK WinMain(
                                        _In_ HINSTANCE hInstance,
                                        _In_opt_ HINSTANCE hPrevInstance,
                                        _In_ LPSTR         lpCmdLine,
                                        _In_ int             nCmdShow 
                                        )
{
    //allocate console at the beginning of the engine
    g_GraphicsEngine.AllocateConsole();

    LogDebug("Set-up profiler");
    EASY_PROFILER_ENABLE
	//EASY_FUNCTION(profiler::colors::Magenta);
	EASY_BLOCK("Whole Engine Run time"); 
	if(GLOBAL::JSPFAILED == g_Engine.Initialize(hInstance, lpCmdLine, nCmdShow))
    {
        return 0;
    }
	g_Engine.Load();
	g_Engine.Update();
	g_Engine.Unload();
	g_Engine.Release();
	EASY_END_BLOCK
	//testing profiler
	
    //system("pause");

    // Main message loop:
    return 1;
}