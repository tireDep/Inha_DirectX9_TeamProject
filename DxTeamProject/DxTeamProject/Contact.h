#pragma once
#include "RigidBody.h"

class ContactResolver;

class Contact
{
	friend class ContactResolver;
public:
	CRigidBody* body[2];
	float friction;
	float restitution;
	D3DXVECTOR3 contactPoint;
	D3DXVECTOR3 contactNormal;
	float penetration;
	void setBodyData(CRigidBody* one, CRigidBody* two, float friction, float restitution);
	Contact();
	~Contact();
protected:
	D3DXMATRIXA16 contactToWorld;
	D3DXVECTOR3 contactVelocity;
	float desiredDeltaVelocity;
	D3DXVECTOR3 relativeContactPosition[2];
	void calculateInternals(float duration);
	void swapBodies();
	void matchAwakeState();
	void calculateDesiredDeltaVelocity(float duration);
	D3DXVECTOR3 calculateLocalVelocity(unsigned bodyIndex, float duration);
	void calculateContactBasis();
	void applyImpulse(const D3DXVECTOR3 &impulse, CRigidBody *body, D3DXVECTOR3 *velocityChange, D3DXVECTOR3 *rotationChange);
	void applyVelocityChange(D3DXVECTOR3 velocityChange[2], D3DXVECTOR3 rotationChange[2]);
	void applyPositionChange(D3DXVECTOR3 linearChange[2], D3DXVECTOR3 angularChange[2], float penetration);
	D3DXVECTOR3 calculateFrictionlessImpulse(D3DXMATRIXA16 *inverseInertiaTensor);
	D3DXVECTOR3 calculateFrictionImpulse(D3DXMATRIXA16 *inverseInertiaTensor);
};
class ContactResolver
{
protected:
	unsigned velocityIterations;
	unsigned positionIterations;
	float velocityEpsilon;
	float positionEpsilon;
public:
	unsigned velocityIterationsUsed;
	unsigned positionIterationsUsed;
private:
	bool validSettings;
public:
	ContactResolver(unsigned iterations, float velocityEpsilon = (float)0.01,	float positionEpsilon = (float)0.01);
	ContactResolver(unsigned velocityIterations, unsigned positionIterations, float velocityEpsilon = (float)0.01, float positionEpsilon = (float)0.01);
	bool isValid();
	void setIterations(unsigned velocityIterations,	unsigned positionIterations);
	void setIterations(unsigned iterations);
	void setEpsilon(float velocityEpsilon, float positionEpsilon);
	void resolveContacts(Contact *contactArray,	unsigned numContacts, float duration);
protected:
	void prepareContacts(Contact *contactArray, unsigned numContacts, float duration);
	void adjustVelocities(Contact *contactArray, unsigned numContacts, float duration);
	void adjustPositions(Contact *contacts, unsigned numContacts, float duration);
};
class ContactGenerator
{
public:
	virtual unsigned addContact(Contact *contact, unsigned limit) const = 0;
};