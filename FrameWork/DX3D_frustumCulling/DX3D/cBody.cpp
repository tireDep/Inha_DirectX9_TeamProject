#include "stdafx.h"
#include "cBody.h"


cBody::cBody()
{
}


cBody::~cBody()
{
}

void cBody::Setup()
{
	cCubeNode::Setup(); 
	D3DXMATRIXA16	matS, matT, mat; 
	D3DXMatrixScaling(&matS, 0.4f, 0.6f, 0.2f); 
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f); 
	mat = matS * matT; 
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat); 
	}

	float width = 0.125f;
	float hWidth = width * 0.5f;

	int k = 0;
	float k2 = 0;
	int c = 0;
	for (size_t i = 0; i < m_vecVertex.size(); i += 6)
	{
		if (i < 24)
		{
			if (k % 2 == 0)
			{
				m_vecVertex[i + 1].t = D3DXVECTOR2(hWidth * (4 + k2), width * 2 + hWidth);
				m_vecVertex[i + 0].t = D3DXVECTOR2(hWidth * (4 + k2), width * 4);
				m_vecVertex[i + 2].t = D3DXVECTOR2(hWidth * (5 + k2), width * 2 + hWidth);
				
				m_vecVertex[i + 3].t = D3DXVECTOR2(hWidth * (4 + k2), width * 4);
				m_vecVertex[i + 4].t = D3DXVECTOR2(hWidth * (5 + k2), width * 2 + hWidth);
				m_vecVertex[i + 5].t = D3DXVECTOR2(hWidth * (5 + k2), width * 4);
			}
			else
			{
				m_vecVertex[i + 0].t = D3DXVECTOR2(hWidth * (5 + k2), width * 4);
				m_vecVertex[i + 1].t = D3DXVECTOR2(hWidth * (5 + k2), width * 2 + hWidth);
				m_vecVertex[i + 2].t = D3DXVECTOR2(hWidth * (7 + k2), width * 2 + hWidth);

				m_vecVertex[i + 3].t = D3DXVECTOR2(hWidth  * (5 + k2), width * 4);
				m_vecVertex[i + 4].t = D3DXVECTOR2(hWidth  * (7 + k2), width * 2 + hWidth);
				m_vecVertex[i + 5].t = D3DXVECTOR2(hWidth  * (7 + k2), width * 4);
				k2+=3;
			}
		}
		else
		{
			m_vecVertex[i + 0].t = D3DXVECTOR2(width * (2 + c) + hWidth, width * 2 + hWidth);
			m_vecVertex[i + 1].t = D3DXVECTOR2(width * (3 + c), width * 2);
			m_vecVertex[i + 2].t = D3DXVECTOR2(width * (3 + c) + hWidth, width * 2);

			m_vecVertex[i + 3].t = D3DXVECTOR2(width * (2 + c) + hWidth, width * 2 + hWidth);
			m_vecVertex[i + 4].t = D3DXVECTOR2(width * (3 + c) + hWidth, width * 2);
			m_vecVertex[i + 5].t = D3DXVECTOR2(width * (3 + c) + hWidth, width * 2 + hWidth);
			c++;
		}
		k++;
	}
}
