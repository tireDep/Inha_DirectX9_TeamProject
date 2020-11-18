#pragma once

class CParticleContact;

class CParticleContactResolver
{
public:
	~CParticleContactResolver();
protected:
	UINT m_unIterations;
	UINT m_unIterationsUsed;
public:
	CParticleContactResolver(UINT iterations);
	void setIterations(UINT iterations);
	void resolveContacts(CParticleContact* contactArray, UINT numContacts, float duration);
};