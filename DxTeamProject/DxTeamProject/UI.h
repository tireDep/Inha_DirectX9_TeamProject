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

	RECT UIrc, Backrc, Backrc2, Redrc, Yellowrc, Greenrc, Bluerc , Blackrc, Whiterc;

	////////small
	D3DXIMAGE_INFO m_smallInfo, m_smallInfo2, m_smallInfo3,
		m_smallInfo4, m_smallInfo5, m_smallInfo6;

	LPDIRECT3DTEXTURE9 m_SmallUI, m_SmallUI2, m_SmallUI3,
		m_SmallUI4, m_SmallUI5, m_SmallUI6;

	RECT s_Redrc, s_Yellowrc, s_Greenrc, s_Bluerc, s_Blackrc, s_Whiterc;

	///////////text
	D3DXIMAGE_INFO m_textInfo , m_textInfo2, m_textInfo3;

	LPDIRECT3DTEXTURE9 m_textUI , m_textUI2 , m_textUI3;

	RECT s_textrc, s_textrc2 , s_textrc3;
	
	//////////Script
	D3DXIMAGE_INFO m_scriInfo, m_scriInfo2, m_scriInfo3,
		m_scriInfo4, m_scriInfo5, m_scriInfo6,
		m_scriInfo7, m_scriInfo8, m_scriInfo9;

	LPDIRECT3DTEXTURE9 m_scriUI, m_scriUI2, m_scriUI3, 
		m_scriUI4, m_scriUI5, m_scriUI6,
		m_scriUI7, m_scriUI8, m_scriUI9;

	RECT s_scrirc, s_scrirc2, s_scrirc3,
		s_scrirc4, s_scrirc5, s_scrirc6,
		s_scrirc7, s_scrirc8, s_scrirc9;

	POINT pUI;
	POINT px; //눌렀을때
	POINT px2; //움직일때
	POINT px3; //떼었을때
	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT imageRC;
	Color OnButton;
	Pick PickColor;

	int puls;
	bool colorpuls;
	///
	
public:


	CUI();
	~CUI();
	bool m_isLButtonDown;
	void Setup_UI();
	void UI_Render();
	void Render_Mapname();
	void Setup_Script();
	void Rneder_Script();
	void RenderGrab();
	void Update();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;

	Color GetOnButton();
	Pick GetPickColor();
	void SetPickColor();

};