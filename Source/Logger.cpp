#include "Logger.h"
#include <stdio.h>
#include <stdarg.h>

void MyLogger::Debug(const char* debugMsg, ...)
{
	if (m_IsDebugMode == false) return;
	//append a new line to the message string
	char tmp[256];
	strcpy(tmp, debugMsg);
	strcat(tmp, "\n");
	//write  message to stdout
	va_list args;
	va_start(args, tmp);
	vfprintf(stdout, tmp, args);
	va_end(args);
}
void MyLogger::Info(const char* infoMsg, ...)
{
	//append a new line to the message string
	char tmp[256];
	strcpy(tmp, infoMsg);
	strcat(tmp, "\n");
	//write  message to stdout
	va_list args;
	va_start(args, tmp);
	vfprintf(stdout, tmp, args);
	va_end(args);
}
