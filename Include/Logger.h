#pragma once
#pragma warning(disable:4996) //to fix CRT_NO_WARNING
#include <iostream> 
#include "Common/SingletonBaseClass.h"
#include "Common/GlobalVariables.h"
#include "ThreadPool.h"
#include <array>
enum File_Type
{
  DEBUG = 0,
  INFO = 1,
  MEMORYDUMP = 2,
  ERROR_MSG = 3,
  CONSOLE = 4
};

#define g_Logger Singleton<MyLogger>::GetInstance()
#define LogDebug(...)      g_Logger.Debug(__VA_ARGS__)
#define LogInfo(...)       g_Logger.LogToFile(File_Type::INFO, __VA_ARGS__)
#define LogMemoryDump(...) g_Logger.LogToFile(File_Type::MEMORYDUMP, __VA_ARGS__)
#define LogConsole(...)    g_Logger.LogToFile(File_Type::CONSOLE, __VA_ARGS__)
#define PrintCont(x)       g_Logger.PrintC(x)

class MyLogger : public Singleton<MyLogger>
{
 
  static constexpr const JSuint32 NUM_OF_FILE_TYPES = 10;
  static constexpr const JSchar* DEBUG_FILE_NAME = "Debug.txt";
  static constexpr const JSchar* INFO_FILE_NAME = "Info.txt";
  static constexpr const JSchar* MEMORYDUMP_FILE_NAME = "MemoryDump.txt";
  static constexpr const JSchar* ERROR_FILE_NAME = "Error.txt";
  static constexpr const JSchar* WRITE_MODE = "wb";

public:
	friend class Singleton<MyLogger>;
	void Debug(const char* debugMsg, ...);
	void Info(const char* inforMsg, ...);
  void LogToFile(File_Type type, const char* msg, ...);

	template <typename Cont>
	void PrintC(const Cont& cont)
	{
    GetThreadPool.AddTask([&cont]()
    {
      for (const auto& elem : cont)
        std::cout << elem << " ";
    std::cout << std::endl;
    }
    );
	}
  void Init(const char* filePath);
  void Release();
private:
    MyLogger() {};
    void InitFile(const char* filePath, const char* fileName, File_Type type);
    bool m_IsDebugMode = true;
    const char* m_LogFilePath;
    std::array<FILE*, NUM_OF_FILE_TYPES> m_FileArrary;
};



