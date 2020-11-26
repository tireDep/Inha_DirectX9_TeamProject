#include "stdafx.h"
#include "Cylinder.h"

CCylinder::CCylinder()
{
	m_vRotate.y = 90;
	m_strObjName = string("Cylinder") + to_string(m_nRefCnt);
	m_ObjectType = ObjectType::eCylinder;
}

CCylinder::~CCylinder()
{
}

void CCylinder::Setup()
{
	CObject::Setup();
	D3DXCreateCylinder(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, 10, 10, &m_pMesh, NULL);
}

void CCylinder::Setup(ST_MapData setData)
{
	CObject::Setup(setData);
	Setup();
}

void CCylinder::Update()
{
}

void CCylinder::Render()
{
	CObject::Render();
}

void CCylinder::SetDiffScale(D3DXVECTOR3 set)
{
	if (m_vScale.x != set.x)
		m_vScale = D3DXVECTOR3(set.x, set.x, set.z);
	else if (m_vScale.y != set.y)
		m_vScale = D3DXVECTOR3(set.y, set.y, set.z);
	else if(m_vScale.z != set.z)
		m_vScale = D3DXVECTOR3(m_vScale.x, m_vScale.y, set.z);
}
