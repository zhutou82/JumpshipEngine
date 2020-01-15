#pragma once
#pragma comment(lib, "d3d11.lib")
//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <stdio.h>
#include <assert.h>
#include "Common/GlobalVariables.h"


class TextureClass
{
public:
	TextureClass()
	:
	m_TextureView(JSNULL),
	m_Texture(JSNULL),
	m_TargaData(JSNULL)
	{}
	TextureClass(const TextureClass&) = delete;
	~TextureClass() {};
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char *);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture() {return m_TextureView;}
private:
  struct TargaHeader
  {
    unsigned char data1[12];
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char data2;
  };
  bool LoadTarga(const char*, int&, int&);
  unsigned char* m_TargaData;
  ID3D11Texture2D* m_Texture;
  ID3D11ShaderResourceView* m_TextureView;
};
