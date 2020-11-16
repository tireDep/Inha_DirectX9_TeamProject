#pragma once
#include "Object.h"

class CCube : public CObject
{
private:
	vector<D3DXVECTOR3>  m_vecPos;
	LPD3DXMESH			m_pMeshCube;
	D3DMATERIAL9		m_stMtlCube;

public:
	CCube();
	~CCube();
	
	virtual void Setup();
	virtual void Update(CRay ray);
	virtual void Render();

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};

