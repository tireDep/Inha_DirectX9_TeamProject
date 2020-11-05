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

	D3DXVECTOR3		m_vAcceleration;
	D3DXVECTOR3		m_vlastFrameAcceleration;

	D3DXMATRIXA16	m_inverseInertiaTensorWorld;
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
	void calculateDerivedData();
};