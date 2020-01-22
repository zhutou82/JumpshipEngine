#include "Serializer/BinSerializer.h"
#include "JumpshipEngine.h"

void Binserializer::Read()
{
  std::cout << "static_i: " <<  static_i << std::endl; 
  m_InputFile = fopen(DATA_FILE_NAME, BINARY_READING_MODE);
  if (m_InputFile != JSNULL)
  {
    std::string profiler;
    std::string image;
    std::string shader;
    //folder path
    Serialize(profiler);
    Serialize(image);
    Serialize(shader);
    std::cout << profiler << ", "
              << image << ", "
              << shader << std::endl;
  }
}

void Binserializer::Write()
{
  m_OutputFile = fopen(DATA_FILE_NAME, BINARY_WRITING_MODE);
  std::string profiler = "ProfilerOutput/";
  std::string image = "Image/";
  std::string shader = "Shader/";

  if (m_OutputFile != JSNULL)
  {
    Deserialize(profiler);
    Deserialize(image);
    Deserialize(shader);
  }
  fclose(m_OutputFile);
}

void Binserializer::WriteStringToFile(const std::string & str)
{
  Deserialize(str.size());
  fwrite(str.c_str(), sizeof(char), str.size(), m_OutputFile);
}

void Binserializer::ReadStringFromFile(std::string & str)
{
  size_t size = 0;
  Serialize(size);
  char* buffer = (char*)malloc(size + 1);
  fread(buffer, sizeof(char), size, m_InputFile);
  buffer[size] = '\0';
  str = std::string(buffer);
  delete buffer;
}
