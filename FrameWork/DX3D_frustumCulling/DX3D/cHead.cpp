#include "stdafx.h"
#include "cHead.h"
#include "cCubeMan.h"

class cCubeMan;

cHead::cHead()
{
}


cHead::~cHead()
{
}

void cHead::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16	matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}
	
	m_vLocalPos.y = 0.5f; 
	
	// >> setTexture
	float width = 0.125f;

	int k = 0; 
	int c = 1;
	for (size_t i = 0; i < m_vecVertex.size(); i+=6)
	{
		if (i < 24)
		{
			m_vecVertex[i+0].t = D3DXVECTOR2(width * k, width * 2);
			m_vecVertex[i+1].t = D3DXVECTOR2(width * k, width);
			m_vecVertex[i+2].t = D3DXVECTOR2(width *(k+1), width);

			m_vecVertex[i+3].t = D3DXVECTOR2(width * k, width * 2);
			m_vecVertex[i+4].t = D3DXVECTOR2(width * (k + 1), width);
			m_vecVertex[i + 5].t = D3DXVECTOR2(width * (k + 1), width * 2);
		}
		else
		{
			m_vecVertex[i + 0].t = D3DXVECTOR2(width * c, width);
			m_vecVertex[i + 1].t = D3DXVECTOR2(width * c, 0);
			m_vecVertex[i + 2].t = D3DXVECTOR2(width * (c + 1), 0);

			m_vecVertex[i + 3].t = D3DXVECTOR2(width * c, width);
			m_vecVertex[i + 4].t = D3DXVECTOR2(width * (c + 1), 0);
			m_vecVertex[i + 5].t = D3DXVECTOR2(width * (c + 1), width);
			c++;
		}
		k++;
	}
	// << setTexture
}
