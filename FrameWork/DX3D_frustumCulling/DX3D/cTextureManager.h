#pragma once
#include "stdafx.h"

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	Singletone(cTextureManager);

	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;

public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(string& sFullPath);

	void Destroy();

};