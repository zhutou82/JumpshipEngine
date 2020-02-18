#include "Serializer/BinSerializer.h"

void Binserializer::Write()
{
    m_OutputFile = fopen(DATA_FILE_NAME, BINARY_WRITING_MODE);
    assert(m_OutputFile != JSNULL);
    //write all configs created by strings
    Deserialize(PROFILER_FOLDER);
    Deserialize(IMAGE_FOLDER);
    Deserialize(SHADER_FOLDER);
    Deserialize(LOG_FOLDER);
    Deserialize(PROFILER_FILE_NAME);
    Deserialize(TEXTURE_SHADER_FILE_NAME);
    Deserialize(COLOR_SHADER_FILER_NAME);
    Deserialize(WINDOWS_NAME);
    //write all configs with vec2f
    Deserialize(Vec2i(800, 600));
    //write all configs with bool
    Deserialize(IS_WINDOW_FULLSCREEN);
    Deserialize(IS_WINDOW_SHOW);
    fclose(m_OutputFile);
}
void Binserializer::WriteStringToFile(const std::string & str)
{
    Deserialize(str.size());
    fwrite(str.c_str(), sizeof(char), str.size(), m_OutputFile);
}
void Binserializer::ReadStringFromFile(std::string & str)
{
    JSuint64 size = 0;
    Serialize(size);
    char* buffer = new char [size + 1];
    fread(buffer, sizeof(char), size, m_InputFile);
    buffer[size] = '\0';
    str = std::string(buffer);
    delete buffer;
}
