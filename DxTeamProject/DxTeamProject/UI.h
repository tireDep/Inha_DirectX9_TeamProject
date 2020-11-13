#pragma once
#include "IListener.h"

class CUI : public IListener
{
private:
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_stImageInfo, m_stImageInfo2, m_stImageInfo3;

	LPDIRECT3DTEXTURE9 m_pTextureUI, m_pTextureUI2, m_pTextureUI3;

	POINT pUI;
	POINT px; //눌렀을때
	POINT px2; //움직일때
	POINT px3; //떼었을때
	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT rc, rc2, rc3, rc4;
	RECT imageRC;
	bool OnRedButton;
	bool PickRed;
	///
	
public:
	CUI();
	~CUI();
	bool m_isLButtonDown;
	void Setup_UI();
	void UI_Render();

	void ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam) override;
	string GetName() override;

	bool GetOnButton();
	bool GetPickColor();
};