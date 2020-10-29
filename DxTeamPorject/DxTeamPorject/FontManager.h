#pragma once
#include "Singleton.h"

#define g_FontManager CFontManager::GetInstance()

class CFontManager : public CSingleton<CFontManager>
{
public:
	// enum eFontType { eDefault, eQuest };

	LPD3DXFONT GetFont();
	void Destroy();
};

