#pragma once
/////////////
// LINKING //
/////////////
/*
Specify the libraries to link when using this object module. 
These libraries contain all the Direct3D functionality for setting up and drawing 3D graphics in DirectX 
as well as tools to interface with the hardware on the computer to obtain information about the refresh rate of the monitor,
the video card being used, and so forth. DirectX 10 libraries are still used, this is because those libraries were never upgraded 
for DirectX 11 as their functionality did not need to change.
*/
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "d3dx10.lib")

#include <Windows.h>
/*
DXGI provides objects to handle tasks such as enumerating graphics adapters and monitors, enumerating display modes, 
choosing buffer formats, sharing resources between processes (such as between applications and the Desktop Window Manager), 
and presenting rendered frames to a window or monitor for display.
*/
#include <dxgi.h> 
#include <d3d11.h>
#include <DirectXMath.h>
#include "Math/JSMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

class D3DClass
{
public:
   D3DClass()
   :
   m_VsyncEnable(false),
   m_VideoCardMemory(0),  
   m_WwapChain(0),
   m_Device(0), 
   m_DeviceContext(0),
   m_RenderTargetView(0),
   m_DepthStencilBuffer(0),
   m_DepthStencilState(0),
   m_DepthStencilView(0),
   m_RasterState(0)
   {};
   bool Initialize(const Vec2i& screenResolution,
                   bool vsyncEnable, //The vsync variable indicates if we want Direct3D to render according to the users monitor refresh rate 
                   HWND hwnd,        //or to just go as fast as possible.
                   bool fullScreen, 
                   float screenDepth, //The screenDepth and screenNear variables are the depth settings  
                   float screenNear); //for our 3D environment that will be rendered in the window.
   void Shutdown();
   void BeginScene(float x, float y, float z, float w);
   void EndScene();
   //A device is used to create resources and to enumerate the capabilities of a display adapter.
   ID3D11Device* GetDevice();
   ID3D11DeviceContext* GetDeviceContext();
   void GetVideoCardInfo(char*, int&);

   D3DClass(const D3DClass&) = delete;
   const D3DClass& operator=(const D3DClass&) = delete;
   ~D3DClass() {} 

private:
  
  bool m_VsyncEnable;
  int m_VideoCardMemory;
  char m_VideoCardDescription[GLOBAL::DEFAULT_SIZE_OF_ADAPTER_DESCRIPTION];
  IDXGISwapChain* m_WwapChain;
  ID3D11Device* m_Device;
  ID3D11DeviceContext* m_DeviceContext;
  ID3D11RenderTargetView* m_RenderTargetView;
  ID3D11Texture2D* m_DepthStencilBuffer;
  ID3D11DepthStencilState* m_DepthStencilState;
  ID3D11DepthStencilView* m_DepthStencilView;
  ID3D11RasterizerState* m_RasterState;

  //D3DXMATRIX m_projectionMatrix;
  //D3DXMATRIX m_worldMatrix;
  //D3DXMATRIX m_orthoMatrix;

};