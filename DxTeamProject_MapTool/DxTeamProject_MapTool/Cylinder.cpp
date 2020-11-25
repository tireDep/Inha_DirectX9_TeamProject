#include "stdafx.h"
#include "Cylinder.h"

CCylinder::CCylinder()
{
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
