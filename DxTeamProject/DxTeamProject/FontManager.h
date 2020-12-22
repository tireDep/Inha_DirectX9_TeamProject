#pragma once

#define g_pFontManager CFontManager::GetInstance()

class CFontManager
{
public:
	enum eFuntType
	{
		E_DEFAULT, E_CABIN
	};
	LPD3DXFONT	GetFont(eFuntType e);
	void Destroy();
private:
	SingleTone(CFontManager);
	map<eFuntType, LPD3DXFONT>	m_mapFont;
};