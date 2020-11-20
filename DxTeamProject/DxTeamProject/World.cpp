#include "stdafx.h"
#include "World.h"
#include "RigidBody.h"

CWorld::CWorld()
{
}

CWorld::~CWorld()
{
}

void CWorld::startFrame()
{
	for (RigidBodies::iterator b = m_vecBodies.begin(); b != m_vecBodies.end(); b++)
	{
		(*b)->clearAccumulators();
		(*b)->calculateDeriveDate();
	}
}

void CWorld::integrate(float duration)
{
	for (RigidBodies::iterator b = m_vecBodies.begin(); b != m_vecBodies.end(); b++)
	{
		(*b)->integrate(duration);
	}
}

void CWorld::runPhysics(float duration)
{
}