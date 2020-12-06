#include "stdafx.h"
#include "OBB.h"

COBB::COBB() : m_vecVertex(NULL)
{
}

COBB::~COBB()
{
}

void COBB::SetupCube(ST_PC_VERTEX v1, ST_PC_VERTEX v2, float CubeSize)
{
	D3DXVECTOR3 vMax = v1.p;
	D3DXVECTOR3 vMin = v2.p;

	m_OriCenterPos = (vMin + vMax) / 2.0f;

	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	vector<D3DXVECTOR3> vecVertex;

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], -CubeSize, -m_fAxisHalfLen[2])); // 0
	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisLen[1] - CubeSize, -m_fAxisHalfLen[2])); //1
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisLen[1] - CubeSize, -m_fAxisHalfLen[2])); //2
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], -CubeSize, -m_fAxisHalfLen[2])); // 3

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], -CubeSize, m_fAxisHalfLen[2])); //4 
	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisLen[1] - CubeSize, m_fAxisHalfLen[2])); // 5
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisLen[1] - CubeSize, m_fAxisHalfLen[2])); //6
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], -CubeSize, m_fAxisHalfLen[2])); //7

	vector<DWORD> vecIndex;
	//앞면
	vecIndex.push_back(0);
	vecIndex.push_back(1);
	vecIndex.push_back(1);
	vecIndex.push_back(2);
	vecIndex.push_back(2);
	vecIndex.push_back(3);
	vecIndex.push_back(3);
	vecIndex.push_back(0);

	//뒷면
	vecIndex.push_back(4);
	vecIndex.push_back(5);
	vecIndex.push_back(5);
	vecIndex.push_back(6);
	vecIndex.push_back(6);
	vecIndex.push_back(7);
	vecIndex.push_back(7);
	vecIndex.push_back(4);

	////왼면
	vecIndex.push_back(0);
	vecIndex.push_back(4);
	vecIndex.push_back(1);
	vecIndex.push_back(5);


	////오른면
	vecIndex.push_back(2);
	vecIndex.push_back(6);
	vecIndex.push_back(3);
	vecIndex.push_back(7);

	m_vecVertex.resize(vecIndex.size());

	for (unsigned int i = 0; i < vecIndex.size(); ++i)
	{
		m_vecVertex[i].p = vecVertex[vecIndex[i]];
	}
	D3DXMatrixIdentity(&m_matWorldTM);
}
void COBB::SetUpXFile(D3DXVECTOR3& xfileMin, D3DXVECTOR3& xfileMax)
{
	D3DXVECTOR3 vMax = xfileMax;
	D3DXVECTOR3 vMin = xfileMin;

	m_OriCenterPos = (vMin + vMax) / 2.0f;

	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = (vMax.x - vMin.x);
	m_fAxisLen[1] = (vMax.y - vMin.y);
	m_fAxisLen[2] = (vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	float max = vMax.y;
	float min = vMin.y;
	vector<D3DXVECTOR3> vecVertex;

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], max   , -m_fAxisHalfLen[2])); // 0
	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0],  0    , -m_fAxisHalfLen[2])); //1
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0],   0    , -m_fAxisHalfLen[2])); //2
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0],  max   , -m_fAxisHalfLen[2])); // 3

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0],  max  , m_fAxisHalfLen[2])); //4 
	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0],   0   , m_fAxisHalfLen[2])); // 5
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0],    0   , m_fAxisHalfLen[2])); //6
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0],   max  , m_fAxisHalfLen[2])); //7

	vector<DWORD> vecIndex;
	//앞면
	vecIndex.push_back(0);
	vecIndex.push_back(1);
	vecIndex.push_back(1);
	vecIndex.push_back(2);
	vecIndex.push_back(2);
	vecIndex.push_back(3);
	vecIndex.push_back(3);
	vecIndex.push_back(0);

	//뒷면
	vecIndex.push_back(4);
	vecIndex.push_back(5);
	vecIndex.push_back(5);
	vecIndex.push_back(6);
	vecIndex.push_back(6);
	vecIndex.push_back(7);
	vecIndex.push_back(7);
	vecIndex.push_back(4);

	////왼면
	vecIndex.push_back(0);
	vecIndex.push_back(4);
	vecIndex.push_back(1);
	vecIndex.push_back(5);


	////오른면
	vecIndex.push_back(2);
	vecIndex.push_back(6);
	vecIndex.push_back(3);
	vecIndex.push_back(7);

	m_vecVertex.resize(vecIndex.size());

	for (unsigned int i = 0; i < vecIndex.size(); ++i)
	{
		m_vecVertex[i].p = vecVertex[vecIndex[i]];
	}
	D3DXMatrixIdentity(&m_matWorldTM);

}
void COBB::Update(D3DXMATRIXA16* pmatWorld)
{
	if (pmatWorld)
		m_matWorldTM = *pmatWorld;



	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3TransformNormal(
			&m_vAxisDir[i],
			&m_vOriAxisDir[i],
			&m_matWorldTM
		);
	}

	D3DXVec3TransformCoord(
		&m_vCenterPos,
		&m_OriCenterPos,
		&m_matWorldTM);
}

void COBB::SetupTile(D3DXVECTOR3& xfileMin, D3DXVECTOR3& xfileMax , D3DXVECTOR3 xfileY ,float x, float z)
{
	D3DXVECTOR3 vMax = xfileMax;
	D3DXVECTOR3 vMin = xfileMin;

	m_OriCenterPos = (vMin + vMax) / 2.0f;

	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = (vMax.x);
	m_fAxisLen[1] = xfileY.y;
	m_fAxisLen[2] = (vMax.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] * x;
	m_fAxisHalfLen[1] = m_fAxisLen[1];
	m_fAxisHalfLen[2] = m_fAxisLen[2] * z;

	
	vector<D3DXVECTOR3> vecVertex;

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisLen[1], -m_fAxisHalfLen[2])); // 0
	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0],  0    , -m_fAxisHalfLen[2])); //1
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0],   0    , -m_fAxisHalfLen[2])); //2
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisLen[1], -m_fAxisHalfLen[2])); // 3

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], m_fAxisLen[1], m_fAxisHalfLen[2])); //4 
	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0],   0   , m_fAxisHalfLen[2])); // 5
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0],    0   , m_fAxisHalfLen[2])); //6
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], m_fAxisLen[1], m_fAxisHalfLen[2])); //7

	vector<DWORD> vecIndex;
	//앞면
	vecIndex.push_back(0);
	vecIndex.push_back(1);
	vecIndex.push_back(1);
	vecIndex.push_back(2);
	vecIndex.push_back(2);
	vecIndex.push_back(3);
	vecIndex.push_back(3);
	vecIndex.push_back(0);

	//뒷면
	vecIndex.push_back(4);
	vecIndex.push_back(5);
	vecIndex.push_back(5);
	vecIndex.push_back(6);
	vecIndex.push_back(6);
	vecIndex.push_back(7);
	vecIndex.push_back(7);
	vecIndex.push_back(4);

	////왼면
	vecIndex.push_back(0);
	vecIndex.push_back(4);
	vecIndex.push_back(1);
	vecIndex.push_back(5);


	////오른면
	vecIndex.push_back(2);
	vecIndex.push_back(6);
	vecIndex.push_back(3);
	vecIndex.push_back(7);

	m_vecVertex.resize(vecIndex.size());

	for (unsigned int i = 0; i < vecIndex.size(); ++i)
	{
		m_vecVertex[i].p = vecVertex[vecIndex[i]];
	}
	D3DXMatrixIdentity(&m_matWorldTM);

}

bool COBB::IsCollision(COBB* pOBB1, COBB* pOBB2)
{
	// 중심						 m_OriCenterPos
	// 축						 m_vOriAxisDir[3]
	// 중심에서 OBB면까지의 거리 m_fAxisHalfLen[3]

	float C[3][3];		// C[i][j] = D3DXVec3Dot(pOBB1->m_vOriAxisDir[i], pOBB2->m_vOriAxisDir[j])
	float absC[3][3];	// absC[i][j] = abs(C[i][j])
	float d[3];			// d[i] = D3DXVec3Dot(pOBB2->m_OriCenterPos - pOBB1->m_OriCenterPos, pOBB1->m_vOriAxisDir[i])

						// 구간 반경과 구간 중심점 사이의 거리
	float r0, r1, r;
	int i;

	// 상자의 축들 사이각들의 cosine을 위한 cutoff
	const float cutoff = 0.999999;
	bool existsParallelPair = false;

	// d를 편하게 계산하기 위해 pOBB2->m_OriCenterPos - pOBB1->m_OriCenterPos 미리 계산
	D3DXVECTOR3 diff = pOBB2->m_vCenterPos - pOBB1->m_vCenterPos;

	// --------------------------------------------------------------------------------------------------------- //
	// 축 C0 + t * A0
	{
		for (i = 0; i < 3; i++)
		{
			C[0][i] = D3DXVec3Dot(&pOBB1->m_vOriAxisDir[0], &pOBB2->m_vOriAxisDir[i]);
			absC[0][i] = abs(C[0][i]);
			if (absC[0][i] > cutoff)
				existsParallelPair = true;
		}
		d[0] = D3DXVec3Dot(&diff, &pOBB1->m_vOriAxisDir[0]);
		r = abs(d[0]);
		r0 = pOBB1->m_fAxisHalfLen[0];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[0][0] + pOBB2->m_fAxisHalfLen[1] * absC[0][1] + pOBB2->m_fAxisHalfLen[2] * absC[0][2];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * A1
	{
		for (i = 0; i < 3; i++)
		{
			C[1][i] = D3DXVec3Dot(&pOBB1->m_vOriAxisDir[1], &pOBB2->m_vOriAxisDir[i]);
			absC[1][i] = abs(C[1][i]);
			if (absC[1][i] > cutoff)
				existsParallelPair = true;
		}
		d[1] = D3DXVec3Dot(&diff, &pOBB1->m_vOriAxisDir[1]);
		r = abs(d[1]);
		r0 = pOBB1->m_fAxisHalfLen[1];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[1][0] + pOBB2->m_fAxisHalfLen[1] * absC[1][1] + pOBB2->m_fAxisHalfLen[2] * absC[1][2];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * A2
	{
		for (i = 0; i < 3; i++)
		{
			C[2][i] = D3DXVec3Dot(&pOBB1->m_vOriAxisDir[2], &pOBB2->m_vOriAxisDir[i]);
			absC[2][i] = abs(C[2][i]);
			if (absC[2][i] > cutoff)
				existsParallelPair = true;
		}
		d[2] = D3DXVec3Dot(&diff, &pOBB1->m_vOriAxisDir[2]);
		r = abs(d[2]);
		r0 = pOBB1->m_fAxisHalfLen[2];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[2][0] + pOBB2->m_fAxisHalfLen[1] * absC[2][1] + pOBB2->m_fAxisHalfLen[2] * absC[2][2];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축 C0 + t * B0
	{
		r = abs(D3DXVec3Dot(&diff, &pOBB2->m_vOriAxisDir[0]));
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[0][0] + pOBB1->m_fAxisHalfLen[1] * absC[1][0] + pOBB1->m_fAxisHalfLen[2] * absC[2][0];
		r1 = pOBB2->m_fAxisHalfLen[0];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * B1
	{
		r = abs(D3DXVec3Dot(&diff, &pOBB2->m_vOriAxisDir[1]));
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[0][1] + pOBB1->m_fAxisHalfLen[1] * absC[1][1] + pOBB1->m_fAxisHalfLen[2] * absC[2][1];
		r1 = pOBB2->m_fAxisHalfLen[1];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * B2
	{
		r = abs(D3DXVec3Dot(&diff, &pOBB2->m_vOriAxisDir[2]));
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[0][2] + pOBB1->m_fAxisHalfLen[1] * absC[1][2] + pOBB1->m_fAxisHalfLen[2] * absC[2][2];
		r1 = pOBB2->m_fAxisHalfLen[2];
		if (r > r0 + r1)
			return false;
	}
	if (existsParallelPair)
		return true;
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A0 × B0
	{
		r = abs(d[2] * C[1][0] - d[1] * C[2][0]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absC[2][0] + pOBB1->m_fAxisHalfLen[2] * absC[1][0];
		r1 = pOBB2->m_fAxisHalfLen[1] * absC[0][2] + pOBB2->m_fAxisHalfLen[2] * absC[0][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A0 × B1
	{
		r = abs(d[2] * C[1][1] - d[1] * C[2][1]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absC[2][1] + pOBB1->m_fAxisHalfLen[2] * absC[1][1];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[0][2] + pOBB2->m_fAxisHalfLen[2] * absC[0][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A0 × B2
	{
		r = abs(d[2] * C[1][2] - d[1] * C[2][2]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absC[2][2] + pOBB1->m_fAxisHalfLen[2] * absC[1][2];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[0][1] + pOBB2->m_fAxisHalfLen[1] * absC[0][0];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A1 × B0
	{
		r = abs(d[0] * C[2][0] - d[2] * C[0][0]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][0] + pOBB1->m_fAxisHalfLen[2] * absC[0][0];
		r1 = pOBB2->m_fAxisHalfLen[1] * absC[1][2] + pOBB2->m_fAxisHalfLen[2] * absC[1][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A1 × B1
	{
		r = abs(d[0] * C[2][1] - d[2] * C[0][1]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][1] + pOBB1->m_fAxisHalfLen[2] * absC[0][1];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[1][2] + pOBB2->m_fAxisHalfLen[2] * absC[1][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A1 × B2
	{
		r = abs(d[0] * C[2][2] - d[2] * C[0][2]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][2] + pOBB1->m_fAxisHalfLen[2] * absC[0][2];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[1][1] + pOBB2->m_fAxisHalfLen[1] * absC[1][0];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A2 × B0
	{
		r = abs(d[1] * C[0][0] - d[0] * C[1][0]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[1][0] + pOBB1->m_fAxisHalfLen[1] * absC[0][0];
		r1 = pOBB2->m_fAxisHalfLen[1] * absC[2][2] + pOBB2->m_fAxisHalfLen[2] * absC[2][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A2 × B1
	{
		r = abs(d[1] * C[0][1] - d[0] * C[1][1]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[1][1] + pOBB1->m_fAxisHalfLen[1] * absC[0][1];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[2][2] + pOBB2->m_fAxisHalfLen[2] * absC[2][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A2 × B2
	{
		r = abs(d[1] * C[0][2] - d[0] * C[1][2]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[1][2] + pOBB1->m_fAxisHalfLen[1] * absC[0][2];
		r1 = pOBB2->m_fAxisHalfLen[0] * absC[2][1] + pOBB2->m_fAxisHalfLen[1] * absC[2][0];
		if (r > r0 + r1)
			return false;
	}
	return true;
}

void COBB::OBBBOX_RENDER(D3DXCOLOR c)
{
	for (unsigned int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].c = c;
	}
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, nullptr);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2,
		&m_vecVertex[0], sizeof(ST_PC_VERTEX));
}