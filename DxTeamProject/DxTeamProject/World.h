#pragma once

class CRigidBody;

class CWorld
{
public:
	typedef vector<CRigidBody*> RigidBodies;
	CWorld();
	~CWorld();
protected:
	RigidBodies m_vecBodies;
public:
	void startFrame();
	void runPhysics(float duration);
	void integrate(float duration);
};