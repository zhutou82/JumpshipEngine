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


}
#define JSNULL NULL

//
#define JSNew(x) \
new x;


#define JSDelete(x) assert(x != NULL); \
delete x; x = NULL;  //deletion will access destructor

#define JSDeleteArray(x) assert(x != NULL); \
delete []x; x = NULL;

//Register enum type 
//#define REGISTER_ENUM_START(x) enum x {
//#define REGISTER_ENUM_ENTRY(x) x, 
//#define REGISTER_ENUM_END(x) x##_MAX_SIZE }; 