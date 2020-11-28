#include "stdafx.h"
#include "Box.h"

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
	Setup();
}

void CBox::Update()
{
}

void CBox::Update(CRay * ray)
{
#ifdef _DEBUG
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
#endif // _DEBUG
}

void CBox::Render()
{
	CObject::Render();
}
