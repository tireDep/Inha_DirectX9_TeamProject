#pragma once
#include "IListener.h"

class CScene : public IListener
{
private:
	LPD3DXSPRITE m_pSprite;

	D3DXIMAGE_INFO m_stImageInfo, m_stImageInfo2 , m_stImageInfo3, m_stImageInfo4,
		m_stImageInfo5, m_stImageInfo6;
	LPDIRECT3DTEXTURE9 m_pTextureScene, m_pTextureScene2, m_pTextureScene3, m_pTextureScene4,
		m_pTextureScene5, m_pTextureScene6;

	D3DXIMAGE_INFO m_stLoading;
	LPDIRECT3DTEXTURE9 m_pLoading;

	D3DXIMAGE_INFO m_onImageInfo, m_onImageInfo2, m_onImageInfo3, m_onImageInfo4
		, m_onImageInfo5, m_onImageInfo6;

	LPDIRECT3DTEXTURE9 m_pOnTexture, m_pOnTexture2, m_pOnTexture3, m_pOnTexture4
		, m_pOnTexture5, m_pOnTexture6;

	D3DXIMAGE_INFO	m_CurImageInfo;

	LPDIRECT3DTEXTURE9 m_pCurTexture;

	D3DXIMAGE_INFO	m_EndInfo;

	LPDIRECT3DTEXTURE9 m_EndTexture;


	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT Backrc, Startrc , Endrc, BigStartrc , Mainrc, Exitrc , loadrc;
	RECT OnNewrc, OnNewrc2, OnNewrc3;
	RECT PickNewrc, PickNewrc2, PickNewrc3;
	RECT Currc , Textrc;
	RECT imageRC;
	POINT px;
	POINT PX2;

	bool OnButton, OnButton2, OnButton3;
	bool PickButton, PickButton2, PickButton3;
	bool TextOn , colorpuls;
	int Alpha;
	float Alpha2;
	float endY;
	float Plus;
public:
	CScene();
	~CScene();

	void Setup();
	void Render_Main();
	void Render_Ending();
	void Update();
	void Render_Loading();
	
	void Cur_Setup();
	void Render_Cur();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;
};