#pragma once

struct ST_XFile;
struct ST_MapData;

#define g_pFileLoadManager CFileLoadManager::GetInstance()

class CFileLoadManager
{
private:
	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
	// >> TextureManager Âü°í

	CFileLoadManager() { }
	LPD3DXEFFECT LoadShader(const string fileName);

	void LoadData(string path);

public:
	static CFileLoadManager* GetInstance();
	virtual ~CFileLoadManager() { }

	/*
	// >> todo
	// >> xfile(skinnedMesh) : animation xFile
	// >> saveData_Player(start play) : saveData
	// >> mapData(start Play) : mapData
	// >> script(Story) : text
	*/

	bool FileLoad_XFile(string szFolder, string szFile, ST_XFile* setXFile);
	bool FileLoad_Texture(string szFolder, string szFile, LPDIRECT3DTEXTURE9& setTexture);
	bool FileLoad_Sprite(string szFolder, string szFile, D3DXIMAGE_INFO& imageInfo, LPDIRECT3DTEXTURE9& lpTexture);
	bool FileLoad_Shader(string szFolder, string szFile, LPD3DXEFFECT& setShader);

	bool FileLoad_MapData(string szFolder, string szFile);

	void Destroy();
};

