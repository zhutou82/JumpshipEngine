#pragma once
#include "Common/CommonHeader.h"
#include "Serializer/tinyxml2.h"
#include "Common/SingletonBaseClass.h"

#define GetSerializer Singleton<Serializer>::GetInstance()
class Serializer : public Singleton<Serializer>
{
public:
	friend class Singleton<Serializer>;
	const Serializer& operator=(const Serializer&) = delete;
	Serializer(const Serializer&) = delete;

	void Serialize(const std::string& path, 
								 const std::string& childElementStr, 
								 std::vector<std::string>& cont);

private:
	Serializer() {};

};
