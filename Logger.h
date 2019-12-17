#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include <sstream>
#include <string>
#include <stdarg.h>
#include <stdio.h>

#define logDebug(x) MyLogger::GetInstance().debug(x)
class MyLogger
{
public:
    static MyLogger& GetInstance()
    {
        static MyLogger logger;
        return logger;
    }
    void debug(const char* debugMsg, ...)
    {
		if (m_IsDebugMode == false) return;
		//append a new line to the message string
		char tmp[256];
		strcpy(tmp, debugMsg);
		strcat(tmp, "\n");
		//write debug message to stdout
        va_list args;
        va_start(args, tmp);
		vfprintf(stdout, tmp, args);
        va_end(args);
    }
    
    MyLogger(const MyLogger& m) = delete;
    const MyLogger& operator=(const MyLogger& m) = delete;

private:
    MyLogger() {};
    ~MyLogger() {};
    std::ostringstream os;
    bool m_IsDebugMode = true;
};


