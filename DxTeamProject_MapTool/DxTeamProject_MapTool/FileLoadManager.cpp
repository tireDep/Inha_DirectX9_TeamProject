#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <fstream>
#include "stdafx.h"
#include "Tile.h" // temp;
#include "FileLoadManager.h"

void CFileLoadManager::ReadMapData(string fileName)
{
	// >> todo : �Ľ�
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

			else if (readData == "# FilePath")
			{
				getline(mapFile, readData);
				mapData.strFilePath = readData;
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
			{
				CTile* temp = new CTile;
				temp->Setup(mapData);

				cout << "todo : load File" << endl;
			}
		}
	}

	mapFile.close();
}

void CFileLoadManager::SaveMapData(string fileName)
{
	// >> todo : �Ľ�
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
			mapData.strFilePath = vecObject[i]->GetFilePath();
			mapData.objType = vecObject[i]->GetObjType();
			mapData.vScale = vecObject[i]->GetScale();
			mapData.vRotate = vecObject[i]->GetRotate();
			mapData.vTranslate = vecObject[i]->GetTranslate();

			mapFile << "# Object_Start" << endl;

			mapFile << "# ObjectName" << endl;
			mapFile << mapData.strObjName << endl;

			mapFile << "# FilePath" << endl;
			mapFile << mapData.strFilePath << endl;

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
			MessageBox(g_hWnd, L"�ش� ������ �������� �ʽ��ϴ�.", L"���� ���� ����", MB_OKCANCEL);
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
	TCHAR strBuffer[128];	// ���� ��ġ ��� ����
	TCHAR fileName[128] = L"\0";	// ��� �� ���� �̸� ����
	TCHAR sFilter[] = L"�� ����\0*.dat\0"; // "��� ����\0*.*\0�ؽ�Ʈ ����\0*.txt\0"

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = sFilter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = 128;
	ofn.lpstrInitialDir = _tgetcwd(strBuffer, 128);	// ���� ��� �ҷ�����
	if (GetOpenFileName(&ofn) != 0)
	{
		// wsprintf(fileName, L"%s", ofn.lpstrFile);
		// MessageBox(g_hWnd, fileName, L"�ҷ����� ����", MB_OKCANCEL);
		string realName;
		if (CheckDataName(fileName, realName))
			ReadMapData(realName);
	}
	// else
	// {
	// 	MessageBox(g_hWnd, L"�ҷ����⸦ ����Ͽ����ϴ�.", L"�ҷ����� ���", MB_OKCANCEL);
	// }
}

void CFileLoadManager::FileLoad_SaveMapData()
{
	OPENFILENAME ofn;
	TCHAR strBuffer[128];	// ���� ��ġ ��� ����
	TCHAR fileName[128] = L"\0";	// ��� �� ���� �̸� ����
	TCHAR sFilter[] = L"�� ����\0*.dat\0"; // "��� ����\0*.*\0�ؽ�Ʈ ����\0*.txt\0"

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = sFilter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = 128;
	ofn.lpstrInitialDir = _tgetcwd(strBuffer, 128);	// ���� ��� �ҷ�����
	if (GetSaveFileName(&ofn) != 0)
	{
		// wsprintf(fileName, L"%s", ofn.lpstrFile);
		// MessageBox(g_hWnd, fileName, L"���� ����", MB_OKCANCEL);
		string realName;
		if (CheckDataName(fileName, realName))
			SaveMapData(realName);
	}
	// else
	// {
	// 	MessageBox(g_hWnd, L"���� ������ ����Ͽ����ϴ�.", L"���� ���", MB_OKCANCEL);
	// }
}
