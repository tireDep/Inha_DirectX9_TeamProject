#pragma once
#include "Object.h"

class CSphere : public CObject
{
private:
	float				m_fRadius;
	D3DXVECTOR3			m_vCenter;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlSphere;
public:
	CSphere();
	CSphere(float radius, D3DXVECTOR3 center);
	~CSphere();

	void Setup();
	void Update(CRay ray, D3DXCOLOR& playerColor);
	void Render();

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};