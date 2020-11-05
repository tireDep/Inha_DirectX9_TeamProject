#pragma once
#include "stdafx.h"
#include "cLight.h"

class PointLight : public cLight
{
private:
	D3DLIGHT9 m_PointLight;

	vector<ST_PC_VERTEX>	m_vecVertex;

public:
	PointLight();
	~PointLight();

	void SetUp();
	void Update();
	void Render();
};