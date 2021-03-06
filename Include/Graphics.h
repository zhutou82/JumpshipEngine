#pragma once
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"
#include "Math/JSMath.h"
#include "Graphics/D3DClass.h"
#include "Graphics/Camera.h"
#include "Graphics/ColorShader.h"
#include "Graphics/Model.h"
#include "Graphics/TextureShader.h"
#include "Common/MemoryManager.h"

constexpr const bool FULL_SCREEN = false;
constexpr const bool VSYNC_ENABLED = true;
constexpr const float SCREEN_DEPTH = 1000.0f;
constexpr const float SCREEN_NEAR = 0.1f;

#define g_GraphicsEngine Singleton<Graphics>::GetInstance()
#define g_Camera g_GraphicsEngine.GetCameraClass()
class Graphics : public Singleton<Graphics>
{
    public:
    friend class Singleton<Graphics>;
    JSbool Initialize(_In_ HINSTANCE hInstance,
                      _In_ LPSTR lpCmdLine,
                      _In_ int nCmdShow,
                      const Vec2i& windowResolution, 
                      const std::string& windowName,
                      const std::string& shaderFolderPath,
                      JSbool isFullScreen,
                      JSbool isShowWindow);
    void AllocateConsole();
    void PopupMessageBox();
    void Shutdown();
    bool Frame();
    bool Render();
    
    CameraClass * GetCameraClass() const {return m_Camera;}

    private:

    static constexpr const JSchar* FailedToCreateWindowMsg = "Call to CreateWindow failed!";
    static constexpr const JSchar* FailedToRegisterWindowMsg = "Call to RegisterClassEx failed!";
    static constexpr const JSchar* FailedToInitD3DClass = "Call to initialize Direct3D failed";
    static constexpr const JSchar* FailedToIniModelObject = "Call to initialize Model object failed";
    static constexpr const JSchar* FailedToInitColorShader = "Call to initialize Color Shader object failed";
    static constexpr const JSchar* ErrorWindowCaption = "ERROR!";
    Graphics() 
    : 
    m_D3D(JSNULL),
    m_Camera(JSNULL),
    m_Model(JSNULL),
    m_ColorShader(JSNULL),
    m_TextureShader(JSNULL)
    {}
    JSbool CreateWindows();
    JSbool SetupD3DClass();
    Vec2i GetDesktopResolution();
    //window creation memebers
    std::string m_WindowsName;
    std::string m_ShaderFolderPath;
    Vec2i m_WindowResulution;
    HINSTANCE m_hInstance;
    LPSTR m_lpCmdLine;
    int m_nCmdShow;
    JSbool m_IsFullScreen;
    JSbool m_IsShowWindow;

    D3DClass* m_D3D;
    HWND m_HWND;

    CameraClass* m_Camera;
    ModelClass* m_Model;
    ColorShaderClass* m_ColorShader;
    TextShaderClass* m_TextureShader;
};