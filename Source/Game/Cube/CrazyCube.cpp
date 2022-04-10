#include "Cube/CrazyCube.h"
#include <iostream>
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   YourCube::Update

  Summary:  Update the cube each frame

  Args:     FLOAT deltaTime
              Time difference of a frame
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

void CrazyCube::Update(_In_ FLOAT deltaTime)
{


    XMMATRIX Spin = XMMatrixRotationZ(-deltaTime);
    XMMATRIX Orbit = XMMatrixRotationY(-deltaTime * 20.0f);
    XMMATRIX Translate = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
    XMMATRIX Scale = XMMatrixScaling(0.7f * (-deltaTime), 0.7f, 0.7f);
    
    m_world = Scale * Spin * Translate * Orbit;

}

