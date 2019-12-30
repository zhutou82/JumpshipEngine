#pragma once
namespace GLOBAL
{
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
}


//Register enum type 
#define REGISTER_ENUM_START(x) enum x {
#define REGISTER_ENUM_ENTRY(x) x, 
#define REGISTER_ENUM_END(x) x##_MAX_SIZE }; 