#pragma once
#include "Object.h"
class CPSCylinder :	public CObject
{
public:
	CPSCylinder();
	~CPSCylinder();
protected:
	Synthesize(float, m_fRadius, Radius);
	Synthesize(float, m_fHeight, Height);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vVelocity, Velocity);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAcceleration, Acceleration);
	D3DXVECTOR3 m_vForceAccum;
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