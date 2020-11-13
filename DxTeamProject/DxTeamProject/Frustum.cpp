#include "stdafx.h"
#include "Frustum.h"

CFrustum::CFrustum()
{
}

CFrustum::~CFrustum()
{
}

void CFrustum::Setup()
{
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 0)); 

	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 1));	
	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 1));

	m_vecPlane.resize(6);
	m_vecWorldVertex.resize(8);

	m_vLeftUpPos = D3DXVECTOR3(m_vecPlane[0].a, m_vecPlane[0].b, m_vecPlane[0].c);
	m_vRightDownPos = D3DXVECTOR3(m_vecPlane[5].a, m_vecPlane[5].b, m_vecPlane[5].c);
}

void CFrustum::Update()
{
	D3DXMATRIXA16 matView, matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	for (int i = 0; i < m_vecProjVertex.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i], &m_vecProjVertex[i], NULL, &matProj, &matView, NULL);
	}

	D3DXPlaneFromPoints(&m_vecPlane[0],
						&m_vecWorldVertex[0],
						&m_vecWorldVertex[1],
						&m_vecWorldVertex[2]);

	D3DXPlaneFromPoints(&m_vecPlane[1],
						&m_vecWorldVertex[6],
						&m_vecWorldVertex[5],
						&m_vecWorldVertex[4]);

	D3DXPlaneFromPoints(&m_vecPlane[2],
						&m_vecWorldVertex[1],
						&m_vecWorldVertex[5],
						&m_vecWorldVertex[6]);

	D3DXPlaneFromPoints(&m_vecPlane[3],
						&m_vecWorldVertex[0],
						&m_vecWorldVertex[3],
						&m_vecWorldVertex[7]);

	D3DXPlaneFromPoints(&m_vecPlane[4],
						&m_vecWorldVertex[1],
						&m_vecWorldVertex[0],
						&m_vecWorldVertex[4]);

	D3DXPlaneFromPoints(&m_vecPlane[5],
						&m_vecWorldVertex[2],
						&m_vecWorldVertex[6],
						&m_vecWorldVertex[7]);

	m_vLeftUpPos = D3DXVECTOR3(m_vecPlane[0].a, m_vecPlane[0].b, m_vecPlane[0].c);
	m_vRightDownPos = D3DXVECTOR3(m_vecPlane[5].a, m_vecPlane[5].b, m_vecPlane[5].c);
}

bool CFrustum::IsInFrustum(D3DXVECTOR3 pos)
{
	float fRadius = 0.0f;
	for each(D3DXPLANE p in m_vecPlane)
	{
		if (D3DXPlaneDotCoord(&p, &pos) > fRadius)
			return false;
	}

	return true;
}

bool CFrustum::IsUpdateCheck(CFrustum const & prevFrustum)
{	
	float range = 0.5f;
	float wheelRange = 0.5f;
	for (int i = 0; i < m_vecPlane.size(); i++)
	{
		if (abs(this->m_vecPlane[i].a - prevFrustum.m_vecPlane[i].a - 0.0001f) >= range)
			return false;
		
		if (abs(this->m_vecPlane[i].b - prevFrustum.m_vecPlane[i].b - 0.0001f) >= range)
			return false;
		// >> left&right
		
		if (abs(this->m_vecPlane[i].c - prevFrustum.m_vecPlane[i].c - 0.0001f) >= range)
			return false;
		// >> UpDown
		
		if (abs(this->m_vecPlane[i].d - prevFrustum.m_vecPlane[i].d - 0.0001f) >= wheelRange)
			return false;
		// >> Zoom
	}

	return true;
}
