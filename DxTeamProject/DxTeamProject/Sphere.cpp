#include "stdafx.h"
#include "Sphere.h"

CSphere::CSphere() :
	m_fRadius(0.0f),
	m_vCenter(0,0,0),
	m_pMeshSphere(NULL)
{
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	Setup();
}

CSphere::CSphere(float radius, D3DXVECTOR3 center)
{
	m_fRadius = radius;
	m_vCenter = center;
	Setup();
}

CSphere::~CSphere()
{
	SafeRelease(m_pMeshSphere);
}

void CSphere::Setup()
{
	m_strName = string("Sphere") + to_string(m_nRefCount);
	m_isPicked = false;
	m_isClicked = false;

	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMeshSphere, NULL);
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient  = m_color;
	m_stMtlSphere.Diffuse  = m_color;
	m_stMtlSphere.Specular = m_color;
}

void CSphere::Update(CRay ray, D3DXCOLOR& playerColor)
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
	{
		m_isPicked = true;
		m_outLineColor = playerColor;
	}
	else
		m_isPicked = false;
}

void CSphere::Render()
{
	m_stMtlSphere.Ambient = m_color;
	m_stMtlSphere.Diffuse = m_color;
	m_stMtlSphere.Specular = m_color;

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld._41 = m_vCenter.x;
	matWorld._42 = m_vCenter.y;
	matWorld._43 = m_vCenter.z;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);

	SetShader(matWorld);

	if (m_isPicked)
	{
		m_pShader->SetVector("OutlineColor", &D3DXVECTOR4(m_outLineColor.r, m_outLineColor.g, m_outLineColor.b, 1));
		m_pShader->SetVector("SurfaceColor", &D3DXVECTOR4(D3DXVECTOR3(m_color), 1));

		UINT numPasses = 0;
		m_pShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				m_pShader->BeginPass(i); // 구체를 그린다

				if (i == 0)
					g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW); // 외곽선
				else
					g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// 내부

				m_pMeshSphere->DrawSubset(0);

				m_pShader->EndPass();
			}
		}
		m_pShader->End();
	}
	else
	{
		m_pMeshSphere->DrawSubset(0);
	}
}

string CSphere::GetName()
{
	return m_strName;
}

void CSphere::ReceiveEvent(ST_EVENT eventMsg)
{
	CObject::ReceiveEvent(eventMsg);
}