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

void COBB::SetupMesh(D3DXVECTOR3 & vMin2, D3DXVECTOR3 & vMax2 , float cubesize)
{
	D3DXVECTOR3 vMax = vMin2;
	D3DXVECTOR3 vMin = vMax2;

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

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], -cubesize /2, -m_fAxisHalfLen[2])); // 0
	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], cubesize / 2, -m_fAxisHalfLen[2])); //1
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], cubesize / 2, -m_fAxisHalfLen[2])); //2
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], -cubesize / 2, -m_fAxisHalfLen[2])); // 3

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], -cubesize / 2, m_fAxisHalfLen[2])); //4 
	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], cubesize / 2, m_fAxisHalfLen[2])); // 5
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], cubesize / 2, m_fAxisHalfLen[2])); //6
	vecVertex.push_back(D3DXVECTOR3(m_fAxisHalfLen[0], -cubesize / 2, m_fAxisHalfLen[2])); //7

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
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;
	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = pOBB2->m_vCenterPos - pOBB1->m_vCenterPos;

	// >> 특이 케이스
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			cos[a][b] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &pOBB2->m_vAxisDir[b]);
			// 두 벡터가 이루는 각을 통해서
			// 0보다 작으면 90도 보다 큼
			// 0보다 크면 90도 보다 작음

			absCos[a][b] = abs(cos[a][b]);

			if (absCos[a][b] > cutOff)
				existsParallelPair = true;	// 직각 or 그 이상

		} // : for_b

		dist[a] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &D);
		r = abs(dist[a]);

		r0 = pOBB1->m_fAxisHalfLen[a];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[a][0] +
			pOBB2->m_fAxisHalfLen[1] * absCos[a][1] +
			pOBB2->m_fAxisHalfLen[2] * absCos[a][2];

		if (r > r0 + r1)
			return false;

	}	// : for_a


	for (int b = 0; b < 3; b++)
	{
		r = abs(D3DXVec3Dot(&pOBB2->m_vAxisDir[b], &D));

		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[0][b] +
			pOBB1->m_fAxisHalfLen[1] * absCos[1][b] +
			pOBB1->m_fAxisHalfLen[2] * absCos[2][b];
		r1 = pOBB2->m_fAxisHalfLen[b];

		if (r > r0 + r1)
			return false;
	}

	if (existsParallelPair)
		return true;
	// << 특이 케이스

	// >> 보편적인 케이스
	// 0 : x축
	r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][0] +
		pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
	r1 = pOBB2->m_fAxisHalfLen[1] * absCos[1][2] +
		pOBB2->m_fAxisHalfLen[2] * absCos[1][1];
	if (r > r0 + r1) return false;

	r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] +
		pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[1][2] +
		pOBB2->m_fAxisHalfLen[2] * absCos[1][0];
	if (r > r0 + r1) return false;

	r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] +
		pOBB1->m_fAxisHalfLen[2] * absCos[0][2];
	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[1][1] +
		pOBB2->m_fAxisHalfLen[1] * absCos[1][0];
	if (r > r0 + r1) return false;

	// ----------------------------------------------------
	// 1 : y축
	r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][0] +
		pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
	r1 = pOBB2->m_fAxisHalfLen[1] * absCos[2][2] +
		pOBB2->m_fAxisHalfLen[2] * absCos[2][1];
	if (r > r0 + r1) return false;

	r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] +
		pOBB1->m_fAxisHalfLen[1] * absCos[0][1];
	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[2][2] +
		pOBB2->m_fAxisHalfLen[2] * absCos[2][0];
	if (r > r0 + r1) return false;

	r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] +
		pOBB1->m_fAxisHalfLen[1] * absCos[0][2];
	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[2][1] +
		pOBB2->m_fAxisHalfLen[1] * absCos[2][0];
	if (r > r0 + r1) return false;

	// ----------------------------------------------------
	// 2 : z축
	r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][0] +
		pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
	r1 = pOBB2->m_fAxisHalfLen[1] * absCos[0][2] +
		pOBB2->m_fAxisHalfLen[2] * absCos[0][1];
	if (r > r0 + r1) return false;

	r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] +
		pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[0][2] +
		pOBB2->m_fAxisHalfLen[2] * absCos[0][0];
	if (r > r0 + r1) return false;

	r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] +
		pOBB1->m_fAxisHalfLen[2] * absCos[1][2];
	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[0][1] +
		pOBB2->m_fAxisHalfLen[1] * absCos[0][0];
	if (r > r0 + r1) return false;
	// << 보편적인 케이스

	return true; // 충돌이 일어나지 않음
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