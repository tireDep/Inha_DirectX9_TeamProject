#pragma once
#include "Object.h"
class CPSphere : public CObject
{
public:
	CPSphere();
	~CPSphere();
protected:
	Synthesize(float, m_fRadius, Radius);
	Synthesize(float, m_finverseMass, InverseMass);
	Synthesize(float, m_fDamping, Damping);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vVelocity, Velocity);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAcceleration, Acceleration);
	D3DXVECTOR3 m_vForceDirection;
	D3DXVECTOR3	m_vForceAccum;
	float coefficientofRestitution;
	
public:
	void Setup();
	void Setup(D3DXVECTOR3 center);
	void Update(float duration);
	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	void Render();
	D3DXVECTOR3 GetPosition(int i);
	void SetPickState(bool set);

	virtual string GetName();
	virtual void ReceiveEvent(ST_EVENT eventMsg);

	// physics
	void SetMass(const float mass);
	float GetMass() const;
	bool hasFiniteMass() const;
	void SetPusingForce(D3DXVECTOR3 forcedirection);
	void AddForce(const D3DXVECTOR3 & force);
	void ClearAccumulator();
	void Integrate(float duration);
	void RunPhysics(float duration);
	bool hasIntersected(CPSphere & othersphere);
	void Collisionsphere(CPSphere & othersphere);
};