#include "stdafx.h"
#include "Ray.h"

CRay::CRay() : 
	m_vOrigin(0, 0, 0),
	m_vDir(0, 0, 0),
	m_eRaySpace(eNone)
{
}


CRay::~CRay()
{
}

CRay CRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);	// viewPort

	D3DXMATRIXA16 matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);	// projection

	CRay r;
	r.m_vDir.x = ((2.0f * nScreenX) / vp.Width - 1.0f) / matProj._11;
	r.m_vDir.y = ((-2.0f * nScreenY) / vp.Height + 1.0f) / matProj._22;
	r.m_vDir.z = 1.0f;

	r.m_eRaySpace = eView;
	// >> 공식 적용

	return r;
}

CRay CRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	CRay r = CRay::RayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);	// view
	D3DXMatrixInverse(&matInvView, 0, &matView);	// 역행렬

	D3DXVec3TransformCoord(&r.m_vOrigin, &r.m_vOrigin, &matInvView);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvView);

	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);	// 단위 통일

	r.m_eRaySpace = eWorld;

	return r;
}

bool CRay::IntersectTri(IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2, OUT D3DXVECTOR3 & vPickedPosition)
{
	// >> 바닥과의 충돌 판정
	float u, v, dist;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vOrigin, &m_vDir, &u, &v, &dist);
	vPickedPosition = m_vOrigin + m_vDir * dist;

	return b;
}

bool CRay::IsPicked(ST_SPHERE * pSphere)
{
	// >> 오브젝트 충돌 판정_1
	// return D3DXSphereBoundProbe(&pSphere->vCenter, pSphere->fRadius, &m_vOrigin, &m_vDir);

	// >> 오브젝트 충돌 판정_2
	CRay r = (*this);
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pSphere->vCenter.x;
	matInvWorld._42 = -pSphere->vCenter.y;
	matInvWorld._43 = -pSphere->vCenter.z;

	D3DXVec3TransformCoord(&r.m_vOrigin, &r.m_vOrigin, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvWorld);

	// ( Q.V )^2 - V.V * ( Q.Q - r*r ) > 0

	float vv = D3DXVec3Dot(&r.m_vDir, &r.m_vDir);
	float qv = D3DXVec3Dot(&r.m_vOrigin, &r.m_vDir);
	float qq = D3DXVec3Dot(&r.m_vOrigin, &r.m_vOrigin);
	float rr = pSphere->fRadius * pSphere->fRadius;

	return qv * qv - vv * (qq - rr) >= 0;
}
