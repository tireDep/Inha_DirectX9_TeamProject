#pragma once
#include "Singleton.h"

struct ST_XFile;
struct ST_MapData;

#define g_pFileLoadManager CFileLoadManager::GetInstance()

class CFileLoadManager : public CSingleton<CFileLoadManager>
{
private:
	bool CheckDataName(TCHAR* openFileName, string& realName);
	void ReadMapData(string fileName);
	void SaveMapData(string fileName);

	void FileSave(ofstream& file, const ST_MapData& mapData);

	LPD3DXEFFECT LoadShader(const string fileName);

public:
	void FileLoad_OpenMapData();
	void FileLoad_SaveMapData();

	bool FileLoad_XFile(string szFolder, string szFile, ST_XFile* setXFile);
	bool FileLoad_Texture(string szFolder, string szFile, LPDIRECT3DTEXTURE9& setTexture);
	bool FileLoad_Sprite(string szFolder, string szFile, D3DXIMAGE_INFO& imageInfo, LPDIRECT3DTEXTURE9& lpTexture);
	bool FileLoad_Shader(string szFolder, string szFile, LPD3DXEFFECT& setShader);
};

