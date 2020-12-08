#include "stdafx.h"
#include "World.h"

CWorld::CWorld(unsigned maxContacts, unsigned iteration)
	: resolver(NULL)
	, firstContactGen(NULL)
	, maxContacts(maxContacts)
{
	contacts = new Contact[maxContacts];
	calculateIterations = (iteration == 0);
}

CWorld::~CWorld()
{
	delete[] contacts;
}

void CWorld::startFrame()
{
	for (RigidBodies::iterator it = m_vecRigidBody.begin(); it != m_vecRigidBody.end(); it++)
	{
		(*it)->clearAccumulators();
		(*it)->calculateDerivedData();
	}
}

unsigned CWorld::generateContacts()
{
	unsigned limit = maxContacts;
	Contact *nextContact = contacts;

	ContactGenRegistration *reg = firstContactGen;
	while (reg)
	{
		unsigned used = reg->gen->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;

		if (limit <= 0) break;
		reg = reg->next;
	}
	return maxContacts - limit;
}

void CWorld::RunPhysics(float duration)
{
	for (RigidBodies::iterator it = m_vecRigidBody.begin(); it != m_vecRigidBody.end(); it++)
	{
		(*it)->integrate(duration);
	}
	unsigned usedContacts = generateContacts();
	if (calculateIterations)
		resolver.setIterations(usedContacts * 4);
	resolver.resolveContacts(contacts, usedContacts, duration);
}