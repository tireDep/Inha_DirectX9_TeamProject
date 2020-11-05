#pragma once
#include "stdafx.h"

class cLight
{
public:
	cLight();
	virtual ~cLight();

	virtual void SetUp() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
