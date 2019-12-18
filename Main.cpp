#include "JumpshipEngine.h"
#include "CommonHeader.h"

//#include "gainput/gainput.h"

int main()
{
	EASY_PROFILER_ENABLE;
	LogDebug("Set-up profiler");
	EASY_FUNCTION(profiler::colors::Magenta); // Magenta block with name "foo"

	EASY_BLOCK("Calculating sum"); // Begin block with default color == Amber100
	GetEngine.Initialize();
	EASY_END_BLOCK; // End of "Calculating sum" block

	GetEngine.Load();
	GetEngine.Update();
	GetEngine.Unload();
	GetEngine.Release();

	profiler::dumpBlocksToFile("test.prof");

  //testing input
  while (true)
  {
    if (GetInput.IsKeyboardKeyPressed('K'))
    {
      LogDebug("K");
    }

    if (GetInput.IsKeyboardKeyDown('A'))
    {
      LogDebug("A");
    }
    //if (GetInput.IsKeyboardKeyToggled('B'))
    //{
    //  LogDebug("B");
    //}
    if (GetInput.IsKeyboardKeyPressed(VK_ESCAPE))
      break;
  }


}