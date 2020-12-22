#include "stdafx.h"
#include "Xfile.h"
#include "IObject.h"
#include "FileLoadManager.h"

#define StrFilePath(path, folder, file) { path = string(folder) + "/" + string(file); }
#define ErrMessageBox(msg, type) { MessageBoxA(g_hWnd, string(msg).c_str(), string(type).c_str(), MB_OK); }

CFileLoadManager::CFileLoadManager() :
	m_limitX(120),
	m_nowX(0),
	m_nowZ(0),
	m_addNum(30),
	m_addNameNum(0),
	m_thread(NULL),
	m_isThreadRun(0.0f)
{
	InitializeCriticalSection(&m_cs);
}

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
			{
				ResetLoadMapData(mapData);
				continue;
			}

			else if (strstr(readData.c_str(), "# ObjectName"))
			{
				ReadAndCutSlashR(file, readData);

				if (strstr(readData.c_str(), "Orb") == NULL)
					mapData.strObjName = readData + to_string(m_addNameNum);
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
				mapData.vTranslate.x = atof(readData.c_str()) + m_nowX;

				ReadAndCutSlashR(file, readData);
				mapData.vTranslate.y = atof(readData.c_str());

				ReadAndCutSlashR(file, readData);
				mapData.vTranslate.z = atof(readData.c_str()) + m_nowZ;
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

			if (strstr(readData.c_str(), "# GimmickData"))
			{
				ReadGimmickData(file, readData, mapData);
			}
			else if (strstr(readData.c_str(), "# ConditionName")
				&& (mapData.objType != eG_Door && mapData.objType != eG_DoorFrame && mapData.objType != eG_ColorChanger))
			{
				ReadAndCutSlashR(file , readData);

				if (readData != ""
				 && readData != "Black"
				 && readData != "White"
				 && readData != "Yellow"
				 && readData != "Green"
				 && readData != "Red"
				 && readData != "Blue")
					mapData.gimmickData.conditionName = readData + to_string(m_addNameNum);
				else
					mapData.gimmickData.conditionName = readData;

			}
			else if (strstr(readData.c_str(), "# TriggerIndex"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.triggerIndex = atoi(readData.c_str());
			}
			else if (strstr(readData.c_str(), "# ZoneIndex"))
			{
				ReadAndCutSlashR(file, readData);
				mapData.zoneIndex = atoi(readData.c_str());
			}

			if (strstr(readData.c_str(), "# Object_End"))
				CObject::CreateObject(mapData); 
			// m_vecMapdata.push_back(mapData); // thread?

			// >> mapTest
			if (strstr(readData.c_str(), "# Section"))
				g_pObjectManager->AddMap();
		}
	}

	// >> 다음 맵 로드 좌표 설정
	if (m_nowX >= m_limitX)
	{
		m_nowX = 0;
		m_nowZ -= m_addNum;
	}
	else
	{
		m_nowX += m_addNum;
	}
	m_addNameNum++; // 다음 맵 오브젝트 이름 구분
	// << 다음 맵 로드 좌표 설정

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

		else if (strstr(readData.c_str(), "# ConditionName"))
		{
			ReadAndCutSlashR(file, readData);

			if (readData != ""
				&& readData != "Black"
				&& readData != "White"
				&& readData != "Yellow"
				&& readData != "Green"
				&& readData != "Red"
				&& readData != "Blue")
				mapData.gimmickData.conditionName = readData + to_string(m_addNameNum);
			else
				mapData.gimmickData.conditionName = readData;
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

		else if (strstr(readData.c_str(), "# WeightIndex"))
		{
			ReadAndCutSlashR(file, readData);
			mapData.gimmickData.weightIndex = atoi(readData.c_str());
		}
	}
}

void CFileLoadManager::ResetLoadMapData(ST_MapData & mapData)
{
	// basicData
	mapData.strFolderPath = "";
	mapData.strXFilePath = "";
	mapData.strTxtPath = "";
	mapData.strObjName = "";
	mapData.objType = ObjectType::eNull;
	mapData.vScale = D3DXVECTOR3(0, 0, 0);
	mapData.vRotate = D3DXVECTOR3(0, 0, 0);
	mapData.vTranslate = D3DXVECTOR3(0, 0, 0);
	mapData.dxColor = D3DXCOLOR(1, 1, 1, 1);
	mapData.vecColorTag.clear();
	mapData.gimmickData.isData = false;

	// >> gimmickData
	mapData.gimmickData.roationSpeed_rotaitonBoard = 0.0f;
	mapData.gimmickData.roationAxialIndex_rotaitonBoard = 0;
	mapData.gimmickData.weightIndex = 0;
	mapData.gimmickData.maxMassIndex_switch = 0;
	mapData.gimmickData.startPos_movingCube = 0.0f;
	mapData.gimmickData.endPos_movingCube = 0.0f;
	mapData.gimmickData.speed_movingCube = 0.0f;
	mapData.gimmickData.directionIndex_movingCube = 0;
	mapData.gimmickData.onOffConditionIndex = 0;
	mapData.gimmickData.conditionName = "";
	mapData.gimmickData.conditionOrbIndex = 0;
}

//bool CFileLoadManager::CheckThread()
//{
//	bool result = false;
//	if (m_vecThread[0] == NULL)
//	{
//		result = true;
//	}
//	else if (m_vecThread[0]->joinable())
//	{
//		m_vecThread[0]->join();
//		m_vecThread[0] = NULL;
//	}
//
//	return result;
//}

void CFileLoadManager::ThreadFunc(string filePath)
{
	EnterCriticalSection(&m_cs);

	m_vecIsIn.push_back(false);

	LoadData(filePath);

	m_vecIsIn[m_vecIsIn.size() - 1] = true;

	m_vecVecMapdata.push_back(m_vecMapdata);
	CreateObject();
	m_vecMapdata.clear();

	LeaveCriticalSection(&m_cs);
}

void CFileLoadManager::CheckThread()
{
	if (m_vecIsIn[m_nowCnt] == true)
	{
		if (m_vecThread[m_nowCnt]->joinable())
		{
			m_vecThread[m_nowCnt]->join();
			// CreateObject();
			m_nowCnt++;
		}
	}

	if (m_nowCnt == m_threadCnt)
	{
		m_isThreadRun = true;
		// >> todo : 위치변경
		for (int i = 0; i < g_pObjectManager->GetVecObject().size(); i++)
		{
			g_pEventManager->AddListener(g_pObjectManager->GetVecObject()[i]);
		}

		// g_pGameManager->SetNowScene(SceneType::eGameScene);
		g_pGameManager->SetNowScene(SceneType::eMainScene);
	}

	/*if (!check)
	{
		for (int i = 0; i < m_vecIsIn.size(); i++)
		{
			if (m_vecIsIn[i] == true && m_nowCnt == i)
			{
				if (m_vecThread[i]->joinable())
				{
					check = true;
					cout << a++ << endl;
					m_vecThread[i]->join();
					CreateObject();
					m_nowCnt++;
					check = false;
				}
			}
		}
	}

	if (m_nowCnt == m_threadCnt)
		m_isThreadRun = true;*/
}

CFileLoadManager * CFileLoadManager::GetInstance()
{
	static CFileLoadManager instance;
	return &instance;
}

CFileLoadManager::~CFileLoadManager()
{
	for (int i = 0; i < m_vecThread.size(); i++)
	{
		if (m_vecThread[i]->joinable())
			m_vecThread[i]->join();
	}

	vector<thread*>::iterator it;
	for (it = m_vecThread.begin(); it != m_vecThread.end();)
	{
		if (*it != NULL)
		{
			thread* temp = *it;
			it = m_vecThread.erase(it);
			SafeDelete(temp);
		}
	}

	// if (m_thread != NULL)
	// {
	// 	if (m_thread->joinable())
	// 		m_thread->join();
	// }
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

	// ===================================
	// >> thread
	//// >> 기존 버전
	//m_vecVecMapdata.push_back(m_vecMapdata);
	//CreateObject();
	//g_pGameManager->SetNowScene(SceneType::eGameScene);
	//// << 기존 버전

	 // thread* tempTread = NULL;
	 // m_vecThread.push_back(tempTread);
	 // m_vecThread[m_threadCnt] = new thread(&CFileLoadManager::ThreadFunc, this, filePath);
	 // m_threadCnt++;
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

void CFileLoadManager::CreateObject()
{
	m_mutex.lock();

	for (int j = 0; j < m_vecVecMapdata[m_nowCnt].size(); j++)
		IObject::CreateObject(m_vecVecMapdata[m_nowCnt][j]);

	// for (int i = 0; i < m_vecMapdata.size(); i++)
		// IObject::CreateObject(m_vecMapdata[i]);
	// m_vecMapdata.clear();

	m_mutex.unlock();
}