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
  EASY_FUNCTION(GetProfiler.GetColor(FUNCTION_COLOR));
	LogDebug("Initialize");
	LogDebug("Serializering data");
	LoadEnginePathConfig();
	GetProfiler.Init(m_EngineConfigFolderVec[EngineFolderConfig_Index::PROFILER_FOLDERER],
                   m_EngineConfigFileNameVec[EngineFileConfig_Index::PROFILER_FILENAME]);
	
}

void JumpshipEngine::LoadEnginePathConfig()
{
  EASY_FUNCTION(GetProfiler.GetColor(FUNCTION_COLOR));
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
	EASY_FUNCTION(GetProfiler.GetColor(FUNCTION_COLOR));
	LogDebug("Loading scene");
}
void JumpshipEngine::Update()
{
	EASY_FUNCTION(GetProfiler.GetColor(FUNCTION_COLOR));
	LogDebug("Engine Loop");
	////input testing
	//while (true)
	//{
	//	if (GetInput.IsKeyboardKeyPressed('K'))
	//	{
	//		LogDebug("K");
	//	}
	//	if (GetInput.IsKeyboardKeyDown('A'))
	//	{
	//		LogDebug("A");
	//	}
	//	if (GetInput.IsKeyboardKeyToggled('B'))
	//	{
	//		LogDebug("B");
	//	}
	//	if (GetInput.IsKeyboardKeyPressed(VK_ESCAPE))
	//	{
	//		LogDebug("Exit Engine Loop");
	//		break;
	//	}
	//}
}
void JumpshipEngine::Unload()
{
	EASY_FUNCTION(GetProfiler.GetColor(FUNCTION_COLOR));
	LogDebug("Unload");
}
void JumpshipEngine::Release()
{
	EASY_FUNCTION(GetProfiler.GetColor(FUNCTION_COLOR));
	LogDebug("Release");
}

