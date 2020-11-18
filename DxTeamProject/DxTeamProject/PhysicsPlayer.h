#pragma once

#define PI							3.1415927f			// ������
#define ROT_SPEED					( PI / 100.0f )		// ȸ���ӵ�
#define CORNER_NUM					20					// ����
#define PLAYER_SPEED				0.15f				// �÷��̾��� �̵��ӵ�
#define PLAYER_ANG_SPEED			( PI / 100.0f )		// �÷��̾��� ȸ���ӵ�
#define GR							0.002f				// �߷°��ӵ�
#define G_CYLINDER_R				10.0f				// ���� ����� ������
#define G_SPHERE_R					10.0f				// ���� �� ������
#define G_SPHERE_Z_POS				5.0f				// ���� �� Z ��ġ

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