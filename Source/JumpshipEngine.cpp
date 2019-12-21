#include "JumpshipEngine.h"
#include "Input.h"

JumpshipEngine::JumpshipEngine()
: 
m_RecourseFolderPath("Resource/"),
m_XMLFolderPath (m_RecourseFolderPath + "XML/"),
m_EngineConfigXMLFile (m_XMLFolderPath + "EngineConfig.xml")
{
	m_EngineConfigFolderVec.reserve(EngineFolderConfig_Index::EngineFolderConfig_Index_MAX_SIZE);
  m_EngineConfigFileNameVec.reserve(EngineFileConfig_Index::EngineFileConfig_Index_MAX_SIZE);
}


void JumpshipEngine::Initialize()
{
  EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Initialize");
	LogDebug("Serializering data");
	LoadEnginePathConfig();
	GetProfiler.Init(m_EngineConfigFolderVec[EngineFolderConfig_Index::PROFILER_FOLDERER],
                   m_EngineConfigFileNameVec[EngineFileConfig_Index::PROFILER_FILENAME]);
	
  //testing vec2 class
  Vec2<int> v(10, 20);
  Vec2<int> vv(20, 30);
  
  std::cout << (v += vv) << GLOBAL::NEW_LINE;
  std::cout << (v -= vv) << GLOBAL::NEW_LINE;

  Vec2<int> windowResolution(800, 600);
  //init graphics engine
  //GetGraphicsEngine.Init(windowResolution);

}

void JumpshipEngine::LoadEnginePathConfig()
{
  EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	//Serializering Engine Config
	LogDebug("Serializering Engine Config");
	GetSerializer.Serialize(m_EngineConfigXMLFile,
													"FolderPath", 
													m_EngineConfigFolderVec);
  GetSerializer.Serialize(m_EngineConfigXMLFile,
                          "FileName",
                          m_EngineConfigFileNameVec);

	PrintCont(m_EngineConfigFolderVec);
}
void JumpshipEngine::Load()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Loading scene");
}
void JumpshipEngine::Update()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Engine Loop");
  //Engine loop
	while (!GetInput.IsKeyboardKeyPressed(VK_ESCAPE))
	{
    //checking input
    CheckInput();
	}
  LogDebug("Exit Engine Loop");
}
void JumpshipEngine::Unload()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Unload");
}
void JumpshipEngine::Release()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Release");
}

void JumpshipEngine::CheckInput()
{
  if (GetInput.IsKeyboardKeyPressed('K'))
  {
    LogDebug("K");
  }
  if (GetInput.IsKeyboardKeyDown('A'))
  {
    LogDebug("A");
  }
  if (GetInput.IsKeyboardKeyToggled('B'))
  {
    LogDebug("B");
  }
  if (GetInput.IsMouseKeyDown(VK_LBUTTON))
  {
    LogDebug("MouseL");
  }
}
