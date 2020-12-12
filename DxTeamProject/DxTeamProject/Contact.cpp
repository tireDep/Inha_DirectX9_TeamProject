#include "stdafx.h"
#include "Contact.h"

void Contact::setObjectData(PObject * one, PObject * two, float friction, float restitution)
{
	object[0] = one;
	object[1] = two;
	Contact::friction = friction;
	Contact::restitution = restitution;
}

Contact::Contact()
{
	// need to modify
	D3DXMatrixIdentity(&contactToWorld);
}

Contact::~Contact()
{
}

void Contact::calculateInternals(float duration)
{
	if (!object[0]) swapObjects();
	assert(object[0]);

	calculateContactBasis();
	relativeContactPosition[0] = contactPoint - object[0]->GetPosition();
	if (object[1])
		relativeContactPosition[1] = contactPoint - object[1]->GetPosition();

	contactVelocity = calculateLocalVelocity(0, duration);
	if (object[1]) 
		contactVelocity -= calculateLocalVelocity(1, duration);

	calculateDesiredDeltaVelocity(duration);
}

void Contact::swapObjects()
{
	contactNormal *= -1;
	PObject *temp = object[0];
	object[0] = object[1];
	object[1] = temp;
}

inline void Contact::calculateContactBasis()
{
	D3DXVECTOR3 contactTangent[2];

	if (fabsf(contactNormal.x) > fabsf(contactNormal.y))
	{
		const float s = (float)1.0f / sqrtf(contactNormal.z * contactNormal.z + contactNormal.x * contactNormal.x);

		contactTangent[0].x = contactNormal.z * s;
		contactTangent[0].y = 0;
		contactTangent[0].z = contactNormal.x * s;

		contactTangent[1].x = contactNormal.y * contactTangent[0].x;
		contactTangent[1].y = contactNormal.z * contactTangent[0].x - contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = -contactNormal.y * contactTangent[0].x;
	}
	else
	{
		const float s = (float)1.0f / sqrtf(contactNormal.z * contactNormal.z + contactNormal.y * contactNormal.y);

		contactTangent[0].x = 0;
		contactTangent[0].y = -contactNormal.z * s;
		contactTangent[0].z = contactNormal.y * s;

		contactTangent[1].x = contactNormal.y * contactTangent[0].z - contactNormal.z * contactTangent[0].y;
		contactTangent[1].y = -contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = contactNormal.x * contactTangent[0].y;
	}

	// modify? Need to Identity...
	contactToWorld._11 = contactNormal.x;     contactToWorld._12 = contactNormal.y;     contactToWorld._13 = contactNormal.z;
	contactToWorld._21 = contactTangent[0].x; contactToWorld._22 = contactTangent[0].y; contactToWorld._23 = contactTangent[0].z;
	contactToWorld._31 = contactTangent[1].x; contactToWorld._32 = contactTangent[1].y; contactToWorld._33 = contactTangent[1].z;
}

D3DXVECTOR3 Contact::calculateLocalVelocity(unsigned bodyIndex, float duration)
{
	return D3DXVECTOR3(0, 0, 0);
	//PObject *thisbody = object[bodyIndex];

	//D3DXVECTOR3 velocity;
	//D3DXVec3Cross(&velocity, &thisbody->GetAngularVelocity(), &relativeContactPosition[bodyIndex]);
	//velocity += thisbody->GetLinearVelocity();

	//// modify? calculateContactBasis 77~79 check
	//D3DXVECTOR3 contactVelocity;
	//D3DXVec3TransformCoord(&contactVelocity, &velocity, &contactToWorld);

	//// modify? calculateContactBasis 77~79 check
	//D3DXVECTOR3 accVelocity = thisbody->GetLastFrameAcceleration() * duration;
	//D3DXVec3TransformCoord(&accVelocity, &accVelocity, &contactToWorld);

	//accVelocity.x = 0;

	//contactVelocity += accVelocity;

	//return contactVelocity;
}

void Contact::calculateDesiredDeltaVelocity(float duration)
{
	//const static float velocityLimit = (float)0.25f;

	//float velocityFromAcc = 0;

	//if (object[0]->GetAwake())
	//{
	//	D3DXVECTOR3 tmp = object[0]->GetLastFrameAcceleration() * duration;
	//	velocityFromAcc = velocityFromAcc + D3DXVec3Dot(&tmp, &contactNormal);
	//}
	//if (object[1] && object[1]->GetAwake())
	//{
	//	D3DXVECTOR3 tmp = object[1]->GetLastFrameAcceleration() * duration;
	//	velocityFromAcc = velocityFromAcc - D3DXVec3Dot(&tmp, &contactNormal);
	//}

	//float thisRestitution = restitution;
	//if (fabsf(contactVelocity.x) < velocityLimit)
	//{
	//	thisRestitution = (float)0.0f;
	//}
	//desiredDeltaVelocity = -contactVelocity.x - thisRestitution * (contactVelocity.x - velocityFromAcc);
}

void Contact::matchAwakeState()
{
	//if (!object[1]) return;

	//bool body0awake = object[0]->GetAwake();
	//bool body1awake = object[1]->GetAwake();

	//if (body0awake ^ body1awake)
	//{
	//	if (body0awake)	object[1]->SetAwake();
	//	else object[0]->SetAwake();
	//}
}

//void Contact::applyImpulse(const D3DXVECTOR3 & impulse, CRigidBody * body, D3DXVECTOR3 * velocityChange, D3DXVECTOR3 * rotationChange)
//{
//}

void Contact::applyVelocityChange(D3DXVECTOR3 velocityChange[2], D3DXVECTOR3 rotationChange[2])
{
	////D3DXVECTOR3 inverseRotationInertia[2];
	////inverseRotationInertia[0] = object[0]->GetinverseRotationInertia();
	////if (object[1])
	////	inverseRotationInertia[1] = object[1]->GetinverseRotationInertia();

	////D3DXVECTOR3 impulseContact;
	////impulseContact = calculateFrictionImpulse(inverseRotationInertia);

	////if (friction == (float)0.0f)
	////{
	////	impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
	////}
	////else
	////{
	////	impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
	////}

	//D3DXVECTOR3 impulse;
	//D3DXVec3TransformCoord(&impulse, &impulseContact, &contactToWorld);

	//D3DXVECTOR3 impulsiveTorque;
	//D3DXVec3Cross(&impulsiveTorque, &relativeContactPosition[0], &impulse);
	//
	//rotationChange[0].x = impulsiveTorque.x * inverseRotationInertia[0].x;
	//rotationChange[0].y = impulsiveTorque.y * inverseRotationInertia[0].y;
	//rotationChange[0].z = impulsiveTorque.z * inverseRotationInertia[0].z;
	//velocityChange[0].x = velocityChange[0].y = velocityChange[0].z = 0.0f;
	//velocityChange[0] += (impulse * object[0]->GetInverseMass());

	//object[0]->SetLinearVelocity(object[0]->GetLinearVelocity() + velocityChange[0]);
	//object[0]->SetAngularVelocity(object[0]->GetAngularVelocity() + rotationChange[0]);

	//if (object[1])
	//{
	//	D3DXVECTOR3 impulsiveTorque;
	//	D3DXVec3Cross(&impulsiveTorque, &impulse, &relativeContactPosition[1]);

	//	rotationChange[1].x = impulsiveTorque.x * inverseRotationInertia[1].x;
	//	rotationChange[1].y = impulsiveTorque.y * inverseRotationInertia[1].y;
	//	rotationChange[1].z = impulsiveTorque.z * inverseRotationInertia[1].z;
	//	velocityChange[1].x = velocityChange[1].y = velocityChange[1].z = 0.0f;
	//	velocityChange[1] += (impulse * -object[1]->GetInverseMass());

	//	object[1]->SetLinearVelocity(object[1]->GetLinearVelocity() + velocityChange[1]);
	//	object[1]->SetAngularVelocity(object[1]->GetAngularVelocity() + rotationChange[1]);
	//}
}

void Contact::applyPositionChange(D3DXVECTOR3 linearChange[2], D3DXVECTOR3 angularChange[2], float penetration)
{
	//const float angularLimit = (float)0.2f;
	//float angularMove[2];
	//float linearMove[2];

	//float totalInertia = 0;
	//float linearInertia[2];
	//float angularInertia[2];

	//for (unsigned i = 0; i < 2; i++) if (object[i])
	//{
	//	D3DXVECTOR3 inverseRotationInertia;
	//	inverseRotationInertia = object[i]->GetinverseRotationInertia();

	//	D3DXVECTOR3 angularInertiaWorld;
	//	D3DXVec3Cross(&angularInertiaWorld, &relativeContactPosition[i], &contactNormal);

	//	angularInertiaWorld.x *= inverseRotationInertia.x;
	//	angularInertiaWorld.y *= inverseRotationInertia.y;
	//	angularInertiaWorld.z *= inverseRotationInertia.z;

	//	D3DXVec3Cross(&angularInertiaWorld, &angularInertiaWorld, &relativeContactPosition[i]);
	//	angularInertia[i] = D3DXVec3Dot(&angularInertiaWorld, &angularInertiaWorld);

	//	linearInertia[i] = object[i]->GetInverseMass();

	//	totalInertia += linearInertia[i] + angularInertia[i];
	//}

	//for (unsigned i = 0; i < 2; i++) if (object[i])
	//{
	//	float sign = (i == 0) ? 1 : -1;
	//	angularMove[i] = sign * penetration * (angularInertia[i] / totalInertia);
	//	linearMove[i] =	sign * penetration * (linearInertia[i] / totalInertia);

	//	D3DXVECTOR3 projection = relativeContactPosition[i];
	//	D3DXVECTOR3 tmp = -relativeContactPosition[i];
	//	projection += (contactNormal *	D3DXVec3Dot(&tmp, &contactNormal));

	//	float maxMagnitude = angularLimit * D3DXVec3Length(&projection);

	//	if (angularMove[i] < -maxMagnitude)
	//	{
	//		float totalMove = angularMove[i] + linearMove[i];
	//		angularMove[i] = -maxMagnitude;
	//		linearMove[i] = totalMove - angularMove[i];
	//	}
	//	else if (angularMove[i] > maxMagnitude)
	//	{
	//		float totalMove = angularMove[i] + linearMove[i];
	//		angularMove[i] = maxMagnitude;
	//		linearMove[i] = totalMove - angularMove[i];
	//	}

	//	if (angularMove[i] == 0)
	//	{
	//		angularChange[i].x = angularChange[i].y = angularChange[i].z = 0.0f;
	//	}
	//	else
	//	{
	//		D3DXVECTOR3 targetAngularDirection;
	//		D3DXVec3Cross(&targetAngularDirection, &relativeContactPosition[i], &contactNormal);

	//		D3DXVECTOR3 inverseRotationInertia;

	//		inverseRotationInertia = object[i]->GetinverseRotationInertia();

	//		angularChange[i].x = targetAngularDirection.x * inverseRotationInertia.x;
	//		angularChange[i].y = targetAngularDirection.y * inverseRotationInertia.y;
	//		angularChange[i].z = targetAngularDirection.z * inverseRotationInertia.z;

	//		angularChange[i] *= (angularMove[i] / angularInertia[i]);
	//	}

	//	linearChange[i] = contactNormal * linearMove[i];

	//	D3DXVECTOR3 pos;
	//	pos = object[i]->GetPosition();
	//	pos += (contactNormal * linearMove[i]);
	//	object[i]->SetPosition(pos);

	//	// modify?
	//	CTestAngleSet orientation = object[i]->GetOrientation();
	//	orientation.setXAngle(orientation.getXAngle() + angularChange[i].x);
	//	orientation.setYAngle(orientation.getYAngle() + angularChange[i].y);
	//	orientation.setZAngle(orientation.getZAngle() + angularChange[i].z);
	//	object[i]->SetOrientation(orientation);

	//	//if (!object[i]->GetAwake()) object[i]->calculateDerivedData();
	//}
}

inline D3DXVECTOR3 Contact::calculateFrictionlessImpulse(D3DXMATRIXA16 * inverseInertiaTensor)
{
	return D3DXVECTOR3(0, 0, 0);
	//D3DXVECTOR3 impulseContact;

	//D3DXVECTOR3 deltaVelWorld;
	//D3DXVec3Cross(&deltaVelWorld, &relativeContactPosition[0], &contactNormal);
	//
	//D3DXVec3TransformCoord(&deltaVelWorld, &deltaVelWorld, &inverseInertiaTensor[0]);
	//D3DXVec3Cross(&deltaVelWorld, &deltaVelWorld, &relativeContactPosition[0]);

	//float deltaVelocity = D3DXVec3Dot(&deltaVelWorld, &contactNormal);

	//deltaVelocity += body[0]->getInverseMass();

	//if (body[1])
	//{
	//	D3DXVECTOR3 deltaVelWorld;
	//	D3DXVec3Cross(&deltaVelWorld, &relativeContactPosition[1], &contactNormal);

	//	D3DXVec3TransformCoord(&deltaVelWorld, &deltaVelWorld, &inverseInertiaTensor[1]);
	//	D3DXVec3Cross(&deltaVelWorld, &deltaVelWorld, &relativeContactPosition[1]);

	//	deltaVelocity = D3DXVec3Dot(&deltaVelWorld, &contactNormal);

	//	deltaVelocity += body[1]->getInverseMass();
	//}

	//impulseContact.x = desiredDeltaVelocity / deltaVelocity;
	//impulseContact.y = 0;
	//impulseContact.z = 0;
	//return impulseContact;
}

//D3DXVECTOR3 Contact::calculateFrictionImpulse(D3DXMATRIXA16 * inverseInertiaTensor)
//{
//	D3DXVECTOR3 impulseContact;
//	float inverseMass = object[0]->GetInverseMass();
//
//	// modify?
//	D3DXMATRIXA16 impulseToTorque;
//	D3DXMatrixIdentity(&impulseToTorque);
//
//	impulseToTorque._11 = 0;	impulseToTorque._22 = 0;	impulseToTorque._33 = 0;
//	impulseToTorque._12 =  relativeContactPosition[0].z;
//	impulseToTorque._13 = -relativeContactPosition[0].y;
//	impulseToTorque._21 = -relativeContactPosition[0].z;
//	impulseToTorque._23 =  relativeContactPosition[0].x;
//	impulseToTorque._31 =  relativeContactPosition[0].y;
//	impulseToTorque._32 = -relativeContactPosition[0].x;
//
//
//	D3DXMATRIXA16 deltaVelWorld = impulseToTorque;
//	deltaVelWorld *= inverseInertiaTensor[0];
//	deltaVelWorld *= impulseToTorque;
//	deltaVelWorld *= -1;
//
//	if (object[1])
//	{
//		impulseToTorque._11 = 0;	impulseToTorque._22 = 0;	impulseToTorque._33 = 0;
//		impulseToTorque._12 =  relativeContactPosition[1].z;
//		impulseToTorque._13 = -relativeContactPosition[1].y;
//		impulseToTorque._21 = -relativeContactPosition[1].z;
//		impulseToTorque._23 =  relativeContactPosition[1].x;
//		impulseToTorque._31 =  relativeContactPosition[1].y;
//		impulseToTorque._32 = -relativeContactPosition[1].x;
//
//		D3DXMATRIXA16 deltaVelWorld2 = impulseToTorque;
//		deltaVelWorld2 *= inverseInertiaTensor[1];
//		deltaVelWorld2 *= impulseToTorque;
//		deltaVelWorld2 *= -1;
//
//		deltaVelWorld += deltaVelWorld2;
//
//		inverseMass += object[1]->GetInverseMass();
//	}
//
//	// modify?
//	D3DXMATRIXA16 deltaVelocity = contactToWorld;
//	deltaVelocity *= deltaVelWorld;
//	deltaVelocity *= contactToWorld;
//
//	deltaVelocity._11 += inverseMass;
//	deltaVelocity._22 += inverseMass;
//	deltaVelocity._33 += inverseMass;
//
//	D3DXMATRIXA16 impulseMatrix;
//	D3DXMatrixInverse(&impulseMatrix, NULL, &deltaVelocity);
//
//	D3DXVECTOR3 velKill(desiredDeltaVelocity, -contactVelocity.y, -contactVelocity.z);
//
//	D3DXVec3TransformCoord(&impulseContact, &velKill, &impulseMatrix);
//
//	float planarImpulse = sqrtf(impulseContact.y * impulseContact.y + impulseContact.z * impulseContact.z);
//
//	if (planarImpulse > impulseContact.x * friction)
//	{
//		impulseContact.y /= planarImpulse;
//		impulseContact.z /= planarImpulse;
//
//		// modify?
//		impulseContact.x = deltaVelocity._11 +
//			deltaVelocity._12 * friction*impulseContact.y +
//			deltaVelocity._13 * friction*impulseContact.z;
//		impulseContact.x = desiredDeltaVelocity / impulseContact.x;
//		impulseContact.y *= friction * impulseContact.x;
//		impulseContact.z *= friction * impulseContact.x;
//	}
//	return impulseContact;
//}

inline D3DXVECTOR3 Contact::calculateFrictionImpulse(D3DXVECTOR3 * inverserRotationInertia)
{
	D3DXVECTOR3 impulseContact;
	float inverseMass = object[0]->GetInverseMass();

	D3DXMATRIXA16 impulseToTorque;
	D3DXMatrixIdentity(&impulseToTorque);

	impulseToTorque._11 = 0;	impulseToTorque._22 = 0;	impulseToTorque._33 = 0;
	impulseToTorque._12 = relativeContactPosition[0].z;
	impulseToTorque._13 = -relativeContactPosition[0].y;
	impulseToTorque._21 = -relativeContactPosition[0].z;
	impulseToTorque._23 = relativeContactPosition[0].x;
	impulseToTorque._31 = relativeContactPosition[0].y;
	impulseToTorque._32 = -relativeContactPosition[0].x;

	D3DXMATRIXA16 deltaVelWorld = impulseToTorque;
	D3DXMATRIXA16 tmpRI;
	D3DXMatrixIdentity(&tmpRI);
	tmpRI._11 = inverserRotationInertia[0].x;
	tmpRI._22 = inverserRotationInertia[0].y;
	tmpRI._33 = inverserRotationInertia[0].z;
	deltaVelWorld *= tmpRI;
	deltaVelWorld *= impulseToTorque;
	deltaVelWorld *= -1;

	if (object[1])
	{
		impulseToTorque._11 = 0;	impulseToTorque._22 = 0;	impulseToTorque._33 = 0;
		impulseToTorque._12 = relativeContactPosition[1].z;
		impulseToTorque._13 = -relativeContactPosition[1].y;
		impulseToTorque._21 = -relativeContactPosition[1].z;
		impulseToTorque._23 = relativeContactPosition[1].x;
		impulseToTorque._31 = relativeContactPosition[1].y;
		impulseToTorque._32 = -relativeContactPosition[1].x;

		D3DXMATRIXA16 deltaVelWorld2 = impulseToTorque;
		tmpRI._11 = inverserRotationInertia[1].x;
		tmpRI._22 = inverserRotationInertia[1].y;
		tmpRI._33 = inverserRotationInertia[1].z;
		deltaVelWorld2 *= tmpRI;
		deltaVelWorld2 *= impulseToTorque;
		deltaVelWorld2 *= -1;

		deltaVelWorld += deltaVelWorld2;

		inverseMass += object[1]->GetInverseMass();
	}

	// modify?
	D3DXMATRIXA16 deltaVelocity = contactToWorld;
	deltaVelocity *= deltaVelWorld;
	D3DXMATRIXA16 contactInverseWorld;
	D3DXMatrixInverse(&contactInverseWorld, NULL, &contactToWorld);
	deltaVelocity *= contactInverseWorld;

	deltaVelocity._11 += inverseMass;
	deltaVelocity._22 += inverseMass;
	deltaVelocity._33 += inverseMass;

	D3DXMATRIXA16 impulseMatrix;
	D3DXMatrixInverse(&impulseMatrix, NULL, &deltaVelocity);

	D3DXVECTOR3 velKill(desiredDeltaVelocity, -contactVelocity.y, -contactVelocity.z);

	D3DXVec3TransformCoord(&impulseContact, &velKill, &impulseMatrix);

	float planarImpulse = sqrtf(impulseContact.y * impulseContact.y + impulseContact.z * impulseContact.z);

	if (planarImpulse > impulseContact.x * friction)
	{
		impulseContact.y /= planarImpulse;
		impulseContact.z /= planarImpulse;

		// modify?
		impulseContact.x = deltaVelocity._11 +
			deltaVelocity._12 * friction * impulseContact.y +
			deltaVelocity._13 * friction * impulseContact.z;
		impulseContact.x = desiredDeltaVelocity / impulseContact.x;
		impulseContact.y *= friction * impulseContact.x;
		impulseContact.z *= friction * impulseContact.x;
	}
	return impulseContact;
}

ContactResolver::ContactResolver(unsigned iterations, float velocityEpsilon, float positionEpsilon)
{
	setIterations(iterations, iterations);
	setEpsilon(velocityEpsilon, positionEpsilon);
}

ContactResolver::ContactResolver(unsigned velocityIterations, unsigned positionIterations, float velocityEpsilon, float positionEpsilon)
{
	setIterations(velocityIterations);
	setEpsilon(velocityEpsilon, positionEpsilon);
}

void ContactResolver::resolveContacts(Contact * contactArray, unsigned numContacts, float duration)
{
	if (numContacts == 0) return;
	if (!isValid()) return;

	prepareContacts(contactArray, numContacts, duration);
	adjustPositions(contactArray, numContacts, duration);
	adjustVelocities(contactArray, numContacts, duration);
}

bool ContactResolver::isValid()
{
	return (velocityIterations > 0)  &&
		   (positionIterations > 0)  &&
		   (positionEpsilon >= 0.0f) &&
		   (positionEpsilon >= 0.0f);
}

void ContactResolver::setIterations(unsigned velocityIterations, unsigned positionIterations)
{
	ContactResolver::velocityIterations = velocityIterations;
	ContactResolver::positionIterations = positionIterations;
}

void ContactResolver::setIterations(unsigned iterations)
{
	setIterations(iterations, iterations);
}

void ContactResolver::setEpsilon(float velocityEpsilon, float positionEpsilon)
{
	ContactResolver::velocityEpsilon = velocityEpsilon;
	ContactResolver::positionEpsilon = positionEpsilon;
}

void ContactResolver::prepareContacts(Contact * contactArray, unsigned numContacts, float duration)
{
	Contact* lastContact = contactArray + numContacts;
	for (Contact* contact = contactArray; contact < lastContact; contact++)
	{
		contact->calculateInternals(duration);
	}
}

void ContactResolver::adjustVelocities(Contact * contactArray, unsigned numContacts, float duration)
{
	D3DXVECTOR3 velocityChange[2], rotationChange[2];
	D3DXVECTOR3 deltaVel;

	velocityIterationsUsed = 0;
	while (velocityIterationsUsed < velocityIterations)
	{
		float max = velocityEpsilon;
		unsigned index = numContacts;
		for (unsigned i = 0; i < numContacts; i++)
		{
			if (contactArray[i].desiredDeltaVelocity > max)
			{
				max = contactArray[i].desiredDeltaVelocity;
				index = i;
			}
		}
		if (index == numContacts) break;

		contactArray[index].matchAwakeState();
		contactArray[index].applyVelocityChange(velocityChange, rotationChange);

		for (unsigned i = 0; i < numContacts; i++)
		{
			for (unsigned b = 0; b < 2; b++) if (contactArray[i].object[b])
			{
				for (unsigned d = 0; d < 2; d++)
				{
					if (contactArray[i].object[b] == contactArray[index].object[d])
					{
						D3DXVECTOR3 tmp;
						D3DXVec3Cross(&tmp, &rotationChange[d], &contactArray[i].relativeContactPosition[b]);
						deltaVel = velocityChange[d] + tmp;

						// modify?
						D3DXVec3TransformCoord(&tmp, &deltaVel, &contactArray[i].contactToWorld);
						contactArray[i].contactVelocity += (tmp * (b ? -1 : 1));
						contactArray[i].calculateDesiredDeltaVelocity(duration);
					}
				}
			}
		}
		velocityIterationsUsed++;
	}
}

void ContactResolver::adjustPositions(Contact * contacts, unsigned numContacts, float duration)
{
	unsigned i, index;
	D3DXVECTOR3 linearChange[2], angularChange[2];
	float max;
	D3DXVECTOR3 deltaPosition;

	positionIterationsUsed = 0;
	while (positionIterationsUsed < positionIterations)
	{
		max = positionEpsilon;
		index = numContacts;
		for (i = 0; i<numContacts; i++)
		{
			if (contacts[i].penetration > max)
			{
				max = contacts[i].penetration;
				index = i;
			}
		}
		if (index == numContacts) break;

		contacts[index].matchAwakeState();
		contacts[index].applyPositionChange(linearChange, angularChange, max);

		for (i = 0; i < numContacts; i++)
		{
			// Check each body in the contact
			for (unsigned b = 0; b < 2; b++) if (contacts[i].object[b])
			{
				for (unsigned d = 0; d < 2; d++)
				{
					if (contacts[i].object[b] == contacts[index].object[d])
					{
						D3DXVECTOR3 tmp;
						D3DXVec3Cross(&tmp, &angularChange[d], &contacts[i].relativeContactPosition[b]);
						deltaPosition = linearChange[d] + tmp;

						contacts[i].penetration += (D3DXVec3Dot(&deltaPosition, &contacts[i].contactNormal)) * (b ? 1 : -1);							
					}
				}
			}
		}
		positionIterationsUsed++;
	}
}