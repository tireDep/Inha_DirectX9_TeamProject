#include "stdafx.h"
#include "PSBox.h"

CPSBox::CPSBox()
	: m_fWidth(1.0f)
	, m_fHeight(1.0f)
	, m_fDepth(1.0f)
	, m_vPosition(0, 0, 0)
	, m_vVelocity(0, 0, 0)
	, m_vAcceleration(0, 0, 0)
	, m_vForceAccum(0, 0, 0)
{
	m_strName = string("Box") + to_string(m_nRefCount);
}

CPSBox::~CPSBox()
{
}

void CPSBox::Setup()
{
	D3DXCreateBox(g_pD3DDevice, m_fWidth, m_fHeight, m_fDepth, &m_pMesh, NULL);
}

void CPSBox::Setup(D3DXVECTOR3 center)
{
	Setup();
	m_vPosition = center;
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CPSBox::Update(float duration)
{

}

void CPSBox::Update(CRay ray, D3DXCOLOR & playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
{
	D3DXVECTOR3* pVertices;

	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	// later.. rotation add
	m_vMin.x += m_matWorld._41;			m_vMax.x += m_matWorld._41;
	m_vMin.y += m_matWorld._42;			m_vMax.y += m_matWorld._42;
	m_vMin.z += m_matWorld._43;			m_vMax.z += m_matWorld._43;
	
	if (D3DXBoxBoundProbe(&m_vMin, &m_vMax, &ray.GetOrigin(), &ray.GetDirection()) == true)
	{
		m_isPicked = true;
		m_outLineColor = playerColor;
	}
	else
	{
		m_isPicked = false;
	}
	vecVPos.push_back(m_vPosition);
	vecIsPick.push_back(m_isPicked);
	m_pMesh->UnlockVertexBuffer();
}

void CPSBox::Render()
{
	m_stMtl.Ambient = m_Color;
	m_stMtl.Diffuse = m_Color;
	m_stMtl.Specular = m_Color;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtl);

	if (m_isPicked && m_pShader)
	{
		OutlineRender();
	}
	else
	{
		m_pMesh->DrawSubset(0);
	}
}

D3DXVECTOR3 CPSBox::GetPosition(int i)
{
	return m_vPosition;
}

void CPSBox::SetPickState(bool set)
{
	m_isPicked = set;
}

string CPSBox::GetName()
{
	return m_strName;
}

void CPSBox::ReceiveEvent(ST_EVENT eventMsg)
{
	CObject::ReceiveEvent(eventMsg);
}