#pragma once

#define GROUND_SIZE					30.0f				// 바닥 크기
#define GROUND_DIVIDE_NUM			50					// 바닥 분할수
#define HEIGHT_NUM					( GROUND_DIVIDE_NUM + 1	)	// 높이 데이터수
#define BLOCK_NUM					( GROUND_DIVIDE_NUM )	// 지형 블록수
#define BLOCK_WIDTH					( GROUND_SIZE / BLOCK_NUM )		// 블록너비

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