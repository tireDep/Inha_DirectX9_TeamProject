#pragma once

class CSkydome
{
private:
	Synthesize_Add_Ref(ID3DXMesh*, m_pMesh, Mesh);
	Synthesize_Add_Ref(ID3DXBuffer*, m_adjBuffer, AdjBuffer);

	Synthesize(DWORD, m_numMtrls, NumMtrl);
	Synthesize(vector<D3DMATERIAL9>, m_vecMtrls, VecMtrls);
	Synthesize(vector<IDirect3DTexture9*>, m_vecTextures, VecTexture);

	void Render_Sky(const D3DXMATRIXA16& matWorld);
public:
	CSkydome();
	~CSkydome();

	void Setup(string folder, string file);
	void Render(D3DXVECTOR3 vCamEye);
};