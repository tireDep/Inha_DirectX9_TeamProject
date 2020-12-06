#include "stdafx.h"
#include "IObject.h"
#include "OBB.h"

COBB::COBB()
{
}

COBB::~COBB()
{
}

void COBB::Setup(IObject* object)
{
	m_matWorld = object->GetmatWorld();

	D3DXVECTOR3* pVertices;
	object->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);

	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXComputeBoundingBox(pVertices, object->GetMesh()->GetNumVertices(),
		object->GetMesh()->GetNumBytesPerVertex(), &m_vMin, &m_vMax);

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
		// OBB Box Triangle Point
		{
		// front
		vecIndex.push_back(7);
		vecIndex.push_back(6);
		vecIndex.push_back(5);
		
		vecIndex.push_back(7);
		vecIndex.push_back(5);
		vecIndex.push_back(4);

		// back
		vecIndex.push_back(0);
		vecIndex.push_back(1);
		vecIndex.push_back(2);

		vecIndex.push_back(0);
		vecIndex.push_back(2);
		vecIndex.push_back(3);

		// left
		vecIndex.push_back(4);
		vecIndex.push_back(5);
		vecIndex.push_back(1);

		vecIndex.push_back(4);
		vecIndex.push_back(1);
		vecIndex.push_back(0);

		// right
		vecIndex.push_back(3);
		vecIndex.push_back(2);
		vecIndex.push_back(6);

		vecIndex.push_back(3);
		vecIndex.push_back(6);
		vecIndex.push_back(7);

		// top
		vecIndex.push_back(1);
		vecIndex.push_back(5);
		vecIndex.push_back(6);

		vecIndex.push_back(1);
		vecIndex.push_back(6);
		vecIndex.push_back(2);

		// bottom
		vecIndex.push_back(4);
		vecIndex.push_back(0);
		vecIndex.push_back(3);

		vecIndex.push_back(4);
		vecIndex.push_back(3);
		vecIndex.push_back(7);

		for (int i = 0; i < vecIndex.size(); i++)
			m_vecVertex.push_back(vecVertex[vecIndex[i]]);
	}

		vecIndex.clear();
		// OBB Box Line
		{
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
		}

		m_vecOBBLineVertex.resize(vecIndex.size());
		for (int i = 0; i < vecIndex.size(); i+=3)
		{
			m_vecOBBLineVertex[i + 0].p = vecVertex[vecIndex[i + 0]];
			m_vecOBBLineVertex[i + 1].p = vecVertex[vecIndex[i + 1]];
			m_vecOBBLineVertex[i + 2].p = vecVertex[vecIndex[i + 2]];

			m_vecOBBLineVertex[i + 0].c = D3DXCOLOR(1, 0, 0, 1);
			m_vecOBBLineVertex[i + 1].c = D3DXCOLOR(1, 0, 0, 1);
			m_vecOBBLineVertex[i + 2].c = D3DXCOLOR(1, 0, 0, 1);
		}
	}

	// Check OriCenterPos, OriAxisDir
	for (int i = 0; i < 3; ++i)
		D3DXVec3TransformNormal(&m_vOriAxisDir[i], &m_vOriAxisDir[i], &m_matWorld);
	D3DXVec3TransformCoord(&m_vOriCenterPos, &m_vOriCenterPos, &m_matWorld);

	object->GetMesh()->UnlockVertexBuffer();
}

void COBB::Update(D3DXMATRIXA16 * pmatWorld)
{
	if (pmatWorld)
		m_matWorld = *pmatWorld;

	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(&m_vOriAxisDir[i], &m_vOriAxisDir[i], &m_matWorld);

	D3DXVec3TransformCoord(&m_vOriCenterPos, &m_vOriCenterPos, &m_matWorld);
}

void COBB::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecOBBLineVertex.size() / 2, &m_vecOBBLineVertex[0], sizeof(ST_PC_VERTEX));
}

vector<D3DXVECTOR3> COBB::GetOBBVertex()
{
	return m_vecVertex;
}
