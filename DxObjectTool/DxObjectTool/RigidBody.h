#pragma once
class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();
protected:
	float			m_finverseMass;
	float			m_flinearDamping;
	float			m_fangularDamping;

	D3DXVECTOR3		m_vPosition;
	D3DXQUATERNION	m_qDirection;
	D3DXVECTOR3		m_vVelocity;
	D3DXVECTOR3		m_vRotation;
	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3		m_vforceAccum;
	D3DXVECTOR3		m_vtorqueAccum;

	bool			m_isAwake;
public:
	void addForce(const D3DXVECTOR3& force);
	void clearAccumulators();
	void intergrate(float duration);
	void addForceAtPoint(const D3DXVECTOR3& force, const D3DXVECTOR3& point);
	void addForceAtBodyPoint(const D3DXVECTOR3& force, const D3DXVECTOR3& point);
	D3DXVECTOR3 getPointInLocalSpace(const D3DXVECTOR3& point) const;

	bool hasFiniteMass() const;
	float getMass() const;
};


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
	void setInverseMass(const float inverseMass);
	float getInverseMass() const;
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