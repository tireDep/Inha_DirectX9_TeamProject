#include "stdafx.h"
#include "Sphere.h"

#define fBasicRadius 0.5f

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
	m_vScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	m_vTranslate = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	D3DXCreateSphere(g_pD3DDevice, m_vScale.x, 10, 10, &m_pMesh, NULL);
	IObject::Setup_OBB_Box();
}

void CSphere::Setup(ST_MapData setData)
{
	CObject::Setup(setData);
	D3DXCreateSphere(g_pD3DDevice, fBasicRadius, 10, 10, &m_pMesh, NULL);
	// >> 월드매트릭스로 크기, 회전, 위치가 변경되므로 기본값으로 세팅
	IObject::Setup_OBB_Box();
}

void CSphere::Update()
{
}

void CSphere::Update(CRay * ray)
{
	IObject::Update(ray);
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
