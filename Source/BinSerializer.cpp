#include "Serializer/BinSerializer.h"

void Binserializer::Write()
{
  m_OutputFile = fopen(DATA_FILE_NAME, BINARY_WRITING_MODE);
  assert(m_OutputFile != JSNULL);
  //write all configs created by strings
  Deserialize(GLOBAL::PROFILER_FOLDER);
  Deserialize(GLOBAL::IMAGE_FOLDER);
  Deserialize(GLOBAL::SHADER_FOLDER);
  Deserialize(GLOBAL::PROFILER_FILE_NAME);
  Deserialize(GLOBAL::TEXTURE_SHADER_FILE_NAME);
  Deserialize(GLOBAL::COLOR_SHADER_FILER_NAME);
  Deserialize(GLOBAL::WINDOWS_NAME);
  //write all configs with vec2f
  Deserialize(Vec2i(800, 600));
  //write all configs with bool
  Deserialize(GLOBAL::IS_WINDOW_FULLSCREEN);
  Deserialize(GLOBAL::IS_WINDOW_SHOW);
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
