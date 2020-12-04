#pragma once
class MeshTile;

class Color_changer
{
public:
	Color_changer();
	~Color_changer();
private:
	D3DXMATRIXA16	m_matS, m_matT, m_matWorld;
	LPD3DXMESH		m_pMesh, m_pBarrel;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_direction;
	D3DMATERIAL9		m_stMtlSphere , m_stMtlSphere2;

	bool istrue;
public:
	
	LPD3DXMESH GetMesh() { return m_pMesh; }
	void Setup();
	void Render();
	void Update();
	

	bool RayCheck(MeshTile& meshtile);
	
	D3DMATERIAL9 GetColor() { return m_stMtlSphere2; }

};

