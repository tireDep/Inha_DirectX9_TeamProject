#pragma once
#include "ForceGenerator.h"
class CGravity : public CForceGenerator
{
private:
	D3DXVECTOR3	m_vGravity;
public:
	CGravity(const D3DXVECTOR3 &gravity);
	virtual void updateForce(RigidBody *body, float duration);
};