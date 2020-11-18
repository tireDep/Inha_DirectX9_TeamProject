#pragma once
#include "ParticleForceRegistry.h"
#include "ParticleContactGenerator.h"
#include "ParticleContactResolver.h"

class CParticle;
class COBB;

class CParticleWorld
{
public:
	CParticleWorld();
	CParticleWorld(UINT maxContacts, UINT iterations);
	~CParticleWorld();
	typedef vector<CParticle*> Particles;
	// collider
	typedef vector<CParticleContactGenerator*> ContactGenerators;
protected:
	Particles				m_vecParticles;
	CParticleForceRegistry  m_stRegistrations;

	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXMATRIXA16			m_matWorld;
	D3DXVECTOR3				m_vPosition;

	// collider
	CParticleContactResolver m_resolver;
	ContactGenerators		m_vecContactGenerator;
	CParticleContact*		m_pContacts;
	UINT					m_unMaxContacts;
	bool					m_isCalculateIterations;
public:
	void StartFrame();
	void Integrate(float duration);
	void RunPhysics(float duration);

	void Setup();
	void Update(float duration);
	void Render();
	void SetCube();
	void SetGravity();
	void SetPusingForce(D3DXVECTOR3 direction);
	void SetDragForce(float k1, float k2);
	D3DXVECTOR3 & GetPosition();

	// collider
	UINT generateContacts();

	///
	//Particles				GetParticles();
	//CParticleForceRegistry  GetForceRegisty();
	//COBB* m_pOBB;
	//COBB* GetOBB();
};