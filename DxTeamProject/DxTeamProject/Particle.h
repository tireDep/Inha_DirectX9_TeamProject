#pragma once
class CParticle
{
public:
	CParticle();
	~CParticle();
protected:
	Synthesize(float, m_finverseMass, InverseMass);
	Synthesize(float, m_fdamping, Damping);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vVelocity, Velocity);
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAcceleration, Acceleration);
	D3DXVECTOR3	m_vForceAccum;
public:
	void  SetMass(const float mass);
	float GetMass() const;
	bool  hasFineteMass() const;
	void  SetPosition(const float x, const float y, const float z);
	void  SetVelocity(const float x, const float y, const float z);
	void  SetAcceleration(const float x, const float y, const float z);
	void  GetPosition(D3DXVECTOR3 *position) const;
	void  GetVelocity(D3DXVECTOR3 *velocity) const;
	void  GetAcceleration(D3DXVECTOR3 *acceleration) const;
	void  ClearAccumulator();

	void  AddForce(const D3DXVECTOR3 & force);
	void  Integrate(float duration);
};