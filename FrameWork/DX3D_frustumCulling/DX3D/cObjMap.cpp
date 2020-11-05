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
	// ������ �ε�Ǿ� �Ѿ��
}

bool cObjMap::GetHeight(IN float x, OUT float & y, IN float z)
{
	float height = 1000;
	D3DXVECTOR3 vRayPos(x, height, z);	// ĳ���� x, ���� ����, ĳ���� z
	D3DXVECTOR3 vRayDir(0, -1, 0);		// �Ʒ�����
	float u = 0, v = 0, fDist = 0;

	for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		if (D3DXIntersectTri(&m_vecSurface[i + 0], &m_vecSurface[i + 1], &m_vecSurface[i + 2],
			&vRayPos, &vRayDir, &u, &v, &fDist))
		{
			// �浹 �߻���
			y = height - fDist;	// ���̿��� �浹 �������� ���
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
