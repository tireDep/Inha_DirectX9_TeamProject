#pragma once
class COrb
{
private:
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_stImageInfo;

	LPDIRECT3DTEXTURE9 m_pTex0;

	vector<ST_PT_VERTEX> m_vecVertex_Multi;
public:
	COrb();
	~COrb();
	void Setup();
	void Render();
	void Update();
	void SetBillbord();
};

