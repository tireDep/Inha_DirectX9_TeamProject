#pragma once
class CScene
{
private:
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_stImageInfo, m_stImageInfo2 , m_stImageInfo3;
	LPDIRECT3DTEXTURE9 m_pTextureScene, m_pTextureScene2, m_pTextureScene3;

	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT Backrc, Startrc , Endrc;
	RECT imageRC;
public:
	CScene();
	~CScene();

	void Setup();
	void Render_Main();
	void Render_Ending();
};

