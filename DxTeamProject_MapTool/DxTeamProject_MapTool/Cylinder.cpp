#include "stdafx.h"
#include "Cylinder.h"

#define fBasicRadius 0.5f
#define fBasicHeight 1.0f

CCylinder::CCylinder()
{
	m_vRotate.x = 90;
	m_strObjName = string("Cylinder") + to_string(m_nRefCnt);
	m_ObjectType = ObjectType::eCylinder;
}

CCylinder::~CCylinder()
{
}

void CCylinder::Setup()
{
	m_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vTranslate = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	D3DXCreateCylinder(g_pD3DDevice, fBasicRadius, fBasicRadius, fBasicHeight, 10, 10, &m_pMesh, NULL);
	IObject::Setup_OBB_Box();
}

void CCylinder::Setup(ST_MapData setData)
{
	CObject::Setup(setData);
	D3DXCreateCylinder(g_pD3DDevice, fBasicRadius, fBasicRadius, fBasicHeight, 10, 10, &m_pMesh, NULL);
	// >> 월드매트릭스로 크기, 회전, 위치가 변경되므로 기본값으로 세팅
	IObject::Setup_OBB_Box();
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
