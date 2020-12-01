#include "stdafx.h"
#include "RigidBody.h"

CRigidBody::CRigidBody()
{
}
CRigidBody::~CRigidBody()
{
}

static inline void _transformInertiaTensor(D3DXMATRIXA16& WorldTensor, const D3DXMATRIXA16& LocalTensor, const D3DXMATRIXA16& WorldMat)
{
	float t4  = WorldMat._11 * LocalTensor._11 + WorldMat._21 * LocalTensor._12 + WorldMat._31 * LocalTensor._13;
	float t9  = WorldMat._11 * LocalTensor._21 + WorldMat._21 * LocalTensor._22 + WorldMat._31 * LocalTensor._23;
	float t14 = WorldMat._11 * LocalTensor._31 + WorldMat._21 * LocalTensor._32 + WorldMat._31 * LocalTensor._33;
	float t28 = WorldMat._12 * LocalTensor._11 + WorldMat._22 * LocalTensor._12 + WorldMat._32 * LocalTensor._13;
	float t33 = WorldMat._12 * LocalTensor._21 + WorldMat._22 * LocalTensor._22 + WorldMat._32 * LocalTensor._23;
	float t38 = WorldMat._12 * LocalTensor._31 + WorldMat._22 * LocalTensor._32 + WorldMat._32 * LocalTensor._33;
	float t52 = WorldMat._13 * LocalTensor._11 + WorldMat._23 * LocalTensor._12 + WorldMat._33 * LocalTensor._13;
	float t57 = WorldMat._13 * LocalTensor._21 + WorldMat._23 * LocalTensor._22 + WorldMat._33 * LocalTensor._23;
	float t62 = WorldMat._13 * LocalTensor._31 + WorldMat._23 * LocalTensor._32 + WorldMat._33 * LocalTensor._33;

	WorldTensor._11 = t4  * WorldMat._11 +  t9  * WorldMat._21 + t14 * WorldMat._31;
	WorldTensor._21 = t4  * WorldMat._12 +	t9  * WorldMat._22 + t14 * WorldMat._32;
	WorldTensor._31 = t4  * WorldMat._13 +	t9  * WorldMat._23 + t14 * WorldMat._33;
	WorldTensor._12 = t28 * WorldMat._11 +	t33 * WorldMat._21 + t38 * WorldMat._31;
	WorldTensor._22 = t28 * WorldMat._12 +	t33 * WorldMat._22 + t38 * WorldMat._32;
	WorldTensor._32 = t28 * WorldMat._13 +	t33 * WorldMat._23 + t38 * WorldMat._33;
	WorldTensor._13 = t52 * WorldMat._11 +	t57 * WorldMat._21 + t62 * WorldMat._31;
	WorldTensor._23 = t52 * WorldMat._12 +	t57 * WorldMat._22 + t62 * WorldMat._32;
	WorldTensor._33 = t52 * WorldMat._13 +	t57 * WorldMat._23 + t62 * WorldMat._33;
}

void CRigidBody::setMass(const float mass)
{
	assert(mass != 0);
	inverseMass = ((float)1.0) / mass;
}

float CRigidBody::getMass() const
{
	if (inverseMass == 0) {
		return FLT_MAX;
	}
	else {
		return ((float)1.0) / inverseMass;
	}
}

void CRigidBody::setInverseMass(const float inverseMass)
{
	CRigidBody::inverseMass = inverseMass;
}

float CRigidBody::getInverseMass() const
{
	return inverseMass;
}

bool CRigidBody::hasFiniteMass() const
{
	return inverseMass >= 0.0f;
}

void CRigidBody::setInertiaTensor(const D3DXMATRIXA16 & inertiaTensor)
{
	D3DXMatrixInverse(&inverseInertiaTensor, NULL, &inertiaTensor);
}

void CRigidBody::getInertiaTensor(D3DXMATRIXA16 * inertiaTensor) const
{
	D3DXMatrixInverse(inertiaTensor, NULL, &inverseInertiaTensor);
}

D3DXMATRIXA16 CRigidBody::getInertiaTensor() const
{
	D3DXMATRIXA16 it;
	getInertiaTensor(&it);
	return it;
}

void CRigidBody::setInverseInertiaTensor(const D3DXMATRIXA16 & inverseInertiaTensor)
{
	CRigidBody::inverseInertiaTensor = inverseInertiaTensor;
}

void CRigidBody::getInverseInertiaTensor(D3DXMATRIXA16 * inverseInertiaTensor) const
{
	*inverseInertiaTensor = CRigidBody::inverseInertiaTensor;
}

D3DXMATRIXA16 CRigidBody::getInverseInertiaTensor() const
{
	return inverseInertiaTensor;
}

void CRigidBody::setDamping(const float linearDamping, const float angularDamping)
{
	CRigidBody::linearDamping = linearDamping;
	CRigidBody::angularDamping = angularDamping;
}

void CRigidBody::setLinearDamping(const float linearDamping)
{
	CRigidBody::linearDamping = linearDamping;
}

float CRigidBody::getLinearDamping() const
{
	return linearDamping;
}

void CRigidBody::setAngularDamping(const float angularDamping)
{
	CRigidBody::angularDamping = angularDamping;
}

float CRigidBody::getAngularDamping() const
{
	return angularDamping;
}

void CRigidBody::setPosition(const D3DXVECTOR3 & position)
{
	CRigidBody::position = position;
}

void CRigidBody::setPosition(const float x, const float y, const float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void CRigidBody::getPosition(D3DXVECTOR3 * position) const
{
	*position = CRigidBody::position;
}

D3DXVECTOR3 CRigidBody::getPosition() const
{
	return position;
}

void CRigidBody::setCurrentOrientation(CTestAngleSet newOrientation)
{
	orientation = newOrientation;
}

CTestAngleSet CRigidBody::getCurrentOrientation()
{
	return orientation;
}

void CRigidBody::setVelocity(const D3DXVECTOR3 & velocity)
{
	CRigidBody::velocity = velocity;
}

void CRigidBody::setVelocity(const float x, const float y, const float z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

void CRigidBody::getVelocity(D3DXVECTOR3 * velocity) const
{
	*velocity = CRigidBody::velocity;
}

D3DXVECTOR3 CRigidBody::getVelocity() const
{
	return velocity;
}

void CRigidBody::addVelocity(const D3DXVECTOR3 & deltaVelocity)
{
	velocity += deltaVelocity;
}

void CRigidBody::setRotation(const D3DXVECTOR3 & rotation)
{
	CRigidBody::rotation = rotation;
}

void CRigidBody::setRotation(const float x, const float y, const float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void CRigidBody::getRotation(D3DXVECTOR3 * rotation) const
{
	*rotation = CRigidBody::rotation;
}

D3DXVECTOR3 CRigidBody::getRotation() const
{
	return rotation;
}

void CRigidBody::addRotation(const D3DXVECTOR3 & deltaRotation)
{
	rotation += deltaRotation;
}

void CRigidBody::setAcceleration(const D3DXVECTOR3 & acceleration)
{
	CRigidBody::acceleration = acceleration;
}

void CRigidBody::setAcceleration(const float x, const float y, const float z)
{
	acceleration.x = x;
	acceleration.y = y;
	acceleration.z = z;
}

void CRigidBody::getAcceleration(D3DXVECTOR3 * acceleration) const
{
	*acceleration = CRigidBody::acceleration;
}

D3DXVECTOR3 CRigidBody::getAcceleration() const
{
	return acceleration;
}

void CRigidBody::getLastFrameAcceleration(D3DXVECTOR3 * linearAcceleration) const
{
	*linearAcceleration = lastFrameAcceleration;
}

D3DXVECTOR3 CRigidBody::getLastFrameAcceleration() const
{
	return lastFrameAcceleration;
}

void CRigidBody::getInertiaTensorWorld(D3DXMATRIXA16 * inertiaTensor) const
{
	D3DXMatrixInverse(inertiaTensor, NULL, &inverseInertiaTensorWorld);
}

D3DXMATRIXA16 CRigidBody::getInertiaTensorWorld() const
{
	D3DXMATRIXA16 it;
	getInertiaTensorWorld(&it);
	return it;
}

void CRigidBody::getInverseInertiaTensorWorld(D3DXMATRIXA16 * inverseInertiaTensor) const
{
	*inverseInertiaTensor = inverseInertiaTensorWorld;
}

D3DXMATRIXA16 CRigidBody::getInverseInertiaTensorWorld() const
{
	return inverseInertiaTensorWorld;
}

void CRigidBody::getTransform(D3DXMATRIXA16 * transform)
{
	transformMatrix = *transform;
}

D3DXMATRIXA16 CRigidBody::getTransform() const
{
	return transformMatrix;
}

D3DXVECTOR3 CRigidBody::getPointInLocalSpace(const D3DXVECTOR3 & point) const
{
	// modify?
	D3DXMATRIXA16 tmpMat;
	D3DXMatrixInverse(&tmpMat, NULL, &transformMatrix);

	D3DXVECTOR3 tmpVec;
	D3DXVec3TransformCoord(&tmpVec, &point, &tmpMat);

	return tmpVec;
}

D3DXVECTOR3 CRigidBody::getPointInWorldSpace(const D3DXVECTOR3 & point) const
{
	// modify?
	D3DXVECTOR3 tmpVec;
	D3DXVec3TransformCoord(&tmpVec, &point, &transformMatrix);

	return tmpVec;
}

D3DXVECTOR3 CRigidBody::getDirectionInLocalSpace(const D3DXVECTOR3 & direction) const
{
	// modify?
	D3DXMATRIXA16 tmpMat;
	D3DXMatrixInverse(&tmpMat, NULL, &transformMatrix);

	D3DXVECTOR3 tmpVec;
	D3DXVec3TransformNormal(&tmpVec, &direction, &tmpMat);

	return tmpVec;
}

D3DXVECTOR3 CRigidBody::getDirectionInWorldSpace(const D3DXVECTOR3 & direction) const
{
	// modify?
	D3DXVECTOR3 tmpVec;
	D3DXVec3TransformNormal(&tmpVec, &direction, &transformMatrix);

	return tmpVec;
}

void CRigidBody::clearAccumulators()
{
	forceAccum.x = forceAccum.y = forceAccum.z = 0.0f;
	torqueAccum.x = torqueAccum.y = torqueAccum.z = 0.0f;
}

void CRigidBody::addForce(const D3DXVECTOR3 & force)
{
	forceAccum += force;
	isAwake = true;
}

void CRigidBody::addForceAtPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
{
	D3DXVECTOR3 pt = point;
	pt -= position;

	forceAccum += force;
	D3DXVec3Cross(&pt, &pt, &force);
	torqueAccum += pt;

	isAwake = true;
}

void CRigidBody::addForceAtBodyPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
{
	D3DXVECTOR3 pt = getPointInWorldSpace(point);
	addForceAtPoint(force, pt);
}

void CRigidBody::addTorque(const D3DXVECTOR3 & torque)
{
	torqueAccum += torque;
	isAwake = true;
}

void CRigidBody::setAwake(const bool awake)
{
	// sleepEpsilon = 0.3f;
	if (awake)
	{
		isAwake = true;
		motion = 0.3 * 2.0f;
	}
	else
	{
		isAwake = false;
		velocity.x = velocity.y = velocity.z = 0.0f;
		rotation.x = rotation.y = rotation.z = 0.0f;
	}
}

bool CRigidBody::getAwake() const
{
	return isAwake;
}

void CRigidBody::setCanSleep(const bool canSleep)
{
	CRigidBody::canSleep = canSleep;
	if (!canSleep && !isAwake) setAwake();
}

bool CRigidBody::getCanSleep() const
{
	return canSleep;
}

void CRigidBody::calculateDerivedData()
{
	// modify?
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationYawPitchRoll(&matR, orientation.getYAngle(), orientation.getXAngle(), orientation.getZAngle());
	D3DXMatrixTranslation(&matT, position.x, position.y, position.z);
	transformMatrix = matR * matT;

	// add local rotation
	// modify?
	_transformInertiaTensor(inverseInertiaTensorWorld, inverseInertiaTensor, transformMatrix);
}

void CRigidBody::integrate(float duration)
{
	if (!isAwake) return;

	lastFrameAcceleration = acceleration;
	lastFrameAcceleration += (forceAccum * inverseMass);

	// modify?
	D3DXVECTOR3 angularAcceleration;
	D3DXVec3TransformCoord(&angularAcceleration, &torqueAccum, &inverseInertiaTensorWorld);

	velocity += (lastFrameAcceleration * duration);
	rotation += (angularAcceleration * duration);

	velocity *= powf(linearDamping, duration);
	rotation *= powf(angularDamping, duration);

	position += (velocity * duration);
	orientation.setXAngle(rotation.x * duration);
	orientation.setYAngle(rotation.y * duration);
	orientation.setZAngle(rotation.z * duration);

	calculateDerivedData();
	clearAccumulators();

	if (canSleep)
	{
		float currentMotion = D3DXVec3LengthSq(&velocity) + D3DXVec3LengthSq(&rotation);
		float bias = powf(0.5f, duration);
		motion = bias * motion + (1 - bias)*currentMotion;

		// sleepEpsilon = 0.3f;
		if (motion < 0.3f) setAwake(false);
		else if (motion > 10 * 0.3f) motion = 10 * 0.3f;
	}
}