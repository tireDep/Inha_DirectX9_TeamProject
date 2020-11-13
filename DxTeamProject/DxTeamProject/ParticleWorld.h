#pragma once
#include "ParticleForceRegistry.h"

class CParticle;
class COBB;

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
	// Pusing Force Test
	D3DXVECTOR3				m_vPosition;
public:
	void StartFrame();
	void Integrate(float duration);
	void RunPhysics(float duration);
	Particles				GetParticles();
	CParticleForceRegistry  GetForceRegisty();

	// Gravity Test
	void Setup();
	void Update(float duration);
	void Render();
	void SetCube();

	// Pusing Force Test
	void SetPusingForce(D3DXVECTOR3 direction);
	D3DXVECTOR3 & GetPosition();
	COBB* m_pOBB;
	COBB* GetOBB();
};