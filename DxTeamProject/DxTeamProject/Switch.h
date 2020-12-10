#pragma once

class COBB;

class CSwitch
{
private:
	D3DXMATRIXA16 matS, matT, matWorld , collWorld;
	D3DXVECTOR3 m_position, m_scale;
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	
	//----- √Êµπ
	LPD3DXMESH m_pBox; // CreateBox
	COBB* m_pOBB;
	D3DXVECTOR3 m_vMin, m_vMax;

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);
public:

	//¿·±Ò
	bool istrue;

	CSwitch();
	~CSwitch();
	void Setup(string folder, string file);
	void Update();
	void Render();

	void SetBool(bool set) { istrue = set; }

	COBB* GetOBB() { return m_pOBB; }
};

