#include "stdafx.h"
#include "MeshTile.h"

MeshTile::MeshTile()
	: m_pMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

MeshTile::~MeshTile()
{
	SafeRelease(m_pMesh);
}

void MeshTile::Setup()
{
	D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);

	D3DXMatrixTranslation(&m_matT, 8, 1, 8);
	D3DXMatrixScaling(&m_matS, 10, 0.2f, 10);
	m_matWorld = m_matS * m_matT;

	DWORD dwVertexNum = m_pMesh->GetNumVertices();

	LPDIRECT3DVERTEXBUFFER9 pVB;
	m_pMesh->GetVertexBuffer(&pVB);
	float* pVertices;

	pVB->Lock(0, sizeof(m_pMesh->GetNumBytesPerVertex()) * m_pMesh->GetNumVertices(), (void**)&pVertices, 0);
	for (DWORD i = 0; i < dwVertexNum * 6; i += 3)
	{
		pVertices[i	   ] *= m_matS._11;		pVertices[i]     += m_matT._41;
		pVertices[i + 1] *= m_matS._22;		pVertices[i + 1] += m_matT._42;
		pVertices[i + 2] *= m_matS._33;		pVertices[i + 2] += m_matT._43;
	}
	pVB->Unlock();
}

void MeshTile::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pMesh->DrawSubset(0);
}

D3DXMATRIXA16 MeshTile::GetMatWorld()
{
	return m_matWorld;
}
