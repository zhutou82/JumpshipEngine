#pragma once
#include "CommonHeader.h"
#include "SingletonBaseClass.h"

#define GetEngine Singleton<JumpshipEngine>::GetInstance()

class JumpshipEngine : public Singleton<JumpshipEngine>
{
public:
	friend class Singleton<JumpshipEngine>;
	void Initialize();
	void InitEngineConfig();
	void Load();
	void Update();
	void Unload();
	void Release();
private:

	JumpshipEngine() {}
	std::string m_ProfileOutputFolderPath;
	std::string m_RecourseFolderPath = "Resource/";
	std::string m_XMLFolderPath = "XML/";
	std::string m_EngineConfigXMLFileName = "EngineConfig.xml";

};
