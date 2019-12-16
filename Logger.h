#pragma once
#include <iostream>
#include <sstream>
#include <string>

//#ifdef ENABLE_DEBUGLOG
//#define LogDebug(str, true) MyLogger::Debug(str, true);
//#define LogInfo(str) MyLogger::Info(str);
//
//#else
//#define LogDebug(str, false) MyLogger::Debug(str, false);
//
//#endif


class MyLogger
{
public:

    MyLogger() {};
    ~MyLogger() {};

    std::ostream& debug()
    {
        return std::cout << "Debugging msg: ";
    }
    template <class T>
    MyLogger& operator<<(const T& debugObj)
    {
        std::cout << debugObj;
        return *this;
    }

    //template <class T>
    //static void Info(const std::string& inforStr);


private:
    std::ostringstream os;
    bool m_IsDebugMode = false;

};


