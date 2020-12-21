#pragma once
#include "IListener.h"


class CScene : public IListener
{
private:
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_stImageInfo, m_stImageInfo2 , m_stImageInfo3, m_stImageInfo4;
	LPDIRECT3DTEXTURE9 m_pTextureScene, m_pTextureScene2, m_pTextureScene3, m_pTextureScene4;

	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT Backrc, Startrc , Endrc, BigStartrc;
	RECT imageRC;
	POINT px;
	POINT PX2;

public:
	CScene();
	~CScene();

	void Setup();
	void Render_Main();
	void Render_Ending();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;
};

