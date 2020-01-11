#pragma once
#pragma comment(lib, "d3d11.lib")
//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include "Common/GlobalVariables.h"
#include "Graphics/DirectXTex.h"

class TextureClass
{
public:
	TextureClass()
	:
	m_texture(JSNULL)
	{}
	TextureClass(const TextureClass&) = delete;
	~TextureClass() {};
	bool Initialize(ID3D11Device* device, const wchar_t *);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture() {return m_texture;}
private:
	ID3D11ShaderResourceView* m_texture;
};

#include "Graphics/DirectXTex.inl"