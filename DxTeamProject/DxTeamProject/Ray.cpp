#include "stdafx.h"
#include "Ray.h"


CRay::CRay()
	: m_vOrg(0, 0, 0)
	, m_vDir(0, 0, 0)
	, m_eRaySpace(E_NONE)
{
}


CRay::~CRay()
{
}

CRay CRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9	vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16	matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	CRay r;
	r.m_vDir.x = ((2.0*nScreenX) / vp.Width - 1.0f) / matProj._11;
	r.m_vDir.y = ((-2.0*nScreenY) / vp.Height + 1.0f) / matProj._22;
	r.m_vDir.z = 1.0f;

	r.m_eRaySpace = E_VIEW;

	return r;
}

CRay CRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	CRay r = CRay::RayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);


	D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &matInvView);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvView);

	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);
	r.m_eRaySpace = E_WORLD;
	return r;
}

bool CRay::IntersectTri(IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2)
{
	float u, v, f;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vOrg, &m_vDir, &u, &v, &f);
	//vPickedPosition = m_vOrg + f*m_vDir;
	return b;
}
