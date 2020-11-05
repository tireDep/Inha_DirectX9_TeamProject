#pragma once
class CParticle
{
public:
	CParticle();
	~CParticle();
protected:
	D3DXVECTOR3		m_vPosition;
	D3DXVECTOR3		m_vVelocity;
	D3DXVECTOR3		m_vAcceleration;
	D3DXVECTOR3		m_vforceAccum;
	// 수치 연산 오차로 인해 증가한 에너지를 줄여주는 역할
	float			m_fDamping;			
	float			m_finverseMass;
public:
	void integrate(float duration);
	// 이 아래 부분 이해가 끝나면 대부분 Synthesize로 고치기?
	void setMass(const float mass);
	float getMass() const;
	void setInverseMass(const float inverseMass);
	float getInverseMass() const;
	bool hasFiniteMass() const;
	void setDamping(const float damping);
	float getDamping() const;
	void setPosition(const D3DXVECTOR3& position);
	void setPosition(const float x, const float y, const float z);
	void getPosition(D3DXVECTOR3 *position) const;
	D3DXVECTOR3 getPosition() const;
	void setVelocity(const D3DXVECTOR3& velocity);
	void setVelocity(const float x, const float y, const float z);
	void getVelocity(D3DXVECTOR3 *velocity) const;
	D3DXVECTOR3 getVelocity() const;
	void setAcceleration(const D3DXVECTOR3& acceleration);
	void setAcceleration(const float x, const float y, const float z);
	void getAcceleration(D3DXVECTOR3 *acceleration) const;
	D3DXVECTOR3 getAcceleration() const;
	void clearAccumulatior();
	void addForce(const D3DXVECTOR3& force);
};