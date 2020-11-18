#pragma once

#define GROUND_SIZE					30.0f				// �ٴ� ũ��
#define GROUND_DIVIDE_NUM			50					// �ٴ� ���Ҽ�
#define HEIGHT_NUM					( GROUND_DIVIDE_NUM + 1	)	// ���� �����ͼ�
#define BLOCK_NUM					( GROUND_DIVIDE_NUM )	// ���� ��ϼ�
#define BLOCK_WIDTH					( GROUND_SIZE / BLOCK_NUM )		// ��ϳʺ�

class CPhysicsPlayer;

class CHeightMap
{
public:
	CHeightMap();
	~CHeightMap();
private:
	float m_fHeights[HEIGHT_NUM][HEIGHT_NUM];
	D3DXVECTOR3	m_vNormal[HEIGHT_NUM][HEIGHT_NUM];
	int m_nHitTriangleIndex;
public:
	void Setup();
	void Render();
	float CheckGroundHeight(CPhysicsPlayer *player);
};