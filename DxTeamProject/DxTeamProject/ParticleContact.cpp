#include "stdafx.h"
#include "ParticleContact.h"
#include "Particle.h"

CParticleContact::CParticleContact()
{
}

CParticleContact::~CParticleContact()
{
}

void CParticleContact::Resolve(float duration)
{
	resolveVelocity(duration);
	resolveInterpenetration(duration);
}

float CParticleContact::calculateSeparatingVelocity() const
{
	D3DXVECTOR3	relativeVelocity = particle[0]->GetVelocity();
	if (particle[1])
		relativeVelocity -= particle[1]->GetVelocity();

	return D3DXVec3Dot(&m_vContactNormal, &relativeVelocity);
}

void CParticleContact::resolveVelocity(float duration)
{
	float separatingVelocity = calculateSeparatingVelocity();
	if (separatingVelocity > 0)
		return;

	float newSeparaintVelocity = -separatingVelocity * m_fRestitution;
	float deltaVelocity = newSeparaintVelocity - separatingVelocity;

	float totalInverseMass = particle[0]->GetInverseMass();
	if (particle[1])
		totalInverseMass += particle[1]->GetInverseMass();
	if (totalInverseMass <= 0)
		return;

	float impulse = deltaVelocity / totalInverseMass;
	D3DXVECTOR3	impulsePerIMass = impulse * m_vContactNormal;

	particle[0]->SetVelocity(particle[0]->GetVelocity() + impulsePerIMass*particle[0]->GetInverseMass());
	if (particle[1])
		particle[1]->SetVelocity(particle[1]->GetVelocity() + impulsePerIMass * -particle[1]->GetInverseMass());
}

void CParticleContact::resolveInterpenetration(float duration)
{
	if (m_fpenetration <= 0)
		return;

	float totalInverseMass = particle[0]->GetInverseMass();
	if (particle[1])
		totalInverseMass += particle[1]->GetInverseMass();
	if (totalInverseMass <= 0)
		return;

	D3DXVECTOR3 movePerIMass = (m_fpenetration / totalInverseMass) * m_vContactNormal;

	m_vParticleMovement[0] = movePerIMass * particle[0]->GetInverseMass();
	if (particle[1])
		m_vParticleMovement[1] = movePerIMass * -particle[1]->GetInverseMass();
	else
		m_vParticleMovement[1].x = m_vParticleMovement[1].y = m_vParticleMovement[2].z = 0.0f;

	particle[0]->SetPosition(particle[0]->GetPosition() + m_vParticleMovement[0]);
	if (particle[1])
		particle[1]->SetPosition(particle[1]->GetPosition() + m_vParticleMovement[1]);
}