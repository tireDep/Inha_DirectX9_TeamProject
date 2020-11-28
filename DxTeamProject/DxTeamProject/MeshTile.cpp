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

	D3DXMatrixTranslation(&m_matT, 5, 1, 5);
	m_matWorld = m_matT;
}

void MeshTile::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pMesh->DrawSubset(0);
}

D3DXMATRIXA16 MeshTile::GetMatWorld()
{
	return m_matWorld;
}
