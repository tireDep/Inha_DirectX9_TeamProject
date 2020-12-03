#pragma once
class MeshTile
{
public:
	MeshTile();
	~MeshTile();
private:
	D3DXMATRIXA16	m_matS, m_matT, m_matWorld;
	LPD3DXMESH		m_pMesh;
	D3DMATERIAL9	m_stMtlSphere , m_stMtlSphere2;
	bool color;
public:
	void Setup();
	LPD3DXMESH GetMesh() { return m_pMesh; }
	void Render();
	D3DXMATRIXA16 GetMatWorld();
	void Update();
	void SetColor(bool istrue) { color = istrue; }
	
};