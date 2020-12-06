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
}

void CBox::Setup()
{
	D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);
	IObject::Setup_OBB_Box();
}

void CBox::Setup(ST_MapData setData)
{
	CObject::Setup(setData);
	D3DXCreateBox(g_pD3DDevice, fBasicScale, fBasicScale, fBasicScale, &m_pMesh, NULL);
	// >> �����Ʈ������ ũ��, ȸ��, ��ġ�� ����ǹǷ� �⺻������ ����
	IObject::Setup_OBB_Box();
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
