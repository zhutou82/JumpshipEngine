#include "JumpshipEngine.h"
#include "Common/CommonHeader.h"

#include <windows.h>
#include <tchar.h>

//#include "gainput/gainput.h"

int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
);

LRESULT CALLBACK WndProc(
  _In_ HWND   hWnd,
  _In_ UINT   message,
  _In_ WPARAM wParam,
  _In_ LPARAM lParam
);

int main()
{
  LogDebug("Set-up profiler");
  EASY_PROFILER_ENABLE
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