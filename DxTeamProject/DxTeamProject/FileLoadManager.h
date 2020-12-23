#pragma once
#include <process.h>
#include <thread>
#include <Windows.h>
#include <mutex>

struct ST_XFile;
struct ST_MapData;
struct ST_Sprite;

#define g_pFileLoadManager CFileLoadManager::GetInstance()

class CFileLoadManager
{
private:
	map<string, LPDIRECT3DTEXTURE9> m_mapTexture; // >> TextureManager Âü°í
	map<string, LPD3DXEFFECT> m_mapShader;
	map<string, ST_Sprite> m_mapSprite;

	LPD3DXEFFECT LoadShader(const string fileName);

	void LoadData(string path);
	void ReadAndCutSlashR(ifstream& file, string& readData);
	void ReadGimmickData(ifstream& file, string& readData, ST_MapData& mapData);

	void ResetLoadMapData(ST_MapData& mapData);
	CFileLoadManager();

	int m_limitX;
	int m_nowX;
	int m_nowZ;
	int m_addNum;
	Synthesize(int, m_xCnt, MapXCnt);
	Synthesize(int, m_addNameNum, FileLoadCnt);

	thread* m_thread;
	CRITICAL_SECTION m_cs;
	mutex m_mutex;
	vector<ST_MapData> m_vecMapdata;
	vector<vector<ST_MapData>> m_vecVecMapdata;
	vector<bool> m_vecIsIn;
	int m_threadCnt = 0;
	int m_nowCnt = 0;
	Synthesize(bool, m_isThreadRun, IsThreadRun);

	vector<thread *> m_vecThread;

public:
	void ThreadFunc(string filePath);
	void CheckThread();
	static CFileLoadManager* GetInstance();
	virtual ~CFileLoadManager();

	bool FileLoad_XFile(string szFolder, string szFile, ST_XFile* setXFile);
	bool FileLoad_Texture(string szFolder, string szFile, LPDIRECT3DTEXTURE9& setTexture);
	bool FileLoad_Sprite(string szFolder, string szFile, D3DXIMAGE_INFO& imageInfo, LPDIRECT3DTEXTURE9& lpTexture);
	bool FileLoad_Shader(string szFolder, string szFile, LPD3DXEFFECT& setShader);

	bool FileLoad_MapData(string szFolder, string szFile);

	LPDIRECT3DTEXTURE9 GetFileNameTexture(string szFolder, string szFile);

	void Destroy();
	void CreateObject();
};