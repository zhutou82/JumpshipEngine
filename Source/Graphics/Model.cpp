#include "Graphics/Model.h"

bool ModelClass::Initialize(ID3D11Device * device)
{
  // Initialize the vertex and index buffers.
  bool result = InitializeBuffers(device);
  if (!result) return false;
  return true;
}

bool ModelClass::InitializeBuffers(ID3D11Device * device)
{
  VertexType* vertices;
  unsigned long* indices;
  D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
  //Specifies data for initializing a subresource.
  D3D11_SUBRESOURCE_DATA vertexData, indexData;
  HRESULT result = GLOBAL::ZERO;
  // Set the number of vertices in the vertex array.
  m_VertexCount = 3;
  // Set the number of indices in the index array.
  m_IndexCount = 3;
  // Create the vertex array.
  vertices = JSNewArray(VertexType, m_VertexCount);
  if (!vertices) return false;
  // Create the index array.
  indices = JSNewArray(unsigned long, m_IndexCount);
  if (!indices) return false;
  
  // Load the vertex array with data.
  vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
  vertices[0].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

  vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
  vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

  vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
  vertices[2].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

  // Load the index array with data.
  indices[0] = 0;  // Bottom left.
  indices[1] = 1;  // Top middle.
  indices[2] = 2;  // Bottom right.
  /*
  With the vertex array and index array filled out we can now use those to create the vertex buffer and index buffer.
  */
  // Set up the description of the static vertex buffer.
  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_VertexCount;
  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertexBufferDesc.CPUAccessFlags = 0;
  vertexBufferDesc.MiscFlags = 0;
  vertexBufferDesc.StructureByteStride = 0;
  // Give the subresource structure a pointer to the vertex data.
  //Pointer to the initialization data.
  vertexData.pSysMem = vertices;
  //The distance (in bytes) from the beginning of one line of a texture to the next line.
  vertexData.SysMemPitch = 0;
  //The distance (in bytes) from the beginning of one depth level to the next.
  vertexData.SysMemSlicePitch = 0;
  // Now create the vertex buffer.
  result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);
  if (FAILED(result)) return false;
  // Set up the description of the static index buffer.
  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_IndexCount;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;
  indexBufferDesc.MiscFlags = 0;
  indexBufferDesc.StructureByteStride = 0;
  // Give the subresource structure a pointer to the index data.
  indexData.pSysMem = indices;
  indexData.SysMemPitch = 0;
  indexData.SysMemSlicePitch = 0;
  // Create the index buffer.
  result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);
  if (FAILED(result)) return false;
  // Release the arrays now that the vertex and index buffers have been created and loaded.
  JSDeleteArray(vertices);
  JSDeleteArray(indices);
  return true;
}

void ModelClass::Render(ID3D11DeviceContext * deviceContext)
{
  // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
  RenderBuffers(deviceContext);
}

void ModelClass::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
  // Set the vertex buffer and index buffer as active on the input assembler in the GPU.
  // Set vertex buffer stride and offset.
  unsigned int stride = sizeof(VertexType), offset = 0;
  // Set the vertex buffer to active in the input assembler so it can be rendered.
  deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
  // Set the index buffer to active in the input assembler so it can be rendered.
  deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
  // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
void ModelClass::Shutdown()
{
  // Shutdown the vertex and index buffers.
  ShutdownBuffers();
}
void ModelClass::ShutdownBuffers()
{
  // Release the index buffer.
  if (m_IndexBuffer)
  {
    m_IndexBuffer->Release();
    m_IndexBuffer = 0;
  }
  // Release the vertex buffer.
  if (m_VertexBuffer)
  {
    m_VertexBuffer->Release();
    m_VertexBuffer = 0;
  }
}