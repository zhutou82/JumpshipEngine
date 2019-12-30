#pragma once
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"
#include "Math/JSMath.h"

#define GetGraphicsEngine Singleton<Graphics>::GetInstance()
class Graphics : public Singleton<Graphics>
{
  public:


  friend class Singleton<Graphics>;

  const Graphics& operator=(const Graphics&) = delete;
  Graphics(const Graphics&) = delete;
  //void Init(const Vec2f& windowResolution, const std::string& windowName);
   
  private:
  Graphics() {}
  

};