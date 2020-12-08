#pragma once
class MeshTile;
class COBB;


class Color_changer
{
public:
	Color_changer();
	~Color_changer();
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);
	D3DXMATRIXA16 matWorld , BeamWorld;
	D3DXMATRIXA16 matS, matT , matR;
	D3DXVECTOR3 m_position , m_scale;
	LPD3DXMESH m_pMeshBeam;
	float size;
	float length;
	bool istrue;
	COBB* m_pOBB;
	D3DXVECTOR3 m_vMin, m_vMax;
	// KT
	float m_fHitLength;
public:
	D3DMATERIAL9 m_stMtlSphere2 , m_stMtlSphere;

	void Setup(string folder, string file);
	void Update();
	void Render();
	COBB* GetOBB() { return m_pOBB; }
	bool RayCheck(MeshTile& meshtile);
	D3DXVECTOR3 GetPos() { return m_position; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	
	// KT
	void SetHitLength(float HitLength);
};

