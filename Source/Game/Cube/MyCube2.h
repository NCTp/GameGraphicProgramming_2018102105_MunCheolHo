#pragma once


#include "BaseCube.h"

class MyCube2 : public BaseCube {
public:
	MyCube2() = default;

	virtual void Update(_In_ FLOAT deltaTime) override;
};
