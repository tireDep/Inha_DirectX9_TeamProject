#pragma once

class CParticle;
class CParticleForceGenerator;

class CParticleForceRegistry
{
public:
	CParticleForceRegistry();
	~CParticleForceRegistry();
protected:
	struct ParticleForceRegistation
	{
		CParticle *particle;
		CParticleForceGenerator *fg;
	};
	typedef vector<ParticleForceRegistation> Registry;
	Registry m_stRegistrations;
public:
	void Add(CParticle* particle, CParticleForceGenerator *fg);
	void Remove(CParticle* particle, CParticleForceGenerator *fg);
	void Clear();
	void UpdateForces(float duration);
};