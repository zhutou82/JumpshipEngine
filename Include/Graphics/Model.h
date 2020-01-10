#pragma once
#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <directxmath.h>
#include "Common/GlobalVariables.h"
using namespace DirectX;

class ModelClass
{
public:
  ModelClass() :
  m_VertexBuffer(JSNULL),
  m_IndexBuffer(JSNULL),
  m_VertexCount(GLOBAL::ZERO),
  m_IndexCount(GLOBAL::ZERO)
  {}
  const ModelClass(const ModelClass&) = delete;
  ~ModelClass() {};
  bool Initialize(ID3D11Device* device);
  void Shutdown();
  void Render(ID3D11DeviceContext* deviceContext);
  int GetIndexCount() const {return m_IndexCount;}

private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

  bool InitializeBuffers(ID3D11Device* device);
  void ShutdownBuffers();
  void RenderBuffers(ID3D11DeviceContext* deviceContext);

  ID3D11Buffer *m_VertexBuffer, *m_IndexBuffer;
  int m_VertexCount, m_IndexCount;


};
