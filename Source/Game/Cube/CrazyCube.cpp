#include "Cube/CrazyCube.h"
#include <iostream>


CrazyCube::CrazyCube() :
    m_deltaTime(0.0f)
{}



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   YourCube::Update

  Summary:  Update the cube each frame

  Args:     FLOAT deltaTime
              Time difference of a frame
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

void CrazyCube::Update(_In_ FLOAT deltaTime)
{
    m_deltaTime += deltaTime;

    m_world = XMMatrixIdentity();

    Scale(0.7f, 0.7f * (-m_deltaTime), 0.7f);

    RotateZ(-m_deltaTime);
    Translate(XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f));
    RotateY(-m_deltaTime * 20.0f);

    //XMVECTOR xmVector(0.0f, 3.0f, 0.0f);
    //Scale(0.7f , 0.7f * (-m_deltaTime), 0.7f);


}

