#pragma once
#include "Common/CommonHeader.h"
#include "Serializer/tinyxml2.h"
#include "Common/SingletonBaseClass.h"
#include "Math/JSMath.h"

#define g_Serializer Singleton<Serializer>::GetInstance()
class Serializer : public Singleton<Serializer>
{
public:
	friend class Singleton<Serializer>;
	const Serializer& operator=(const Serializer&) = delete;
	Serializer(const Serializer&) = delete;
	void Init(const std::string& path) { m_XMLDoc.LoadFile(path.c_str()); }
	template <typename T>
	void Serialize(const std::string& childElementStr,
		std::vector<T>& cont)
	{
		//<Config> 123 </Config>
		//Value/Name = Config, GetText = 123
		tinyxml2::XMLElement* titleElement = m_XMLDoc.FirstChildElement();
		while (titleElement)
		{
			if (titleElement->Name() == childElementStr)
			{
				tinyxml2::XMLElement* childElement = titleElement->FirstChildElement();
				while (childElement)
				{
					T val = T();
					GetText(childElement->GetText(), val);
					cont.push_back(val);
					childElement = childElement->NextSiblingElement();
				}
				break;
			}
			titleElement = titleElement->NextSiblingElement();
		}
	}

	void GetText(const std::string& text, std::string& val) { val = text; }
	void GetText(const std::string& text, Vec2i& val) {val = JSMath::StringToVec2i(text); }
	void GetText(const std::string& text, bool& val) {val = stoi(text); } 

	
private:
	Serializer() {};
	tinyxml2::XMLDocument m_XMLDoc;
	std::string m_XMLDocPath;

	
};
