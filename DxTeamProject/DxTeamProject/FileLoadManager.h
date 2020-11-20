#pragma once

struct ST_XFile;
class CXfile;

#define g_pFileLoadManager CFileLoadManager::GetInstance()

class CFileLoadManager
{
private:
	CFileLoadManager() { }
	LPD3DXEFFECT LoadShader(const string fileName);

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

	bool FileLoad_XFile(char* szFolder, char* szFile, ST_XFile* setXFile);
	bool FileLoad_Texture(char* szFolder, char* szFile, LPDIRECT3DTEXTURE9& setTexture);
	bool FileLoad_Sprite(char* szFolder, char* szFile, D3DXIMAGE_INFO& imageInfo, LPDIRECT3DTEXTURE9& lpTexture);
	bool FileLoad_Shader(char* szFolder, char* szFile, LPD3DXEFFECT& setShader);
};

