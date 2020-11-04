#pragma once

enum eRaySpace { eNone, eView, eWorld, eLocal };

class CRay
{
private:

protected:
	D3DXVECTOR3 m_vOrigin;	// position
	D3DXVECTOR3 m_vDir;		// vector
	eRaySpace m_eRaySpace;

public:
	CRay();
	~CRay();

	static CRay RayAtViewSpace(int nScreenX, int nScreenY);
	static CRay RayAtWorldSpace(int nScreenX, int nScreenY);

	bool IntersectTri(IN D3DXVECTOR3& v0, IN D3DXVECTOR3& v1, IN D3DXVECTOR3& v2, OUT D3DXVECTOR3& vPickedPosition);

	bool IsPicked(ST_SPHERE* pSphere);
};

