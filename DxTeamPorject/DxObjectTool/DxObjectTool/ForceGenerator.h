#pragma once
class CForceGenerator
{
public:
	virtual void updateForce(RigidBody *body, float duration) = 0;
};