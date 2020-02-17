#pragma once
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"
#include "JSMath.h"	
//#define SerializeByXML
#define WriteDataToBinary 
using namespace std;

//Register enum type 
#define REGISTER_ENUM_START(x) enum x##Config_Index {
#define REGISTER_ENUM_ENTRY(x) x, 
#define REGISTER_ENUM_END(x) x##Config_MAX_SIZE }; \
static std::vector<x> g_EngineConfig##x##ConfigVec; \

////Register struct type 
//#define REGISTER_STRUCT_START(x) struct x##_Index_Struct {
//#define REGISTER_STRUCT_ENTRY(type, name) type name;
//#define REGISTER_STRUCT_END(x) }; \
//static x##_Index_Struct g_EngineConfig##x##Strcut;\

REGISTER_ENUM_START(string)
REGISTER_ENUM_ENTRY(PROFILER_FOLDERER)
REGISTER_ENUM_ENTRY(IMAGE_FOLDER)
REGISTER_ENUM_ENTRY(SHADER_FOLDER)
REGISTER_ENUM_ENTRY(LOG_FOLDER)
REGISTER_ENUM_ENTRY(PROFILER_FILENAME)
REGISTER_ENUM_ENTRY(TEXTURE_SHADER_FILENAME)
REGISTER_ENUM_ENTRY(COLOR_SHADER_FILENAME)
REGISTER_ENUM_ENTRY(WINDOWS_NAME)
REGISTER_ENUM_END(string)

REGISTER_ENUM_START(Vec2i)
REGISTER_ENUM_ENTRY(WINDOW_RESOLUTION)
REGISTER_ENUM_END(Vec2i)

REGISTER_ENUM_START(bool)
REGISTER_ENUM_ENTRY(IS_WINDOW_FULLSCREEN)
REGISTER_ENUM_ENTRY(IS_WINDOW_SHOW)
REGISTER_ENUM_END(bool)



//REGISTER_ENUM_START(FileName)
//REGISTER_ENUM_ENTRY(PROFILER_FILENAME)
//REGISTER_ENUM_ENTRY(TEXTURE_SHADER_FILENAME)
//REGISTER_ENUM_ENTRY(COLOR_SHADER_FILENAME)
//REGISTER_ENUM_END(FileName)




#define g_Engine Singleton<JumpshipEngine>::GetInstance()
class JumpshipEngine : public Singleton<JumpshipEngine>
{
public:

	friend class Singleton<JumpshipEngine>;
	JSbool Initialize(_In_ HINSTANCE hInstance, 
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
