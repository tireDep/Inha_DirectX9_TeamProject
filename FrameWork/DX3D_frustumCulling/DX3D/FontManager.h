#pragma once

#define g_pFontManager CFontManager::GetInstance()

class CFontManager
{
public:
	enum eFontType { E_DEFAULT, E_QUEST };

private:
	Singletone(CFontManager);
	map<eFontType, LPD3DXFONT> m_mapFont;

public:
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();

};

