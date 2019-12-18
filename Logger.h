#pragma once
#pragma warning(disable:4996) //to fix CRT_NO_WARNING
#include "CommonHeader.h"
#include "SingletonBaseClass.h"

#define LogDebug(x) Singleton<MyLogger>::GetInstance().Debug(x)
#define LogInfo(x) Singleton<MyLogger>::GetInstance().Info(x)
class MyLogger : public Singleton<MyLogger>
{
public:
	friend class Singleton<MyLogger>;
	void Debug(const char* debugMsg, ...);
	void Info(const char* inforMsg, ...);
private:
    MyLogger() {};
    bool m_IsDebugMode = true;
};



