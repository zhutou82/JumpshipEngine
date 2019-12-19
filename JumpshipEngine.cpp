#include "JumpshipEngine.h"
#include "Input.h"

void JumpshipEngine::Initialize()
{
	EASY_FUNCTION(GetProfiler.GetColor(FUNCTION_COLOR));
	LogDebug("Initialize");
	m_XMLFolderPath = m_RecourseFolderPath + m_XMLFolderPath;

	LogDebug("Serializering data");
	InitEngineConfig();
}

void JumpshipEngine::InitEngineConfig()
{
	LogDebug("Serializering Engine Config");
	tinyxml2::XMLDocument doc;
	doc.LoadFile(std::string(m_XMLFolderPath + m_EngineConfigXMLFileName).c_str());
	tinyxml2::XMLElement* folderPathChildElement = doc.FirstChildElement("FolderPath");
	m_ProfileOutputFolderPath = folderPathChildElement->FirstChildElement()->GetText();
	LogDebug(m_ProfileOutputFolderPath.c_str());
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