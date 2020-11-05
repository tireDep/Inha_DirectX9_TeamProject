#include "stdafx.h"
#include "Gravity.h"

CGravity::CGravity(const D3DXVECTOR3 & gravity)
	: m_vGravity(gravity)
{
}

void CGravity::updateForce(CRigidBody * body, float duration)
{
	//if (!body->hasFiniteMass()) return;
	//body->addForce(m_vGravity* body->getMass());
}