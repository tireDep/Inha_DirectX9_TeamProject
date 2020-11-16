#include "stdafx.h"
#include "Sphere.h"

CSphere::CSphere() :
	m_fRadius(0.0f),
	m_vCenter(0,0,0)
{
	Setup();
}

CSphere::CSphere(float radius, int zPos)
{
	m_fRadius = radius;
	m_vCenter = D3DXVECTOR3(0, 0, -10 + 2 * zPos);

	Setup();
}

CSphere::~CSphere()
{
}

void CSphere::Setup()
{
	m_strName = string("Sphere") + to_string(m_nRefCount);
	m_isPicked = false;
	m_isClicked = false;

	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMeshSphere, NULL);
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
}

void CSphere::Update(CRay ray)
{
	{
		// D3DXSphereBoundProbe(&m_vCenter, m_fRadius, &ray.GetOrigin(), &ray.GetDirection());

		// CRay r = (*this);
		// D3DXMATRIXA16 matInvWorld;
		// D3DXMatrixIdentity(&matInvWorld);
		// matInvWorld._41 = -pSphere->vCenter.x;
		// matInvWorld._42 = -pSphere->vCenter.y;
		// matInvWorld._43 = -pSphere->vCenter.z;
		// 
		// D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &matInvWorld);
		// D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvWorld);
		// 
		// // ( Q.V)^2 -  V.V*(Q.Q - r*r) > 0 
		// float vv = D3DXVec3Dot(&r.m_vDir, &r.m_vDir);
		// float qv = D3DXVec3Dot(&r.m_vOrg, &r.m_vDir);
		// float qq = D3DXVec3Dot(&r.m_vOrg, &r.m_vOrg);
		// float rr = pSphere->fRadius * pSphere->fRadius;
		// return qv*qv - vv * (qq - rr) >= 0;
	}

	if (D3DXSphereBoundProbe(&m_vCenter, m_fRadius, &ray.GetOrigin(), &ray.GetDirection()) == true)
		m_isPicked = true;
	else
		m_isPicked = false;
}

void CSphere::Render()
{
	if (m_isClicked)
	{
		// >> todo 색상값 받아오기
		m_stMtlSphere.Ambient = BLUE;
		m_stMtlSphere.Diffuse = BLUE;
		m_stMtlSphere.Specular = BLUE;
	}
	else if (m_isPicked)
	{
		m_stMtlSphere.Ambient = RED;
		m_stMtlSphere.Diffuse = RED;
		m_stMtlSphere.Specular = RED;
	}
	else
	{
		m_stMtlSphere.Ambient = YELLOW;
		m_stMtlSphere.Diffuse = YELLOW;
		m_stMtlSphere.Specular = YELLOW;
	}


	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	D3DXMatrixIdentity(&matWorld);
	matWorld._41 = m_vCenter.x;
	matWorld._42 = m_vCenter.y;
	matWorld._43 = m_vCenter.z;
		
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);
	m_pMeshSphere->DrawSubset(0);
}

string CSphere::GetName()
{
	return m_strName;
}

void CSphere::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eInputEvent && eventMsg.message == WM_LBUTTONDOWN)
	{
		if (m_isPicked == true)
		{
			// todo : 색상값 받아와야 함
			m_isClicked = true;
		}
		else
			m_isClicked = false;
	}
}
