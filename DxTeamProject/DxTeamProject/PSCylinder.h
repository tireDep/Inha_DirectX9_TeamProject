#pragma once
#include "Object.h"
class CPSCylinder :	public CObject
{
public:
	CPSCylinder();
	~CPSCylinder();
protected:
	float m_fRadius;
	float m_fHeight;
	D3DXVECTOR3	m_vCenter;
public:
	void Setup();
	void Setup(D3DXVECTOR3 center);
	void Update(float duration);
	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	void Render();

	void SetPickState(bool set);

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);
};