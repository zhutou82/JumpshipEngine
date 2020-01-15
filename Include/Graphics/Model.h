#pragma once
#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <directxmath.h>
#include "Common/GlobalVariables.h"
#include "Graphics/Texture.h"
using namespace DirectX;

class ModelClass
{
public:
  ModelClass() :
  m_VertexBuffer(JSNULL),
  m_IndexBuffer(JSNULL),
  m_VertexCount(GLOBAL::ZERO),
  m_IndexCount(GLOBAL::ZERO),
  m_Texture(JSNULL)
  {}
  const ModelClass(const ModelClass&) = delete;
  ~ModelClass() {};
  bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* textureFilename);
  void Shutdown();
  void Render(ID3D11DeviceContext* deviceContext);
  int GetIndexCount() const {return m_IndexCount;}
  ID3D11ShaderResourceView* GetTexture() {return m_Texture->GetTexture(); }

private:
	//struct VertexType
	//{
	//	XMFLOAT3 position;
	//	XMFLOAT4 color;
	//};

  struct VertexType
  {
    XMFLOAT3 position;
    XMFLOAT2 texture;
  };

  bool InitializeBuffers(ID3D11Device* device);
  void ShutdownBuffers();
  void RenderBuffers(ID3D11DeviceContext* deviceContext);
  bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const char*);
  void ReleaseTexture();

  ID3D11Buffer *m_VertexBuffer, *m_IndexBuffer;
  int m_VertexCount, m_IndexCount;
  TextureClass* m_Texture;



};
