#pragma once

class CObject;

class CRay
{
public:
	enum eRaySpace
	{
		E_NONE, E_VIEW, E_WORLD, E_LOCAL
	};
	CRay();
	~CRay();
	static CRay RayAtViewSpace(int nScreenX, int nScreenY);
	static CRay RayAtWorldSpace(int nScreenX, int nScreenY);
	bool	IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3& v2);
protected:
	Synthesize(D3DXVECTOR3, m_vOrg, Origin);
	Synthesize(D3DXVECTOR3, m_vDir, Direction);
	eRaySpace		m_eRaySpace;
};