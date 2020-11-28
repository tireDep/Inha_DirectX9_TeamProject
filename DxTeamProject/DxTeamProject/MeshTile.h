#pragma once
class MeshTile
{
public:
	MeshTile();
	~MeshTile();
private:
	D3DXMATRIXA16	m_matS, m_matT, m_matWorld;
	LPD3DXMESH		m_pMesh;
public:
	void Setup();
	LPD3DXMESH GetMesh() { return m_pMesh; }
	void Render();
	D3DXMATRIXA16 GetMatWorld();
};