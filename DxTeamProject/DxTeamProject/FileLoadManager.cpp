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
				ReadAndCutSlashR(file, readData);
				mapData.strObjName = readData;
			}

			else if (strstr(readData.c_str(), "# FolderPath"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.strFolderPath = readData;
			}

			else if (strstr(readData.c_str(), "# FilePath"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.strXFilePath = readData;
			}

			else if (strstr(readData.c_str(), "# TxtPath"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.strTxtPath = readData;
			}

			else if (strstr(readData.c_str(), "# ObjectType"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.objType = (ObjectType)atoi(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Scale"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.vScale.x = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.vScale.y = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.vScale.z = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Rotate"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.vRotate.x = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.vRotate.y = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.vRotate.z = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Translate"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.vTranslate.x = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.vTranslate.y = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.vTranslate.z = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Color") && strstr(readData.c_str(), "Tag") == NULL)
			{
				ReadAndCutSlashR(file, readData);
				mapData.dxColor.r = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.dxColor.g = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.dxColor.b = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.dxColor.a = atof(readData.c_str());
			}
			
			// >> colorTag_Background
			else if (strstr(readData.c_str(), "# ColorTag"))
			{
				while (true)
				{
					ReadAndCutSlashR(file, readData);

					if (strstr(readData.c_str(), "#"))
						break;

					mapData.vecColorTag.push_back(readData);
				}
			}

			else if (strstr(readData.c_str(), "# GimmickData"))
			{
				ReadGimmickData(file, readData, mapData);
			}
			else if (strstr(readData.c_str(), "# ConditionName")
				&& (mapData.objType != eG_Door && mapData.objType != eG_DoorFrame && mapData.objType != eG_ColorChanger))
			{
				ReadAndCutSlashR(file , readData);
				mapData.gimmickData.conditionName = readData;
			}

			if (strstr(readData.c_str(), "# Object_End"))
				CObject::CreateObject(mapData);

			// >> mapTest
			if (strstr(readData.c_str(), "# Section"))
				g_pObjectManager->AddMap();
		}
	}

	file.close();
}

void CFileLoadManager::ReadAndCutSlashR(ifstream & file, string & readData)
{
	getline(file, readData);
	if (strstr(readData.c_str(), "\r"))
		readData = readData.substr(0, readData.length() - 1);
}

void CFileLoadManager::ReadGimmickData(ifstream & file, string& readData, ST_MapData & mapData)
{
	while (true)
	{
		getline(file, readData);

		if (strstr(readData.c_str(), "# Object_End"))
			break;

		// >> 회전판자
		if (strstr(readData.c_str(), "# RotationSpeed"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.roationSpeed_rotaitonBoard = atof(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# RotationAxialIndex"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.roationAxialIndex_rotaitonBoard = atoi(readData.c_str());
		}
		// << 회전판자

		// >> 무빙큐브
		else if (strstr(readData.c_str(), "# StartPos"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.startPos_movingCube = atof(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# EndPos"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.endPos_movingCube = atof(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# Speed"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.speed_movingCube = atof(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# DirectionIndex"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.directionIndex_movingCube = atoi(readData.c_str());
		}
		// << 무빙큐브

		// >> 조건변수(문, 컬러레이저)
		else if (strstr(readData.c_str(), "# ConditionName"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.conditionName = readData.c_str();
		}
		else if (strstr(readData.c_str(), "# ConditionIndex"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.onOffConditionIndex = atoi(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# ConditionOrbIndex"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.conditionOrbIndex = atoi(readData.c_str());
		}
		// << 조건변수(문, 컬러레이저)
	}
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

LPDIRECT3DTEXTURE9 CFileLoadManager::GetFileNameTexture(string szFolder, string szFile)
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

	return m_mapTexture[filePath];
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
