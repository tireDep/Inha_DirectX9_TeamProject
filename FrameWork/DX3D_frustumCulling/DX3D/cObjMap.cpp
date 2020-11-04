#include "stdafx.h"
#include "cObjMap.h"
#include "cObjLoader.h"

cObjMap::cObjMap(IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pmat)
{
	Load(szFolder, szFile, pmat);
}

cObjMap::~cObjMap()
{

}

void cObjMap::Load(IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pmat)
{
	cObjLoader l;
	l.LoadSurface(m_vecSurface, szFolder, szFile, pmat);
	// 정보가 로드되어 넘어옴
}

bool cObjMap::GetHeight(IN float x, OUT float & y, IN float z)
{
	float height = 1000;
	D3DXVECTOR3 vRayPos(x, height, z);	// 캐릭터 x, 레이 높이, 캐릭터 z
	D3DXVECTOR3 vRayDir(0, -1, 0);		// 아래방향
	float u = 0, v = 0, fDist = 0;

	for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		if (D3DXIntersectTri(&m_vecSurface[i + 0], &m_vecSurface[i + 1], &m_vecSurface[i + 2],
			&vRayPos, &vRayDir, &u, &v, &fDist))
		{
			// 충돌 발생시
			y = height - fDist;	// 높이에서 충돌 지점까지 계산
			return true;
		}
	}

	return false;
}

void cObjMap::Render()
{
}

vector<D3DXVECTOR3> cObjMap::GetVecVertex()
{
	return vector<D3DXVECTOR3>();
}

void cObjMap::SetFrustumMap(const vector<bool>& vecCheck)
{
}
