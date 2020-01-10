#pragma once
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"
#include "Math/JSMath.h"
#include "Graphics/D3DClass.h"
#include "Graphics/Camera.h"
#include "Graphics/ColorShader.h"
#include "Graphics/Model.h"

constexpr const bool FULL_SCREEN = false;
constexpr const bool VSYNC_ENABLED = true;
constexpr const float SCREEN_DEPTH = 1000.0f;
constexpr const float SCREEN_NEAR = 0.1f;

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
  void Shutdown();
  bool Frame();
  bool Render();
  
  private:

  static constexpr const char* FailedToCreateWindowMsg = "Call to CreateWindow failed!";
  static constexpr const char* FailedToRegisterWindowMsg = "Call to RegisterClassEx failed!";
  static constexpr const char* FailedToInitD3DClass = "Call to initialize Direct3D failed";
  static constexpr const char* FailedToIniModelObject = "Call to initialize Model object failed";
  static constexpr const char* FailedToInitColorShader = "Call to initialize Color Shader object failed";
  static constexpr const char* ErrorWindowCaption = "ERROR!";
  Graphics() 
  : 
  m_D3D(JSNULL),
  m_Camera(JSNULL),
  m_Model(JSNULL),
  m_ColorShader(JSNULL)
  {}
  int CreateWindows();
  int SetupD3DClass();
  Vec2i GetDesktopResolution();
  //window creation memebers
  std::string m_WindowsName;
  Vec2i m_WindowResulution;
  HINSTANCE m_hInstance;
  LPSTR m_lpCmdLine;
  int m_nCmdShow;
  bool m_IsFullScreen;

  D3DClass* m_D3D;
  HWND m_HWND;

  CameraClass* m_Camera;
  ModelClass* m_Model;
  ColorShaderClass* m_ColorShader;
};