#include "Cube/RotatingCube.h"



RotatingCube::RotatingCube(const XMFLOAT4& outputColor)
    : BaseCube(outputColor)
{
}

void RotatingCube::Update(_In_ FLOAT deltaTime)
{
    // Rotate cube around the origin
    static FLOAT time = 0.0f;
    time += deltaTime;

    XMMATRIX mSpin = XMMatrixRotationZ(-time);
    XMMATRIX mOrbit = XMMatrixRotationY(-time * 2.0f);
    XMMATRIX mTranslate = XMMatrixTranslation(0.0f, 0.0f, -5.0f);
    XMMATRIX mScale = XMMatrixScaling(0.3f, 0.3f, 0.3f);

    m_world = mScale * mSpin * mTranslate * mOrbit;

}