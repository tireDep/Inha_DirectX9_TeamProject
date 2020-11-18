#include "stdafx.h"
#include "PhysicsPlayer.h"
#include "HeightMap.h"

CPhysicsPlayer::CPhysicsPlayer()
{
}

CPhysicsPlayer::~CPhysicsPlayer()
{
}

D3DXVECTOR3 CPhysicsPlayer::getPosition()
{
	return m_vPostion;
}

void CPhysicsPlayer::setPosition(D3DXVECTOR3 position)
{
	m_vPostion = position;
}

D3DXVECTOR3 CPhysicsPlayer::getNormal()
{
	return m_vNormal;
}

void CPhysicsPlayer::setNormal(D3DXVECTOR3 normal)
{
	m_vNormal = normal;
}

void CPhysicsPlayer::Setup(float yPosition)
{
	float fVel;
	m_vPostion = D3DXVECTOR3(G_CYLINDER_R - 3.0f, 0.0f, -4.0f);
	m_vPostion.y = yPosition;
	m_vVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.10f);
	m_fAngleXZ = 0.0f;
	m_vNormal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fEnergy = GR * m_vPostion.y;
	fVel = D3DXVec3Length(&m_vPostion);
	m_fEnergy += 0.5f * fVel * fVel;
}

void CPhysicsPlayer::Update(float yPosition)
{
	D3DXVECTOR3	v3Drop, v3Side, v3Up;
	D3DXVECTOR3 v3Vel;
	float fNowKineticE;
	float fNowVel;

	if (GetAsyncKeyState(VK_NUMPAD4))
	{
		m_fAngleXZ += PLAYER_ANG_SPEED;
		if (m_fAngleXZ > (2.0f*PI))
			m_fAngleXZ -= 2.0f * PI;
	}
	if (GetAsyncKeyState(VK_NUMPAD6))
	{
		m_fAngleXZ -= PLAYER_ANG_SPEED;
		if (m_fAngleXZ < (2.0f*PI))
			m_fAngleXZ += 2.0f * PI;
	}
	m_vPostion.x += m_vVelocity.x;
	m_vPostion.y += m_vVelocity.y;
	m_vPostion.z += m_vVelocity.z;

	if (m_vPostion.x > GROUND_SIZE / 2)
	{
		m_vPostion.x = GROUND_SIZE / 2;
		m_vVelocity.x = -m_vVelocity.x;
	}
	if (m_vPostion.x < -GROUND_SIZE / 2)
	{
		m_vPostion.x = -GROUND_SIZE / 2;
		m_vVelocity.x = -m_vVelocity.x;
	}
	if (m_vPostion.z > GROUND_SIZE / 2)
	{
		m_vPostion.z = GROUND_SIZE / 2;
		m_vVelocity.z = -m_vVelocity.z;
	}
	if (m_vPostion.z < -GROUND_SIZE / 2)
	{
		m_vPostion.z = -GROUND_SIZE / 2;
		m_vVelocity.z = -m_vVelocity.z;
	}
	m_vPostion.y = yPosition;
	v3Up = m_vNormal;
	v3Side = D3DXVECTOR3(v3Up.z, 0.0f, -v3Up.x);
	D3DXVec3Cross(&v3Drop, &v3Side, &v3Up);
	m_vVelocity.x += GR * v3Drop.x;
	m_vVelocity.y += GR * v3Drop.y;
	m_vVelocity.z += GR * v3Drop.z;
	v3Up = m_vNormal;
	v3Vel = m_vVelocity;
	D3DXVec3Cross(&v3Side, &v3Vel, &v3Up);
	D3DXVec3Cross(&v3Vel, &v3Up, &v3Side);
	D3DXVec3Normalize(&v3Vel, &v3Vel);
	fNowKineticE = m_fEnergy - GR * m_vPostion.y;
	if (fNowKineticE > 0.0f)
	{
		fNowVel = sqrtf(2.0f * fNowKineticE);
		m_vVelocity.x = fNowVel * v3Vel.x;
		m_vVelocity.y = fNowVel * v3Vel.y;
		m_vVelocity.z = fNowVel * v3Vel.z;
	}
	else
	{
		m_vVelocity.x = GR*v3Drop.x;
		m_vVelocity.y = GR*v3Drop.y;
		m_vVelocity.z = GR*v3Drop.z;
	}
}

void CPhysicsPlayer::Render()
{
}
