#pragma once

#define g_pFontManager CFontManager::GetInstance()

class CFontManager
{
public:
	enum eFuntType
	{
		E_DEFAULT, E_CABIN
	};
private:
	SingleTone(CFontManager);
	map<eFuntType, LPD3DXFONT>	m_mapFont;
public:
	LPD3DXFONT	GetFont(eFuntType e);
	void Destroy();
};