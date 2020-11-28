#pragma once
#include "Singleton.h"

struct ST_XFile;
struct ST_MapData;

#define g_pFileLoadManager CFileLoadManager::GetInstance()

class CFileLoadManager : public CSingleton<CFileLoadManager>
{
private:
	vector<int> m_vecFileIndex;

	float m_fNowX;
	float m_fNowZ;
	float m_fAddNumX;
	float m_fAddNumZ;
	float m_fLimitNumX;

	bool CheckDataName(TCHAR* openFileName, string& realName);
	void ReadMapData(string fileName);
	void SaveMapData(string fileName);

	void DoFileSave(int index);
	void FileSave(ofstream& file, const ST_MapData& mapData);
	void FileSave_Section(ofstream& file);

	LPD3DXEFFECT LoadShader(const string fileName);

public:
	void Setup();

	void FileLoad_OpenMapData();
	void FileLoad_SaveMapData();

	bool FileLoad_XFile(string szFolder, string szFile, ST_XFile* setXFile);
	bool FileLoad_Texture(string szFolder, string szFile, LPDIRECT3DTEXTURE9& setTexture);
	bool FileLoad_Sprite(string szFolder, string szFile, D3DXIMAGE_INFO& imageInfo, LPDIRECT3DTEXTURE9& lpTexture);
	bool FileLoad_Shader(string szFolder, string szFile, LPD3DXEFFECT& setShader);

	void SetIndexNumZero();
};

