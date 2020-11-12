#include "stdafx.h"
#include "ParticleGravity.h"
#include "Particle.h"			// �� ���漱�� �����. ����� ���� cpp�� �����ߴµ�? ����� ��� �׷���

CParticleGravity::CParticleGravity()
	: m_vGravity(0, -9.81f, 0)
{
}

CParticleGravity::CParticleGravity(const D3DXVECTOR3 & gravity)
	: m_vGravity(gravity)
{
}

void CParticleGravity::UpdateForce(CParticle * particle, float duration)
{
	if (!particle->hasFineteMass()) return;
	particle->AddForce(m_vGravity * particle->GetMass());
}