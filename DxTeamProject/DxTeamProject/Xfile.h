#pragma once

class COBB;

class CXfile
{
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9*>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	LPDIRECT3DTEXTURE9 m_pTexture;

	D3DXVECTOR3 m_vScale;
	D3DXVECTOR3 m_vRotate;
	D3DXVECTOR3 m_vTranslate;

	COBB* m_pOBB;

public:
	CXfile();
	~CXfile();
	void Update();
	void Setup();
	void Render(D3DXVECTOR3 eye);
};

