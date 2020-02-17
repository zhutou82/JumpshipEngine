#pragma once
#include <string>
#include <assert.h> 
//typedef
typedef void                JSvoid;
typedef bool                JSbool;
typedef bool                JSint1;
typedef char                JSbyte;
typedef char                JSchar;
typedef char                JSint8;
typedef unsigned char       JSuint8;
typedef short               JSint16;
typedef unsigned short      JSuint16;
typedef int                 JSint32;
typedef long long           JSint64;
typedef unsigned            JSuint32;
typedef unsigned long long  JSuint64;
typedef float               JSfloat;
typedef double              JSdouble;

namespace GLOBAL
{ 
   //Debug info
	 constexpr const JSchar* SLASH = "/";
   constexpr const JSchar* NEW_LINE = "\n";
   constexpr const JSchar* BRACKET_O = "(";
   constexpr const JSchar* BRACKET_C = ")";
   constexpr const JSchar* COMMA = ", ";
   constexpr const JSchar* COLON = ": ";
   constexpr const JSchar* SQUARE_BRACKET_O = "[";
   constexpr const JSchar* SQUARE_BRACKET_C = "]";
   constexpr const JSchar* ARROW = "->";
   constexpr const JSchar* DASH = "-";
   constexpr const JSchar* JSTRUE = "True";
   constexpr const JSchar* JSFALSE = "False";
   constexpr const JSchar* JSPASS = "Pass!";
   constexpr const JSchar* JSFAIL = "Failed!";
   //String manipulation
   constexpr const JSchar* JSSCOMMA = ",";
   //Window creation 
   constexpr const JSint32 ZERO = 0;
   constexpr const JSbool JSPFAILED = 1;
   constexpr const JSbool JSPSUCCESSED = 0;
   constexpr const JSchar* CONSOLESTR = "CON";
   constexpr const JSchar* CONSOLE_WRITE = "w";
   constexpr const JSchar* CONSOLE_READ = "r";
   //D3D creation
   constexpr const JSint32 MB_IN_BYTES = 1048576;
   constexpr const JSint32 DEFAULT_SIZE_OF_ADAPTER_DESCRIPTION = 128;
   constexpr const JSchar* VERTEXT_SHADER_FILE_EXTENSION = "vs";
   constexpr const JSchar* PIXEL_SHADER_FILE_EXTENSION = "ps";
}
#define JSNULL NULL
#define JSassert(x) assert(x)

#include "MemoryManager.h"
//#define JSassert(x) assert(x)








//Register enum type 
//#define REGISTER_ENUM_START(x) enum x {
//#define REGISTER_ENUM_ENTRY(x) x, 
//#define REGISTER_ENUM_END(x) x##_MAX_SIZE };
