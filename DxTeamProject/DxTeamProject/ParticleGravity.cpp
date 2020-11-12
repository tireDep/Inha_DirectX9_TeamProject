#include "stdafx.h"
#include "ParticleGravity.h"
#include "Particle.h"			// 이 전방선언 물어보기. 상속한 상위 cpp에 선언했는데? 헤더에 없어서 그런가

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