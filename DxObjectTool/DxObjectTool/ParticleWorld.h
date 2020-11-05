#pragma once

class CParticle;

class CParticleWorld
{
public:
	CParticleWorld(unsigned maxContacts, unsigned iterations = 0);
	~CParticleWorld();

	typedef vector<CParticle*>	Particles;
protected:
	Particles particles;
	void startFrame();
};