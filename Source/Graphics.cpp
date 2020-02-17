#include "Graphics.h"


JSbool Graphics::Initialize(HINSTANCE hInstance, 
                          LPSTR lpCmdLine, 
                          int nCmdShow, 
                          const Vec2i & windowResolution, 
                          const std::string & windowName, 
                          const std::string & shaderFolderPath,
                          JSbool isFullScreen,
                          JSbool isShowWindow)
{
  m_hInstance = hInstance;
  m_lpCmdLine = lpCmdLine;
  m_nCmdShow = nCmdShow;
  m_WindowsName = windowName;
  m_WindowResulution = windowResolution;
  m_IsFullScreen = isFullScreen;
  m_ShaderFolderPath = shaderFolderPath;
  m_IsShowWindow = isShowWindow;
  //create window
  if(GLOBAL::JSPFAILED == CreateWindows()) return GLOBAL::JSPFAILED;

  //initialize directX 11
  if(false == SetupD3DClass()) return false;

  return GLOBAL::JSPSUCCESSED;
}
void Graphics::AllocateConsole()
{
  //allocate console and redirect cout to console
  AllocConsole();
  //"CON" is a special keyword which refers to the console.
  freopen(GLOBAL::CONSOLESTR, GLOBAL::CONSOLE_READ, stdin);
  freopen(GLOBAL::CONSOLESTR, GLOBAL::CONSOLE_WRITE, stdout);
  freopen(GLOBAL::CONSOLESTR, GLOBAL::CONSOLE_WRITE, stderr);
}

void Graphics::Shutdown()
{
  // Release the color shader object.
  //m_ColorShader->Shutdown();
  //JSDelete(m_ColorShader);
  // Release the model object.
  m_Model->Shutdown();
  JSDelete(m_Model);
  // Release the camera object.
  JSDelete(m_Camera);
  m_D3D->Shutdown();
  JSDelete(m_D3D);
  // Release the texture shader object.
  m_TextureShader->Shutdown();
  JSDelete(m_TextureShader);
}

bool Graphics::Frame()
{
  //return true;
  //render the graphics scene
  bool result  = Render();
  return result;
}

bool Graphics::Render()
{
  XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
  m_D3D->BeginScene(Vec4f(0.0f,0.1f,0.1f,1.f));
  // Generate the view matrix based on the camera's position.
  m_Camera->Render();
  viewMatrix = m_Camera->GetViewMatrix();
  worldMatrix = m_D3D->GetWorldMatrix();
  projectionMatrix = m_D3D->GetProjectionMatrix();
  // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
  m_Model->Render(m_D3D->GetDeviceContext());
  // Render the model using the color shader.
/*  bool result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
  if (!result) return false*/;
  // Render the model using the texture shader.
  bool result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
  if (!result)return false;
  m_D3D->EndScene();
  return true;
}

//handle messages that the application receives from Windows when events occur
//it is to handle an event, like "OK", "QUIT" from users' input
LRESULT CALLBACK WndProc(
  _In_ HWND   hWnd,
  _In_ UINT   message,
  _In_ WPARAM wParam,
  _In_ LPARAM lParam
)
{
  PAINTSTRUCT ps;
  //HDC in the code is a handle to a device context, 
  //which is a data structure that Windows uses to enable your application to communicate with the graphics subsystem. 
  HDC hdc;
  TCHAR greeting[] = _T("Hello, JSEngine!");

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    // Here your application is laid out.
    // For this introduction, we just print out "Hello, Windows desktop!"
    // in the top left corner.
    TextOut(hdc,
      5, 5,
      greeting,
      _tcslen(greeting)
    );
    // End application-specific layout section.

    EndPaint(hWnd, &ps);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }
  return 0;
}
JSbool Graphics::CreateWindows()
{
  /*contains the information about the window, such as:
  1. the application icon
  2. the background color of the window
  3. the name to display in the title bar etc
  Importantly, it contains a function pointer to your window procedure.
  */
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX); //The size, in bytes, of this structure. Be sure to set this member before calling the GetClassInfoEx function.
  /*Defines how to update the window after moving or resizing it,
    how to process double-clicks of the mouse, how to allocate space for the device context,
    and other aspects of the window.*/
  wcex.style = CS_HREDRAW | CS_VREDRAW; //Redraws the entire window if a movement or size adjustment changes the width/height of the client area.
  wcex.lpfnWndProc = WndProc; //Pointer to the function that processes all messages sent to windows in the class and defines the behavior of the window.
  /*Specifies the amount of extra memory, in bytes, that the system should reserve for the class.
    All windows in the class share the extra memory and can use it for any application-defined purpose.
    The system initializes this memory to zero.*/
  wcex.cbClsExtra = 0;
  /*Specifies the amount of extra memory, in bytes, that the system should reserve for each window belonging to the class.
    The extra memory can be used for any application-defined purpose.
    The system initializes this memory to zero.*/
  wcex.cbWndExtra = 0;
  wcex.hInstance = m_hInstance;
  /*Defines the large icon and the small icon.
    The system displays a window's large class icon in the task-switch window that appears when the user presses ALT+TAB.
    The small class icon appears in a window's title bar and in the small icon views of the task bar and explorer. */
  wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
  wcex.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //Defines the mouse cursor that the system displays for a window of the class.
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //Defines the color and pattern that fill the client area when the window is opened or painted.
  wcex.lpszMenuName = "Testing menu name"; //A class menu defines the default menu to be used by the windows in the class if no explicit menu is given when the windows are created.
  wcex.lpszClassName = m_WindowsName.c_str(); //Distinguishes the class from other registered classes.

   //register window class
  if (!RegisterClassEx(&wcex))
  {
    std::cout << "GetLastError() returns: " << GetLastError() << "\n";
    printf("Error in Function = WinMain() at line = %d, with error code = %X \n", __LINE__ - 3, (unsigned int)GetLastError());
    MessageBox(NULL,
               FailedToRegisterWindowMsg,
               ErrorWindowCaption,
               MB_ICONERROR);
    return GLOBAL::JSPFAILED;
  } 

  // The parameters to CreateWindow explained:
  // szWindowClass: the name of the application
  // szTitle: the text that appears in the title bar
  // WS_OVERLAPPEDWINDOW: the type of window to create
  // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
  // 500, 100: initial size (width, length)
  // NULL: the parent of this window
  // NULL: this application does not have a menu bar
  // hInstance: the first parameter from WinMain
  // NULL: not used in this application
  const Vec2i& resolution = GetDesktopResolution();
  m_HWND =!m_IsFullScreen ? CreateWindow(m_WindowsName.c_str(),
                                            m_WindowsName.c_str(),
                                            WS_OVERLAPPEDWINDOW,
                                            (resolution.GetX() - m_WindowResulution.GetX()) >> 1, 
                                            (resolution.GetY() - m_WindowResulution.GetY()) >> 1,
                                            m_WindowResulution.GetX(),
                                            m_WindowResulution.GetY(),
                                            NULL,
                                            NULL,
                                            m_hInstance,
                                            NULL
                                           ) 
                             :
                             CreateWindow(m_WindowsName.c_str(),
                                          m_WindowsName.c_str(),
                                          WS_POPUP | WS_VISIBLE,
                                          0,
                                          0,
                                          resolution.GetX(),
                                          resolution.GetY(),
                                          NULL,
                                          NULL,
                                          m_hInstance,
                                          NULL
                                          );
  // This function returns an HWND, which is a handle to a window. A handle is somewhat like a pointer that Windows uses to keep track of open windows. 
  if (!m_HWND)
  {
    MessageBox(NULL,
               FailedToCreateWindowMsg,  
               ErrorWindowCaption,
               MB_ICONERROR);
    return GLOBAL::JSPFAILED;
  }


  // hWnd: the value returned from CreateWindow
// nCmdShow: the fourth parameter from WinMain
  if (m_IsShowWindow)
  {
    ShowWindow(m_HWND, m_nCmdShow);
    UpdateWindow(m_HWND);
  }
  return GLOBAL::JSPSUCCESSED;
}

JSbool Graphics::SetupD3DClass()
{
  m_D3D = JSNew(D3DClass);
  //initialize the Direct3D object
  JSbool result = m_D3D->Initialize(m_WindowResulution, 
                                    VSYNC_ENABLED, 
                                    m_HWND, 
                                    FULL_SCREEN, 
                                    SCREEN_DEPTH,
                                    SCREEN_NEAR);
  if (!result)
    MessageBox(m_HWND, 
               FailedToInitD3DClass, 
               ErrorWindowCaption, 
               MB_ICONERROR);
  // Create the camera object.
  m_Camera = JSNew(CameraClass);
  //m_Camera = reinterpret_cast<CameraClass*>(g_MemoryManager.AllocateMemory(sizeof(CameraClass)));
  if(!m_Camera) return false;

  // Set the initial position of the camera.
  m_Camera->SetPosition(Vec4f(0.f, 0.0f, -5.0f, 0.f));
  m_Camera->SetLookAt(Vec4f(0.f, 0.f, 1.f, 0.f));
  m_Camera->SetUpVec(Vec4f(0.f, 1.f, 0.f, 0.f));
  // Create the model object.
  m_Model = JSNew(ModelClass);
  if (!m_Model) return false;
  // Initialize the model object.
  //result = m_Model->Initialize(m_D3D->GetDevice());
  result = m_Model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), "Resource/Image/stone01.tga");
  if (!result) 
  {
    MessageBox(m_HWND, FailedToIniModelObject, ErrorWindowCaption, MB_OK);
    return false;
  }
  //// Create the color shader object.
  //m_ColorShader = JSNew(ColorShaderClass);
  //if(!m_ColorShader) return false;
  //// Initialize the color shader object.
  //result = m_ColorShader->Initialize(m_D3D->GetDevice(), m_HWND);
  //if (!result)
  //{
  //  MessageBox(m_HWND, FailedToInitColorShader, ErrorWindowCaption, MB_OK);
  //  return false;
  //}

  // Create the texture shader object.
  m_TextureShader = JSNew(TextShaderClass);
  if (!m_TextureShader) return false;
  // Initialize the color shader object.
  result = m_TextureShader->Initialize(m_D3D->GetDevice(), m_HWND);
  if (!result)
  {
    MessageBox(m_HWND, FailedToInitColorShader, ErrorWindowCaption, MB_OK);
    return false;
  }

  return result;
}

Vec2i Graphics::GetDesktopResolution()
{
  RECT desktop;
  // Get a handle to the desktop window
  const HWND hDesktop = GetDesktopWindow();
  // Get the size of screen to the variable desktop
  GetWindowRect(hDesktop, &desktop);
  // The top left corner will have coordinates (0,0)
  // and the bottom right corner will have coordinates
  // (horizontal, vertical)
  return Vec2i(desktop.right, 
               desktop.bottom);
}