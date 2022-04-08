#include "Shader.h"

namespace library
{
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Shader::Shader

      Summary:  Constructor

      Args:     PCWSTR pszFileName
                  Name of the file that contains the shader code
              PCSTR pszEntryPoint
                  Name of the shader entry point functino where shader
                  execution begins
              PCSTR pszShaderModel
                  Specifies the shader target or set of shader features
                  to compile against

      Modifies: [m_pszFileName, m_pszEntryPoint, m_pszShaderModel].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Shader::Shader definition (remove the comment)
    --------------------------------------------------------------------*/
    Shader::Shader(PCWSTR pszFileName, PCSTR pszEntryPoint, PCSTR pszShaderModel) :

        m_pszFileName(pszFileName),
        m_pszEntryPoint(pszEntryPoint),
        m_pszShaderModel(pszShaderModel)

    {};

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Shader::GetFileName

      Summary:  Returns the shader file name

      Returns:  PCWSTR
                  Shader file name
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Shader::GetFileName definition (remove the comment)
    --------------------------------------------------------------------*/
    PCWSTR Shader::GetFileName() const {
        return m_pszFileName;
    }
   

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Shader::compile

      Summary:  Compiles the given shader file

      Args:     ID3DBlob** ppOutBlob
                  Receives a pointer to the ID3DBlob interface that you
                  can use to access the compiled code

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Shader::compile definition (remove the comment)
    --------------------------------------------------------------------*/
    HRESULT Shader::compile(_Outptr_ ID3DBlob** ppOutBlob) {
        HRESULT hr = S_OK;

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows 
        // the shaders to be optimized and to run exactly the way they will run in 
        // the release configuration of this program.
        dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
        const D3D_SHADER_MACRO defines[] =
        {
            {"EXAMPLE_DEFINE"}, {"1"},
            {NULL}, {NULL}
        };

        ComPtr<ID3DBlob> pErrorBlob;
        hr = D3DCompileFromFile(
            m_pszFileName, 
            defines, 
            D3D_COMPILE_STANDARD_FILE_INCLUDE,
            m_pszEntryPoint, 
            m_pszShaderModel,
            dwShaderFlags, 
            0, 
            ppOutBlob, 
            pErrorBlob.GetAddressOf());

        if (FAILED(hr))
        {
            if (pErrorBlob != NULL)
                OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
            //if (pErrorBlob) pErrorBlob->Release();
            return hr;
        }
        //if (pErrorBlob) pErrorBlob->Release();

        return S_OK;

    }
}
