#include "stdafx.h"
#include "Cube.h"

CCube::	CCube()
{
	Setup();
}

CCube::~CCube()
{
}

void CCube::Setup()
{
	m_strName = string("Cube") + to_string(m_nRefCount);
	m_isClicked = false;
	m_isPicked = false;
	
	D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMeshCube, NULL);

	ZeroMemory(&m_stMtlCube, sizeof(D3DMATERIAL9));
	m_stMtlCube.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlCube.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlCube.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	D3DXVECTOR3 v;
	// : down
	v = D3DXVECTOR3(-1, -1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(-1, 1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, -1);
	m_vecPos.push_back(v);

	v = D3DXVECTOR3(-1, -1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, -1, -1);
	m_vecPos.push_back(v);

	// :back
	v = D3DXVECTOR3(-1, -1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(-1, 1, 1);
	m_vecPos.push_back(v);

	v = D3DXVECTOR3(-1, -1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, -1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, 1);
	m_vecPos.push_back(v);

	// : left
	v = D3DXVECTOR3(-1, -1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(-1, 1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(-1, 1, -1);
	m_vecPos.push_back(v);

	v = D3DXVECTOR3(-1, -1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(-1, 1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(-1, -1, -1);
	m_vecPos.push_back(v);

	// : right 
	v = D3DXVECTOR3(1, -1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, 1);
	m_vecPos.push_back(v);

	v = D3DXVECTOR3(1, -1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, -1, 1);
	m_vecPos.push_back(v);

	// : top 
	v = D3DXVECTOR3(-1, 1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(-1, 1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, 1);
	m_vecPos.push_back(v);

	v = D3DXVECTOR3(-1, 1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, 1, -1);
	m_vecPos.push_back(v);

	// : bottom
	v = D3DXVECTOR3(-1, -1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(-1, -1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, -1, -1);
	m_vecPos.push_back(v);

	v = D3DXVECTOR3(-1, -1, 1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, -1, -1);
	m_vecPos.push_back(v);
	v = D3DXVECTOR3(1, -1, 1);
	m_vecPos.push_back(v);
}

void CCube::Update(CRay ray)
{
	for (int i = 0; i < m_vecPos.size(); i+=3)
	{
		if (ray.IntersectTri(m_vecPos[i + 0], m_vecPos[i + 1], m_vecPos[i + 2]) == true)
			m_isPicked = true;
		else
			m_isPicked = false;
	}
}

void CCube::Render()
{
	if (m_isClicked)
	{
		// >> todo 색상값 받아오기
		m_stMtlCube.Ambient = BLUE;
		m_stMtlCube.Diffuse = BLUE;
		m_stMtlCube.Specular = BLUE;
	}
	else if (m_isPicked)
	{
		m_stMtlCube.Ambient = RED;
		m_stMtlCube.Diffuse = RED;
		m_stMtlCube.Specular = RED;
	}
	else
	{
		m_stMtlCube.Ambient = YELLOW;
		m_stMtlCube.Diffuse = YELLOW;
		m_stMtlCube.Specular = YELLOW;
	}

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtlCube);
	g_pD3DDevice->SetTexture(0, 0);

	m_pMeshCube->DrawSubset(0);
}

string CCube::GetName()
{
	return m_strName;
}

void CCube::ReceiveEvent(ST_EVENT eventMsg)
{
	CObject::ReceiveEvent(eventMsg);
}
