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

	D3DXIMAGE_INFO m_onImageInfo, m_onImageInfo2;

	LPDIRECT3DTEXTURE9 m_pOnTexture, m_pOnTexture2;

	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT Backrc, Startrc , Endrc, BigStartrc , Mainrc, Exitrc , loadrc;
	RECT OnNewrc, PickNewrc;
	RECT imageRC;
	POINT px;
	POINT PX2;

	bool OnButton;
	bool PickButton;
public:
	CScene();
	~CScene();

	void Setup();
	void Render_Main();
	void Render_Ending();
	void Render_Loading();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;
};