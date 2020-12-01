#pragma once
#include "TestAngleSet.h"
class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();
protected:
	float		  inverseMass;
	D3DXMATRIXA16 inverseInertiaTensor;

	float linearDamping;
	float angularDamping;

	D3DXVECTOR3 position;
	CTestAngleSet orientation;

	D3DXVECTOR3 velocity;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 acceleration;
	D3DXVECTOR3 lastFrameAcceleration;

	D3DXMATRIXA16 inverseInertiaTensorWorld;

	D3DXMATRIXA16 transformMatrix;

	float motion;
	bool isAwake;
	bool canSleep;

	D3DXVECTOR3 forceAccum;
	D3DXVECTOR3 torqueAccum;

public:
	void setMass(const float mass);
	float getMass() const;
	void setInverseMass(const float inverseMass);
	float getInverseMass() const;
	bool hasFiniteMass() const;

	void setInertiaTensor(const D3DXMATRIXA16 & inertiaTensor);
	void getInertiaTensor(D3DXMATRIXA16 *inertiaTensor) const;
	D3DXMATRIXA16 getInertiaTensor() const;
	void setInverseInertiaTensor(const D3DXMATRIXA16 &inverseInertiaTensor);
	void getInverseInertiaTensor(D3DXMATRIXA16 *inverseInertiaTensor) const;
	D3DXMATRIXA16 getInverseInertiaTensor() const;

	void setDamping(const float linearDamping, const float angularDamping);
	void setLinearDamping(const float linearDamping);
	float getLinearDamping() const;
	void setAngularDamping(const float angularDamping);
	float getAngularDamping() const;

	void setPosition(const D3DXVECTOR3 &position);
	void setPosition(const float x, const float y, const float z);
	void getPosition(D3DXVECTOR3 *position) const;
	D3DXVECTOR3 getPosition() const;
	void setCurrentOrientation(CTestAngleSet newOrientation);
	CTestAngleSet getCurrentOrientation();

	void setVelocity(const D3DXVECTOR3 &velocity);
	void setVelocity(const float x, const float y, const float z);
	void getVelocity(D3DXVECTOR3 *velocity) const;
	D3DXVECTOR3 getVelocity() const;
	void addVelocity(const D3DXVECTOR3 &deltaVelocity);

	void setRotation(const D3DXVECTOR3 &rotation);
	void setRotation(const float x, const float y, const float z);
	void getRotation(D3DXVECTOR3 *rotation) const;
	D3DXVECTOR3 getRotation() const;
	void addRotation(const D3DXVECTOR3 &deltaRotation);

	void setAcceleration(const D3DXVECTOR3 &acceleration);
	void setAcceleration(const float x, const float y, const float z);
	void getAcceleration(D3DXVECTOR3 *acceleration) const;
	D3DXVECTOR3 getAcceleration() const;

	void getLastFrameAcceleration(D3DXVECTOR3 *linearAcceleration) const;
	D3DXVECTOR3 getLastFrameAcceleration() const;

	void getInertiaTensorWorld(D3DXMATRIXA16 *inertiaTensor) const;
	D3DXMATRIXA16 getInertiaTensorWorld() const;
	void getInverseInertiaTensorWorld(D3DXMATRIXA16 *inverseInertiaTensor) const;
	D3DXMATRIXA16 getInverseInertiaTensorWorld() const;

	void getTransform(D3DXMATRIXA16 *transform);
	D3DXMATRIXA16 getTransform() const;
	D3DXVECTOR3 getPointInLocalSpace(const D3DXVECTOR3 &point) const;
	D3DXVECTOR3 getPointInWorldSpace(const D3DXVECTOR3 &point) const;
	D3DXVECTOR3 getDirectionInLocalSpace(const D3DXVECTOR3 &direction) const;
	D3DXVECTOR3 getDirectionInWorldSpace(const D3DXVECTOR3 &direction) const;

	void clearAccumulators();
	void addForce(const D3DXVECTOR3 &force);
	void addForceAtPoint(const D3DXVECTOR3 &force, const D3DXVECTOR3 &point);
	void addForceAtBodyPoint(const D3DXVECTOR3 &force, const D3DXVECTOR3 &point);
	void addTorque(const D3DXVECTOR3 &torque);

	void setAwake(const bool awake = true);
	bool getAwake() const;
	void setCanSleep(const bool canSleep = true);
	bool getCanSleep() const;

	void calculateDerivedData();
	void integrate(float duration);
};