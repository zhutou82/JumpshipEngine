#include "Graphics/TextureShader.h"
#include "JumpshipEngine.h"

bool TextShaderClass::Initialize(ID3D11Device * device, HWND hwnd)
{
    bool result = false;

    //std::string textureFolderPath = GetEngine.GetRecourceFolderPath() + g_EngineConfigFolderPathVec[FolderPath_Index::SHADER_FOLDER];

    //std::string textureVsFileName = textureFolderPath +
    //                                                                g_EngineConfigFileNameVec[FileName_Index::TEXTURE_SHADER_FILENAME] + 
    //                                                                GLOBAL::VERTEXT_SHADER_FILE_EXTENSION;
    //std::string texturePsFileName = textureFolderPath +
    //                                                                g_EngineConfigFileNameVec[FileName_Index::TEXTURE_SHADER_FILENAME] + 
    //                                                                GLOBAL::PIXEL_SHADER_FILE_EXTENSION;
    // Initialize the vertex and pixel shaders.
    result = InitializeShader(device, hwnd, "Resource/Shader/texture.vs", "Resource/Shader/texture.ps");
    if (!result) return result;
    return result;
}

void TextShaderClass::Shutdown()
{
 	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader(); 
}

bool TextShaderClass::Render(ID3D11DeviceContext * deviceContext, 
                                                            int indexCount,
                                                            XMMATRIX worldMatrix,
                                                            XMMATRIX viewMatrix, 
                                                            XMMATRIX projectionMatrix,
                                                            ID3D11ShaderResourceView* texture)
{
    // Set the shader parameters that it will use for rendering.
    bool result = SetShaderParameters(deviceContext, 
                                                                        worldMatrix, 
                                                                        viewMatrix, 
                                                                        projectionMatrix,
                                                                        texture);
    if (!result) return false;
    // Now render the prepared buffers with the shader.
    RenderShader(deviceContext, indexCount);
    return true;
}

bool TextShaderClass::InitializeShader(ID3D11Device * device, HWND hwnd, const char * vsFileName, const char*psFileName)
{
    HRESULT result = JSNULL;
    ID3D10Blob* errorMessage;
    ID3D10Blob* vertexShaderBuffer;
    ID3D10Blob* pixelShaderBuffer;
    D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
    D3D11_BUFFER_DESC matrixBufferDesc;
    //Hold the description of the texture sampler
    D3D11_SAMPLER_DESC samplerDesc; 
    size_t cSize = strlen(vsFileName) + 1;
    wchar_t tmpShaderFile[128];
    mbstowcs(tmpShaderFile, vsFileName, cSize);
    // Initialize the pointers this function will use to null.
    errorMessage = 0;
    vertexShaderBuffer = 0;
    pixelShaderBuffer = 0;
    // Compile the vertex shader code.
    result = D3DCompileFromFile(tmpShaderFile,
                                                            NULL, 
                                                            NULL, 
                                                            "ColorVertexShader", 
                                                            "vs_5_0", 
                                                            D3D10_SHADER_ENABLE_STRICTNESS, 
                                                            0,
                                                            &vertexShaderBuffer, 
                                                            &errorMessage);
    if (FAILED(result))
    {
        // If the shader failed to compile it should have writen something to the error message.
        if (errorMessage)
        {
            OutputShaderErrorMessage(errorMessage, hwnd, tmpShaderFile);
        }
        // If there was    nothing in the error message then it simply could not find the shader file itself.
        else
        {
            MessageBox(hwnd, vsFileName, FailedToLoadShaderFile, MB_OK);
        }
        return false;
    }
    memset(tmpShaderFile, 0, 255);
    cSize = strlen(psFileName) + 1;
    mbstowcs(tmpShaderFile, psFileName, cSize);
    // Compile the pixel shader code.
    result = D3DCompileFromFile(tmpShaderFile,
                                                            NULL, 
                                                            NULL, 
                                                            "TexturePixelShader", 
                                                            "ps_5_0", 
                                                            D3D10_SHADER_ENABLE_STRICTNESS, 
                                                            0,
                                                            &pixelShaderBuffer, 
                                                            &errorMessage);
    if (FAILED(result))
    {
        // If the shader failed to compile it should have writen something to the error message.
        if (errorMessage)
        {
            OutputShaderErrorMessage(errorMessage, hwnd, tmpShaderFile);
        }
        // If there was nothing in the error message then it simply could not find the file itself.
        else
        {
            MessageBox(hwnd, psFileName, FailedToLoadShaderFile , MB_OK);
        }
        return false;
    }
    /*
    Once the vertex shader and pixel shader code has successfully compiled into buffers we then use those buffers to create the shader objects themselves. 
    We will use these pointers to interface with the vertex and pixel shader from this point forward.
    */
    // Create the vertex shader from the buffer.
    result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_VertexShader);
    if (FAILED(result)) return false;
    // Create the pixel shader from the buffer.
    result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_PixelShader);
    if (FAILED(result)) return false;
    
    // Create the vertex input layout description, a description of a single element for the input-assembler stage.
    // This setup needs to match the VertexType stucture in the ModelClass and in the shader.
    //The HLSL semantic associated with this element in a shader input-signature.
    //Allows the shader to determine the usage of this element of the layout
    polygonLayout[0].SemanticName = "POSITION";
    //The semantic index for the element. A semantic index modifies a semantic, with an integer index number.
    polygonLayout[0].SemanticIndex = 0;
    polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    //An integer value that identifies the input-assembler
    polygonLayout[0].InputSlot = 0;
    //Optional. Offset (in bytes) between each element. 
    polygonLayout[0].AlignedByteOffset = 0;
    //Identifies the input data class for a single input slot
    polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; //Input data is per-vertex data.
    //The number of instances to draw using the same per-instance data before advancing in the buffer by one element. 
    //This value must be 0 for an element that contains per-vertex data (the slot class is set to D3D11_INPUT_PER_VERTEX_DATA).
    polygonLayout[0].InstanceDataStepRate = 0;

    polygonLayout[1].SemanticName = "TEXCOORD";
    polygonLayout[1].SemanticIndex = 0;
    polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
    polygonLayout[1].InputSlot = 0;
    polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[1].InstanceDataStepRate = 0;
    // Create the vertex input layout.
    result = device->CreateInputLayout(polygonLayout, 
                                                                         sizeof(polygonLayout) / sizeof(polygonLayout[0]), //number of elements
                                                                         vertexShaderBuffer->GetBufferPointer(),
                                                                         vertexShaderBuffer->GetBufferSize(), 
                                                                         &m_Layout);
    if (FAILED(result)) return false;
    // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
    vertexShaderBuffer->Release();
    vertexShaderBuffer = 0;
    pixelShaderBuffer->Release();
    pixelShaderBuffer = 0;
    // Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
    //Identify how the buffer is expected to be read from and written to.
    //The buffer usage needs to be set to dynamic since we will be updating it each frame.
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
    //The bind flags indicate that this buffer will be a constant buffer.
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
    //The size of each element in the buffer structure (in bytes) when the buffer represents a structured buffer.
    matrixBufferDesc.StructureByteStride = 0;
    // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
    result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_MatrixBuffer);
    if (FAILED(result)) return false;
    // Create a texture sampler state description, texture sampling is the act of retrieving data from a texture.
    //Filtering method to use when sampling a texture
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; 
    //Method to use for resolving a u texture coordinate that is outside the 0 to 1 range
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    //Method to use for resolving a v texture coordinate that is outside the 0 to 1 range
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    //Method to use for resolving a w texture coordinate that is outside the 0 to 1 range
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    //Offset from the calculated mipmap level. For example, if Direct3D calculates that a texture should be sampled at mipmap level 3 and MipLODBias is 2, then the texture will be sampled at mipmap level 5.
    samplerDesc.MipLODBias = 0.0f;
    //Clamping value used if D3D11_FILTER_ANISOTROPIC or D3D11_FILTER_COMPARISON_ANISOTROPIC is specified in Filter. 
    samplerDesc.MaxAnisotropy = 1;
    //A function that compares sampled data against existing sampled data.
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    //Lower end of the mipmap range to clamp access to, where 0 is the largest and most detailed mipmap level and any level higher than that is less detailed.
    samplerDesc.MinLOD = 0;
    //Upper end of the mipmap range to clamp access to
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    // Create the texture sampler state.
    result = device->CreateSamplerState(&samplerDesc, &m_SampleState);
    if (FAILED(result)) return false;
    

    return true;
}
bool TextShaderClass::SetShaderParameters(ID3D11DeviceContext * deviceContext, 
                                                                                     XMMATRIX worldMatrix, 
                                                                                     XMMATRIX viewMatrix, 
                                                                                     XMMATRIX projectionMatrix,
                                                                                     ID3D11ShaderResourceView* texture)
{
    HRESULT result = JSNULL;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    MatrixBufferType* dataPtr;
    unsigned int bufferNumber;
    // Make sure to transpose matrices before sending them into the shader, this is a requirement for DirectX 11.
    // Transpose the matrices to prepare them for the shader.
    worldMatrix = XMMatrixTranspose(worldMatrix);
    viewMatrix = XMMatrixTranspose(viewMatrix);
    projectionMatrix = XMMatrixTranspose(projectionMatrix);

    // Lock the constant buffer so it can be written to.
    result = deviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result)) return false;
    // Get a pointer to the data in the constant buffer.
    dataPtr = (MatrixBufferType*)mappedResource.pData;
    // Copy the matrices into the constant buffer.
    dataPtr->world = worldMatrix;
    dataPtr->view = viewMatrix;
    dataPtr->projection = projectionMatrix;
    // Unlock the constant buffer.
    deviceContext->Unmap(m_MatrixBuffer, 0);
    // Set the position of the constant buffer in the vertex shader.
    bufferNumber = 0;
    // Finanly set the constant buffer in the vertex shader with the updated values.
    //Sets the constant buffers used by the vertex shader pipeline stage.
    deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);
    // Set shader texture resource in the pixel shader.
    deviceContext->PSSetShaderResources(0, 1, &texture);
    return true;
}

void TextShaderClass::RenderShader(ID3D11DeviceContext * deviceContext, int indexCount)
{
    // Set the vertex input layout.
    deviceContext->IASetInputLayout(m_Layout);
    // Set the vertex and pixel shaders that will be used to render this triangle.
    deviceContext->VSSetShader(m_VertexShader, NULL, 0);
    deviceContext->PSSetShader(m_PixelShader, NULL, 0);
    // Set the sampler state in the pixel shader.
    deviceContext->PSSetSamplers(0, 1, &m_SampleState);
    // Render the triangle.
    deviceContext->DrawIndexed(indexCount, 0, 0);
}

void TextShaderClass::ShutdownShader()
{
    // Release the matrix constant buffer.
    if (m_MatrixBuffer)
    {
        m_MatrixBuffer->Release();
        m_MatrixBuffer = 0;
    }
    // Release the layout.
    if (m_Layout)
    {
        m_Layout->Release();
        m_Layout = 0;
    }
    // Release the pixel shader.
    if (m_PixelShader)
    {
        m_PixelShader->Release();
        m_PixelShader = 0;
    }
    // Release the vertex shader.
    if (m_VertexShader)
    {
        m_VertexShader->Release();
        m_VertexShader = 0;
    }
    if (m_SampleState)
    {
        m_SampleState->Release();
        m_SampleState = 0;
    }
    

}

void TextShaderClass::OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, const wchar_t* shaderFilename)
{
    char* compileErrors;
    unsigned long long bufferSize, i;
    ofstream fout;
    // Get a pointer to the error message text buffer.
    compileErrors = (char*)(errorMessage->GetBufferPointer());
    // Get the length of the message.
    bufferSize = errorMessage->GetBufferSize();
    // Open a file to write the error message to.
    fout.open("shader-error.txt");
    // Write out the error message.
    for (i = 0; i < bufferSize; i++)
    {
        fout << compileErrors[i];
    }
    // Close the file.
    fout.close();
    // Release the error message.
    errorMessage->Release();
    errorMessage = 0;
    // Pop a message up on the screen to notify the user to check the text file for compile errors.
    MessageBox(hwnd, "Error compiling shader.    Check shader-error.txt for message.", (LPCSTR)shaderFilename, MB_OK);
}