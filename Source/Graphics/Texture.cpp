#include "Graphics/Texture.h"

bool TextureClass::Initialize(ID3D11Device* device, const wchar_t* fileName)
{
  return true;
}

void TextureClass::Shutdown()
{
  m_texture->Release();
  m_texture = 0;
}
