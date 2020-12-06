#pragma once
#include "RigidBody.h"
#include "Contact.h"

class CWorld
{
public:
	typedef vector<CRigidBody*> RigidBodies;
private:
	bool calculateIterations;
	ContactResolver resolver;
	RigidBodies m_vecRigidBody;
	struct ContactGenRegistration
	{
		ContactGenerator *gen;
		ContactGenRegistration *next;
	};
	ContactGenRegistration *firstContactGen;
	Contact *contacts;
	unsigned maxContacts;
public:
	CWorld(unsigned maxContacts, unsigned iteration = 0);
	~CWorld();
	void startFrame();
	unsigned generateContacts();
	void RunPhysics(float duration);
};