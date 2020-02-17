#include "Graphics/Texture.h"

bool TextureClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* fileName)
{
  bool result;
  int height, width;
  D3D11_TEXTURE2D_DESC textureDesc;
  HRESULT hResult;
  unsigned int rowPitch;
  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  // Load the targa image data into memory.
  result = LoadTarga(fileName, height, width);
  if (!result) return false;

  // Setup the description of the texture.
  textureDesc.Height = height;
  textureDesc.Width = width;
  //The maximum number of mipmap levels in the texture. 
  textureDesc.MipLevels = 0; //Use 1 for a multisampled texture; or 0 to generate a full set of subtextures.
  //Number of textures in the texture array.
  textureDesc.ArraySize = 1;
  textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  //The number of multisamples per pixel.
  textureDesc.SampleDesc.Count = 1;
  //The image quality level. The higher the quality, the lower the performance. 
  textureDesc.SampleDesc.Quality = 0;
  textureDesc.Usage = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

  // Create the empty texture.
  hResult = device->CreateTexture2D(&textureDesc, NULL, &m_Texture);
  if (FAILED(hResult))
  {
    return false;
  }

  // Set the row pitch of the targa image data.
  rowPitch = (width * 4) * sizeof(unsigned char);
  // Copy the targa image data into the texture.
  //The recommendation is that you use Map and Unmap for data that is going to be reloaded each frame or on a very regular basis. 
  //And you should use UpdateSubresource for something that will be loaded once or that gets loaded rarely during loading sequences.
  deviceContext->UpdateSubresource(m_Texture, 0, NULL, m_TargaData, rowPitch, 0);
  // Setup the shader resource view description.
  srvDesc.Format = textureDesc.Format;
  //The resource type of the view.
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; //The resource is a 2D texture.
  //Index of the most detailed mipmap level to use; 
  srvDesc.Texture2D.MostDetailedMip = 0;
  srvDesc.Texture2D.MipLevels = -1;
  // Create the shader resource view for the texture.
  hResult = device->CreateShaderResourceView(m_Texture, &srvDesc, &m_TextureView);
  if (FAILED(hResult)) return false;
  // Generate mipmaps for this texture.
  deviceContext->GenerateMips(m_TextureView);
  return true;
}

void TextureClass::Shutdown()
{
  if (m_Texture)
  {
    m_Texture->Release();
    m_Texture = 0;
  }
  if (m_TextureView)
  {
    m_TextureView->Release();
    m_TextureView = 0;
  }
  // Release the targa data.
  if (m_TargaData)
  {
    delete[] m_TargaData;
    m_TargaData = 0;
  }
}
/*
This is our targa image loading function. Once again note that targa images are stored upside down and need to be flipped before using. 
So here we will open the file, read it into an array, and then take that array data and load it into the m_targaData array in the correct order.
Note we are purposely only dealing with 32 bit targa files that have alpha channels, this function will reject targa's that are saved as 24 bit.
*/
bool TextureClass::LoadTarga(const char* filename, int& height, int& width)
{
  int error, bpp, imageSize, index, i, j, k;
  FILE* filePtr;
  unsigned int count;
  TargaHeader targaFileHeader;
  unsigned char* targaImage;


  // Open the targa file for reading in binary.
  error = fopen_s(&filePtr, filename, "rb");
  if (error != 0)
  {
    return false;
  }

  // Read in the file header.
  count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
  if (count != 1)
  {
    return false;
  }

  // Get the important information from the header.
  height = (int)targaFileHeader.height;
  width = (int)targaFileHeader.width;
  bpp = (int)targaFileHeader.bpp;

  // Check that it is 32 bit and not 24 bit.
  if (bpp != 32)
  {
    return false;
  }

  // Calculate the size of the 32 bit image data.
  imageSize = width * height * 4;

  // Allocate memory for the targa image data.
  targaImage = JSNewArray(unsigned char, imageSize);
  if (!targaImage)
  {
    return false;
  }

  // Read in the targa image data.
  count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
  if (count != imageSize)
  {
    return false;
  }

  // Close the file.
  error = fclose(filePtr);
  if (error != 0)
  {
    return false;
  }

  // Allocate memory for the targa destination data.
  m_TargaData = JSNewArray(unsigned char, imageSize);
  if (!m_TargaData)
  {
    return false;
  }

  // Initialize the index into the targa destination data array.
  index = 0;

  // Initialize the index into the targa image data.
  k = (width * height * 4) - (width * 4);

  // Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
  for (j = 0; j < height; j++)
  {
    for (i = 0; i < width; i++)
    {
      m_TargaData[index + 0] = targaImage[k + 2];  // Red.
      m_TargaData[index + 1] = targaImage[k + 1];  // Green.
      m_TargaData[index + 2] = targaImage[k + 0];  // Blue
      m_TargaData[index + 3] = targaImage[k + 3];  // Alpha

      // Increment the indexes into the targa data.
      k += 4;
      index += 4;
    }

    // Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
    k -= (width * 8);
  }

  // Release the targa image data now that it was copied into the destination array.
  JSDeleteArray(targaImage);
  targaImage = 0;

  return true;
}
