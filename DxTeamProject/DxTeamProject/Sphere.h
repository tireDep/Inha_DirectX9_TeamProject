#pragma once
#include "Object.h"

class CSphere : public CObject
{
private:
	float		m_fRadius;
	D3DXVECTOR3	m_vCenter;
	bool		m_isPicked;
	bool		m_isClicked;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlSphere;

public:
	CSphere();
	CSphere(float radius, int zPos);
	~CSphere();

	void Setup();
	void Update(CRay ray);
	void Render();

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};

