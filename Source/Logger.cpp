#include "Logger.h"
#include <stdio.h>
#include <stdarg.h>



void MyLogger::Debug(const char* debugMsg, ...)
{
	if (m_IsDebugMode == false) return;
	//write  message to stdout
	va_list args;
	va_start(args, debugMsg);
  vfprintf(stdout, debugMsg, args);
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

void MyLogger::LogToFile(File_Type type, const char * msg, ...)
{
  if (m_IsDebugMode == false) return;
  //write  message to stdout
  va_list args;
  va_start(args, msg);
  vfprintf(m_FileArrary[type], msg, args);
  va_end(args);
}


void MyLogger::Init(const char * filePath)
{
  InitFile(filePath, DEBUG_FILE_NAME, File_Type::DEBUG);
  InitFile(filePath, INFO_FILE_NAME, File_Type::INFO);
  InitFile(filePath, MEMORYDUMP_FILE_NAME, File_Type::MEMORYDUMP);
  InitFile(filePath, ERROR_FILE_NAME, File_Type::ERROR_MSG);
  m_FileArrary[File_Type::CONSOLE] = stdout; 
}



void MyLogger::Release()
{
  for (JSuint32 i = 0; i < NUM_OF_FILE_TYPES; ++i)
  {
    fclose(m_FileArrary[i]);
  }
}

void MyLogger::InitFile(const char * filePath , const char* fileName, File_Type type)
{
  char tmpFilePath[256];
  strcpy(tmpFilePath, filePath);
  strcat(tmpFilePath, fileName);
  m_FileArrary[type] = fopen(tmpFilePath, WRITE_MODE);
  JSassert(m_FileArrary[type] != JSNULL);
}

