#pragma once
#include "ParticleForceRegistry.h"

class CParticle;

class CParticleWorld
{
public:
	CParticleWorld();
	~CParticleWorld();
	typedef vector<CParticle*> Particles;
protected:
	Particles				m_vecParticles;
	CParticleForceRegistry  m_stRegistrations;
	// Gravity test
	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXMATRIXA16			m_matWorld;
public:
	void StartFrame();
	void Integrate(float duration);
	void RunPhysics(float duration);
	Particles				GetParticles();
	CParticleForceRegistry  GetForceRegisty();

	// Gravity test
	void Setup();
	void Update(float duration);
	void Render();
	void UpdatePosition();
};