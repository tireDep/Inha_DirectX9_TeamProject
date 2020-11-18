#pragma once

#define PI							3.1415927f			// 원주율
#define ROT_SPEED					( PI / 100.0f )		// 회전속도
#define CORNER_NUM					20					// 각수
#define PLAYER_SPEED				0.15f				// 플레이어의 이동속도
#define PLAYER_ANG_SPEED			( PI / 100.0f )		// 플레이어의 회전속도
#define GR							0.002f				// 중력가속도
#define G_CYLINDER_R				10.0f				// 지면 원기둥 반지름
#define G_SPHERE_R					10.0f				// 지면 구 반지름
#define G_SPHERE_Z_POS				5.0f				// 지면 구 Z 위치

#include "HeightMap.h"

class CPhysicsPlayer
{
public:
	CPhysicsPlayer();
	~CPhysicsPlayer();
private:
	D3DXVECTOR3		m_vPostion;
	D3DXVECTOR3		m_vVelocity;
	float			m_fAngleXZ;
	D3DXVECTOR3		m_vNormal;
	float			m_fEnergy;
public:
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 getNormal();
	void setNormal(D3DXVECTOR3 normal);

	void Setup(float yPosition);
	void Update(float yPosition);
	void Render();
};