#include "stdafx.h"
#include "OBB.h"
#include "AllocateHierarchy.h"

COBB::COBB() :
	m_vCenterPos(0, 0, 0),
	m_vOriCenterPos(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
}

COBB::~COBB()
{
}

void COBB::Setup(CObject & object)
{
	//m_matWorld = object.GetmatWorld();

	object.Update(0.0001f);

	D3DXVECTOR3* pVertices;
	object.GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);

	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXComputeBoundingBox(pVertices, object.GetMesh()->GetNumVertices(), object.GetMesh()->GetNumBytesPerVertex(), &m_vMin, &m_vMax);

	m_vOriCenterPos = (m_vMin + m_vMax) / 2.0f;
	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);
	m_fAxisHalfLen[0] = fabsf(m_vMax.x - m_vMin.x) / 2.0f;
	m_fAxisHalfLen[1] = fabsf(m_vMax.y - m_vMin.y) / 2.0f;
	m_fAxisHalfLen[2] = fabsf(m_vMax.z - m_vMin.z) / 2.0f;

	// OBB BOX LINE 
	{
		vector<D3DXVECTOR3> vecVertex;
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x - m_fAxisHalfLen[0], m_vOriCenterPos.y - m_fAxisHalfLen[1], m_vOriCenterPos.z - m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x - m_fAxisHalfLen[0], m_vOriCenterPos.y + m_fAxisHalfLen[1], m_vOriCenterPos.z - m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x + m_fAxisHalfLen[0], m_vOriCenterPos.y + m_fAxisHalfLen[1], m_vOriCenterPos.z - m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x + m_fAxisHalfLen[0], m_vOriCenterPos.y - m_fAxisHalfLen[1], m_vOriCenterPos.z - m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x - m_fAxisHalfLen[0], m_vOriCenterPos.y - m_fAxisHalfLen[1], m_vOriCenterPos.z + m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x - m_fAxisHalfLen[0], m_vOriCenterPos.y + m_fAxisHalfLen[1], m_vOriCenterPos.z + m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x + m_fAxisHalfLen[0], m_vOriCenterPos.y + m_fAxisHalfLen[1], m_vOriCenterPos.z + m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x + m_fAxisHalfLen[0], m_vOriCenterPos.y - m_fAxisHalfLen[1], m_vOriCenterPos.z + m_fAxisHalfLen[2]));

		vector<DWORD> vecIndex;
		// front
		vecIndex.push_back(0);
		vecIndex.push_back(1);
		vecIndex.push_back(1);
		vecIndex.push_back(2);
		vecIndex.push_back(2);
		vecIndex.push_back(3);
		vecIndex.push_back(3);
		vecIndex.push_back(0);
		// back
		vecIndex.push_back(4);
		vecIndex.push_back(5);
		vecIndex.push_back(5);
		vecIndex.push_back(6);
		vecIndex.push_back(6);
		vecIndex.push_back(7);
		vecIndex.push_back(7);
		vecIndex.push_back(4);
		// left
		vecIndex.push_back(1);
		vecIndex.push_back(5);
		vecIndex.push_back(0);
		vecIndex.push_back(4);
		// right
		vecIndex.push_back(2);
		vecIndex.push_back(6);
		vecIndex.push_back(3);
		vecIndex.push_back(7);

		m_vOBBLineVertex.resize(vecIndex.size());
		for (int i = 0; i < vecIndex.size(); i++)
		{
			m_vOBBLineVertex[i].p = vecVertex[vecIndex[i]];
			m_vOBBLineVertex[i].c = RED;
		}
	}

	// JW ADD...
	m_fAxisHalfLen[0] *= object.GetScale().x;
	m_fAxisHalfLen[1] *= object.GetScale().y;
	m_fAxisHalfLen[2] *= object.GetScale().z;

	// Check OriCenterPos, OriAxisDir
	for (int i = 0; i < 3; ++i)
		D3DXVec3TransformNormal(&m_vOriAxisDir[i], &m_vOriAxisDir[i], &m_matWorld);
		D3DXVec3TransformCoord(&m_vOriCenterPos, &m_vOriCenterPos, &m_matWorld);
	//for (int i = 0; i < 3; ++i)
	//	D3DXVec3TransformNormal(&m_vOriAxisDir[i], &m_vOriAxisDir[i], &object.GetmatWorld());
	//D3DXVec3TransformCoord(&m_vOriCenterPos, &m_vOriCenterPos, &object.GetmatWorld());

	object.GetMesh()->UnlockVertexBuffer();
}

void COBB::Setup(CAllocateHierarchy & ah)
{
	//m_matWorld = D3DXMATRIXA16(
	//	5.161628, 0.000000, 0.000000, 0.000000, 
	//	0.000000, 5.161628, 0.000000, 0.000000, 
	//	0.000000, 0.000000, 5.161628, 0.000000, 
	//	0.003480, 0.304418, 5.063910, 1.000000);
	D3DXVECTOR3 Upvector = D3DXVECTOR3(0, 1.5, 0);
	D3DXVECTOR3 m_vMin = ah.GetMin() * 2 + Upvector;
	D3DXVECTOR3 m_vMax = ah.GetMax() * 2 + Upvector;
	m_vMin.x = ah.GetMin().x * 1.8;		m_vMin.z = ah.GetMin().z * 5;
	m_vMax.x = ah.GetMax().x * 1.8;		m_vMax.z = ah.GetMax().z * 5;

	m_vOriCenterPos = (m_vMin + m_vMax) / 2.0f;
	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);
	m_fAxisHalfLen[0] = fabsf(m_vMax.x - m_vMin.x) / 2.0f;
	m_fAxisHalfLen[1] = fabsf(m_vMax.y - m_vMin.y) / 2.0f;
	m_fAxisHalfLen[2] = fabsf(m_vMax.z - m_vMin.z) / 2.0f;

	// OBB BOX LINE 
	{
		vector<D3DXVECTOR3> vecVertex;
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x - m_fAxisHalfLen[0], m_vOriCenterPos.y - m_fAxisHalfLen[1], m_vOriCenterPos.z - m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x - m_fAxisHalfLen[0], m_vOriCenterPos.y + m_fAxisHalfLen[1], m_vOriCenterPos.z - m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x + m_fAxisHalfLen[0], m_vOriCenterPos.y + m_fAxisHalfLen[1], m_vOriCenterPos.z - m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x + m_fAxisHalfLen[0], m_vOriCenterPos.y - m_fAxisHalfLen[1], m_vOriCenterPos.z - m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x - m_fAxisHalfLen[0], m_vOriCenterPos.y - m_fAxisHalfLen[1], m_vOriCenterPos.z + m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x - m_fAxisHalfLen[0], m_vOriCenterPos.y + m_fAxisHalfLen[1], m_vOriCenterPos.z + m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x + m_fAxisHalfLen[0], m_vOriCenterPos.y + m_fAxisHalfLen[1], m_vOriCenterPos.z + m_fAxisHalfLen[2]));
		vecVertex.push_back(D3DXVECTOR3(m_vOriCenterPos.x + m_fAxisHalfLen[0], m_vOriCenterPos.y - m_fAxisHalfLen[1], m_vOriCenterPos.z + m_fAxisHalfLen[2]));

		vector<DWORD> vecIndex;
		// front
		vecIndex.push_back(0);
		vecIndex.push_back(1);
		vecIndex.push_back(1);
		vecIndex.push_back(2);
		vecIndex.push_back(2);
		vecIndex.push_back(3);
		vecIndex.push_back(3);
		vecIndex.push_back(0);
		// back
		vecIndex.push_back(4);
		vecIndex.push_back(5);
		vecIndex.push_back(5);
		vecIndex.push_back(6);
		vecIndex.push_back(6);
		vecIndex.push_back(7);
		vecIndex.push_back(7);
		vecIndex.push_back(4);
		// left
		vecIndex.push_back(1);
		vecIndex.push_back(5);
		vecIndex.push_back(0);
		vecIndex.push_back(4);
		// right
		vecIndex.push_back(2);
		vecIndex.push_back(6);
		vecIndex.push_back(3);
		vecIndex.push_back(7);

		m_vOBBLineVertex.resize(vecIndex.size());
		for (int i = 0; i < vecIndex.size(); i++)
		{
			m_vOBBLineVertex[i].p = vecVertex[vecIndex[i]];
			m_vOBBLineVertex[i].c = RED;
		}
	}

	//m_fAxisHalfLen[0] *= object.GetScale().x;
	//m_fAxisHalfLen[1] *= object.GetScale().y;
	//m_fAxisHalfLen[2] *= object.GetScale().z;

	// Check OriCenterPos, OriAxisDir
	for (int i = 0; i < 3; ++i)
		D3DXVec3TransformNormal(&m_vOriAxisDir[i], &m_vOriAxisDir[i], &m_matWorld);
	D3DXVec3TransformCoord(&m_vOriCenterPos, &m_vOriCenterPos, &m_matWorld);
}

void COBB::SetupMesh(D3DXVECTOR3 & vMin2, D3DXVECTOR3 & vMax2, float cubesize)
{
	D3DXVECTOR3 vMax = vMin2;
	D3DXVECTOR3 vMin = vMax2;

	m_vOriCenterPos = (vMin + vMax) / 2.0f;

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

	vecVertex.push_back(D3DXVECTOR3(-m_fAxisHalfLen[0], -cubesize / 2, -m_fAxisHalfLen[2])); // 0
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

	m_vOBBLineVertex.resize(vecIndex.size());

	for (unsigned int i = 0; i < vecIndex.size(); ++i)
	{
		m_vOBBLineVertex[i].p = vecVertex[vecIndex[i]];
	}
	D3DXMatrixIdentity(&m_matWorld);
}

void COBB::Update(D3DXMATRIXA16 * pmatWorld)
{
	if (pmatWorld)
		m_matWorld = *pmatWorld;
	for (int i = 0; i < 3; i++)
	{
		D3DXVec3TransformNormal(&m_vAxisDir[i], &m_vOriAxisDir[i], &m_matWorld);
		// JW ADD...
		D3DXVec3Normalize(&m_vAxisDir[i], &m_vAxisDir[i]);
	}
	D3DXVec3TransformCoord(&m_vCenterPos, &m_vOriCenterPos, &m_matWorld);
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
//bool COBB::IsCollision(COBB * pOBB1, COBB * pOBB2)
//{
//	float cos[3][3];
//	float absCos[3][3];
//	float dist[3];
//	float r0, r1, r;
//	const float cutOff = 0.999999f;
//	bool existsParallelPair = false;
//
//	D3DXVECTOR3 D = pOBB2->m_vCenterPos - pOBB1->m_vCenterPos;
//
//	// >> 특이 케이스
//	for (int a = 0; a < 3; a++)
//	{
//		for (int b = 0; b < 3; b++)
//		{
//			cos[a][b] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &pOBB2->m_vAxisDir[b]);
//			// 두 벡터가 이루는 각을 통해서
//			// 0보다 작으면 90도 보다 큼
//			// 0보다 크면 90도 보다 작음
//
//			absCos[a][b] = abs(cos[a][b]);
//
//			if (absCos[a][b] > cutOff)
//				existsParallelPair = true;	// 직각 or 그 이상
//
//		} // : for_b
//
//		dist[a] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &D);
//		r = abs(dist[a]);
//
//		r0 = pOBB1->m_fAxisHalfLen[a];
//		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[a][0] +
//			pOBB2->m_fAxisHalfLen[1] * absCos[a][1] +
//			pOBB2->m_fAxisHalfLen[2] * absCos[a][2];
//
//		if (r > r0 + r1)
//			return false;
//
//	}	// : for_a
//
//
//	for (int b = 0; b < 3; b++)
//	{
//		r = abs(D3DXVec3Dot(&pOBB2->m_vAxisDir[b], &D));
//
//		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[0][b] +
//			pOBB1->m_fAxisHalfLen[1] * absCos[1][b] +
//			pOBB1->m_fAxisHalfLen[2] * absCos[2][b];
//		r1 = pOBB2->m_fAxisHalfLen[b];
//
//		if (r > r0 + r1)
//			return false;
//	}
//
//	if (existsParallelPair)
//		return true;
//	// << 특이 케이스
//
//	// >> 보편적인 케이스
//	// 0 : x축
//	r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][0] +
//		pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
//	r1 = pOBB2->m_fAxisHalfLen[1] * absCos[1][2] +
//		pOBB2->m_fAxisHalfLen[2] * absCos[1][1];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] +
//		pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
//	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[1][2] +
//		pOBB2->m_fAxisHalfLen[2] * absCos[1][0];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] +
//		pOBB1->m_fAxisHalfLen[2] * absCos[0][2];
//	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[1][1] +
//		pOBB2->m_fAxisHalfLen[1] * absCos[1][0];
//	if (r > r0 + r1) return false;
//
//	// ----------------------------------------------------
//	// 1 : y축
//	r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][0] +
//		pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
//	r1 = pOBB2->m_fAxisHalfLen[1] * absCos[2][2] +
//		pOBB2->m_fAxisHalfLen[2] * absCos[2][1];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] +
//		pOBB1->m_fAxisHalfLen[1] * absCos[0][1];
//	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[2][2] +
//		pOBB2->m_fAxisHalfLen[2] * absCos[2][0];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
//	r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] +
//		pOBB1->m_fAxisHalfLen[1] * absCos[0][2];
//	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[2][1] +
//		pOBB2->m_fAxisHalfLen[1] * absCos[2][0];
//	if (r > r0 + r1) return false;
//
//	// ----------------------------------------------------
//	// 2 : z축
//	r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
//	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][0] +
//		pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
//	r1 = pOBB2->m_fAxisHalfLen[1] * absCos[0][2] +
//		pOBB2->m_fAxisHalfLen[2] * absCos[0][1];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
//	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] +
//		pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
//	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[0][2] +
//		pOBB2->m_fAxisHalfLen[2] * absCos[0][0];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
//	r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] +
//		pOBB1->m_fAxisHalfLen[2] * absCos[1][2];
//	r1 = pOBB2->m_fAxisHalfLen[0] * absCos[0][1] +
//		pOBB2->m_fAxisHalfLen[1] * absCos[0][0];
//	if (r > r0 + r1) return false;
//	// << 보편적인 케이스
//
//	return true; // 충돌이 일어나지 않음
//}

//bool COBB::IsCollision(COBB * otherOBB)
//{
//	float cos[3][3];
//	float absCos[3][3];
//	float dist[3];
//	float r0, r1, r;
//	const float cutOff = 0.999999f;
//	bool existsParallelPair = false;
//
//	D3DXVECTOR3 D = otherOBB->m_vCenterPos - this->m_vCenterPos;
//
//	// >> 특이 케이스
//	for (int a = 0; a < 3; a++)
//	{
//		for (int b = 0; b < 3; b++)
//		{
//			cos[a][b] = D3DXVec3Dot(&this->m_vAxisDir[a], &otherOBB->m_vAxisDir[b]);
//			// 두 벡터가 이루는 각을 통해서
//			// 0보다 작으면 90도 보다 큼
//			// 0보다 크면 90도 보다 작음
//
//			absCos[a][b] = abs(cos[a][b]);
//
//			if (absCos[a][b] > cutOff)
//				existsParallelPair = true;	// 직각 or 그 이상
//
//		} // : for_b
//
//		dist[a] = D3DXVec3Dot(&this->m_vAxisDir[a], &D);
//		r = abs(dist[a]);
//
//		r0 = this->m_fAxisHalfLen[a];
//		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[a][0] +
//			otherOBB->m_fAxisHalfLen[1] * absCos[a][1] +
//			otherOBB->m_fAxisHalfLen[2] * absCos[a][2];
//
//		if (r > r0 + r1)
//			return false;
//
//	}	// : for_a
//
//
//	for (int b = 0; b < 3; b++)
//	{
//		r = abs(D3DXVec3Dot(&otherOBB->m_vAxisDir[b], &D));
//
//		r0 = this->m_fAxisHalfLen[0] * absCos[0][b] +
//			this->m_fAxisHalfLen[1] * absCos[1][b] +
//			this->m_fAxisHalfLen[2] * absCos[2][b];
//		r1 = otherOBB->m_fAxisHalfLen[b];
//
//		if (r > r0 + r1)
//			return false;
//	}
//
//	if (existsParallelPair)
//		return true;
//
//	// << 특이 케이스
//
//	// >> 보편적인 케이스
//	// 0 : x축
//	r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
//	r0 = this->m_fAxisHalfLen[0] * absCos[2][0] +
//		this->m_fAxisHalfLen[2] * absCos[0][0];
//	r1 = otherOBB->m_fAxisHalfLen[1] * absCos[1][2] +
//		otherOBB->m_fAxisHalfLen[2] * absCos[1][1];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
//	r0 = this->m_fAxisHalfLen[0] * absCos[2][1] +
//		this->m_fAxisHalfLen[2] * absCos[0][1];
//	r1 = otherOBB->m_fAxisHalfLen[0] * absCos[1][2] +
//		otherOBB->m_fAxisHalfLen[2] * absCos[1][0];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
//	r0 = this->m_fAxisHalfLen[0] * absCos[2][2] +
//		this->m_fAxisHalfLen[2] * absCos[0][2];
//	r1 = otherOBB->m_fAxisHalfLen[0] * absCos[1][1] +
//		otherOBB->m_fAxisHalfLen[1] * absCos[1][0];
//	if (r > r0 + r1) return false;
//
//	// ----------------------------------------------------
//	// 1 : y축
//	r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
//	r0 = this->m_fAxisHalfLen[0] * absCos[1][0] +
//		this->m_fAxisHalfLen[1] * absCos[0][0];
//	r1 = otherOBB->m_fAxisHalfLen[1] * absCos[2][2] +
//		otherOBB->m_fAxisHalfLen[2] * absCos[2][1];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
//	r0 = this->m_fAxisHalfLen[0] * absCos[1][1] +
//		this->m_fAxisHalfLen[1] * absCos[0][1];
//	r1 = otherOBB->m_fAxisHalfLen[0] * absCos[2][2] +
//		otherOBB->m_fAxisHalfLen[2] * absCos[2][0];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
//	r0 = this->m_fAxisHalfLen[0] * absCos[1][2] +
//		this->m_fAxisHalfLen[1] * absCos[0][2];
//	r1 = otherOBB->m_fAxisHalfLen[0] * absCos[2][1] +
//		otherOBB->m_fAxisHalfLen[1] * absCos[2][0];
//	if (r > r0 + r1) return false;
//
//	// ----------------------------------------------------
//	// 2 : z축
//	r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
//	r0 = this->m_fAxisHalfLen[1] * absCos[2][0] +
//		this->m_fAxisHalfLen[2] * absCos[1][0];
//	r1 = otherOBB->m_fAxisHalfLen[1] * absCos[0][2] +
//		otherOBB->m_fAxisHalfLen[2] * absCos[0][1];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
//	r0 = this->m_fAxisHalfLen[1] * absCos[2][1] +
//		this->m_fAxisHalfLen[2] * absCos[1][1];
//	r1 = otherOBB->m_fAxisHalfLen[0] * absCos[0][2] +
//		otherOBB->m_fAxisHalfLen[2] * absCos[0][0];
//	if (r > r0 + r1) return false;
//
//	r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
//	r0 = this->m_fAxisHalfLen[1] * absCos[2][2] +
//		this->m_fAxisHalfLen[2] * absCos[1][2];
//	r1 = otherOBB->m_fAxisHalfLen[0] * absCos[0][1] +
//		otherOBB->m_fAxisHalfLen[1] * absCos[0][0];
//	if (r > r0 + r1) return false;
//	// << 보편적인 케이스
//
//	return true; // 충돌이 일어나지 않음
//}

// KT TEST 
bool COBB::IsCollision(COBB * otherOBB)
{
	// 중심							m_vCenterPos
	// 축							m_vAxisDir[3]
	// 중심에서 OBB면까지의 거리	m_fAxisHalfLen[3]
	float cos[3][3];			//	cos[3][3] = D3DXVec3Dot(pOBB1->m_vOriAxisDir[i], pOBB2->m_vOriAxisDir[j])
	float absCos[3][3];			//	absCos[3][3] = abs(Cos[i][j])
	float dist[3];				//  각 축에 대한 중심벡터의 투영 길이
	float r0, r1, r;			//  구간 반경과 구간 중심점 사이의 거리
	int i;
	// 상자의 축들 사이각들의 consine을 위한 cutoff
	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = otherOBB->m_vCenterPos - this->m_vCenterPos;

	// --------------------------------------------------------------------------------------------------------- //
	// 축 C0 + t * A0
	{
		for (i = 0; i < 3; i++)
		{
			cos[0][i] = D3DXVec3Dot(&this->m_vAxisDir[0], &otherOBB->m_vAxisDir[i]);
			absCos[0][i] = abs(cos[0][i]);
			if (absCos[0][i] > cutOff)
				existsParallelPair = true;
		}
		dist[0] = D3DXVec3Dot(&D, &this->m_vAxisDir[0]);
		r = abs(dist[0]);
		r0 = this->m_fAxisHalfLen[0];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[0][0] + otherOBB->m_fAxisHalfLen[1] * absCos[0][1] + otherOBB->m_fAxisHalfLen[2] * absCos[0][2];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * A1
	{
		for (i = 0; i < 3; i++)
		{
			cos[1][i] = D3DXVec3Dot(&this->m_vAxisDir[1], &otherOBB->m_vAxisDir[i]);
			absCos[1][i] = abs(cos[1][i]);
			if (absCos[1][i] > cutOff)
				existsParallelPair = true;
		}
		dist[1] = D3DXVec3Dot(&D, &this->m_vAxisDir[1]);
		r = abs(dist[1]);
		r0 = this->m_fAxisHalfLen[1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[1][0] + otherOBB->m_fAxisHalfLen[1] * absCos[1][1] + otherOBB->m_fAxisHalfLen[2] * absCos[1][2];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * A2
	{
		for (i = 0; i < 3; i++)
		{
			cos[2][i] = D3DXVec3Dot(&this->m_vAxisDir[2], &otherOBB->m_vAxisDir[i]);
			absCos[2][i] = abs(cos[2][i]);
			if (absCos[2][i] > cutOff)
				existsParallelPair = true;
		}
		dist[2] = D3DXVec3Dot(&D, &this->m_vAxisDir[2]);
		r = abs(dist[2]);
		r0 = this->m_fAxisHalfLen[2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[2][0] + otherOBB->m_fAxisHalfLen[1] * absCos[2][1] + otherOBB->m_fAxisHalfLen[2] * absCos[2][2];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축 C0 + t * B0
	{
		r = abs(D3DXVec3Dot(&D, &otherOBB->m_vAxisDir[0]));
		r0 = this->m_fAxisHalfLen[0] * absCos[0][0] + this->m_fAxisHalfLen[1] * absCos[1][0] + this->m_fAxisHalfLen[2] * absCos[2][0];
		r1 = otherOBB->m_fAxisHalfLen[0];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * B1
	{
		r = abs(D3DXVec3Dot(&D, &otherOBB->m_vAxisDir[1]));
		r0 = this->m_fAxisHalfLen[0] * absCos[0][1] + this->m_fAxisHalfLen[1] * absCos[1][1] + this->m_fAxisHalfLen[2] * absCos[2][1];
		r1 = otherOBB->m_fAxisHalfLen[1];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * B2
	{
		r = abs(D3DXVec3Dot(&D, &otherOBB->m_vAxisDir[2]));
		r0 = this->m_fAxisHalfLen[0] * absCos[0][2] + this->m_fAxisHalfLen[1] * absCos[1][2] + this->m_fAxisHalfLen[2] * absCos[2][2];
		r1 = otherOBB->m_fAxisHalfLen[2];
		if (r > r0 + r1)
			return false;
	}
	if (existsParallelPair)
		return true;
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A0 × B0
	{
		r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
		r0 = this->m_fAxisHalfLen[1] * absCos[2][0] + this->m_fAxisHalfLen[2] * absCos[1][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absCos[0][2] + otherOBB->m_fAxisHalfLen[2] * absCos[0][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A0 × B1
	{
		r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
		r0 = this->m_fAxisHalfLen[1] * absCos[2][1] + this->m_fAxisHalfLen[2] * absCos[1][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[0][2] + otherOBB->m_fAxisHalfLen[2] * absCos[0][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A0 × B2
	{
		r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
		r0 = this->m_fAxisHalfLen[1] * absCos[2][2] + this->m_fAxisHalfLen[2] * absCos[1][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[0][1] + otherOBB->m_fAxisHalfLen[1] * absCos[0][0];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A1 × B0
	{
		r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
		r0 = this->m_fAxisHalfLen[0] * absCos[2][0] + this->m_fAxisHalfLen[2] * absCos[0][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absCos[1][2] + otherOBB->m_fAxisHalfLen[2] * absCos[1][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A1 × B1
	{
		r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
		r0 = this->m_fAxisHalfLen[0] * absCos[2][1] + this->m_fAxisHalfLen[2] * absCos[0][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[1][2] + otherOBB->m_fAxisHalfLen[2] * absCos[1][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A1 × B2
	{
		r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
		r0 = this->m_fAxisHalfLen[0] * absCos[2][2] + this->m_fAxisHalfLen[2] * absCos[0][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[1][1] + otherOBB->m_fAxisHalfLen[1] * absCos[1][0];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A2 × B0
	{
		r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
		r0 = this->m_fAxisHalfLen[0] * absCos[1][0] + this->m_fAxisHalfLen[1] * absCos[0][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absCos[2][2] + otherOBB->m_fAxisHalfLen[2] * absCos[2][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A2 × B1
	{
		r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
		r0 = this->m_fAxisHalfLen[0] * absCos[1][1] + this->m_fAxisHalfLen[1] * absCos[0][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[2][2] + otherOBB->m_fAxisHalfLen[2] * absCos[2][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A2 × B2
	{
		r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
		r0 = this->m_fAxisHalfLen[0] * absCos[1][2] + this->m_fAxisHalfLen[1] * absCos[0][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[2][1] + otherOBB->m_fAxisHalfLen[1] * absCos[2][0];
		if (r > r0 + r1)
			return false;
	}
	return true;
}

bool COBB::IsCollision(COBB * otherOBB, D3DXVECTOR3 * contactNormal, float * penetration)
{
	// 중심							m_vCenterPos
	// 축							m_vAxisDir[3]
	// 중심에서 OBB면까지의 거리	m_fAxisHalfLen[3]
	float cos[3][3];			//	cos[3][3] = D3DXVec3Dot(pOBB1->m_vOriAxisDir[i], pOBB2->m_vOriAxisDir[j])
	float absCos[3][3];			//	absCos[3][3] = abs(Cos[i][j])
	float dist[3];				//  각 축에 대한 중심 사이 벡터의 투영 길이
	float r0, r1, r;			//  구간 반경과 구간 중심점 사이의 거리
	int i;
	// 상자의 축들 사이각들의 consine을 위한 cutoff
	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = otherOBB->m_vCenterPos - this->m_vCenterPos;
	float penetrationTmp = FLT_MAX;
	unsigned best = 0xffffff;

	// --------------------------------------------------------------------------------------------------------- //
	// 축 C0 + t * A0	// 0
	{
		for (i = 0; i < 3; i++)
		{
			cos[0][i] = D3DXVec3Dot(&this->m_vAxisDir[0], &otherOBB->m_vAxisDir[i]);
			absCos[0][i] = abs(cos[0][i]);
			if (absCos[0][i] > cutOff)
				existsParallelPair = true;
		}
		dist[0] = D3DXVec3Dot(&D, &this->m_vAxisDir[0]);
		r = abs(dist[0]);
		r0 = this->m_fAxisHalfLen[0];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[0][0] + otherOBB->m_fAxisHalfLen[1] * absCos[0][1] + otherOBB->m_fAxisHalfLen[2] * absCos[0][2];
		if (r > r0 + r1)
			return false;
		else
		{
			penetrationTmp = r0 + r1 - r;
			best = 0;
		}
	}
	// 축 C0 + t * A1	// 1
	{
		for (i = 0; i < 3; i++)
		{
			cos[1][i] = D3DXVec3Dot(&this->m_vAxisDir[1], &otherOBB->m_vAxisDir[i]);
			absCos[1][i] = abs(cos[1][i]);
			if (absCos[1][i] > cutOff)
				existsParallelPair = true;
		}
		dist[1] = D3DXVec3Dot(&D, &this->m_vAxisDir[1]);
		r = abs(dist[1]);
		r0 = this->m_fAxisHalfLen[1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[1][0] + otherOBB->m_fAxisHalfLen[1] * absCos[1][1] + otherOBB->m_fAxisHalfLen[2] * absCos[1][2];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 1;
			}
		}
	}
	// 축 C0 + t * A2	// 2
	{
		for (i = 0; i < 3; i++)
		{
			cos[2][i] = D3DXVec3Dot(&this->m_vAxisDir[2], &otherOBB->m_vAxisDir[i]);
			absCos[2][i] = abs(cos[2][i]);
			if (absCos[2][i] > cutOff)
				existsParallelPair = true;
		}
		dist[2] = D3DXVec3Dot(&D, &this->m_vAxisDir[2]);
		r = abs(dist[2]);
		r0 = this->m_fAxisHalfLen[2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[2][0] + otherOBB->m_fAxisHalfLen[1] * absCos[2][1] + otherOBB->m_fAxisHalfLen[2] * absCos[2][2];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 2;
			}
		}
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축 C0 + t * B0	// 3
	{
		r = abs(D3DXVec3Dot(&D, &otherOBB->m_vAxisDir[0]));
		r0 = this->m_fAxisHalfLen[0] * absCos[0][0] + this->m_fAxisHalfLen[1] * absCos[1][0] + this->m_fAxisHalfLen[2] * absCos[2][0];
		r1 = otherOBB->m_fAxisHalfLen[0];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 3;
			}
		}
	}
	// 축 C0 + t * B1	// 4
	{
		r = abs(D3DXVec3Dot(&D, &otherOBB->m_vAxisDir[1]));
		r0 = this->m_fAxisHalfLen[0] * absCos[0][1] + this->m_fAxisHalfLen[1] * absCos[1][1] + this->m_fAxisHalfLen[2] * absCos[2][1];
		r1 = otherOBB->m_fAxisHalfLen[1];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 4;
			}
		}
	}
	// 축 C0 + t * B2	// 5
	{
		r = abs(D3DXVec3Dot(&D, &otherOBB->m_vAxisDir[2]));
		r0 = this->m_fAxisHalfLen[0] * absCos[0][2] + this->m_fAxisHalfLen[1] * absCos[1][2] + this->m_fAxisHalfLen[2] * absCos[2][2];
		r1 = otherOBB->m_fAxisHalfLen[2];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 5;
			}
		}
	}
	if (existsParallelPair)
	{
		if (best < 3)
		{
			D3DXVECTOR3 normal;
			normal = this->m_vAxisDir[best];
			if (D3DXVec3Dot(&D, &this->m_vAxisDir[best]) < 0)
				normal = normal * -1.0f;
			contactNormal->x = normal.x;
			contactNormal->y = normal.y;
			contactNormal->z = normal.z;
			*penetration = penetrationTmp;
			return true;
		}
		else if (best < 6)
		{
			D3DXVECTOR3 normal;
			normal = otherOBB->m_vAxisDir[best - 3];
			if (D3DXVec3Dot(&D, &otherOBB->m_vAxisDir[best - 3]) > 0)
				normal = normal * -1.0f;
			contactNormal->x = normal.x;
			contactNormal->y = normal.y;
			contactNormal->z = normal.z;
			*penetration = penetrationTmp;
			return true;
		}
	}

	return true;

	unsigned bestSingleAxis = best;
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A0 × B0	// 6
	{
		r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
		r0 = this->m_fAxisHalfLen[1] * absCos[2][0] + this->m_fAxisHalfLen[2] * absCos[1][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absCos[0][2] + otherOBB->m_fAxisHalfLen[2] * absCos[0][1];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 6;
			}
		}
	}
	// 축C0 + t * A0 × B1	// 7
	{
		r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
		r0 = this->m_fAxisHalfLen[1] * absCos[2][1] + this->m_fAxisHalfLen[2] * absCos[1][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[0][2] + otherOBB->m_fAxisHalfLen[2] * absCos[0][0];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 7;
			}
		}
	}
	// 축C0 + t * A0 × B2	// 8
	{
		r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
		r0 = this->m_fAxisHalfLen[1] * absCos[2][2] + this->m_fAxisHalfLen[2] * absCos[1][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[0][1] + otherOBB->m_fAxisHalfLen[1] * absCos[0][0];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 8;
			}
		}
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A1 × B0	// 9
	{
		r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
		r0 = this->m_fAxisHalfLen[0] * absCos[2][0] + this->m_fAxisHalfLen[2] * absCos[0][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absCos[1][2] + otherOBB->m_fAxisHalfLen[2] * absCos[1][1];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 9;
			}
		}
	}
	// 축C0 + t * A1 × B1	// 10
	{
		r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
		r0 = this->m_fAxisHalfLen[0] * absCos[2][1] + this->m_fAxisHalfLen[2] * absCos[0][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[1][2] + otherOBB->m_fAxisHalfLen[2] * absCos[1][0];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 10;
			}
		}
	}
	// 축C0 + t * A1 × B2	// 11
	{
		r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
		r0 = this->m_fAxisHalfLen[0] * absCos[2][2] + this->m_fAxisHalfLen[2] * absCos[0][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[1][1] + otherOBB->m_fAxisHalfLen[1] * absCos[1][0];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 11;
			}
		}
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A2 × B0	// 12
	{
		r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
		r0 = this->m_fAxisHalfLen[0] * absCos[1][0] + this->m_fAxisHalfLen[1] * absCos[0][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absCos[2][2] + otherOBB->m_fAxisHalfLen[2] * absCos[2][1];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 12;
			}
		}
	}
	// 축C0 + t * A2 × B1	// 13
	{
		r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
		r0 = this->m_fAxisHalfLen[0] * absCos[1][1] + this->m_fAxisHalfLen[1] * absCos[0][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[2][2] + otherOBB->m_fAxisHalfLen[2] * absCos[2][0];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 13;
			}
		}
	}
	// 축C0 + t * A2 × B2	// 14
	{
		r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
		r0 = this->m_fAxisHalfLen[0] * absCos[1][2] + this->m_fAxisHalfLen[1] * absCos[0][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absCos[2][1] + otherOBB->m_fAxisHalfLen[1] * absCos[2][0];
		if (r > r0 + r1)
			return false;
		else
		{
			float p = r0 + r1 - r;
			if (p < penetrationTmp)
			{
				penetrationTmp = p;
				best = 14;
			}
		}
	}

	assert(best != 0xffffff);
	if (best < 3)
	{
		D3DXVECTOR3 normal;
		normal = this->m_vAxisDir[best];
		if (D3DXVec3Dot(&D, &this->m_vAxisDir[best]) < 0)
			normal = normal * -1.0f;
		contactNormal->x = normal.x;
		contactNormal->y = normal.y;
		contactNormal->z = normal.z;
		*penetration = penetrationTmp;
		return true;
	}
	else if (best < 6)
	{
		D3DXVECTOR3 normal;
		normal = otherOBB->m_vAxisDir[best - 3];
		if (D3DXVec3Dot(&D, &otherOBB->m_vAxisDir[best - 3]) > 0)
			normal = normal * -1.0f;
		contactNormal->x = normal.x;
		contactNormal->y = normal.y;
		contactNormal->z = normal.z;
		*penetration = penetrationTmp;
		return true;
	}
	else
	{
		return true;
	}
}

void COBB::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vOBBLineVertex.size() / 2, &m_vOBBLineVertex[0], sizeof(ST_PC_VERTEX));
}