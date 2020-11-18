#pragma once

class CParticle;

class CParticleContact
{
public:
	CParticleContact();
	~CParticleContact();
public:
	CParticle* particle[2];
	float m_fRestitution;
	D3DXVECTOR3	m_vContactNormal;

	float m_fpenetration;
	D3DXVECTOR3 m_vParticleMovement[2];
protected:
	void Resolve(float duration);
	float calculateSeparatingVelocity() const;
private:
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);
	friend class CParticleContactResolver;
};