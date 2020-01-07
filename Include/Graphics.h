#pragma once
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"
#include "Math/JSMath.h"


#define GetGraphicsEngine Singleton<Graphics>::GetInstance()
class Graphics : public Singleton<Graphics>
{
  public:
  friend class Singleton<Graphics>;
  int Initialize(_In_ HINSTANCE hInstance,
                  _In_ LPSTR lpCmdLine,
                  _In_ int nCmdShow,
                  const Vec2i& windowResolution, 
                  const std::string& windowName,
                  bool isFullScreen);
  void AllocateConsole();
  void PopupMessageBox();
  private:

  static constexpr const char* FailedToCreateWindowMsg = "Call to CreateWindow failed!";
  static constexpr const char* FailedToRegisterWindowMsg = "Call to RegisterClassEx failed!";
  static constexpr const char* ErrorWindowCaption = "ERROR!";
  Graphics() {}
  int CreateWindows();
  Vec2i GetDesktopResolution();
  //window creation memebers
  std::string m_WindowsName;
  Vec2i m_WindowResulution;
  HINSTANCE m_hInstance;
  LPSTR m_lpCmdLine;
  int m_nCmdShow;
  bool m_IsFullScreen;

};