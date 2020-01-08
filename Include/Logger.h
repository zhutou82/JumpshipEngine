#pragma once
#pragma warning(disable:4996) //to fix CRT_NO_WARNING
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"
#include "ThreadPool.h"

#define LogDebug(x) Singleton<MyLogger>::GetInstance().Debug(x)
#define LogInfo(x) Singleton<MyLogger>::GetInstance().Info(x)
#define PrintCont(x) Singleton<MyLogger>::GetInstance().PrintC(x)
class MyLogger : public Singleton<MyLogger>
{
public:
	friend class Singleton<MyLogger>;
	void Debug(const char* debugMsg, ...);
	void Info(const char* inforMsg, ...);
	template <typename Cont>
	void PrintC(const Cont& cont)
	{
    //GetThreadPool.GetInstance();
		for (const auto& elem : cont)
			std::cout << elem << " ";
		std::cout << std::endl;
	}
private:
    MyLogger() {};
    bool m_IsDebugMode = true;
};



