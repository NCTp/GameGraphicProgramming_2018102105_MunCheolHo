#include "Cube/MyCube.h"

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   Cube::Cube

  Summary:  Constructor

  Args:     const std::filesystem::path& textureFilePath
              Path to the texture to use
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
MyCube::MyCube(_In_ const std::filesystem::path& textureFilePath)
    : BaseCube(textureFilePath)
{
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   Cube::Cube

  Summary:  Constructor

  Args:     const XMFLOAT4& outputColor
              Default color of the cube
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
MyCube::MyCube(_In_ const XMFLOAT4& outputColor)
    : BaseCube(outputColor)
{
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   Cube::Update

  Summary:  Updates the cube every frame

  Args:     FLOAT deltaTime
              Elapsed time

  Modifies: [m_world].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void MyCube::Update(_In_ FLOAT deltaTime)
{
    XMMATRIX mTranslate = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
    m_world = mTranslate;
    // Does nothing
}