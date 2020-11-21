#include "stdafx.h"
#include "PSCylinder.h"

float m_fRadius;
float m_fHeight;
CPSCylinder::CPSCylinder()
	: m_fRadius(0.5f)
	, m_fHeight(1.0f)
	, m_vCenter(0, 0, 0)
{
	m_strName = string("Cylinder") + to_string(m_nRefCount);
}

CPSCylinder::~CPSCylinder()
{
}

void CPSCylinder::Setup()
{
	D3DXCreateCylinder(g_pD3DDevice, m_fRadius, m_fRadius, m_fHeight, 10, 10, &m_pMesh, NULL);
}

void CPSCylinder::Setup(D3DXVECTOR3 center)
{
	Setup();
	m_vCenter = center;
	D3DXMatrixTranslation(&m_matWorld, m_vCenter.x, m_vCenter.y, m_vCenter.z);
}

void CPSCylinder::Update(float duration)
{

}

void CPSCylinder::Update(CRay ray, D3DXCOLOR & playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
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
	vecVPos.push_back(m_vCenter);
	vecIsPick.push_back(m_isPicked);
	m_pMesh->UnlockVertexBuffer();
}

void CPSCylinder::Render()
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

void CPSCylinder::SetPickState(bool set)
{
	m_isPicked = set;
}

string CPSCylinder::GetName()
{
	return m_strName;
}

void CPSCylinder::ReceiveEvent(ST_EVENT eventMsg)
{
	CObject::ReceiveEvent(eventMsg);
}