#pragma once

namespace GLOBAL
{
	 const std::string SLASH = "/";
}

//Register enum type 
#define REGISTER_ENUM_START(x) enum x {
#define REGISTER_ENUM_ENTRY(x) x, 
#define REGISTER_ENUM_END(x) x##_MAX_SIZE }; 