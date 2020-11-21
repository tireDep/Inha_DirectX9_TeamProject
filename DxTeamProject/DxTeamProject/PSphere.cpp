#include "stdafx.h"
#include "PSphere.h"

CPSphere::CPSphere()
	: m_fRadius(0.5f)
	, m_vCenter(0, 0, 0)
{
	m_strName = string("Sphere") + to_string(m_nRefCount);
}

CPSphere::~CPSphere()
{
}

void CPSphere::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMesh, NULL);
}

void CPSphere::Setup(D3DXVECTOR3 center)
{
	Setup();
	m_vCenter = center;
	D3DXMatrixTranslation(&m_matWorld, m_vCenter.x, m_vCenter.y, m_vCenter.z);
}

void CPSphere::Update(float duration)
{

}

void CPSphere::Update(CRay ray, D3DXCOLOR & playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos)
{
	if (D3DXSphereBoundProbe(&m_vCenter, m_fRadius, &ray.GetOrigin(), &ray.GetDirection()) == true)
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
}

void CPSphere::Render()
{
	m_stMtl.Ambient  = m_Color;
	m_stMtl.Diffuse  = m_Color;
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

void CPSphere::SetPickState(bool set)
{
	m_isPicked = set;
}

string CPSphere::GetName()
{
	return m_strName;
}

void CPSphere::ReceiveEvent(ST_EVENT eventMsg)
{
	CObject::ReceiveEvent(eventMsg);
}