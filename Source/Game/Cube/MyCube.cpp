#include "Cube/MyCube.h"

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   Cube::Cube

  Summary:  Constructor

  Args:     const std::filesystem::path& textureFilePath
              Path to the texture to use
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
MyCube::MyCube(const std::filesystem::path& textureFilePath) :

    BaseCube(textureFilePath)

{}
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   Cube::Update

  Summary:  Updates the cube every frame

  Args:     FLOAT deltaTime
              Elapsed time

  Modifies: [m_world].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void MyCube::Update(_In_ FLOAT deltaTime)
{
    static FLOAT s_totalTime = 0.0f;
    s_totalTime += deltaTime;

    XMMATRIX translate = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
    XMMATRIX scale = XMMatrixScaling(1.2f, 1.2f, 1.2f);

    m_world = XMMatrixTranslation(0.0f, XMScalarSin(s_totalTime), 0.0f) * XMMatrixRotationY(-s_totalTime * 1.2f) * translate * scale;

}