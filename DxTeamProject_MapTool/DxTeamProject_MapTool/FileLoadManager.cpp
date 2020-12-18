#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <fstream>
#include "stdafx.h"
#include "IObject.h"
#include "FileLoadManager.h"
#include "RotationBoard.h"
#include "MovingCube.h"
#include "Door.h"
#include "EventTrigger.h"

#define StrFilePath(path, folder, file) { path = string(folder) + "/" + string(file); }
#define ErrMessageBox(msg, type) { MessageBoxA(g_hWnd, string(msg).c_str(), string(type).c_str(), MB_OK); }

#define nGridSize 30

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

void CFileLoadManager::ReadAndCutSlashR(ifstream & mapFile, string & readData)
{
	getline(mapFile, readData);
	if (strstr(readData.c_str(), "\r"))
		readData = readData.substr(0, readData.length() - 1);
}

void CFileLoadManager::SaveGimmickData(ofstream& file, ST_MapData& mapData)
{
	file << "# GimmickData" << endl;
	if (mapData.objType == ObjectType::eG_RotationBoard)
	{
		file << "# RotationSpeed" << endl;
		file << mapData.gimmickData.roationSpeed_rotaitonBoard << endl;

		file << "# RotationAxialIndex" << endl;
		file << mapData.gimmickData.roationAxialIndex_rotaitonBoard << endl;
	}
	else if (mapData.objType == ObjectType::eG_MovingCube)
	{
		file << "# StartPos" << endl;
		file << mapData.gimmickData.startPos_movingCube << endl;

		file << "# EndPos" << endl;
		file << mapData.gimmickData.endPos_movingCube << endl;

		file << "# Speed" << endl;
		file << mapData.gimmickData.speed_movingCube << endl;

		file << "# DirectionIndex" << endl;
		file << mapData.gimmickData.directionIndex_movingCube << endl;
	}
	else if (mapData.objType == ObjectType::eG_DoorFrame
		|| mapData.objType == ObjectType::eG_Door
		|| mapData.objType == ObjectType::eG_ColorChanger)
	{
		file << "# ConditionName" << endl;
		file << mapData.gimmickData.conditionName << endl;

		file << "# ConditionIndex" << endl;
		file << mapData.gimmickData.onOffConditionIndex << endl;

		file << "# ConditionOrbIndex" << endl;
		file << mapData.gimmickData.conditionOrbIndex << endl;
	}
}

void CFileLoadManager::ReadGimmickData(ifstream & mapFile, string& readData, ST_MapData& mapData)
{
	while (true)
	{
		if (strstr(readData.c_str(), "# Object_End"))
			break;

		ReadAndCutSlashR(mapFile, readData);

		if (strstr(readData.c_str(), "# RotationSpeed"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.roationSpeed_rotaitonBoard = atof(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# RotationAxialIndex"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.roationAxialIndex_rotaitonBoard = atoi(readData.c_str());
		}
		// >> 회전판자

		else if (strstr(readData.c_str(), "# StartPos"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.startPos_movingCube = atof(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# EndPos"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.endPos_movingCube = atof(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# Speed"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.speed_movingCube = atof(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# DirectionIndex"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.directionIndex_movingCube = atoi(readData.c_str());
		}
		// >> 무빙큐브

		else if (strstr(readData.c_str(), "# ConditionName"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.conditionName = readData.c_str();
		}
		else if (strstr(readData.c_str(), "# ConditionIndex"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.onOffConditionIndex = atoi(readData.c_str());
		}
		else if (strstr(readData.c_str(), "# ConditionOrbIndex"))
		{
			ReadAndCutSlashR(mapFile, readData);
			mapData.gimmickData.conditionOrbIndex = atoi(readData.c_str());
		}
	}
}

void CFileLoadManager::ResetMapData(ST_MapData& mapData)
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
	mapData.gimmickData.conditionIndex_switch = 0;
	mapData.gimmickData.maxMassIndex_switch = 0;
	mapData.gimmickData.startPos_movingCube = 0.0f;
	mapData.gimmickData.endPos_movingCube = 0.0f;
	mapData.gimmickData.speed_movingCube = 0.0f;
	mapData.gimmickData.directionIndex_movingCube = 0;
	mapData.gimmickData.onOffConditionIndex = 0;
	mapData.gimmickData.conditionName = "";
	mapData.gimmickData.conditionOrbIndex = 0;
}

void CFileLoadManager::ReadMapData(string fileName)
{
	ifstream mapFile;
	mapFile.open(fileName.c_str(), ios::in | ios::binary);

	int loopCnt = 0;
	if (mapFile.is_open())
	{
		g_pObjectManager->SetPreVecSize(g_pObjectManager->GetVecSize());

		if(m_fNowX == -nGridSize && g_pObjectManager->GetVecObject().size() != 0)
			m_fNowX += m_fAddNumX * 2; // object exist && first load
		else if (m_fNowX < m_fLimitNumX)
			m_fNowX += m_fAddNumX;	// first load, load
		else
		{
			m_fNowZ += m_fAddNumZ;
			m_fNowX = 0;
		}

		ST_MapData mapData;
		string readData;

		while (getline(mapFile, readData))
		{
			if (strstr(readData.c_str(), "# Object_Start"))
			{
				ResetMapData(mapData);
				continue;
			}

			else if (strstr(readData.c_str(), "# ObjectName"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.strObjName = readData;
			}

			else if (strstr(readData.c_str(), "# FolderPath"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.strFolderPath = readData;
			}

			else if (strstr(readData.c_str(), "# FilePath"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.strXFilePath = readData;
			}

			else if (strstr(readData.c_str(), "# TxtPath"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.strTxtPath = readData;
			}

			else if (strstr(readData.c_str(), "# ObjectType"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.objType = (ObjectType)atoi(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Scale"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.vScale.x = atof(readData.c_str());

				ReadAndCutSlashR(mapFile, readData);
				mapData.vScale.y = atof(readData.c_str());

				ReadAndCutSlashR(mapFile, readData);
				mapData.vScale.z = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Rotate"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.vRotate.x = atof(readData.c_str());

				ReadAndCutSlashR(mapFile, readData);
				mapData.vRotate.y = atof(readData.c_str());

				ReadAndCutSlashR(mapFile, readData);
				mapData.vRotate.z = atof(readData.c_str());
			}

			else if (strstr(readData.c_str(), "# Translate"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.vTranslate.x = atof(readData.c_str()) + m_fNowX;

				ReadAndCutSlashR(mapFile, readData);
				mapData.vTranslate.y = atof(readData.c_str());

				ReadAndCutSlashR(mapFile, readData);
				mapData.vTranslate.z = atof(readData.c_str()) + m_fNowZ;
			}

			else if (strstr(readData.c_str(), "# Color") && strstr(readData.c_str(), "Tag") == NULL)
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.dxColor.r = atof(readData.c_str());

				ReadAndCutSlashR(mapFile, readData);
				mapData.dxColor.g = atof(readData.c_str());

				ReadAndCutSlashR(mapFile, readData);
				mapData.dxColor.b = atof(readData.c_str());

				ReadAndCutSlashR(mapFile, readData);
				mapData.dxColor.a = atof(readData.c_str());
			}

			// >> colorTag_Background
			else if (strstr(readData.c_str(), "# ColorTag"))
			{
				// mapData.vecColorTag.clear();

				while (true)
				{
					ReadAndCutSlashR(mapFile, readData);

					if (strstr(readData.c_str(), "#"))
						break;

					mapData.vecColorTag.push_back(readData);
				}
			}

			// >> gimmick
			if (strstr(readData.c_str(), "# GimmickData"))
				ReadGimmickData(mapFile, readData, mapData);
			else if (strstr(readData.c_str(), "# ConditionName") 
				&& (mapData.objType != eG_Door && mapData.objType != eG_DoorFrame && mapData.objType != eG_ColorChanger))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.gimmickData.conditionName = readData;
			}
			else if (strstr(readData.c_str(), "# TriggerIndex"))
			{
				ReadAndCutSlashR(mapFile, readData);
				mapData.triggerIndex = atoi(readData.c_str());
			}

			if (strstr(readData.c_str(), "# Object_End"))
			{
				IObject::CreateObject(mapData);
			}

			else if (strstr(readData.c_str(), "# Section"))
				loopCnt++;
		}
	}

	mapFile.close();

	
	for (int i = 1; i < loopCnt; i++)		
	{
		// >> 한 파일에 여러 맵이 있을 경우 인덱스 계산
		if (m_fNowX < m_fLimitNumX)
			m_fNowX += m_fAddNumX;
		else
		{
			m_fNowZ += m_fAddNumZ;
			m_fNowX = 0;
		}
	}
}

void CFileLoadManager::SaveMapData(string fileName)
{
	ofstream saveFile;
	saveFile.open(fileName.c_str(), ios::out | ios::binary);

	ofstream mapFile;
	mapFile.open("mapData.dat", ios::out | ios::binary);

	if (!mapFile.is_open() || !saveFile.is_open())
		return;

	int saveNum = 0;
	float halfGridNum = nGridSize * 0.5f;
	float addNum = 1.5f; // 그리드 범위 밖 여유 판정

	float minNumX = -halfGridNum - addNum, maxNumX = halfGridNum + addNum;
	float minNumZ = -halfGridNum - addNum, maxNumZ = halfGridNum + addNum;
	int maxIndex = g_pObjectManager->GetVecSize();

	int preNum = 0;
	int checkNum = 0;
	while (saveNum < maxIndex)
	{
		preNum = saveNum;
		for (int i = 0; i < maxIndex; i++)
		{
			D3DXVECTOR3 vPos = g_pObjectManager->GetIObject(i).GetTranslate();
			if (minNumX <= vPos.x && vPos.x <= maxNumX && minNumZ <= vPos.z && vPos.z <= maxNumZ)
			{
				DoFileSave(saveFile, mapFile, i);
				saveNum++;
			}
		}

		if (preNum == saveNum)
			checkNum++;

		if (checkNum >= 9999)
		{
			// << 무한루프 처리
			ErrMessageBox("파일저장에러, 그리드 범위 확인", "ERROR");
			break;
		}

		// >> Next map set
		if (minNumX < m_fLimitNumX)
		{
			minNumX += m_fAddNumX;
			maxNumX += m_fAddNumX;
		}
		else
		{
			minNumX = -halfGridNum;
			maxNumX = halfGridNum;
			minNumZ += m_fAddNumZ;
			maxNumZ += m_fAddNumZ;
		}

		// << Next map set
		FileSave_Section(saveFile);
		FileSave_Section(mapFile);

	} // >> : while

	saveFile.close();
	mapFile.close();
}

ST_MapData CFileLoadManager::SetSaveData(int index)
{
	IObject& vecObject = g_pObjectManager->GetIObject(index);
	ST_MapData mapData;

	mapData.strObjName = vecObject.GetObjectName();

	mapData.strFolderPath = vecObject.GetFolderPath();
	mapData.strXFilePath = vecObject.GetXFilePath();
	mapData.strTxtPath = vecObject.GetXTxtPath();

	mapData.objType = vecObject.GetObjType();
	mapData.vScale = vecObject.GetScale();
	mapData.vRotate = vecObject.GetRotate();
	mapData.vTranslate = vecObject.GetTranslate();

	mapData.dxColor = vecObject.GetColor();

	mapData.vecColorTag = vecObject.GetVecColorTag();

	if (mapData.objType == eG_RotationBoard)
	{
		CRotationBoard* temp = static_cast<CRotationBoard*> (&g_pObjectManager->GetIObject(index));
		mapData.gimmickData.isData = true;
		mapData.gimmickData.roationSpeed_rotaitonBoard = temp->GetRotationSpeed();
		mapData.gimmickData.roationAxialIndex_rotaitonBoard = temp->GetRotationAxialIndex();
	}
	else if(mapData.objType == eG_MovingCube)
	{
		CMovingCube* temp = static_cast<CMovingCube*> (&g_pObjectManager->GetIObject(index));
		mapData.gimmickData.isData = true;
		mapData.gimmickData.startPos_movingCube = temp->GetStartPos();
		mapData.gimmickData.endPos_movingCube = temp->GetEndPos();
		mapData.gimmickData.speed_movingCube = temp->GetSpeed();
		mapData.gimmickData.directionIndex_movingCube = temp->GetDirection();
	}
	else if (mapData.objType == eG_DoorFrame
		  || mapData.objType == eG_Door
		  || mapData.objType == eG_ColorChanger)
	{
		CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
		mapData.gimmickData.isData = true;
		mapData.gimmickData.onOffConditionIndex = temp->GetOpenConditionIndex();
		mapData.gimmickData.conditionName = temp->GetConditionName();
		mapData.gimmickData.conditionOrbIndex = temp->GetConditionOrbIndex();
	}

	else
	{
		mapData.gimmickData.isData = false;

		if (vecObject.GetConditionName() != "")
			mapData.gimmickData.conditionName = vecObject.GetConditionName();
	}

	if (mapData.objType == eTrigger)
	{
		CEventTrigger* temp = static_cast<CEventTrigger*> (&g_pObjectManager->GetIObject(index));
		mapData.triggerIndex = temp->GetTriggerIndex();
	}

	return mapData;
}

void CFileLoadManager::DoFileSave(ofstream & saveFile, ofstream & mapFile, int index)
{
	ST_MapData mapData = SetSaveData(index);
	FileSave(saveFile, mapData);
	FileSave(mapFile, mapData);
}

void CFileLoadManager::FileSave(ofstream& file, ST_MapData& mapData)
{
	file << "# Object_Start" << endl;

	file << "# ObjectName" << endl;
	file << mapData.strObjName << endl;

	file << "# FolderPath" << endl;
	file << mapData.strFolderPath << endl;

	file << "# FilePath" << endl;
	file << mapData.strXFilePath << endl;

	file << "# TxtPath" << endl;
	file << mapData.strTxtPath << endl;

	file << "# ObjectType" << endl;
	file << mapData.objType << endl;

	file << "# Scale" << endl;
	file << mapData.vScale.x << endl << mapData.vScale.y << endl << mapData.vScale.z << endl;

	file << "# Rotate" << endl;
	file << mapData.vRotate.x << endl << mapData.vRotate.y << endl << mapData.vRotate.z << endl;

	file << "# Translate" << endl;
	file << mapData.vTranslate.x << endl << mapData.vTranslate.y << endl << mapData.vTranslate.z << endl;

	file << "# Color" << endl;
	file << mapData.dxColor.r << endl << mapData.dxColor.g << endl << mapData.dxColor.b << endl << mapData.dxColor.a << endl;

	file << "# ColorTag" << endl;
	for (int i = 0; i<mapData.vecColorTag.size(); i++)
		file << mapData.vecColorTag[i] << endl;

	// >> 기믹, 이벤트 트리거 등 오브젝트 타입에 따라 파싱 추가
	if (mapData.gimmickData.isData == true)
	{	
		SaveGimmickData(file, mapData);
	}

	if (mapData.gimmickData.conditionName != ""
	 && (mapData.objType != eG_Door && mapData.objType != eG_DoorFrame && mapData.objType != eG_ColorChanger))
	{
		// >> 두 번 저장 방지
		// >> 조건 오브젝트 저장(쌍방 저장)
		file << "# ConditionName" << endl;
		file << mapData.gimmickData.conditionName << endl;
	}

	if (mapData.objType == eTrigger)
	{
		file << "# TriggerIndex" << endl;
		file << mapData.triggerIndex << endl;
	}

	file << "# Object_End" << endl << endl;
}

void CFileLoadManager::FileSave_Section(ofstream & file)
{
	file << "# Section =======================================" << endl << endl;
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

void CFileLoadManager::Setup()
{
	m_fNowX = -nGridSize;
	m_fNowZ = 0;
	m_fAddNumX = nGridSize;
	m_fAddNumZ = -nGridSize;
	// >> default set

	m_fLimitNumX = 0;

	ifstream file;
	file.open("Resource/mapSetValue.txt", ios::in | ios::binary);

	if (file.is_open())
	{
		ST_MapData mapData;
		string readData;

		while (getline(file, readData))
		{
			/*if (strstr(readData.c_str(), "# addX"))
			{
				getline(file, readData);
				m_fAddNumX = atof(readData.c_str());
			}

			if (strstr(readData.c_str(), "# addZ"))
			{
				getline(file, readData);
				m_fAddNumZ = atof(readData.c_str());
			}*/

			if (strstr(readData.c_str(), "# limitX"))
			{
				getline(file, readData);
				m_fLimitNumX = atof(readData.c_str());
			}

		}

		file.close();
	}
	else
		ErrMessageBox("MapSetting File Open Fail", "ERROR");
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

void CFileLoadManager::SetIndexNumZero()
{
	m_fNowX = -nGridSize;
	m_fNowZ = 0;
}

void CFileLoadManager::SetIndexNumPrev()
{
	if (m_fNowX == -nGridSize && m_fNowZ == 0)
		return;

	bool isCheck = false;
	if (m_fNowX == -nGridSize)
	{
		m_fNowX = m_fLimitNumX;
		isCheck = true;
	}
	else
		m_fNowX -= m_fAddNumX;

	if (isCheck)
		m_fNowZ -= m_fAddNumZ;
}

void CFileLoadManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SafeRelease(it.second);
	}
	m_mapTexture.clear();


	for each(auto it in m_mapShader)
	{
		SafeRelease(it.second);
	}
	m_mapShader.clear();

	for each(auto it in m_mapSprite)
	{
		SafeRelease(it.second.lpTexture);
	}
	m_mapSprite.clear();
}

//D3DXVECTOR3 CFileLoadManager::GetSelectCenterPos(D3DXVECTOR3 vSelect)
//{
//	m_fNowX = -nGridSize;
//	m_fNowZ = 0;
//	m_fAddNumX = nGridSize;
//	m_fAddNumZ = -nGridSize;
//
//	for (int i = 0; i >= m_fNowZ; i -= nGridSize)
//	{
//		for (int j = -nGridSize; j <= m_fLimitNumX; j += nGridSize)
//		{
//			if ((vSelect.x <= j && vSelect.x >= j + nGridSize) 
//			 && (vSelect.z >= i && vSelect.z <= i - nGridSize))
//				return D3DXVECTOR3((j + nGridSize)*0.5f, 0.5f, (i - nGridSize) * 0.5f);
//		}
//	}
//}
