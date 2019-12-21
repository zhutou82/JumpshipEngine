#include "Serializer/Serializer.h"

void Serializer::Serialize(const std::string& path, 
													 const std::string& childElementStr, 
													 std::vector<std::string>& cont)
{
  //<Config> 123 </Config>
  //Value/Name = Config, GetText = 123
	tinyxml2::XMLDocument doc;
	doc.LoadFile(path.c_str());
	tinyxml2::XMLElement* titleElement = doc.FirstChildElement();
  while (titleElement)
  {
    if (titleElement->Name() == childElementStr)
    {
      tinyxml2::XMLElement* childElement = titleElement->FirstChildElement();
      while (childElement)
      {
        cont.push_back(childElement->GetText());
        childElement = childElement->NextSiblingElement();
      }
      break;
    }
    titleElement = titleElement->NextSiblingElement();
  }
}
