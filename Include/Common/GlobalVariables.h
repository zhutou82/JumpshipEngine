#pragma once
namespace GLOBAL
{ 
   //Debug info
	 constexpr const char* SLASH = "/";
   constexpr const char* NEW_LINE = "\n";
   constexpr const char* BRACKET_O = "(";
   constexpr const char* BRACKET_C = ")";
   constexpr const char* COMMA = ", ";
   constexpr const char* COLON = ": ";
   constexpr const char* SQUARE_BRACKET_O = "[";
   constexpr const char* SQUARE_BRACKET_C = "]";
   constexpr const char* JSTRUE = "True";
   constexpr const char* JSFALSE = "False";
   constexpr const char* JSPASS = "Pass!";
   constexpr const char* JSFAIL = "Failed!";
   //String manipulation
   constexpr const char* JSSCOMMA = ",";
   //Window creation 
   constexpr const int ZERO = 0;
   constexpr const int JSPFAILED = 1;
   constexpr const int JSPSUCCESSED = 0;
   constexpr const char* CONSOLESTR = "CON";
   constexpr const char* CONSOLE_WRITE = "w";
   constexpr const char* CONSOLE_READ = "r";
   //D3D creation
   constexpr const int MB_IN_BYTES = 1048576;
   constexpr const int DEFAULT_SIZE_OF_ADAPTER_DESCRIPTION = 128;
   constexpr const char* VERTEXT_SHADER_FILE_EXTENSION = "vs";
   constexpr const char* PIXEL_SHADER_FILE_EXTENSION = "ps";
   //Serializer
   constexpr const char* PROFILER_FOLDER = "ProfilerOutput/";
   constexpr const char* IMAGE_FOLDER = "Image/";
   constexpr const char* SHADER_FOLDER = "Shader/";
   constexpr const char* TEXTURE_SHADER_FILE_NAME = "texture";
   constexpr const char* COLOR_SHADER_FILER_NAME = "color";
   constexpr const char* PROFILER_FILE_NAME = "version1";
   constexpr const char* WINDOWS_NAME = "JSEngine";
   constexpr const bool IS_WINDOW_FULLSCREEN = false;
   constexpr const bool IS_WINDOW_SHOW = false;

}
#define JSNULL NULL


#define JSNewArray(x, y) \
new x[y]


#define JSDelete(x) assert(x != NULL); \
delete x; x = NULL;  //deletion will access destructor

#define JSDeleteArray(x) assert(x != NULL); \
delete []x; x = NULL;

//Register enum type 
//#define REGISTER_ENUM_START(x) enum x {
//#define REGISTER_ENUM_ENTRY(x) x, 
//#define REGISTER_ENUM_END(x) x##_MAX_SIZE }; 