#include "stdafx.h"
#include "Map.h"

int CMap::m_nowMapPos = 0;

CMap::CMap()
{
}

CMap::~CMap()
{
}

void CMap::CalcNowPositionIndex(const D3DXVECTOR3& m_characterPos)
{
	float mapSize = 30;
	D3DXVECTOR3 playerPos = m_characterPos;

	POINT result;
	result.x = ((float)mapSize / 2.0f) + playerPos.x;
	result.y = ((float)mapSize / 2.0f) - playerPos.z;

	result.x = floorf(result.x) - 15;
	result.y = floorf(result.y) - 15;

	int gridNum = -15;
	int gridAddNum = 30;
	int maxSize = g_pFileLoadManager->GetFileLoadCnt();

	for (int i = 0; i < maxSize; i++)
	{
		if (gridNum + (gridAddNum * i) <= result.x && gridNum + (gridAddNum * (i + 1)) >= result.x)
			result.x = i;

		if (gridNum + (gridAddNum * i) <= result.y && gridNum + (gridAddNum * (i + 1)) >= result.y)
			result.y = i;
	}

	// cout << result.x << ", " << result.y << endl;
	// cout << "-15 : ";
	// cout << x - 15 << ", " << z - 15 << endl;
	// -15 ~ 15
	// 15 ~ 45
	// 45 ~ 75
	// ... x, z

	CMap::m_nowMapPos = result.x + (result.y * 5);
	// >> 현재 플레이어가 위치한 맵 번호
}

void CMap::SetIsRenderState()
{
	int maxSize = g_pFileLoadManager->GetFileLoadCnt();
	vector<bool> vecCheck;

	for (int i = 0; i < maxSize; i++)
		vecCheck.push_back(false);

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i < 0 || j < 0 || i >= maxSize * 0.5f || j >= maxSize * 0.5f)
				continue;
			// >> 인덱스가 0보다 작음, 맵 범위를 넘어감

			vecCheck[i + (j * 5)] = true;
		}
	}
	// >> 랜더 범위 적용
}
