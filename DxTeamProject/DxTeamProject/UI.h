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
	D3DXIMAGE_INFO m_textInfo , m_textInfo2, m_textInfo3;	// Grab, Winter, Fall
	D3DXIMAGE_INFO m_textInfo4, m_textInfo5;				// Push, Pull
	D3DXIMAGE_INFO m_textInfo6, m_textInfo7;				// Ctrl, Reset

	D3DXIMAGE_INFO m_brushInfo, m_brushInfo2, m_brushInfo3,	//Brush
		m_brushInfo4, m_brushInfo5, m_brushInfo6, m_brushInfo7;


	LPDIRECT3DTEXTURE9 m_textUI , m_textUI2 , m_textUI3;	// Grab, Winter, Fall
	LPDIRECT3DTEXTURE9 m_textUI4, m_textUI5;				// Push, Pull
	LPDIRECT3DTEXTURE9 m_textUI6, m_textUI7;				// Ctrl, Reset

	LPDIRECT3DTEXTURE9 m_brushCur, m_brushCur2, m_brushCur3, //Brush
		m_brushCur4, m_brushCur5, m_brushCur6, m_brushCur7;


	RECT s_textrc, s_textrc2 , s_textrc3;	// Grab, Winter, Fall
	RECT s_textrc4, s_textrc5;				// Push, Pull
	RECT s_textrc6, s_textrc7;				// Ctrl, Reset
	RECT s_brushrc, s_brushrc2,				//Brush
		s_brushrc3, s_brushrc4,
		s_brushrc5, s_brushrc6,
		s_brushrc7;

	//////////Script
	D3DXIMAGE_INFO m_scriInfo, m_scriInfo2, m_scriInfo3,
		m_scriInfo4, m_scriInfo5, m_scriInfo6,
		m_scriInfo7, m_scriInfo8, m_scriInfo9;

	LPDIRECT3DTEXTURE9 m_scriUI, m_scriUI2, m_scriUI3, 
		m_scriUI4, m_scriUI5, m_scriUI6,
		m_scriUI7, m_scriUI8, m_scriUI9;

	RECT s_scrirc, s_scrirc2, s_scrirc3,	// Black Script
		s_scrirc4, s_scrirc5, s_scrirc6,	// White Script
		s_scrirc7, s_scrirc8, s_scrirc9;	// Yellow Script

	/////////Attain
	D3DXIMAGE_INFO m_attInfo, m_attInfo2, m_attInfo3,
		m_attInfo4, m_attInfo5, m_attInfo6,
		m_attInfo7, m_attInfo8, m_attInfo9, m_attInfo10;

	LPDIRECT3DTEXTURE9 m_attUI, m_attUI2, m_attUI3,
		m_attUI4, m_attUI5, m_attUI6,
		m_attUI7, m_attUI8, m_attUI9, m_attUI10;

	RECT s_attrc, s_attrc2, s_attrc3,
		s_attrc4, s_attrc5, s_attrc6,
		s_attrc7, s_attrc8, s_attrc9,
		s_attrc10;

	POINT pUI;
	POINT px; //눌렀을때
	POINT px2; //움직일때
	POINT px3; //떼었을때
	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT imageRC;
	Color OnButton;
	Pick PickColor;

	float puls;
	bool colorpuls;
	bool BookCol;

	int BlackAlp, BlackAlp2, BlackAlp3;
	bool Blacksw, Blacksw2, Blacksw3;
	bool HasOrb;
	///
	
	float scriptPlus;
	bool is_scriptPlus;
	bool is_scriptBlackOrb, is_scriptWhiteOrb, is_scriptYellowOrb;
	bool CollideWinterZone;
	bool CollideAutumnZone;
	bool HasBlackOrb;
	bool BlackScript[3];
	bool HasWhiteOrb;
	bool WhiteScript[3];
	bool HasYellowOrb;
	bool YellowScript[3];
	bool AttainWinter[2];
	bool AttatinAutumn[2];
public:

	CUI();
	~CUI();
	bool m_isLButtonDown;

	void Setup_UI();
	void UI_Render();
	void Render_Mapname();
	void RenderGrab();
	void RenderPushPull();

	void Setup_Cursor();
	void Render_Cursor();

	void Setup_Script();
	void Render_Script();

	void Setup_Attain();
	void Render_Attain();

	void Update();
	void Script_Update();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;

	Color GetOnButton();
	Pick GetPickColor();
	void SetPickColor();

};