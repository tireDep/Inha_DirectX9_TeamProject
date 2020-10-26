#pragma once
#include "BasicHeader.h"

class CCube
{
private:
	vector<ST_PC_VERTEX> m_vecVertex;
	float m_fRotY;
	D3DXVECTOR3 m_vDirection;
	D3DXVECTOR3	m_vPosition;
	D3DXMATRIXA16 m_matWorld;

public:
	CCube();
	~CCube();

	void SetUp();
	void Update();
	void Render();

	D3DXVECTOR3& GetPosition();
};

