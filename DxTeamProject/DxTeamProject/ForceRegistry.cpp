#include "stdafx.h"
#include "ForceRegistry.h"
#include "ForceGenerator.h"
#include "RigidBody.h"

void CForceRegistry::add(CRigidBody * body, CForceGenerator * fg)
{
	ForceRegistration registration;
	registration.body = body;
	registration.fg = fg;
	registrations.push_back(registration);
}

void CForceRegistry::remove(CRigidBody * body, CForceGenerator * fg)
{
	// 추후 구현. erase 이용?
}

void CForceRegistry::clear()
{
	// 추후 구현. clear 이용?
}

void CForceRegistry::updateForces(float duration)
{
	Registry::iterator it = registrations.begin();
	for (; it != registrations.end(); it++)
	{
		it->fg->updateForce(it->body, duration);
	}
}