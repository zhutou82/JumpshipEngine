#pragma once
//The ColorShaderClassClass is what we will use to invoke our HLSL shaders for drawing the 3D models that are on the GPU.
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "Common/GlobalVariables.h"
using namespace DirectX;
using namespace std;


class ColorShaderClass
{

public:
    ColorShaderClass() : 
    m_VertexShader(JSNULL),
    m_PixelShader(JSNULL),
    m_Layout(JSNULL),
    m_MatrixBuffer(JSNULL)
    {};
    ColorShaderClass(const ColorShaderClass&) = delete;
    ~ColorShaderClass() {};

    bool Initialize(ID3D11Device* device, HWND hwnd); 
    void Shutdown();
    bool Render(ID3D11DeviceContext* deviceContext, 
                            int indexCount,
                            XMMATRIX worldMatrix,
                            XMMATRIX viewMatrix, 
                            XMMATRIX projectionMatrix);

private:

    struct MatrixBufferType
    {
        XMMATRIX world;
        XMMATRIX view;
        XMMATRIX projection;
    };

    bool InitializeShader(ID3D11Device* device, HWND hwnd, const wchar_t*, const wchar_t*);
    void ShutdownShader();
    void OutputShaderErrorMessage(ID3D10Blob*, HWND, const wchar_t*);

    bool SetShaderParameters(ID3D11DeviceContext* deviceContext, 
                                                     XMMATRIX worldMatrix, 
                                                     XMMATRIX viewMatrix, 
                                                     XMMATRIX projectionMatrix);
    void RenderShader(ID3D11DeviceContext*, int);

    ID3D11VertexShader* m_VertexShader;
    ID3D11PixelShader* m_PixelShader;
    ID3D11InputLayout* m_Layout;
    ID3D11Buffer* m_MatrixBuffer;

};

