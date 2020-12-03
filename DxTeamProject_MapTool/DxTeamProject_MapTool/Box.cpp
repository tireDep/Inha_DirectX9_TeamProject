#include "stdafx.h"
#include "Box.h"

#define fBasicScale 1.0f

CBox::CBox()
{
	m_strObjName = string("Box") + to_string(m_nRefCnt);
	m_ObjectType = ObjectType::eBox;
}

CBox::~CBox()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_pTexture);
}

void CBox::Setup()
{
	CObject::Setup();
	D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);
}

void CBox::Setup(ST_MapData setData)
{
	CObject::Setup(setData);
	D3DXCreateBox(g_pD3DDevice, fBasicScale, fBasicScale, fBasicScale, &m_pMesh, NULL);
	// >> 월드매트릭스로 크기, 회전, 위치가 변경되므로 기본값으로 세팅
}

void CBox::Update()
{
}

void CBox::Update(CRay * ray)
{
	IObject::Update(ray);
}

void CBox::Render()
{
	CObject::Render();
}
