#include "stdafx.h"
#include "ParticleWorld.h"
#include "Particle.h"
#include "ParticleGravity.h"
#include "ParticlePusingForce.h"
#include "ParticleDrag.h"

#include "ParticleContact.h"
#include "OBB.h"

CParticleWorld::CParticleWorld()
	: m_vPosition(0, 0, 0)
	, m_resolver(NULL)
	, m_pContacts(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

// collider
CParticleWorld::CParticleWorld(UINT maxContacts, UINT iterations) 
	: m_resolver(iterations)
	, m_unMaxContacts(maxContacts)
{
	m_pContacts = new CParticleContact[maxContacts];
	m_isCalculateIterations = (iterations == 0);
}

CParticleWorld::~CParticleWorld()
{
	for each(auto p in m_vecParticles)
		SafeDelete(p);
	// Need Force Delete

	// collider
	if(m_pContacts)
		delete[] m_pContacts;
}

void CParticleWorld::Setup()
{
	CParticle* particle = NULL;
	const float cubesize = 0.5f;

	particle = new CParticle; particle->SetPosition(D3DXVECTOR3(-cubesize, -cubesize, -cubesize));	m_vecParticles.push_back(particle);
	particle = new CParticle; particle->SetPosition(D3DXVECTOR3(-cubesize,  cubesize, -cubesize));	m_vecParticles.push_back(particle);
	particle = new CParticle; particle->SetPosition(D3DXVECTOR3( cubesize,  cubesize, -cubesize));	m_vecParticles.push_back(particle);
	particle = new CParticle; particle->SetPosition(D3DXVECTOR3( cubesize, -cubesize, -cubesize));	m_vecParticles.push_back(particle);
	particle = new CParticle; particle->SetPosition(D3DXVECTOR3(-cubesize, -cubesize,  cubesize));	m_vecParticles.push_back(particle);
	particle = new CParticle; particle->SetPosition(D3DXVECTOR3(-cubesize,  cubesize,  cubesize));	m_vecParticles.push_back(particle);
	particle = new CParticle; particle->SetPosition(D3DXVECTOR3( cubesize,  cubesize,  cubesize));	m_vecParticles.push_back(particle);
	particle = new CParticle; particle->SetPosition(D3DXVECTOR3( cubesize, -cubesize,  cubesize));	m_vecParticles.push_back(particle);

	for (int i = 0; i < m_vecParticles.size(); i++)
		m_vecParticles[i]->SetPosition(m_vecParticles[i]->GetPosition() + D3DXVECTOR3(0, cubesize, 0));

	SetCube();
	//SetGravity();
	SetPusingForce(D3DXVECTOR3(1, 0, 1));
	//SetDragForce(0.4, 0.4);
}

void CParticleWorld::SetCube()
{
	vector<DWORD> vecIndex;
	{
		// : front
		vecIndex.push_back(0);
		vecIndex.push_back(1);
		vecIndex.push_back(2);
		vecIndex.push_back(0);
		vecIndex.push_back(2);
		vecIndex.push_back(3);
		// : back 
		vecIndex.push_back(4);
		vecIndex.push_back(6);
		vecIndex.push_back(5);
		vecIndex.push_back(4);
		vecIndex.push_back(7);
		vecIndex.push_back(6);
		// : left 
		vecIndex.push_back(4);
		vecIndex.push_back(5);
		vecIndex.push_back(1);
		vecIndex.push_back(4);
		vecIndex.push_back(1);
		vecIndex.push_back(0);
		// : right 
		vecIndex.push_back(3);
		vecIndex.push_back(2);
		vecIndex.push_back(6);
		vecIndex.push_back(3);
		vecIndex.push_back(6);
		vecIndex.push_back(7);
		// : top 
		vecIndex.push_back(1);
		vecIndex.push_back(5);
		vecIndex.push_back(6);
		vecIndex.push_back(1);
		vecIndex.push_back(6);
		vecIndex.push_back(2);
		// : bottom 
		vecIndex.push_back(4);
		vecIndex.push_back(0);
		vecIndex.push_back(3);
		vecIndex.push_back(4);
		vecIndex.push_back(3);
		vecIndex.push_back(7);
	}
	m_vecVertex.resize(36);
	for (size_t i = 0; i < vecIndex.size(); i += 3)
	{
		m_vecVertex[i + 0].p = m_vecParticles[vecIndex[i + 0]]->GetPosition();
		m_vecVertex[i + 1].p = m_vecParticles[vecIndex[i + 1]]->GetPosition();
		m_vecVertex[i + 2].p = m_vecParticles[vecIndex[i + 2]]->GetPosition();
	}
	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		m_vecVertex[i].c = RED;
	}
}

void CParticleWorld::SetGravity()
{
	CParticleGravity* gravity = new CParticleGravity(D3DXVECTOR3(0, -9.81f / 5, 0));

	for (int i = 0; i < 8; i++)
		m_stRegistrations.Add(m_vecParticles[i], gravity);
}

void CParticleWorld::SetPusingForce(D3DXVECTOR3 direction)
{
	D3DXVec3Normalize(&direction, &direction);
	CParticlePusingForce* pusingforce = new CParticlePusingForce(direction);
	for (int i = 0; i < m_vecParticles.size(); i++)
	{
		m_stRegistrations.Add(m_vecParticles[i], pusingforce);
	}
}

void CParticleWorld::SetDragForce(float k1, float k2)
{
	CParticleDrag* drag = new CParticleDrag(k1, k2);

	for (int i = 0; i < 8; i++)
		m_stRegistrations.Add(m_vecParticles[i], drag);
}

void CParticleWorld::Update(float duration)
{
	StartFrame();
	Integrate(duration);
	RunPhysics(duration);
	D3DXMatrixTranslation(&m_matWorld, m_vecParticles[0]->GetPosition().x, m_vecParticles[0]->GetPosition().y, m_vecParticles[0]->GetPosition().z);
	m_vPosition = (m_vecParticles[0]->GetPosition() + m_vecParticles[6]->GetPosition()) / 2.0f;
}

void CParticleWorld::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

void CParticleWorld::StartFrame()
{
	for (Particles::iterator it = m_vecParticles.begin(); it != m_vecParticles.end(); it++)
	{
		(*it)->ClearAccumulator();
	}
}

void CParticleWorld::Integrate(float duration)
{
	for (Particles::iterator it = m_vecParticles.begin(); it != m_vecParticles.end(); it++)
	{
		(*it)->Integrate(duration);
	}
}

void CParticleWorld::RunPhysics(float duration)
{
	m_stRegistrations.UpdateForces(duration);
	Integrate(duration);
	// collider
	UINT usedContacts = generateContacts();
	if (usedContacts)
	{
		if (m_isCalculateIterations)
			m_resolver.setIterations(usedContacts * 2);
		m_resolver.resolveContacts(m_pContacts, usedContacts, duration);
	}
}

D3DXVECTOR3 & CParticleWorld::GetPosition()
{
	return m_vPosition;
}

unsigned CParticleWorld::generateContacts()
{
	UINT limit = m_unMaxContacts;
	CParticleContact *nextContact = m_pContacts;

	for (ContactGenerators::iterator g = m_vecContactGenerator.begin(); g != m_vecContactGenerator.end(); g++)
	{
		UINT used = (*g)->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;
		if (limit <= 0)
			break;
	}
	return m_unMaxContacts - limit;
}

///
//
//COBB * CParticleWorld::GetOBB()
//{
//	return m_pOBB;
//}
//
//CParticleWorld::Particles CParticleWorld::GetParticles()
//{
//	return m_vecParticles;
//}
//
//CParticleForceRegistry CParticleWorld::GetForceRegisty()
//{
//	return m_stRegistrations;
//}