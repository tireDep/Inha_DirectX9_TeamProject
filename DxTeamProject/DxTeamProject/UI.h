#pragma once
#include "IListener.h"

class CUI : public IListener
{
private:
	
	LPD3DXSPRITE m_pSprite;
	///////////big
	D3DXIMAGE_INFO m_stImageInfo, m_stImageInfo2, m_stImageInfo3,
		m_stImageInfo4, m_stImageInfo5, m_stImageInfo6, m_stImageInfo7,
		m_stImageInfo8, m_stImageInfo9;

	LPDIRECT3DTEXTURE9 m_pTextureUI, m_pTextureUI2, m_pTextureUI3,
		m_pTextureUI4, m_pTextureUI5, m_pTextureUI6, m_pTextureUI7,
		m_pTextureUI8, m_pTextureUI9;

	////////small
	D3DXIMAGE_INFO m_smallInfo, m_smallInfo2, m_smallInfo3,
		m_smallInfo4, m_smallInfo5, m_smallInfo6;

	LPDIRECT3DTEXTURE9 m_SmallUI, m_SmallUI2, m_SmallUI3,
		m_SmallUI4, m_SmallUI5, m_SmallUI6;

	D3DXIMAGE_INFO m_textInfo;

	LPDIRECT3DTEXTURE9 m_textUI;

	RECT s_Redrc, s_Yellowrc, s_Greenrc, s_Bluerc, s_Blackrc, s_Whiterc;
	RECT s_textrc;

	POINT pUI;
	POINT px; //눌렀을때
	POINT px2; //움직일때
	POINT px3; //떼었을때
	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT UIrc, Backrc, Backrc2, Redrc, Yellowrc, Greenrc, Bluerc , Blackrc, Whiterc;
	RECT imageRC;
	Color OnButton;
	Pick PickColor;
	///
	
public:


	CUI();
	~CUI();
	bool m_isLButtonDown;
	void Setup_UI();
	void UI_Render();
	void RenderGrab();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;

	Color GetOnButton();
	Pick GetPickColor();
	void SetPickColor();

};