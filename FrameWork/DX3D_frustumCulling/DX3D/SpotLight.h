#pragma once
#include "stdafx.h"
#include "cLight.h"

class SpotLight : public cLight
{
private:
	D3DLIGHT9 m_SpotLight;

	vector<ST_PC_VERTEX>	m_vecVertex;

	D3DXVECTOR3 m_vRotation;

public:
	SpotLight();
	~SpotLight();

	void SetUp() override;
	void Update() override;
	void Render() override;
};
