#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <fstream>
#include "stdafx.h"
#include "Tile.h" // temp;
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

void CFileLoadManager::ReadMapData(string fileName)
{
	// >> todo : 파싱
	cout << " todo Something_readMap " << endl;
	
	ifstream mapFile;
	mapFile.open(fileName.c_str(), ios::in | ios::binary);

	if (mapFile.is_open())
	{
		ST_MapData mapData;
		string readData;

		while (getline(mapFile, readData))
		{
			if (readData == "# Object_Start")
				continue;

			else if (readData == "# ObjectName")
			{
				getline(mapFile, readData);
				mapData.strObjName = readData;
			}

			else if (readData == "# FolderPath")
			{
				getline(mapFile, readData);
				mapData.strFolderPath = readData;
			}

			else if (readData == "# FilePath")
			{
				getline(mapFile, readData);
				mapData.strXFilePath = readData;
			}

			else if (readData == "# TxtPath")
			{
				getline(mapFile, readData);
				mapData.strTxtPath = readData;
			}

			else if (readData == "# ObjectType")
			{
				getline(mapFile, readData);
				mapData.objType = (ObjectType)atoi(readData.c_str());
			}

			else if (readData == "# Scale")
			{
				getline(mapFile, readData);

				string temp = readData;
				int index = temp.find(",");
				mapData.vScale.x = atof(readData.c_str());

				readData = readData.substr(index + 2, readData.length());
				index = temp.find(",");
				mapData.vScale.y = atof(readData.c_str());

				readData = readData.substr(index + 2, readData.length());
				mapData.vScale.z = atof(readData.c_str());
			}

			else if (readData == "# Rotate")
			{
				getline(mapFile, readData);

				string temp = readData;
				int index = temp.find(",");
				mapData.vRotate.x = atof(readData.c_str());

				readData = readData.substr(index + 2, readData.length());
				index = temp.find(",");
				mapData.vRotate.y = atof(readData.c_str());

				readData = readData.substr(index + 2, readData.length());
				mapData.vRotate.z = atof(readData.c_str());
			}

			else if (readData == "# Translate")
			{
				getline(mapFile, readData);
				string temp = readData;
				int index = temp.find(",");
				mapData.vTranslate.x = atof(readData.c_str());

				readData = readData.substr(index + 2, readData.length());
				index = temp.find(",");
				mapData.vTranslate.y = atof(readData.c_str());

				readData = readData.substr(index + 2, readData.length());
				mapData.vTranslate.z = atof(readData.c_str());
			}

			else if (readData == "# Object_End")
				IObject::CreateObject(mapData);
		}
	}

	mapFile.close();
}

void CFileLoadManager::SaveMapData(string fileName)
{
	// >> todo : 파싱
	cout << " todo Something_saveMap " << endl;

	ofstream mapFile;
	mapFile.open(fileName.c_str(), ios::out | ios::binary);

	if (mapFile.is_open())
	{
		vector<IObject *> vecObject = g_pObjectManager->GetVecObject();
		ST_MapData mapData;

		for (int i = 0; i < vecObject.size(); i++)
		{
			mapData.strObjName = vecObject[i]->GetObjectName();

			mapData.strFolderPath = vecObject[i]->GetFolderPath();
			mapData.strXFilePath = vecObject[i]->GetXFilePath();
			mapData.strTxtPath = vecObject[i]->GetXTxtPath();

			mapData.objType = vecObject[i]->GetObjType();
			mapData.vScale = vecObject[i]->GetScale();
			mapData.vRotate = vecObject[i]->GetRotate();
			mapData.vTranslate = vecObject[i]->GetTranslate();

			mapFile << "# Object_Start" << endl;

			mapFile << "# ObjectName" << endl;
			mapFile << mapData.strObjName << endl;

			mapFile << "# FolderPath" << endl;
			mapFile << mapData.strFolderPath << endl;

			mapFile << "# FilePath" << endl;
			mapFile << mapData.strXFilePath << endl;

			mapFile << "# TxtPath" << endl;
			mapFile << mapData.strTxtPath << endl;

			mapFile << "# ObjectType" << endl;
			mapFile << mapData.objType << endl;

			mapFile << "# Scale" << endl;
			mapFile << mapData.vScale.x << ", " << mapData.vScale.y << ", " << mapData.vScale.z << endl;

			mapFile << "# Rotate" << endl;
			mapFile << mapData.vRotate.x << ", " << mapData.vRotate.y << ", " << mapData.vRotate.z << endl;

			mapFile << "# Translate" << endl;
			mapFile << mapData.vTranslate.x << ", " << mapData.vTranslate.y << ", " << mapData.vTranslate.z << endl;

			mapFile << "# Object_End" << endl << endl;
		}
		mapFile.close();
	}

	mapFile.close();
}

bool CFileLoadManager::CheckDataName(TCHAR * openFileName, string& realName)
{
	string readDataFile;

	std::wstring wStr = openFileName;
	readDataFile = string(wStr.begin(), wStr.end());

	if (strstr(readDataFile.c_str(), ".dat") == NULL)
		readDataFile += ".dat";
	// >> TCHAR -> string

	char *changeFile;
	changeFile = strtok(&readDataFile[0], "\\");

	while (1)
	{
		changeFile = strtok(NULL, "\\");
		if (changeFile == NULL)
		{
			MessageBox(g_hWnd, L"해당 파일을 지원하지 않습니다.", L"파일 열기 실패", MB_OKCANCEL);
			return false;
		}
		if (strstr(changeFile, ".dat"))
		{
			realName = changeFile;
			return true;
		}
	}
}

void CFileLoadManager::FileLoad_OpenMapData()
{
	OPENFILENAME ofn;
	TCHAR strBuffer[128];	// 현재 위치 경로 버퍼
	TCHAR fileName[128] = L"\0";	// 경로 및 파일 이름 버퍼
	TCHAR sFilter[] = L"맵 파일\0*.dat\0"; // "모든 파일\0*.*\0텍스트 파일\0*.txt\0"

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = sFilter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = 128;
	ofn.lpstrInitialDir = _tgetcwd(strBuffer, 128);	// 현재 경로 불러오기
	if (GetOpenFileName(&ofn) != 0)
	{
		string realName;
		if (CheckDataName(fileName, realName))
			ReadMapData(realName);
	}
}

void CFileLoadManager::FileLoad_SaveMapData()
{
	OPENFILENAME ofn;
	TCHAR strBuffer[128];	// 현재 위치 경로 버퍼
	TCHAR fileName[128] = L"\0";	// 경로 및 파일 이름 버퍼
	TCHAR sFilter[] = L"맵 파일\0*.dat\0"; // "모든 파일\0*.*\0텍스트 파일\0*.txt\0"

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = sFilter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = 128;
	ofn.lpstrInitialDir = _tgetcwd(strBuffer, 128);	// 현재 경로 불러오기
	if (GetSaveFileName(&ofn) != 0)
	{
		string realName;
		if (CheckDataName(fileName, realName))
			SaveMapData(realName);
	}
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
			setXFile->vecMtrl.push_back(&mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != NULL)
			{
				IDirect3DTexture9* tex = 0;

				string txtFilePath = string(szFolder) + ("/") + string(mtrls[i].pTextureFilename);
				D3DXCreateTextureFromFileA(g_pD3DDevice, txtFilePath.c_str(), &tex);

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

	if (D3DXCreateTextureFromFileA(g_pD3DDevice, filePath.c_str(), &setTexture))
	{
		ErrMessageBox("Texture Load Error", "ERROR");
		return false;
	}

	return true;
}

bool CFileLoadManager::FileLoad_Sprite(string szFolder, string szFile, D3DXIMAGE_INFO& imageInfo, LPDIRECT3DTEXTURE9& lpTexture)
{
	string filePath;
	StrFilePath(filePath, szFolder, szFile);

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

	return true;
}

bool CFileLoadManager::FileLoad_Shader(string szFolder, string szFile, LPD3DXEFFECT & setShader)
{
	string filePath;;
	StrFilePath(filePath, szFolder, szFile);

	setShader = LoadShader(filePath);

	if (!setShader)
	{
		ErrMessageBox("Shader Load Fail", "Error");
		return false;
	}

	return true;
}
