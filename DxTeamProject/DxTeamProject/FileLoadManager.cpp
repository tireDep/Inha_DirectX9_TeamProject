#include "stdafx.h"
#include "Xfile.h"
#include "IObject.h"
#include "FileLoadManager.h"

#define StrFilePath(path, folder, file) { path = string(folder) + "/" + string(file); }
#define ErrMessageBox(msg, type) { MessageBoxA(g_hWnd, string(msg).c_str(), string(type).c_str(), MB_OK); }

LPD3DXEFFECT CFileLoadManager::LoadShader(const string fileName)
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileA(g_pD3DDevice, fileName.c_str(),
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		// if (ack)
		// {
		// 	char* str = new char[size];
		// 	sprintf(str, (const char*)ack, size);
		// 	OutputDebugString(str);
		// 	delete[] str;
		// }
	}

	return ret;
}

void CFileLoadManager::LoadData(string path)
{
	ifstream file;
	file.open(path.c_str(), ios::in | ios::binary);

	if (file.is_open())
	{
		ST_MapData mapData;
		string readData;

		while (getline(file, readData))
		{
			if (strstr(readData.c_str(), "# Object_Start"))
				continue;

			else if (strstr(readData.c_str(), "# ObjectName"))
			{
				getline(file, readData);
				if(strstr(readData.c_str(), "\r"))
					readData = readData.substr(0, readData.length() - 1);
				mapData.strObjName = readData;
			}

			else if (strstr(readData.c_str(), "# FolderPath"))
			{
				getline(file, readData);
				if (strstr(readData.c_str(), "\r"))
					readData = readData.substr(0, readData.length() - 1);
				mapData.strFolderPath = readData;
			}

			else if (strstr(readData.c_str(), "# FilePath"))
			{
				getline(file, readData);
				if (strstr(readData.c_str(), "\r"))
					readData = readData.substr(0, readData.length() - 1);
				mapData.strXFilePath = readData;
			}

			else if (strstr(readData.c_str(), "# TxtPath"))
			{
				getline(file, readData);
				if (strstr(readData.c_str(), "\r"))
					readData = readData.substr(0, readData.length() - 1);
				mapData.strTxtPath = readData;
			}

			else if (strstr(readData.c_str(), "# ObjectType"))
			{
				getline(file, readData);
				mapData.objType = (ObjectType)atoi(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Scale"))
			{
				getline(file, readData);
				mapData.vScale.x = atof(readData.c_str());

				getline(file, readData);
				mapData.vScale.y = atof(readData.c_str());

				getline(file, readData);
				mapData.vScale.z = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Rotate"))
			{
				getline(file, readData);
				mapData.vRotate.x = atof(readData.c_str());

				getline(file, readData);
				mapData.vRotate.y = atof(readData.c_str());

				getline(file, readData);
				mapData.vRotate.z = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Translate"))
			{
				getline(file, readData);
				mapData.vTranslate.x = atof(readData.c_str());

				getline(file, readData);
				mapData.vTranslate.y = atof(readData.c_str());

				getline(file, readData);
				mapData.vTranslate.z = atof(readData.c_str());
			}

			else if (readData == "# Color")
			{
				getline(file, readData);
				mapData.dxColor.r = atof(readData.c_str());

				getline(file, readData);
				mapData.dxColor.g = atof(readData.c_str());

				getline(file, readData);
				mapData.dxColor.b = atof(readData.c_str());

				getline(file, readData);
				mapData.dxColor.a = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(),  "# GimmickData"))
				continue;

			else if (strstr(readData.c_str(), "# RotationSpeed"))
			{
				getline(file, readData);
				mapData.gimmickData.roationSpeed = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# RotationAxialIndex"))
			{
				getline(file, readData);
				mapData.gimmickData.roationAxialIndex = atoi(readData.c_str());
			}


			else if (strstr(readData.c_str(), "# Object_End"))
				CObject::CreateObject(mapData);

			// >> mapTest
			else if (strstr(readData.c_str(), "# Section"))
				g_pObjectManager->AddMap();
		}
	}

	file.close();
}


CFileLoadManager * CFileLoadManager::GetInstance()
{
	static CFileLoadManager instance;
	return &instance;
}

bool CFileLoadManager::FileLoad_XFile(string szFolder, string szFile, ST_XFile* setXFile)
{
	string filePath;
	StrFilePath(filePath, szFolder, szFile);

	HRESULT hr = D3DXLoadMeshFromXA(filePath.c_str(), D3DXMESH_MANAGED, g_pD3DDevice,
		&setXFile->adjBuffer, &setXFile->mtrlBuffer, 0, &setXFile->nMtrlNum, &setXFile->pMesh);

	if (FAILED(hr))
	{
		ErrMessageBox("XFile Load Error", "ERROR");
		return false;
	}

	// >> mtrl, texture
	if (setXFile->mtrlBuffer != 0 && setXFile->nMtrlNum != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)setXFile->mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < setXFile->nMtrlNum; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			setXFile->vecMtrl.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != NULL)
			{
				IDirect3DTexture9* tex = 0;

				string txtFilePath = string(szFolder) + ("/") + string(mtrls[i].pTextureFilename);
				FileLoad_Texture(szFolder, mtrls[i].pTextureFilename, tex);
				setXFile->vecTextrure.push_back(tex);
			}
			else
				setXFile->vecTextrure.push_back(0);
		}

		SafeRelease(setXFile->mtrlBuffer);
	}

	return true;
}

bool CFileLoadManager::FileLoad_Texture(string szFolder, string szFile, LPDIRECT3DTEXTURE9 & setTexture)
{
	string filePath;
	StrFilePath(filePath, szFolder, szFile);

	if (m_mapTexture.find(filePath) == m_mapTexture.end())
	{
		if (D3DXCreateTextureFromFileA(g_pD3DDevice, filePath.c_str(), &m_mapTexture[filePath.c_str()]))
		{
			ErrMessageBox("Texture Load Error", "ERROR");
			return false;
		}
	}

	setTexture = m_mapTexture[filePath];

	return true;
}

bool CFileLoadManager::FileLoad_Sprite(string szFolder, string szFile, D3DXIMAGE_INFO& imageInfo, LPDIRECT3DTEXTURE9& lpTexture)
{
	string filePath;
	StrFilePath(filePath, szFolder, szFile);

	if (m_mapSprite.find(filePath) == m_mapSprite.end())
	{
		if (D3DXCreateTextureFromFileExA(g_pD3DDevice,
			filePath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED, D3DX_FILTER_NONE
			, D3DX_DEFAULT, 0, &imageInfo, NULL, &lpTexture))
		{
			ErrMessageBox("Sprite Load Error", "ERROR");
			return false;
		}

		ST_Sprite spriteInfo;
		spriteInfo.imageInfo = imageInfo;
		spriteInfo.lpTexture = lpTexture;

		m_mapSprite[filePath] = spriteInfo;
	}

	imageInfo = m_mapSprite[filePath].imageInfo;
	lpTexture = m_mapSprite[filePath].lpTexture;

	return true;
}

bool CFileLoadManager::FileLoad_Shader(string szFolder, string szFile, LPD3DXEFFECT & setShader)
{
	string filePath;
	StrFilePath(filePath, szFolder, szFile);

	if (m_mapShader.find(filePath) == m_mapShader.end())
	{
		setShader = LoadShader(filePath);

		if (!setShader)
		{
			ErrMessageBox("Shader Load Fail", "Error");
			return false;
		}

		m_mapShader[filePath] = setShader;
	}

	setShader = m_mapShader[filePath];

	return true;
}

bool CFileLoadManager::FileLoad_MapData(string szFolder, string szFile)
{
	string filePath;
	StrFilePath(filePath, szFolder, szFile);
	LoadData(filePath);

	return true;
}

void CFileLoadManager::Destroy()
{
	for each(auto it in m_mapTexture)
		SafeRelease(it.second);

	for each(auto it in m_mapShader)
		SafeRelease(it.second);

	for each(auto it in m_mapSprite)
		SafeRelease(it.second.lpTexture);

	m_mapTexture.clear();
	m_mapShader.clear();
	m_mapSprite.clear();
}
