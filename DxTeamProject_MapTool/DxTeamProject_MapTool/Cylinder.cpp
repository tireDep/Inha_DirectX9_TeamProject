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

void CCylinder::Update(CRay * ray)
{
	D3DXVECTOR3* pVertices;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	// later.. rotation add
	m_vMin += m_vTranslate;				m_vMax += m_vTranslate;

	if (D3DXBoxBoundProbe(&m_vMin, &m_vMax, &ray->GetOrigin(), &ray->GetDirection()) == true)
	{
		cout << "Picked" << endl;
	}
	else
	{
	}
	m_pMesh->UnlockVertexBuffer();
}

void CCylinder::Render()
{
	CObject::Render();
}
