#pragma once

class CParticle;
class CParticleForceGenerator;

class CParticleForceRegistry
{
protected:
	struct ParticleForceRegistration
	{
		CParticle *particle;
		CParticleForceGenerator *fg;
	};
	typedef vector<ParticleForceRegistration> Registry;
	Registry	m_vRegistrations;
public:
	void add(CParticle *particle, CParticleForceGenerator *fg);
	void remove(CParticle *particle, CParticleForceGenerator *fg);
	void clear();
	void updateForces(float duration);
};