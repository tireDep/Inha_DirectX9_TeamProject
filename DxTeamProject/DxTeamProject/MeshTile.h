#pragma once

class COBB;

class MeshTile
{
public:
	MeshTile();
	~MeshTile();
private:
	D3DXMATRIXA16	m_matS, m_matT, m_matWorld , obbWorld;
	D3DXVECTOR3 m_pos;
	LPD3DXMESH		m_pMesh;
	D3DMATERIAL9	m_stMtlSphere , m_stMtlSphere2;
	COBB* m_pOBB;
public:
	void Setup(float x, float y, float z);
	LPD3DXMESH GetMesh() { return m_pMesh; }
	void Render();
	D3DXMATRIXA16 GetMatWorld();
	void Update();
	COBB* GetOBB() { return m_pOBB; }
	D3DXVECTOR3 GetPos() { return m_pos;  }
	void SetColor(D3DMATERIAL9 color) { m_stMtlSphere2 = color; }
	
};