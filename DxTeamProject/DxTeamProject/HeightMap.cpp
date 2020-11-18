#include "stdafx.h"
#include "HeightMap.h"
#include "PhysicsPlayer.h"

CHeightMap::CHeightMap()
{
}


CHeightMap::~CHeightMap()
{
}

void CHeightMap::Setup()
{
	int nIndex;
	int nIndexZ1, nIndexZ2;
	float x, y, z;
	float ysq;
	float u, v;
	
	nIndex = 0;
	z = -GROUND_SIZE / 2;
	for (int i = 0; i < GROUND_DIVIDE_NUM + 1; i++)
	{
		x = -GROUND_SIZE / 2;
		v = (float)i / 20.0f;
		for (int j = 0; j < GROUND_DIVIDE_NUM + 1; j++)
		{
			if (z > G_SPHERE_Z_POS)
			{
				ysq = G_SPHERE_R * G_SPHERE_R - x*x - (z - G_SPHERE_Z_POS)*(z - G_SPHERE_Z_POS);
			}
			else
			{
				ysq = G_CYLINDER_R * G_CYLINDER_R - x*x;
			}
		}
	}
}

void CHeightMap::Render()
{
}

float CHeightMap::CheckGroundHeight(CPhysicsPlayer * player)
{
	float fPlayerBlock_x, fPlayerBlock_z;
	int nBlockIndex_x, nBlockIndex_z;
	float fBlockRes_x, fBlockRes_z;
	float fGrad_x, fGrad_z;
	int nInIndex;
	float fHeight;
	D3DXVECTOR3	v3Grad1, v3Grad2;

	fPlayerBlock_x = (player->getPosition().x + (GROUND_SIZE / 2)) / (float)BLOCK_WIDTH;
	nBlockIndex_x = (int)fPlayerBlock_x;
	if (nBlockIndex_x < 0)	nBlockIndex_x = 0;
	if (nBlockIndex_x > BLOCK_NUM - 1) nBlockIndex_x = BLOCK_NUM - 1;
	fBlockRes_x = fPlayerBlock_x - nBlockIndex_x;
	fPlayerBlock_z = (player->getPosition().z + (GROUND_SIZE / 2)) / (float)BLOCK_WIDTH;
	nBlockIndex_z = (int)fPlayerBlock_z;
	if (nBlockIndex_z < 0) nBlockIndex_z = 0;
	if (nBlockIndex_z > BLOCK_NUM - 1) nBlockIndex_z = BLOCK_NUM - 1;
	fBlockRes_z = fPlayerBlock_z - nBlockIndex_z;

	if ((fBlockRes_x + fBlockRes_z) < 1.0f)
	{
		fGrad_x = m_fHeights[nBlockIndex_z][nBlockIndex_x + 1] - m_fHeights[nBlockIndex_z][nBlockIndex_x];
		fGrad_z = m_fHeights[nBlockIndex_z + 1][nBlockIndex_x] - m_fHeights[nBlockIndex_z][nBlockIndex_x];
		fHeight = fGrad_x * fBlockRes_x + fGrad_z * fBlockRes_z + m_fHeights[nBlockIndex_z][nBlockIndex_x];
		nInIndex = 0;
		v3Grad1 = m_vNormal[nBlockIndex_z][nBlockIndex_x + 1] - m_vNormal[nBlockIndex_z][nBlockIndex_x];
		v3Grad2 = m_vNormal[nBlockIndex_z + 1][nBlockIndex_x] - m_vNormal[nBlockIndex_z][nBlockIndex_x];
		D3DXVECTOR3	playerNormal;
		playerNormal.x = v3Grad1.x * fBlockRes_x + v3Grad2.x * fBlockRes_z + m_vNormal[nBlockIndex_z][nBlockIndex_x].x;
		playerNormal.y = v3Grad1.y * fBlockRes_x + v3Grad2.y * fBlockRes_z + m_vNormal[nBlockIndex_z][nBlockIndex_x].y;
		playerNormal.z = v3Grad1.z * fBlockRes_x + v3Grad2.z * fBlockRes_z + m_vNormal[nBlockIndex_z][nBlockIndex_x].z;
		D3DXVec3Normalize(&playerNormal, &playerNormal);
		player->setNormal(playerNormal);
	}
	else
	{
		fGrad_x = m_fHeights[nBlockIndex_z + 1][nBlockIndex_x] - m_fHeights[nBlockIndex_z + 1][nBlockIndex_x + 1];
		fGrad_z = m_fHeights[nBlockIndex_z][nBlockIndex_x + 1] - m_fHeights[nBlockIndex_z + 1][nBlockIndex_x + 1];
		fHeight = fGrad_x * (1.0f - fBlockRes_x) + fGrad_z*(1.0f - fBlockRes_z) + m_fHeights[nBlockIndex_z + 1][nBlockIndex_x + 1];
		nInIndex = 1;
		v3Grad1 = m_vNormal[nBlockIndex_z + 1][nBlockIndex_x] - m_vNormal[nBlockIndex_z + 1][nBlockIndex_x + 1];
		v3Grad2 = m_vNormal[nBlockIndex_z][nBlockIndex_x + 1] - m_vNormal[nBlockIndex_z + 1][nBlockIndex_x + 1];
		D3DXVECTOR3	playerNormal;
		playerNormal.x = v3Grad1.x * (1.0f - fBlockRes_x) + v3Grad2.x * (1.0f - fBlockRes_z) + m_vNormal[nBlockIndex_z + 1][nBlockIndex_x + 1].x;
		playerNormal.y = v3Grad1.y * (1.0f - fBlockRes_x) + v3Grad2.y * (1.0f - fBlockRes_z) + m_vNormal[nBlockIndex_z + 1][nBlockIndex_x + 1].y;
		playerNormal.z = v3Grad1.z * (1.0f - fBlockRes_x) + v3Grad2.z * (1.0f - fBlockRes_z) + m_vNormal[nBlockIndex_z + 1][nBlockIndex_x + 1].z;
		D3DXVec3Normalize(&playerNormal, &playerNormal);
		player->setNormal(playerNormal);
	}
	m_nHitTriangleIndex = nBlockIndex_z * GROUND_DIVIDE_NUM * 2 + nBlockIndex_x * 2 + nInIndex;
	return fHeight;
}
