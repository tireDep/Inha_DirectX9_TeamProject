#pragma once

#include "RigidBody.h"

class CForceGenerator
{
public:
	virtual void updateForce(CRigidBody *body, float duration) = 0;
};