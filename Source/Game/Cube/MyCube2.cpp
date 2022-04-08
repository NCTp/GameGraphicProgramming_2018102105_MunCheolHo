#include "MyCube2.h"


void MyCube2::Update(_In_ FLOAT deltaTime) {

	m_world = XMMatrixRotationY(deltaTime);

};