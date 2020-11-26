#include "stdafx.h"
#include "Sphere.h"

CSphere::CSphere()
{
	m_strObjName = string("Sphere") + to_string(m_nRefCnt);

	m_ObjectType = ObjectType::eSphere;
}

CSphere::~CSphere()
{
}

void CSphere::Setup()
{
	CObject::Setup();
	D3DXCreateSphere(g_pD3DDevice, m_vScale.x, 10, 10, &m_pMesh, NULL);
}

void CSphere::Setup(ST_MapData setData)
{
	CObject::Setup(setData);
	Setup();
}

void CSphere::Update()
{
}

void CSphere::Render()
{
	CObject::Render();
}

void CSphere::SetDiffScale(D3DXVECTOR3 set)
{
	if(set.x != m_vScale.x)
		m_vScale = D3DXVECTOR3(set.x, set.x, set.x);
	else if (set.y != m_vScale.y)
		m_vScale = D3DXVECTOR3(set.y, set.y, set.y);
	else if (set.z != m_vScale.z)
		m_vScale = D3DXVECTOR3(set.z, set.z, set.z);
}
