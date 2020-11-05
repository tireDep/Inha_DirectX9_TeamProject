#pragma once

class CRigidBody;

class CForceGenerator
{
public:
	virtual void updateForce(CRigidBody *body, float duration) = 0;
};