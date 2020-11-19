#pragma once
class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();
protected:
	// 1..
	float m_finverseMass;
	float m_flinearDamping;
	D3DXVECTOR3	m_vPosition;
	D3DXQUATERNION m_qOrientation;
	D3DXVECTOR3 m_vVelocity;
	D3DXVECTOR3 m_vRotation;
	D3DXMATRIXA16 m_matTransformmatrix;
	// 2..
	D3DXMATRIXA16 m_matinverseInertiaTensor;
	D3DXMATRIXA16 m_matinverseInertiaTensorWorld;
	// 3..
	D3DXVECTOR3 m_vforceAccum;
	D3DXVECTOR3 m_vtorqueAccum;
	bool m_isAwake;


	//
	float m_fmotion;
	bool m_canSleep;
	D3DXVECTOR3 m_vAcceleration;
	D3DXVECTOR3 m_lastFrameAcceleration;
public:
	// 1..
	void calculateDeriveDate();
	void calculateTransformMatrix();
	// 2..
	void calculateTransformInertiaTensor();
	// 3..
	void addForce(const D3DXVECTOR3& force);
	void clearAccumulators();
	void integrate(float duration);
	void addForceAtPoint(const D3DXVECTOR3& force, const D3DXVECTOR3& point);
	void addForceAtBodyPoint(const D3DXVECTOR3& force, const D3DXVECTOR3& point);

	//
	void setMass(const float mass);
	float getMass() const;
	void setInverseMass(const float inverseMass);
	float getInverseMass() const;
	bool hasFiniteMass() const;
	void setDamping(const float linearDamping, const float angularDamping);
	void setLinearDamping(const float linearDamping);
	float getLinearDamping() const;
	void setAngularDamping(const float angularDamping);
	float getAngularDamping() const;
	void setPosition(const D3DXVECTOR3 & position);
	void setPosition(const float x, const float y, const float z);
	void getPosition(D3DXVECTOR3* position) const;
	D3DXVECTOR3 getPosition() const;
	void setVelocity(const D3DXVECTOR3& velocity);
	void setVelocity(const float x, const float y, const float z);
	void getVelocity(D3DXVECTOR3* velocity) const;
	D3DXVECTOR3 getVelocity() const;
	void addVelocity(const D3DXVECTOR3 & deltaVelocity);
	void setRotation(const D3DXVECTOR3 & rotation);
	void setRotation(const float x, const float y, const float z);
	void getRotation(D3DXVECTOR3 * rotation) const;
	D3DXVECTOR3 getRotation() const;
	void addRotation(const D3DXVECTOR3 & deltaRotation);
	bool getAwake() const { return m_isAwake; }
	void setAwake(const bool awake = true);
	bool getCanSleep() const { return m_canSleep; }
	void setCanSleep(const bool canSleep = true);
	void getLastFrameAcceleration(D3DXVECTOR3 * linearAcceleration) const;
	D3DXVECTOR3 getLastFrameAcceleration() const;
	void addTorque(const D3DXVECTOR3& torque);
	void setAcceleration(const D3DXVECTOR3& acceleration);
	void setAcceleration(const float x, const float y, const float z);
	void getAcceleration(D3DXVECTOR3* acceleration) const;
	D3DXVECTOR3 getAcceleration() const;
};