#include "stdafx.h"
#include "OBB.h"

#include "SkinnedMesh.h"

COBB::COBB()
{
}

COBB::~COBB()
{
}

void COBB::SetUp(CSkinnedMesh * pSkinnedMesh)
{
	D3DXVECTOR3 vMin = pSkinnedMesh->GetMin();
	D3DXVECTOR3 vMax = pSkinnedMesh->GetMax();
	
	// >> hitBox
	vector<ST_PC_VERTEX> tempVec;
	int maxPoint = 8;
	tempVec.resize(8);
	tempVec[0].p = D3DXVECTOR3(vMin.x, vMin.y, vMin.z);
	tempVec[1].p = D3DXVECTOR3(vMin.x, vMin.y, vMax.z);
	tempVec[2].p = D3DXVECTOR3(vMax.x, vMin.y, vMax.z);
	tempVec[3].p = D3DXVECTOR3(vMax.x, vMin.y, vMin.z);

	tempVec[4].p = D3DXVECTOR3(vMin.x, vMax.y, vMin.z);
	tempVec[5].p = D3DXVECTOR3(vMin.x, vMax.y, vMax.z);
	tempVec[6].p = D3DXVECTOR3(vMax.x, vMax.y, vMax.z);
	tempVec[7].p = D3DXVECTOR3(vMax.x, vMax.y, vMin.z);
	// hitBox_Triangle
	{
		// front
		m_vecVertex.push_back(tempVec[0]);
		m_vecVertex.push_back(tempVec[4]);
		m_vecVertex.push_back(tempVec[7]);

		m_vecVertex.push_back(tempVec[0]);
		m_vecVertex.push_back(tempVec[7]);
		m_vecVertex.push_back(tempVec[3]);

		// back
		m_vecVertex.push_back(tempVec[1]);
		m_vecVertex.push_back(tempVec[6]);
		m_vecVertex.push_back(tempVec[5]);

		m_vecVertex.push_back(tempVec[1]);
		m_vecVertex.push_back(tempVec[2]);
		m_vecVertex.push_back(tempVec[6]);

		// left
		m_vecVertex.push_back(tempVec[1]);
		m_vecVertex.push_back(tempVec[5]);
		m_vecVertex.push_back(tempVec[4]);

		m_vecVertex.push_back(tempVec[1]);
		m_vecVertex.push_back(tempVec[4]);
		m_vecVertex.push_back(tempVec[0]);

		// right
		m_vecVertex.push_back(tempVec[3]);
		m_vecVertex.push_back(tempVec[7]);
		m_vecVertex.push_back(tempVec[6]);

		m_vecVertex.push_back(tempVec[3]);
		m_vecVertex.push_back(tempVec[6]);
		m_vecVertex.push_back(tempVec[2]);

		// top
		m_vecVertex.push_back(tempVec[4]);
		m_vecVertex.push_back(tempVec[5]);
		m_vecVertex.push_back(tempVec[6]);

		m_vecVertex.push_back(tempVec[4]);
		m_vecVertex.push_back(tempVec[6]);
		m_vecVertex.push_back(tempVec[7]);

		// bottom
		m_vecVertex.push_back(tempVec[1]);
		m_vecVertex.push_back(tempVec[0]);
		m_vecVertex.push_back(tempVec[3]);

		m_vecVertex.push_back(tempVec[1]);
		m_vecVertex.push_back(tempVec[3]);
		m_vecVertex.push_back(tempVec[2]);

		m_vecVertex_Basic = m_vecVertex;
	}
	// << hitBox

	m_vOriCenterPos = (vMin + vMax) / 2.f;
	m_vOriAxidDir[0] = D3DXVECTOR3(1, 0, 0);	// x
	m_vOriAxidDir[1] = D3DXVECTOR3(0, 1, 0);	// y
	m_vOriAxidDir[2] = D3DXVECTOR3(0, 0, 1);	// z

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);	// x
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);	// y
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);	// z

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	D3DXMatrixIdentity(&m_matWorldTM);
}

void COBB::Update(D3DXMATRIXA16 * pmatWorld)
{
	if (pmatWorld)
	{
		m_matWorldTM = *pmatWorld;
	}

	for (int i = 0; i < 3; i++)
	{
		D3DXVec3TransformNormal(&m_vAxisDir[i], &m_vOriAxidDir[i], &m_matWorldTM);
	}

	D3DXVec3TransformCoord(&m_vCenterPos, &m_vOriCenterPos, &m_matWorldTM);

	vector<ST_PC_VERTEX> temp = m_vecVertex_Basic;
	for (int i = 0; i < m_vecVertex_Basic.size(); i++)
		D3DXVec3TransformCoord(&temp[i].p, &temp[i].p, &m_matWorldTM);

	m_vecVertex = temp;
}

bool COBB::IsCollision(COBB * pOBB1, COBB * pOBB2)
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

		r0= pOBB1->m_fAxisHalfLen[0] * absCos[0][b] +
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
	r1 = pOBB1->m_fAxisHalfLen[1] * absCos[1][2] + 
		 pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
	if (r > r0 + r1) return false;

	r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] + 
		 pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] + 
		 pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
	if (r > r0 + r1) return false;

	r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] +
		 pOBB1->m_fAxisHalfLen[2] * absCos[0][2];
	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] +
		 pOBB1->m_fAxisHalfLen[1] * absCos[1][0];
	if (r > r0 + r1) return false;

	// ----------------------------------------------------
	// 1 : y축
	r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][0] +
		 pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
	r1 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] +
		 pOBB1->m_fAxisHalfLen[2] * absCos[2][1];
	if (r > r0 + r1) return false;

	r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] +
		 pOBB1->m_fAxisHalfLen[1] * absCos[0][1];
	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] +
		 pOBB1->m_fAxisHalfLen[2] * absCos[2][0];
	if (r > r0 + r1) return false;

	r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] +
		 pOBB1->m_fAxisHalfLen[1] * absCos[0][2];
	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] +
		 pOBB1->m_fAxisHalfLen[1] * absCos[2][0];
	if (r > r0 + r1) return false;

	// ----------------------------------------------------
	// 2 : z축
	r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][0] +
		 pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
	r1 = pOBB1->m_fAxisHalfLen[1] * absCos[0][2] +
		 pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
	if (r > r0 + r1) return false;

	r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] +
		 pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[0][2] +
		 pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
	if (r > r0 + r1) return false;

	r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] +
		 pOBB1->m_fAxisHalfLen[2] * absCos[1][2];
	r1 = pOBB1->m_fAxisHalfLen[0] * absCos[0][1] +
		 pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
	if (r > r0 + r1) return false;
	// << 보편적인 케이스

	return true; // 충돌이 일어나지 않음
}

void COBB::Render_OBB_BOX(D3DCOLOR c)
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		m_vecVertex[i].c = c;
	}

	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vecVertex.size()-1, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
