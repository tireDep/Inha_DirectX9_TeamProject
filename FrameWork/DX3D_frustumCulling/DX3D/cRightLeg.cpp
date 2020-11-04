#include "stdafx.h"
#include "cRightLeg.h"


cRightLeg::cRightLeg()
{
}


cRightLeg::~cRightLeg()
{
}

void cRightLeg::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16	matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0.1f, -0.3f, 0.0f);
	mat = matS * matT;
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}

	m_vLocalPos.y = -0.3f;

	float width = 0.125f;
	float hWidth = width * 0.5f;

	int k = 0;
	int c = 0;
	for (size_t i = 0; i < m_vecVertex.size(); i += 6)
	{
		if (i < 24)
		{
			m_vecVertex[i + 1].t = D3DXVECTOR2(hWidth * (k + 4), width * 6 + hWidth);
			m_vecVertex[i + 0].t = D3DXVECTOR2(hWidth * (k + 4), width * 8);
			m_vecVertex[i + 2].t = D3DXVECTOR2(hWidth * (k + 5), width * 6 + hWidth);

			m_vecVertex[i + 3].t = D3DXVECTOR2(hWidth * (k + 4), width * 8);
			m_vecVertex[i + 4].t = D3DXVECTOR2(hWidth * (k + 5), width * 6 + hWidth);
			m_vecVertex[i + 5].t = D3DXVECTOR2(hWidth * (k + 5), width * 8);

		}
		else
		{
			m_vecVertex[i + 0].t = D3DXVECTOR2(hWidth * (c + 5), width * 6 + hWidth);
			m_vecVertex[i + 1].t = D3DXVECTOR2(hWidth * (c + 5), width * 6);
			m_vecVertex[i + 2].t = D3DXVECTOR2(hWidth * (c + 6), width * 6);

			m_vecVertex[i + 3].t = D3DXVECTOR2(hWidth * (c + 5), width * 6 + hWidth);
			m_vecVertex[i + 4].t = D3DXVECTOR2(hWidth * (c + 5), width * 6);
			m_vecVertex[i + 5].t = D3DXVECTOR2(hWidth * (c + 6), width * 6 + hWidth);
			c++;
		}
		k++;
	}
}
