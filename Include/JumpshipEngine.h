#pragma once
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"

extern std::vector<std::string> g_EngineConfigFolderPathVec;

//Register enum type 
#define REGISTER_ENUM_START(x) enum x##_Index {
#define REGISTER_ENUM_ENTRY(x) x, 
#define REGISTER_ENUM_END(x) x##_MAX_SIZE }; \
static std::vector<std::string> g_EngineConfig##x##Vec; \

#define GetEngine Singleton<JumpshipEngine>::GetInstance()

REGISTER_ENUM_START(FolderPath)
REGISTER_ENUM_ENTRY(PROFILER_FOLDERER)
REGISTER_ENUM_ENTRY(IMAGE_FOLDER)
REGISTER_ENUM_ENTRY(SHADER_FOLDER)
REGISTER_ENUM_END(FolderPath)
         
REGISTER_ENUM_START(FileName)
REGISTER_ENUM_ENTRY(PROFILER_FILENAME)
REGISTER_ENUM_ENTRY(TEXTURE_SHADER_FILENAME)
REGISTER_ENUM_ENTRY(COLOR_SHADER_FILENAME)
REGISTER_ENUM_END(FileName)

REGISTER_ENUM_START(GraphicsEngine)
REGISTER_ENUM_ENTRY(WindowName)
REGISTER_ENUM_ENTRY(WindowResolution)
REGISTER_ENUM_ENTRY(WindowFullScreen)
REGISTER_ENUM_ENTRY(WindowsShow)
REGISTER_ENUM_END(GraphicsEngine)

class JumpshipEngine : public Singleton<JumpshipEngine>
{
public:

	friend class Singleton<JumpshipEngine>;
	int Initialize(_In_ HINSTANCE hInstance, 
                  _In_ LPSTR lpCmdLine, 
                  _In_ int nCmdShow);
	void LoadEnginePathConfig();
	void Load();
	void Update();
	void Unload();
	void Release();
  void CheckInput();

  //const std::string& GetFolerPath(FolderPath_Index index) const { return g_EngineConfigFolderPathVec[index]; }
  const std::string& GetRecourceFolderPath () const { return m_RecourseFolderPath;}

private:

	JumpshipEngine();
	std::string m_RecourseFolderPath;
	std::string m_XMLFolderPath;
	std::string m_EngineConfigXMLFile;

};
