#pragma once
#include "Singleton.h"

struct ST_XFile;
struct ST_MapData;
struct ST_Sprite;

#define g_pFileLoadManager CFileLoadManager::GetInstance()

class CFileLoadManager : public CSingleton<CFileLoadManager>
{
private:
	float m_fNowX;
	float m_fNowZ;
	float m_fAddNumX;
	float m_fAddNumZ;
	float m_fLimitNumX;

	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
	// >> Texture Manager 참고
	// - 매번 생성하면 메모리 문제 있어서 한 번 로드 후 그 텍스쳐 반환

	map<string, LPD3DXEFFECT> m_mapShader;
	map<string, ST_Sprite> m_mapSprite;

	bool CheckDataName(TCHAR* openFileName, string& realName);
	void ReadMapData(string fileName);
	void SaveMapData(string fileName);

	ST_MapData SetSaveData(int index);
	void DoFileSave(ofstream& saveFile, ofstream& mapFile, int index);
	void FileSave(ofstream& file, ST_MapData& mapData);
	void FileSave_Section(ofstream& file);

	LPD3DXEFFECT LoadShader(const string fileName);

	void ReadAndCutSlashR(ifstream& mapFile, string& readData);

	void SaveGimmickData(ofstream& file, ST_MapData& mapData);
	void ReadGimmickData(ifstream& mapFile, string& readData, ST_MapData& mapData);

	void ResetMapData(ST_MapData& mapData);

public:
	void Setup();

	void FileLoad_OpenMapData();
	void FileLoad_SaveMapData();

	bool FileLoad_XFile(string szFolder, string szFile, ST_XFile* setXFile);
	bool FileLoad_Texture(string szFolder, string szFile, LPDIRECT3DTEXTURE9& setTexture);
	bool FileLoad_Sprite(string szFolder, string szFile, D3DXIMAGE_INFO& imageInfo, LPDIRECT3DTEXTURE9& lpTexture);
	bool FileLoad_Shader(string szFolder, string szFile, LPD3DXEFFECT& setShader);

	void SetIndexNumZero();
	void SetIndexNumPrev();

	// D3DXVECTOR3 GetSelectCenterPos(D3DXVECTOR3 vSelect);

	void Destroy();
};

