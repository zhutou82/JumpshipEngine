#include "Graphics/D3DClass.h"

bool D3DClass::Initialize(const Vec2i& screenResolution,
                          bool vsyncEnable, 
                          HWND hwnd, 
                          bool fullScreen, 
                          float screenDepth, 
                          float screenNear)
{
  HRESULT result = 0;
  IDXGIFactory* factory = NULL;
  //An adapter is an abstraction of the hardware and the software capability of your computer.
  IDXGIAdapter* adapter = NULL;
  IDXGIOutput* adapterOutput = NULL;
  unsigned int numModes = 0, i = 0, numerator = 0, denominator = 0;
  size_t stringLength = 0;
  DXGI_MODE_DESC* displayModeList = NULL;
  DXGI_ADAPTER_DESC adapterDesc;
  int error = 0;
  DXGI_SWAP_CHAIN_DESC swapChainDesc;
  D3D_FEATURE_LEVEL featureLevel;
  ID3D11Texture2D* backBufferPtr = NULL;
  D3D11_TEXTURE2D_DESC depthBufferDesc;
  D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
  D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
  D3D11_RASTERIZER_DESC rasterDesc;
  D3D11_VIEWPORT viewport;
  float fieldOfView = 0.f, screenAspect = 0.f;
  int screenWidth = screenResolution.GetX();
  int screenHeight = screenResolution.GetY();

  m_VsyncEnable = vsyncEnable;
  /*
  This part is to get monitor refresh rate for the current computer
  */
  //Create a DirectX graphics interface factory.
  //An IDXGIFactory interface implements methods for generating DXGI objects 
  //(which handle full screen transitions).
  result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
  if (FAILED(result)) return false;
  // Use the factory to create an adapter for the primary graphics interface (video card).
  result = factory->EnumAdapters(GLOBAL::ZERO, &adapter);
  if (FAILED(result)) return false;
  // Enumerate the primary adapter output (monitor).
  result = adapter->EnumOutputs(GLOBAL::ZERO, &adapterOutput);
  if (FAILED(result)) return false;
  // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM (A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits per channel including alpha.)
  // display format for the adapter output (monitor).
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
  if (FAILED(result)) return false;
  // Create a list to hold all the possible display modes for this monitor/video card combination.
  displayModeList = new DXGI_MODE_DESC[numModes];
  if (!displayModeList) { return false; }
  // Now fill the display mode list structures.
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
  if (FAILED(result)) return false;
  
  // Now go through all the display modes and find the one that matches the screen width and height.
  // When a match is found store the numerator and denominator of the refresh rate for that monitor.
  for (i = 0; i < numModes; i++)
  {
    if (displayModeList[i].Width == (unsigned int)screenWidth)
    {
      if (displayModeList[i].Height == (unsigned int)screenHeight)
      {
        numerator = displayModeList[i].RefreshRate.Numerator;
        denominator = displayModeList[i].RefreshRate.Denominator;
      }
    }
  }
  // Get the adapter (video card) description.
  result = adapter->GetDesc(&adapterDesc);
  if (FAILED(result)) return false;
  // Store the dedicated video card memory in megabytes.
  m_VideoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / GLOBAL::MB_IN_BYTES);
  // Convert the name of the video card to a character array and store it.
  error = wcstombs_s(&stringLength, 
                     m_VideoCardDescription, 
                     GLOBAL::DEFAULT_SIZE_OF_ADAPTER_DESCRIPTION, 
                     adapterDesc.Description, 
                     GLOBAL::DEFAULT_SIZE_OF_ADAPTER_DESCRIPTION);
  if (error != GLOBAL::ZERO) return false;

  // Release the display mode list.
  JSDeleteArray(displayModeList);
  // Release the adapter output.
  adapterOutput->Release();
  adapterOutput = JSNULL;
  // Release the adapter.
  adapter->Release();
  adapter = JSNULL;
  // Release the factory.
  factory->Release();
  factory = JSNULL;
  /*
  This part is to initialize DirectX
  */
  // Initialize the swap chain description.
  ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
  // Set to a single back buffer.
  swapChainDesc.BufferCount = 1;
  // Set the width and height of the back buffer.
  swapChainDesc.BufferDesc.Width = screenWidth;
  swapChainDesc.BufferDesc.Height = screenHeight;
  // Set regular 32-bit surface for the back buffer.
  swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  //The next part of the description of the swap chain is the refresh rate. 
  //The refresh rate is how many times a second it draws the back buffer to the front buffer. 
  //If vsync is set to true in our graphicsclass.h header then this will lock the refresh rate to the system settings (for example 60hz). 
  //That means it will only draw the screen 60 times a second (or higher if the system refresh rate is more than 60). 
  //However if we set vsync to false then it will draw the screen as many times a second as it can, however this can cause some visual artifacts.
  if (m_VsyncEnable)
  {
    swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
  }
  else
  {
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
  }
  //Set the usage of the back buffer.
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Use the surface or resource as an output render target
  //Set the handle for the window to render to.
  swapChainDesc.OutputWindow = hwnd;
  //Turn multisampling off.
  //Multisample point anti-aliasing (MSAA) is a type of spatial anti-aliasing, a technique used in computer graphics to improve image quality.
  //https://vulkan-tutorial.com/Multisampling
  swapChainDesc.SampleDesc.Count = 1;
  swapChainDesc.SampleDesc.Quality = 0;
  // Set to full screen or windowed mode.
  if (fullScreen) swapChainDesc.Windowed = false;
  else swapChainDesc.Windowed = true;
  //Set the scan line ordering and scaling to unspecified.
  swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //Flags indicating the method the raster uses to create an image on a surface, 
                                                                                    //Scanline rendering works on a row-by-row basis rather than a polygon-by-polygon or pixel-by-pixel basis.
  swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //Flags indicating how an image is stretched to fit a given monitor's resolution.
  //Discard the back buffer contents after presenting.
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  //Don't set the advanced flags.
  swapChainDesc.Flags = 0;
  // Set the feature level to DirectX 11.
  featureLevel = D3D_FEATURE_LEVEL_11_0;
  // Create the swap chain, Direct3D device, and Direct3D device context.
  /*
  Note that if the user does not have a DirectX 11 video card this function call will fail to create the device and device context. 
  Also if you are testing DirectX 11 functionality yourself and don't have a DirectX 11 video card then you can replace D3D_DRIVER_TYPE_HARDWARE with D3D_DRIVER_TYPE_REFERENCE 
  and DirectX will use your CPU to draw instead of the video card hardware. Note that this runs 1/1000 the speed but it is good for people who don't have DirectX 11 
  video cards yet on all their machines.
  */
  result = D3D11CreateDeviceAndSwapChain(NULL, 
                                         D3D_DRIVER_TYPE_HARDWARE, 
                                         NULL, 
                                         0, 
                                         &featureLevel, 
                                         1,
                                         D3D11_SDK_VERSION, 
                                         &swapChainDesc, 
                                         &m_WwapChain, 
                                         &m_Device, 
                                         NULL, 
                                         &m_DeviceContext);
  if (FAILED(result)) return false;
  // Get the pointer to the back buffer.
  result = m_WwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
  if (FAILED(result)) return false;
  // Create the render target view with the back buffer pointer.
  result = m_Device->CreateRenderTargetView(backBufferPtr, NULL, &m_RenderTargetView);
  if (FAILED(result)) return false;
  // Release pointer to the back buffer as we no longer need it.
  backBufferPtr->Release();
  backBufferPtr = JSNULL;
  /*
  set up a depth buffer description. We'll use this to create a depth buffer so that our polygons can be rendered properly in 3D space. 
  At the same time we will attach a stencil buffer to our depth buffer. The stencil buffer can be used to achieve effects such as motion blur, 
  volumetric shadows, and other things.
  */
  // Initialize the description of the depth buffer.
  ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
  // Set up the description of the depth buffer.
  depthBufferDesc.Width = screenWidth;
  depthBufferDesc.Height = screenHeight;
  depthBufferDesc.MipLevels = 1;
  depthBufferDesc.ArraySize = 1;
  depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthBufferDesc.SampleDesc.Count = 1;
  depthBufferDesc.SampleDesc.Quality = 0;
  depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depthBufferDesc.CPUAccessFlags = 0;
  depthBufferDesc.MiscFlags = 0;

  return false;
}

void D3DClass::Shutdown()
{
}

void D3DClass::BeginScene(float x, float y, float z, float w)
{
}

void D3DClass::EndScene()
{
}
