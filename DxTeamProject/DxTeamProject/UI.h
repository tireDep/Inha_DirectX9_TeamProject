#pragma once
class CUI
{
private:
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_stImageInfo, m_stImageInfo2, m_stImageInfo3;



	LPDIRECT3DTEXTURE9 m_pTextureUI, m_pTextureUI2, m_pTextureUI3;

	POINT pUI;
	POINT px; //��������
	POINT px2; //�����϶�
	POINT px3; //��������
	D3DXMATRIXA16 matT, matWorld;
	int movep, movepy;
	RECT rc, rc2, rc3, rc4;
	RECT imageRC;

	///
	
public:
	CUI();
	~CUI();
	bool m_isLButtonDown;
	void Setup_UI();
	void UI_Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	

};
