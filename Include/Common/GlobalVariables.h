#pragma once
#include "Common/CommonHeader.h"
namespace GLOBAL
{
	 const std::string SLASH = "/";
   const std::string NEW_LINE = "\n";
}


//Register enum type 
#define REGISTER_ENUM_START(x) enum x {
#define REGISTER_ENUM_ENTRY(x) x, 
#define REGISTER_ENUM_END(x) x##_MAX_SIZE }; 