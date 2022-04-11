#include "Cube/OrbitCube.h"

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   OrbitCube::Update
  Summary:  Update the cube each frame
  Args:     FLOAT deltaTime
              Time difference of a frame
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

OrbitCube::OrbitCube() :
	m_deltaTime(0.0f) // deltaTime을 누적시키기 위한 멤버 변수.

{};

void OrbitCube::Update(_In_ FLOAT deltaTime)
{

    m_deltaTime += deltaTime;
    m_world = XMMatrixIdentity();

    Scale(0.3f, 0.3f, 0.3f);
    RotateZ(-m_deltaTime);
    Translate(XMVectorSet(-4.0f, 0.0f, 0.0f, 0.0f));
    RotateY(-m_deltaTime * 2.0f);



}

