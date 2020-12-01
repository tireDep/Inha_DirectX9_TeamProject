#include "stdafx.h"
#include "Contact.h"

void Contact::setBodyData(CRigidBody * one, CRigidBody * two, float friction, float restitution)
{
	body[0] = one;
	body[1] = two;
	Contact::friction = friction;
	Contact::restitution = restitution;
}

Contact::Contact()
{
}

Contact::~Contact()
{
}

void Contact::calculateInternals(float duration)
{
	if (!body[0]) swapBodies();
	assert(body[0]);

	calculateContactBasis();
	relativeContactPosition[0] = contactPoint - body[0]->getPosition();
	if (body[1]) 
	{
		relativeContactPosition[1] = contactPoint - body[1]->getPosition();
	}

	contactVelocity = calculateLocalVelocity(0, duration);
	if (body[1]) {
		contactVelocity -= calculateLocalVelocity(1, duration);
	}

	calculateDesiredDeltaVelocity(duration);
}

void Contact::swapBodies()
{
	contactNormal *= -1;
	CRigidBody *temp = body[0];
	body[0] = body[1];
	body[1] = temp;
}

void Contact::matchAwakeState()
{
	if (!body[1]) return;

	bool body0awake = body[0]->getAwake();
	bool body1awake = body[1]->getAwake();

	if (body0awake ^ body1awake)
	{
		if (body0awake)	body[1]->setAwake();
		else body[0]->setAwake();
	}
}

void Contact::calculateDesiredDeltaVelocity(float duration)
{
	const static float velocityLimit = (float)0.25f;

	float velocityFromAcc = 0;

	if (body[0]->getAwake())
	{
		D3DXVECTOR3 tmp = body[0]->getLastFrameAcceleration() * duration;
		velocityFromAcc = velocityFromAcc + D3DXVec3Dot(&tmp, &contactNormal);
	}
	if (body[1] && body[1]->getAwake())
	{
		D3DXVECTOR3 tmp = body[1]->getLastFrameAcceleration() * duration;
		velocityFromAcc = velocityFromAcc - D3DXVec3Dot(&tmp, &contactNormal);
	}

	float thisRestitution = restitution;
	if (fabsf(contactVelocity.x) < velocityLimit)
	{
		thisRestitution = (float)0.0f;
	}
	desiredDeltaVelocity = -contactVelocity.x - thisRestitution * (contactVelocity.x - velocityFromAcc);
}

D3DXVECTOR3 Contact::calculateLocalVelocity(unsigned bodyIndex, float duration)
{
	CRigidBody *thisbody = body[bodyIndex];

	D3DXVECTOR3 velocity;
	D3DXVec3Cross(&velocity, &thisbody->getRotation(), &relativeContactPosition[bodyIndex]);
	velocity += thisbody->getVelocity();
	
	// modify?
	D3DXVECTOR3 contactVelocity;
	D3DXVec3TransformCoord(&contactVelocity, &velocity, &contactToWorld);
	
	// modify?
	D3DXVECTOR3 accVelocity = thisbody->getLastFrameAcceleration() * duration;
	D3DXVec3TransformCoord(&accVelocity, &accVelocity, &contactToWorld);

	accVelocity.x = 0;

	contactVelocity += accVelocity;

	return contactVelocity;
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

		contactTangent[1].x =  contactNormal.y * contactTangent[0].x;
		contactTangent[1].y =  contactNormal.z * contactTangent[0].x - contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = -contactNormal.y * contactTangent[0].x;
	}
	else
	{
		const float s = (float)1.0f / sqrtf(contactNormal.z * contactNormal.z + contactNormal.y * contactNormal.y);

		contactTangent[0].x =  0;
		contactTangent[0].y = -contactNormal.z * s;
		contactTangent[0].z =  contactNormal.y * s;

		contactTangent[1].x =  contactNormal.y * contactTangent[0].z -	contactNormal.z * contactTangent[0].y;
		contactTangent[1].y = -contactNormal.x * contactTangent[0].z;
		contactTangent[1].z =  contactNormal.x * contactTangent[0].y;
	}


	// modify? Need to Identity...
	contactToWorld._11 = contactNormal.x;     contactToWorld._12 = contactNormal.y;     contactToWorld._13 = contactNormal.z;
	contactToWorld._21 = contactTangent[0].x; contactToWorld._22 = contactTangent[0].y; contactToWorld._23 = contactTangent[0].z;
	contactToWorld._31 = contactTangent[1].x; contactToWorld._32 = contactTangent[1].y; contactToWorld._33 = contactTangent[1].z;
}

void Contact::applyImpulse(const D3DXVECTOR3 & impulse, CRigidBody * body, D3DXVECTOR3 * velocityChange, D3DXVECTOR3 * rotationChange)
{
}

void Contact::applyVelocityChange(D3DXVECTOR3 velocityChange[2], D3DXVECTOR3 rotationChange[2])
{
	D3DXMATRIXA16 inverseInertiaTensor[2];
	body[0]->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
	if (body[1])
		body[1]->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

	D3DXVECTOR3 impulseContact;

	if (friction == (float)0.0f)
	{
		impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
	}
	else
	{
		impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
	}

	D3DXVECTOR3 impulse;
	D3DXVec3TransformCoord(&impulse, &impulseContact, &contactToWorld);

	D3DXVECTOR3 impulsiveTorque;
	D3DXVec3Cross(&impulsiveTorque, &relativeContactPosition[0], &impulse);
	
	D3DXVec3TransformCoord(&rotationChange[0], &impulsiveTorque, &inverseInertiaTensor[0]);
	velocityChange[0].x = velocityChange[0].y = velocityChange[0].z = 0.0f;
	velocityChange[0] += (impulse * body[0]->getInverseMass());

	body[0]->addVelocity(velocityChange[0]);
	body[0]->addRotation(rotationChange[0]);

	if (body[1])
	{
		D3DXVECTOR3 impulsiveTorque;
		D3DXVec3Cross(&impulsiveTorque, &impulse, &relativeContactPosition[1]);

		D3DXVec3TransformCoord(&rotationChange[1], &impulsiveTorque, &inverseInertiaTensor[1]);
		velocityChange[1].x = velocityChange[1].y = velocityChange[1].z = 0.0f;
		velocityChange[1] += (impulse * -body[1]->getInverseMass());

		body[1]->addVelocity(velocityChange[1]);
		body[1]->addRotation(rotationChange[1]);
	}
}

void Contact::applyPositionChange(D3DXVECTOR3 linearChange[2], D3DXVECTOR3 angularChange[2], float penetration)
{
	const float angularLimit = (float)0.2f;
	float angularMove[2];
	float linearMove[2];

	float totalInertia = 0;
	float linearInertia[2];
	float angularInertia[2];

	for (unsigned i = 0; i < 2; i++) if (body[i])
	{
		D3DXMATRIXA16 inverseInertiaTensor;
		body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

		D3DXVECTOR3 angularInertiaWorld;
		D3DXVec3Cross(&angularInertiaWorld, &relativeContactPosition[i], &contactNormal);
		D3DXVec3TransformCoord(&angularInertiaWorld, &angularInertiaWorld, &inverseInertiaTensor);
		D3DXVec3Cross(&angularInertiaWorld, &angularInertiaWorld, &relativeContactPosition[i]);
		angularInertia[i] = D3DXVec3Dot(&angularInertiaWorld, &angularInertiaWorld);

		linearInertia[i] = body[i]->getInverseMass();

		totalInertia += linearInertia[i] + angularInertia[i];
	}

	for (unsigned i = 0; i < 2; i++) if (body[i])
	{
		float sign = (i == 0) ? 1 : -1;
		angularMove[i] = sign * penetration * (angularInertia[i] / totalInertia);
		linearMove[i] =	sign * penetration * (linearInertia[i] / totalInertia);

		D3DXVECTOR3 projection = relativeContactPosition[i];
		projection += (contactNormal *	D3DXVec3Dot(&-relativeContactPosition[i],&contactNormal));

		float maxMagnitude = angularLimit * D3DXVec3Length(&projection);

		if (angularMove[i] < -maxMagnitude)
		{
			float totalMove = angularMove[i] + linearMove[i];
			angularMove[i] = -maxMagnitude;
			linearMove[i] = totalMove - angularMove[i];
		}
		else if (angularMove[i] > maxMagnitude)
		{
			float totalMove = angularMove[i] + linearMove[i];
			angularMove[i] = maxMagnitude;
			linearMove[i] = totalMove - angularMove[i];
		}

		if (angularMove[i] == 0)
		{
			angularChange[i].x = angularChange[i].y = angularChange[i].z = 0.0f;
		}
		else
		{
			D3DXVECTOR3 targetAngularDirection;
			D3DXVec3Cross(&targetAngularDirection, &relativeContactPosition[i], &contactNormal);

			D3DXMATRIXA16 inverseInertiaTensor;
			body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

			D3DXVec3TransformCoord(&angularChange[i], &targetAngularDirection, &inverseInertiaTensor);
			angularChange[i] *= angularMove[i] / angularInertia[i];
		}

		linearChange[i] = contactNormal * linearMove[i];

		D3DXVECTOR3 pos;
		body[i]->getPosition(&pos);
		pos += (contactNormal * linearMove[i]);
		body[i]->setPosition(pos);

		// modify?
		CTestAngleSet orientation = body[i]->getCurrentOrientation();
		orientation.setXAngle(orientation.getXAngle() + angularChange[i].x);
		orientation.setYAngle(orientation.getYAngle() + angularChange[i].y);
		orientation.setZAngle(orientation.getZAngle() + angularChange[i].z);
		body[i]->setCurrentOrientation(orientation);

		if (!body[i]->getAwake()) body[i]->calculateDerivedData();
	}
}

inline D3DXVECTOR3 Contact::calculateFrictionlessImpulse(D3DXMATRIXA16 * inverseInertiaTensor)
{
	D3DXVECTOR3 impulseContact;

	D3DXVECTOR3 deltaVelWorld;
	D3DXVec3Cross(&deltaVelWorld, &relativeContactPosition[0], &contactNormal);
	
	D3DXVec3TransformCoord(&deltaVelWorld, &deltaVelWorld, &inverseInertiaTensor[0]);
	D3DXVec3Cross(&deltaVelWorld, &deltaVelWorld, &relativeContactPosition[0]);

	float deltaVelocity = D3DXVec3Dot(&deltaVelWorld, &contactNormal);

	deltaVelocity += body[0]->getInverseMass();

	if (body[1])
	{
		D3DXVECTOR3 deltaVelWorld;
		D3DXVec3Cross(&deltaVelWorld, &relativeContactPosition[1], &contactNormal);

		D3DXVec3TransformCoord(&deltaVelWorld, &deltaVelWorld, &inverseInertiaTensor[1]);
		D3DXVec3Cross(&deltaVelWorld, &deltaVelWorld, &relativeContactPosition[1]);

		deltaVelocity = D3DXVec3Dot(&deltaVelWorld, &contactNormal);

		deltaVelocity += body[1]->getInverseMass();
	}

	impulseContact.x = desiredDeltaVelocity / deltaVelocity;
	impulseContact.y = 0;
	impulseContact.z = 0;
	return impulseContact;
}

D3DXVECTOR3 Contact::calculateFrictionImpulse(D3DXMATRIXA16 * inverseInertiaTensor)
{
	D3DXVECTOR3 impulseContact;
	float inverseMass = body[0]->getInverseMass();

	// modify?
	D3DXMATRIXA16 impulseToTorque;
	D3DXMatrixIdentity(&impulseToTorque);

	impulseToTorque._11 = 0;	impulseToTorque._22 = 0;	impulseToTorque._33 = 0;
	impulseToTorque._12 =  relativeContactPosition[0].z;
	impulseToTorque._13 = -relativeContactPosition[0].y;
	impulseToTorque._21 = -relativeContactPosition[0].z;
	impulseToTorque._23 =  relativeContactPosition[0].x;
	impulseToTorque._31 =  relativeContactPosition[0].y;
	impulseToTorque._32 = -relativeContactPosition[0].x;


	D3DXMATRIXA16 deltaVelWorld = impulseToTorque;
	deltaVelWorld *= inverseInertiaTensor[0];
	deltaVelWorld *= impulseToTorque;
	deltaVelWorld *= -1;

	if (body[1])
	{
		impulseToTorque._11 = 0;	impulseToTorque._22 = 0;	impulseToTorque._33 = 0;
		impulseToTorque._12 =  relativeContactPosition[1].z;
		impulseToTorque._13 = -relativeContactPosition[1].y;
		impulseToTorque._21 = -relativeContactPosition[1].z;
		impulseToTorque._23 =  relativeContactPosition[1].x;
		impulseToTorque._31 =  relativeContactPosition[1].y;
		impulseToTorque._32 = -relativeContactPosition[1].x;

		D3DXMATRIXA16 deltaVelWorld2 = impulseToTorque;
		deltaVelWorld2 *= inverseInertiaTensor[1];
		deltaVelWorld2 *= impulseToTorque;
		deltaVelWorld2 *= -1;

		deltaVelWorld += deltaVelWorld2;

		inverseMass += body[1]->getInverseMass();
	}

	// modify?
	D3DXMATRIXA16 deltaVelocity = contactToWorld;
	deltaVelocity *= deltaVelWorld;
	deltaVelocity *= contactToWorld;

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
			deltaVelocity._12 * friction*impulseContact.y +
			deltaVelocity._13 * friction*impulseContact.z;
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

void ContactResolver::resolveContacts(Contact * contactArray, unsigned numContacts, float duration)
{
	if (numContacts == 0) return;
	if (!isValid()) return;

	prepareContacts(contactArray, numContacts, duration);

	adjustPositions(contactArray, numContacts, duration);

	adjustVelocities(contactArray, numContacts, duration);
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
			for (unsigned b = 0; b < 2; b++) if (contactArray[i].body[b])
			{
				for (unsigned d = 0; d < 2; d++)
				{
					if (contactArray[i].body[b] == contactArray[index].body[d])
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
			for (unsigned b = 0; b < 2; b++) if (contacts[i].body[b])
			{
				for (unsigned d = 0; d < 2; d++)
				{
					if (contacts[i].body[b] == contacts[index].body[d])
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