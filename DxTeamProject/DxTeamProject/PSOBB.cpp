#include "stdafx.h"
#include "PSOBB.h"

CPSOBB::CPSOBB()
{
}

CPSOBB::~CPSOBB()
{
}

void CPSOBB::Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
}

void CPSOBB::Update(D3DXMATRIXA16 * pmatWorld)
{
	if (pmatWorld)
		m_matWorldTM = *pmatWorld;
	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(&m_vAxisDir[i], &m_vOriAxisDir[i], &m_matWorldTM);
	D3DXVec3TransformCoord(&m_vCenterPos, &m_OriCenterPos, &m_matWorldTM);
}

bool CPSOBB::IsCollision(CPSOBB * pOBB1, CPSOBB * pOBB2)
{
	// �߽�						 m_OriCenterPos
	// ��						 m_vOriAxisDir[3]
	// �߽ɿ��� OBB������� �Ÿ� m_fAxisHalfLen[3]

	float C[3][3];		// C[i][j] = D3DXVec3Dot(pOBB1->m_vOriAxisDir[i], pOBB2->m_vOriAxisDir[j])
	float absC[3][3];	// absC[i][j] = abs(C[i][j])
	float d[3];			// d[i] = D3DXVec3Dot(pOBB2->m_OriCenterPos - pOBB1->m_OriCenterPos, pOBB1->m_vOriAxisDir[i])

	// ���� �ݰ�� ���� �߽��� ������ �Ÿ�
	float r0, r1, r;
	int i;

	// ������ ��� ���̰����� cosine�� ���� cutoff
	const float cutoff = 0.999999;
	bool existsParallelPair = false;

	// d�� ���ϰ� ����ϱ� ���� pOBB2->m_OriCenterPos - pOBB1->m_OriCenterPos �̸� ���
	D3DXVECTOR3 diff = pOBB2->m_OriCenterPos - pOBB1->m_OriCenterPos;


	// --------------------------------------------------------------------------------------------------------- //
	// �� C0 + t * A0
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

	// �� C0 + t * A1
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

	// �� C0 + t * A2
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

	// �� C0 + t * B0
	{
		r = abs(D3DXVec3Dot(&diff, &pOBB2->m_vOriAxisDir[0]));
		r0 = pOBB1->m_fAxisHalfLen[0] * absC[0][0] + pOBB1->m_fAxisHalfLen[1] * absC[1][0] + pOBB1->m_fAxisHalfLen[2] * absC[2][0];
		r1 = pOBB2->m_fAxisHalfLen[0];
		if (r > r0 + r1)
			return false;
	}

	// �� C0 + t * B1
	r = abs(D3DXVec3Dot(&diff, &pOBB2->m_vOriAxisDir[1]));
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[0][1] + pOBB1->m_fAxisHalfLen[1] * absC[1][1] + pOBB1->m_fAxisHalfLen[2] * absC[2][1];
	r1 = pOBB2->m_fAxisHalfLen[1];
	if (r > r0 + r1)
		return false;

	// �� C0 + t * B2
	r = abs(D3DXVec3Dot(&diff, &pOBB2->m_vOriAxisDir[2]));
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[0][2] + pOBB1->m_fAxisHalfLen[1] * absC[1][2] + pOBB1->m_fAxisHalfLen[2] * absC[2][2];
	r1 = pOBB2->m_fAxisHalfLen[2];
	if (r > r0 + r1)
		return false;

	if (existsParallelPair)
		return true;

	// --------------------------------------------------------------------------------------------------------- //

	// ��C0 + t * A0 �� B0
	r = abs(d[2] * C[1][0] - d[1] * C[2][0]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absC[2][0] + pOBB1->m_fAxisHalfLen[2] * absC[1][0];
	r1 = pOBB2->m_fAxisHalfLen[1] * absC[0][2] + pOBB2->m_fAxisHalfLen[2] * absC[0][1];
	if (r > r0 + r1)
		return false;

	// ��C0 + t * A0 �� B1
	r = abs(d[2] * C[1][1] - d[1] * C[2][1]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absC[2][1] + pOBB1->m_fAxisHalfLen[2] * absC[1][1];
	r1 = pOBB2->m_fAxisHalfLen[0] * absC[0][2] + pOBB2->m_fAxisHalfLen[2] * absC[0][0];
	if (r > r0 + r1)
		return false;

	// ��C0 + t * A0 �� B2
	r = abs(d[2] * C[1][2] - d[1] * C[2][2]);
	r0 = pOBB1->m_fAxisHalfLen[1] * absC[2][2] + pOBB1->m_fAxisHalfLen[2] * absC[1][2];
	r1 = pOBB2->m_fAxisHalfLen[0] * absC[0][1] + pOBB2->m_fAxisHalfLen[1] * absC[0][0];
	if (r > r0 + r1)
		return false;

	// --------------------------------------------------------------------------------------------------------- //

	// ��C0 + t * A1 �� B0
	r = abs(d[0] * C[2][0] - d[2] * C[0][0]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][0] + pOBB1->m_fAxisHalfLen[2] * absC[0][0];
	r1 = pOBB2->m_fAxisHalfLen[1] * absC[1][2] + pOBB2->m_fAxisHalfLen[2] * absC[1][1];
	if (r > r0 + r1)
		return false;

	// ��C0 + t * A1 �� B1
	r = abs(d[0] * C[2][1] - d[2] * C[0][1]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][1] + pOBB1->m_fAxisHalfLen[2] * absC[0][1];
	r1 = pOBB2->m_fAxisHalfLen[0] * absC[1][2] + pOBB2->m_fAxisHalfLen[2] * absC[1][0];
	if (r > r0 + r1)
		return false;

	// ��C0 + t * A1 �� B2
	r = abs(d[0] * C[2][2] - d[2] * C[0][2]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][2] + pOBB1->m_fAxisHalfLen[2] * absC[0][2];
	r1 = pOBB2->m_fAxisHalfLen[0] * absC[1][1] + pOBB2->m_fAxisHalfLen[1] * absC[1][0];
	if (r > r0 + r1)
		return false;

	// --------------------------------------------------------------------------------------------------------- //

	// ��C0 + t * A1 �� B0
	r = abs(d[0] * C[2][0] - d[2] * C[0][0]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][0] + pOBB1->m_fAxisHalfLen[2] * absC[0][0];
	r1 = pOBB2->m_fAxisHalfLen[1] * absC[1][2] + pOBB2->m_fAxisHalfLen[2] * absC[1][1];
	if (r > r0 + r1)
		return false;

	// ��C0 + t * A1 �� B1
	r = abs(d[0] * C[2][1] - d[2] * C[0][1]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][1] + pOBB1->m_fAxisHalfLen[2] * absC[0][1];
	r1 = pOBB2->m_fAxisHalfLen[0] * absC[1][2] + pOBB2->m_fAxisHalfLen[2] * absC[1][0];
	if (r > r0 + r1)
		return false;

	// ��C0 + t * A1 �� B2
	r = abs(d[0] * C[2][2] - d[2] * C[0][2]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[2][2] + pOBB1->m_fAxisHalfLen[2] * absC[0][2];
	r1 = pOBB2->m_fAxisHalfLen[0] * absC[1][1] + pOBB2->m_fAxisHalfLen[1] * absC[1][0];
	if (r > r0 + r1)
		return false;

	// --------------------------------------------------------------------------------------------------------- //

	// ��C0 + t * A2 �� B0
	r = abs(d[1] * C[0][0] - d[0] * C[1][0]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[1][0] + pOBB1->m_fAxisHalfLen[1] * absC[0][0];
	r1 = pOBB2->m_fAxisHalfLen[1] * absC[2][2] + pOBB2->m_fAxisHalfLen[2] * absC[2][1];
	if (r > r0 + r1)
		return false;

	// ��C0 + t * A2 �� B1
	r = abs(d[1] * C[0][1] - d[0] * C[1][1]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[1][1] + pOBB1->m_fAxisHalfLen[1] * absC[0][1];
	r1 = pOBB2->m_fAxisHalfLen[0] * absC[2][2] + pOBB2->m_fAxisHalfLen[2] * absC[2][0];
	if (r > r0 + r1)
		return false;

	// ��C0 + t * A2 �� B2
	r = abs(d[1] * C[0][2] - d[0] * C[1][2]);
	r0 = pOBB1->m_fAxisHalfLen[0] * absC[1][2] + pOBB1->m_fAxisHalfLen[1] * absC[0][2];
	r1 = pOBB2->m_fAxisHalfLen[0] * absC[2][1] + pOBB2->m_fAxisHalfLen[1] * absC[2][0];
	if (r > r0 + r1)
		return false;

	return true;
}

void CPSOBB::OBBBOX_RENDER()
{
}