#include "stdafx.h"
#include "PSOBB.h"

CPSOBB::CPSOBB()
{
}

CPSOBB::~CPSOBB()
{
}

void CPSOBB::Setup(CObject & object)
{
	m_matWorld = object.GetmatWorld();

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
	// Check OriCenterPos, OriAxisDir
	for (int i = 0; i < 3; ++i)
		D3DXVec3TransformNormal(&m_vOriAxisDir[i],	&m_vOriAxisDir[i], &m_matWorld);
	D3DXVec3TransformCoord(&m_vOriCenterPos, &m_vOriCenterPos, &m_matWorld);

	object.GetMesh()->UnlockVertexBuffer();
}

void CPSOBB::Update(D3DXMATRIXA16 * pmatWorld)
{
	if (pmatWorld)
		m_matWorld = *pmatWorld;
	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(&m_vOriAxisDir[i], &m_vOriAxisDir[i], &m_matWorld);
	D3DXVec3TransformCoord(&m_vOriCenterPos, &m_vOriCenterPos, &m_matWorld);
}

bool CPSOBB::IsCollision(CPSOBB * pOBB1, CPSOBB * pOBB2)
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
	D3DXVECTOR3 diff = pOBB2->m_vOriCenterPos - pOBB1->m_vOriCenterPos;

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

bool CPSOBB::IsCollision(CPSOBB * otherOBB)
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
	D3DXVECTOR3 diff = otherOBB->m_vOriCenterPos - this->m_vOriCenterPos;

	// --------------------------------------------------------------------------------------------------------- //
	// 축 C0 + t * A0
	{
		for (i = 0; i < 3; i++)
		{
			C[0][i] = D3DXVec3Dot(&this->m_vOriAxisDir[0], &otherOBB->m_vOriAxisDir[i]);
			absC[0][i] = abs(C[0][i]);
			if (absC[0][i] > cutoff)
				existsParallelPair = true;
		}
		d[0] = D3DXVec3Dot(&diff, &this->m_vOriAxisDir[0]);
		r = abs(d[0]);
		r0 = this->m_fAxisHalfLen[0];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[0][0] + otherOBB->m_fAxisHalfLen[1] * absC[0][1] + otherOBB->m_fAxisHalfLen[2] * absC[0][2];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * A1
	{
		for (i = 0; i < 3; i++)
		{
			C[1][i] = D3DXVec3Dot(&this->m_vOriAxisDir[1], &otherOBB->m_vOriAxisDir[i]);
			absC[1][i] = abs(C[1][i]);
			if (absC[1][i] > cutoff)
				existsParallelPair = true;
		}
		d[1] = D3DXVec3Dot(&diff, &this->m_vOriAxisDir[1]);
		r = abs(d[1]);
		r0 = this->m_fAxisHalfLen[1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[1][0] + otherOBB->m_fAxisHalfLen[1] * absC[1][1] + otherOBB->m_fAxisHalfLen[2] * absC[1][2];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * A2
	{
		for (i = 0; i < 3; i++)
		{
			C[2][i] = D3DXVec3Dot(&this->m_vOriAxisDir[2], &otherOBB->m_vOriAxisDir[i]);
			absC[2][i] = abs(C[2][i]);
			if (absC[2][i] > cutoff)
				existsParallelPair = true;
		}
		d[2] = D3DXVec3Dot(&diff, &this->m_vOriAxisDir[2]);
		r = abs(d[2]);
		r0 = this->m_fAxisHalfLen[2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[2][0] + otherOBB->m_fAxisHalfLen[1] * absC[2][1] + otherOBB->m_fAxisHalfLen[2] * absC[2][2];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축 C0 + t * B0
	{
		r = abs(D3DXVec3Dot(&diff, &otherOBB->m_vOriAxisDir[0]));
		r0 = this->m_fAxisHalfLen[0] * absC[0][0] + this->m_fAxisHalfLen[1] * absC[1][0] + this->m_fAxisHalfLen[2] * absC[2][0];
		r1 = otherOBB->m_fAxisHalfLen[0];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * B1
	{
		r = abs(D3DXVec3Dot(&diff, &otherOBB->m_vOriAxisDir[1]));
		r0 = this->m_fAxisHalfLen[0] * absC[0][1] + this->m_fAxisHalfLen[1] * absC[1][1] + this->m_fAxisHalfLen[2] * absC[2][1];
		r1 = otherOBB->m_fAxisHalfLen[1];
		if (r > r0 + r1)
			return false;
	}
	// 축 C0 + t * B2
	{
		r = abs(D3DXVec3Dot(&diff, &otherOBB->m_vOriAxisDir[2]));
		r0 = this->m_fAxisHalfLen[0] * absC[0][2] + this->m_fAxisHalfLen[1] * absC[1][2] + this->m_fAxisHalfLen[2] * absC[2][2];
		r1 = otherOBB->m_fAxisHalfLen[2];
		if (r > r0 + r1)
			return false;
	}
	if (existsParallelPair)
		return true;
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A0 × B0
	{
		r = abs(d[2] * C[1][0] - d[1] * C[2][0]);
		r0 = this->m_fAxisHalfLen[1] * absC[2][0] + this->m_fAxisHalfLen[2] * absC[1][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absC[0][2] + otherOBB->m_fAxisHalfLen[2] * absC[0][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A0 × B1
	{
		r = abs(d[2] * C[1][1] - d[1] * C[2][1]);
		r0 = this->m_fAxisHalfLen[1] * absC[2][1] + this->m_fAxisHalfLen[2] * absC[1][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[0][2] + otherOBB->m_fAxisHalfLen[2] * absC[0][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A0 × B2
	{
		r = abs(d[2] * C[1][2] - d[1] * C[2][2]);
		r0 = this->m_fAxisHalfLen[1] * absC[2][2] + this->m_fAxisHalfLen[2] * absC[1][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[0][1] + otherOBB->m_fAxisHalfLen[1] * absC[0][0];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A1 × B0
	{
		r = abs(d[0] * C[2][0] - d[2] * C[0][0]);
		r0 = this->m_fAxisHalfLen[0] * absC[2][0] + this->m_fAxisHalfLen[2] * absC[0][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absC[1][2] + otherOBB->m_fAxisHalfLen[2] * absC[1][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A1 × B1
	{
		r = abs(d[0] * C[2][1] - d[2] * C[0][1]);
		r0 = this->m_fAxisHalfLen[0] * absC[2][1] + this->m_fAxisHalfLen[2] * absC[0][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[1][2] + otherOBB->m_fAxisHalfLen[2] * absC[1][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A1 × B2
	{
		r = abs(d[0] * C[2][2] - d[2] * C[0][2]);
		r0 = this->m_fAxisHalfLen[0] * absC[2][2] + this->m_fAxisHalfLen[2] * absC[0][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[1][1] + otherOBB->m_fAxisHalfLen[1] * absC[1][0];
		if (r > r0 + r1)
			return false;
	}
	// --------------------------------------------------------------------------------------------------------- //
	// 축C0 + t * A2 × B0
	{
		r = abs(d[1] * C[0][0] - d[0] * C[1][0]);
		r0 = this->m_fAxisHalfLen[0] * absC[1][0] + this->m_fAxisHalfLen[1] * absC[0][0];
		r1 = otherOBB->m_fAxisHalfLen[1] * absC[2][2] + otherOBB->m_fAxisHalfLen[2] * absC[2][1];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A2 × B1
	{
		r = abs(d[1] * C[0][1] - d[0] * C[1][1]);
		r0 = this->m_fAxisHalfLen[0] * absC[1][1] + this->m_fAxisHalfLen[1] * absC[0][1];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[2][2] + otherOBB->m_fAxisHalfLen[2] * absC[2][0];
		if (r > r0 + r1)
			return false;
	}
	// 축C0 + t * A2 × B2
	{
		r = abs(d[1] * C[0][2] - d[0] * C[1][2]);
		r0 = this->m_fAxisHalfLen[0] * absC[1][2] + this->m_fAxisHalfLen[1] * absC[0][2];
		r1 = otherOBB->m_fAxisHalfLen[0] * absC[2][1] + otherOBB->m_fAxisHalfLen[1] * absC[2][0];
		if (r > r0 + r1)
			return false;
	}
	return true;
}

void CPSOBB::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vOBBLineVertex.size() / 2, &m_vOBBLineVertex[0], sizeof(ST_PC_VERTEX));
}