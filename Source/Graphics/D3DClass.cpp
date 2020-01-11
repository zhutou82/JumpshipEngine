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
  //Specifies the subresources of a texture that are accessible from a depth-stencil view.
  //Direct3D can reference an entire resource or it can reference subsets of a resource. The term subresource refers to a subset of a resource.
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
                                         &m_SwapChain,
                                         &m_Device,
                                         NULL,
                                         &m_DeviceContext);
  if (FAILED(result)) return false;
  // Get the pointer to the back buffer.
  result = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
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
  //Initialize the description of the depth buffer.
  ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
  // Set up the description of the depth buffer.
  depthBufferDesc.Width = screenWidth;
  depthBufferDesc.Height = screenHeight;
  //Improving image quality, increased performance
  /* Mipmaps are smaller, pre-filtered versions of a texture image, representing different levels of detail (LOD) of the texture.
  They are often stored in sequences of progressively smaller textures called mipmap chains with each level half as small as the previous one.*/
  depthBufferDesc.MipLevels = 1; //Use 1 for a multisampled texture; or 0 to generate a full set of subtextures.
  depthBufferDesc.ArraySize = 1; //Number of textures in the texture array.
  depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //A 32-bit z-buffer format that supports 24 bits for depth and 8 bits for stencil.
  depthBufferDesc.SampleDesc.Count = 1; //The number of multisamples per pixel.
  depthBufferDesc.SampleDesc.Quality = 0; //The image quality level. The higher the quality, the lower the performance.
  depthBufferDesc.Usage = D3D11_USAGE_DEFAULT; //Value that identifies how the texture is to be read from and written to. The most common value is D3D11_USAGE_DEFAULT; 
  depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //Bind a texture as a depth-stencil target for the output-merger stage.
  depthBufferDesc.CPUAccessFlags = 0; //Flags to specify the types of CPU access allowed. Use 0 if CPU access is not required. These flags can be combined with a logical OR.
  /*Flags that identify other, less common resource options. Use 0 if none of these flags apply.
  These flags can be combined by using a logical OR. For a texture cube-map,
  set the D3D11_RESOURCE_MISC_TEXTURECUBE flag. Cube-map arrays (that is, ArraySize > 6)
  require feature level D3D_FEATURE_LEVEL_10_1 or higher.
  */
  depthBufferDesc.MiscFlags = 0;
  // Create the texture for the depth buffer using the filled out description.
  result = m_Device->CreateTexture2D(&depthBufferDesc, NULL, &m_DepthStencilBuffer);
  if (FAILED(result))return false;

  //Initialize the description of the stencil state.
  /*
  Stencil buffer is used to limit the area of rendering
  The simple combination of depth test and stencil modifiers make a vast number of effects possible
  (such as stencil shadow volumes, Two-Sided Stencil,[1] compositing, decaling, dissolves, fades, swipes, silhouettes, outline drawing or
  highlighting of intersections between complex primitives)
  The most typical application is still to add shadows to 3D applications. It is also used for planar reflections.
  */
  ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
  // Set up the description of the stencil state.
  depthStencilDesc.DepthEnable = true; //Enable depth testing.
  //Identify a portion of the depth-stencil buffer that can be modified by depth data,
  depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //Turn on writes to the depth-stencil buffer
  depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; //If the source data is less than the destination data, the comparison passes
  depthStencilDesc.StencilEnable = true; //Enable stencil testing.
  depthStencilDesc.StencilReadMask = 0xFF; //Identify a portion of the depth-stencil buffer for reading stencil data, the last 8 bits
  depthStencilDesc.StencilWriteMask = 0xFF; //Identify a portion of the depth-stencil buffer for writing  stencil data, the last 8 bits
  //Stencil operations if pixel is front-facing.
  //Identify how to use the results of the depth test and the stencil test for pixels whose surface normal is facing towards the camera
  depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; //A D3D12_STENCIL_OP-typed value that identifies the stencil operation to perform when stencil testing fails.
  depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR; //A D3D12_STENCIL_OP-typed value that identifies the stencil operation to perform when stencil testing passes and depth testing fails.
  depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP; //A D3D12_STENCIL_OP-typed value that identifies the stencil operation to perform when stencil testing and depth testing both pass.
  depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS; //A D3D12_COMPARISON_FUNC-typed value that identifies the function that compares stencil data against existing stencil data.
  //Stencil operations if pixel is back-facing.
  //Identify how to use the results of the depth test and the stencil test for pixels whose surface normal is facing away from the camera
  depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
  depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
  // Create the depth stencil state.
  result = m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);
  if (FAILED(result)) return false;
  // Set the depth stencil state.
  //The output-merger (OM) stage generates the final rendered pixel color using a combination of pipeline state
  //The OM stage is the final step for determining which pixels are visible (with depth-stencil testing) and blending the final pixel colors.
  m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState, 1); //Sets the depth-stencil state of the output-merger stage.
  //Initailze the depth stencil view.
  ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
  //Set up the depth stencil view description.
  depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //A 32-bit z-buffer format that supports 24 bits for depth and 8 bits for stencil.
  //Specifies how a depth-stencil resource will be accessed
  depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; //The resource will be accessed as a 2D texture.
  //The index of the first mipmap level to use.
  depthStencilViewDesc.Texture2D.MipSlice = 0; 
  //Create the depth stencil view.
  result = m_Device->CreateDepthStencilView(m_DepthStencilBuffer, &depthStencilViewDesc, &m_DepthStencilView);
  if (FAILED(result))return false;
  // Bind the render target view and depth stencil buffer to the output render pipeline.
  m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
  // Setup the raster description which will determine how and what polygons will be drawn.
  //Specifies whether to enable line antialiasing; only applies if doing line drawing and MultisampleEnable is FALSE.
  rasterDesc.AntialiasedLineEnable = false;
  //Indicates triangles facing the specified direction are not drawn 
  rasterDesc.CullMode = D3D11_CULL_BACK; //Do not draw triangles that are back-facing.
  //Depth value added to a given pixel. For info about depth bias
  rasterDesc.DepthBias = 0;
  //Maximum depth bias of a pixel
  rasterDesc.DepthBiasClamp = 0.0f;
  //Enable clipping based on distance.
  rasterDesc.DepthClipEnable = true;
  //Determines the fill mode to use when rendering
  rasterDesc.FillMode = D3D11_FILL_SOLID; //Fill the triangles formed by the vertices. Adjacent vertices are not drawn.
  /* Determines if a triangle is front- or back-facing. If this parameter is TRUE, 
  a triangle will be considered front-facing if its vertices are counter-clockwise 
  on the render target and considered back-facing if they are clockwise. 
  If this parameter is FALSE, the opposite is true.*/
  rasterDesc.FrontCounterClockwise = false;
  //Specifies whether to use the quadrilateral or alpha line anti-aliasing algorithm on multisample antialiasing (MSAA) render targets
  rasterDesc.MultisampleEnable = false;
  //Enable scissor-rectangle culling. All pixels outside an active scissor rectangle are culled.
  rasterDesc.ScissorEnable = false;
  rasterDesc.SlopeScaledDepthBias = 0.0f;
  // Create the rasterizer state from the description we just filled out.
  result = m_Device->CreateRasterizerState(&rasterDesc, &m_RasterState);
  if (FAILED(result)) return false;
  // Now set the rasterizer state.
  m_DeviceContext->RSSetState(m_RasterState);

  // Setup the viewport for rendering.
  viewport.Width = (float)screenWidth;
  viewport.Height = (float)screenHeight;
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;
  viewport.TopLeftX = 0.0f;
  viewport.TopLeftY = 0.0f;
  // Create the viewport.
  m_DeviceContext->RSSetViewports(1, &viewport);
  // Setup the projection matrix.
  fieldOfView = (float)DirectX::XM_PI / 4.0f;
  screenAspect = (float)screenWidth / (float)screenHeight;
  // Create the projection matrix for 3D rendering.
  m_ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);
  // Initialize the world matrix to the identity matrix.
  m_WorldMatrix = DirectX::XMMatrixIdentity();
  // Create an orthographic projection matrix for 2D rendering.
  m_OrthoMatrix = DirectX::XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);

  return true;
}
void D3DClass::BeginScene(const Vec4f& color)
{
  // Clear the back buffer.
  m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, color.GetPtr());
  // Clear the depth buffer.
  m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3DClass::EndScene()
{
  // Present the back buffer to the screen since rendering is complete.
  if (m_VsyncEnable)
    // Lock to screen refresh rate.
    m_SwapChain->Present(1, 0);
  else
    // Present as fast as possible.
    m_SwapChain->Present(0, 0);
}

void D3DClass::GetVideoCardInfo(char * cardName, int& memory)
{
  strcpy_s(cardName, 128, m_VideoCardDescription);
  memory = m_VideoCardMemory;
}


void D3DClass::Shutdown()
{
  // Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
  if (m_SwapChain)
  {
    m_SwapChain->SetFullscreenState(false, NULL);
  }

  if (m_RasterState)
  {
    m_RasterState->Release();
    m_RasterState = 0;
  }

  if (m_DepthStencilView)
  {
    m_DepthStencilView->Release();
    m_DepthStencilView = 0;
  }

  if (m_DepthStencilState)
  {
    m_DepthStencilState->Release();
    m_DepthStencilState = 0;
  }

  if (m_DepthStencilBuffer)
  {
    m_DepthStencilBuffer->Release();
    m_DepthStencilBuffer = 0;
  }

  if (m_RenderTargetView)
  {
    m_RenderTargetView->Release();
    m_RenderTargetView = 0;
  }

  if (m_DeviceContext)
  {
    m_DeviceContext->Release();
    m_DeviceContext = 0;
  }

  if (m_Device)
  {
    m_Device->Release();
    m_Device = 0;
  }

  if (m_SwapChain)
  {
    m_SwapChain->Release();
    m_SwapChain = 0;
  }
}