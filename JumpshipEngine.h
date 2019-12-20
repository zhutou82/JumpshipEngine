#pragma once
#include "CommonHeader.h"
#include "SingletonBaseClass.h"

#define GetEngine Singleton<JumpshipEngine>::GetInstance()

REGISTER_ENUM_START(EngineFolderConfig_Index)
REGISTER_ENUM_ENTRY(PROFILER_FOLDERER)
REGISTER_ENUM_ENTRY(IMAGE_FOLDER)
REGISTER_ENUM_END(EngineFolderConfig_Index)
         
REGISTER_ENUM_START(EngineFileConfig_Index)
REGISTER_ENUM_ENTRY(PROFILER_FILENAME)
REGISTER_ENUM_END(EngineFileConfig_Index)


class JumpshipEngine : public Singleton<JumpshipEngine>
{
public:

	friend class Singleton<JumpshipEngine>;
	void Initialize();
	void LoadEnginePathConfig();
	void Load();
	void Update();
	void Unload();
	void Release();
private:

	JumpshipEngine();
	std::vector<std::string> m_EngineConfigFolderVec;
  std::vector<std::string> m_EngineConfigFileNameVec;

	std::string m_RecourseFolderPath;
	std::string m_XMLFolderPath;
	std::string m_EngineConfigXMLFile;

};
