#include "stdafx.h"
#include "ParticleWorld.h"
#include "Particle.h"
#include "ParticleGravity.h"
#include "ParticlePusingForce.h"
#include "OBB.h"

CParticleWorld::CParticleWorld()
	: m_vPosition(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
}

CParticleWorld::~CParticleWorld()
{
	for each(auto p in m_vecParticles)
		SafeDelete(p);
}

 // Push Test
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

	//CParticleGravity* gravity = new CParticleGravity;
	SetCube();
}

void CParticleWorld::SetPusingForce(D3DXVECTOR3 direction)
{
	CParticlePusingForce* pusingforce = new CParticlePusingForce(direction);
	for (int i = 0; i < m_vecParticles.size(); i++)
	{
		m_stRegistrations.Add(m_vecParticles[i], pusingforce);
	}
}

D3DXVECTOR3 & CParticleWorld::GetPosition()
{
	return m_vPosition;
}

COBB * CParticleWorld::GetOBB()
{
	return m_pOBB;
}

// Gravity Test
//void CParticleWorld::Setup()
//{
//	CParticle* particle = NULL;
//	const float cubesize = 0.5f;
//
//	particle = new CParticle; particle->SetPosition(D3DXVECTOR3(-cubesize, -cubesize, -cubesize));	m_vecParticles.push_back(particle);
//	particle = new CParticle; particle->SetPosition(D3DXVECTOR3(-cubesize,  cubesize, -cubesize));	m_vecParticles.push_back(particle);
//	particle = new CParticle; particle->SetPosition(D3DXVECTOR3( cubesize,  cubesize, -cubesize));	m_vecParticles.push_back(particle);
//	particle = new CParticle; particle->SetPosition(D3DXVECTOR3( cubesize, -cubesize, -cubesize));	m_vecParticles.push_back(particle);
//	particle = new CParticle; particle->SetPosition(D3DXVECTOR3(-cubesize, -cubesize,  cubesize));	m_vecParticles.push_back(particle);
//	particle = new CParticle; particle->SetPosition(D3DXVECTOR3(-cubesize,  cubesize,  cubesize));	m_vecParticles.push_back(particle);
//	particle = new CParticle; particle->SetPosition(D3DXVECTOR3( cubesize,  cubesize,  cubesize));	m_vecParticles.push_back(particle);
//	particle = new CParticle; particle->SetPosition(D3DXVECTOR3( cubesize, -cubesize,  cubesize));	m_vecParticles.push_back(particle);
//
//	//CParticleGravity* gravity = new CParticleGravity;
//	CParticleGravity* gravity = new CParticleGravity(D3DXVECTOR3(0, -9.81f / 5, 0));
//
//	for (int i = 0; i < 8; i++)
//		m_stRegistrations.Add(m_vecParticles[i], gravity);
//	SetCube();
//}

void CParticleWorld::Update(float duration)
{
	StartFrame();
	Integrate(duration);
	RunPhysics(duration);
	D3DXMatrixTranslation(&m_matWorld, m_vecParticles[0]->GetPosition().x, m_vecParticles[0]->GetPosition().y, m_vecParticles[0]->GetPosition().z);
	if (m_pOBB)
		m_pOBB->Update(&m_matWorld);
	//m_vPosition = m_vecVertex[0].p + m_vecVertex[11].p;
	m_vPosition = m_vecParticles[0]->GetPosition() + m_vecParticles[6]->GetPosition();
}

void CParticleWorld::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
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
		m_vecVertex[i + 0].c = RED;
		m_vecVertex[i + 1].p = m_vecParticles[vecIndex[i + 1]]->GetPosition();
		m_vecVertex[i + 1].c = RED;
		m_vecVertex[i + 2].p = m_vecParticles[vecIndex[i + 2]]->GetPosition();
		m_vecVertex[i + 2].c = RED;
	}
	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		m_vecVertex[i].p += D3DXVECTOR3(-5, 0.5f, -5);
	}

	m_pOBB = new COBB;
	m_pOBB->SetupCube(m_vecVertex[0], m_vecVertex[11]);
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
}

CParticleWorld::Particles CParticleWorld::GetParticles()
{
	return m_vecParticles;
}

CParticleForceRegistry CParticleWorld::GetForceRegisty()
{
	return m_stRegistrations;
}