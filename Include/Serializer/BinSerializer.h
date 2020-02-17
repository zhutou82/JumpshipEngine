#pragma once
#include "Common/SingletonBaseClass.h"
#include "Common/GlobalVariables.h"
#include "JumpshipEngine.h"
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include "JumpshipEngine.h"


class BinaryFile
{
  public:

  void Write(const std::string& str);
  void Write(int in);
  void Write(float fl);
  void Wrtie(double dou);

};



#define g_Binserializer Singleton<Binserializer>::GetInstance()
class Binserializer : Singleton<Binserializer>
{
  const std::string PROFILER_FOLDER = "ProfilerOutput/";
  const std::string IMAGE_FOLDER = "Image/";
  const std::string SHADER_FOLDER = "Shader/";
  const std::string LOG_FOLDER = "LogFiles/";
  const std::string TEXTURE_SHADER_FILE_NAME = "texture";
  const std::string COLOR_SHADER_FILER_NAME = "color";
  const std::string PROFILER_FILE_NAME = "version1";
  const std::string WINDOWS_NAME = "JSEngine";
  static constexpr const JSbool IS_WINDOW_FULLSCREEN = false;
  static constexpr const JSbool IS_WINDOW_SHOW = false;

public:
  friend class Singleton<Binserializer>;
  static constexpr const JSchar* DATA_FILE_NAME = "Engine.dat";
  static constexpr const JSchar* BINARY_WRITING_MODE = "wb";
  static constexpr const JSchar* BINARY_READING_MODE = "rb";
  void StartReading() { m_InputFile = fopen(DATA_FILE_NAME, BINARY_READING_MODE); assert(m_InputFile != JSNULL); }
  template <typename T>
  void Read(std::vector<T>& vec, int max_size)
  {
    //assert(vec.size() == max_size);1
    for (size_t i = 0; i < max_size; ++i)
    {
      T tmpValue;
      Serialize(tmpValue);
      vec.push_back(tmpValue);
    }
  }
  void EndReading() { fclose(m_InputFile); }
  void Write();
  template<typename T>
  void WriteToFile(T value, size_t size = 1) { fwrite(&value, sizeof(char), size, m_OutputFile); }
  void WriteStringToFile(const std::string& str);

  template <typename T>
  void ReadFromFile(T& value, size_t size = 1) { fread(&value, sizeof(char), size, m_InputFile); }
  void ReadStringFromFile(std::string& str);

  void Deserialize(const std::string& str) { WriteStringToFile(str); }
  template <typename T>
  void Deserialize(T in) { WriteToFile(in, sizeof(T)); }

  void Serialize(std::string& str) { ReadStringFromFile(str); }
  template <typename T> 
  void Serialize(T& in) { ReadFromFile(in, sizeof(T)); }

 private:
   Binserializer() {};
   BinaryFile m_BinaryFile;
   FILE* m_OutputFile;
   FILE* m_InputFile;
};

