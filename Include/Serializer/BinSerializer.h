#pragma once
#include "Common/SingletonBaseClass.h"
#include "JumpshipEngine.h"
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h> 


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
public:
  friend class Singleton<Binserializer>;
  static constexpr const char* DATA_FILE_NAME = "Engine.dat";
  static constexpr const char* BINARY_WRITING_MODE = "wb";
  static constexpr const char* BINARY_READING_MODE = "wb";
  void Read();
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

