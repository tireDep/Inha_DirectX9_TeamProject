#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <fstream>
#include "stdafx.h"
#include "FileLoadManager.h"

void CFileLoadManager::ReadMapData(string fileName)
{
	// >> todo : �Ľ�
	cout << " todo Something_readMap " << endl;
	
	ifstream mapFile;
	mapFile.open(fileName.c_str(), ios::in | ios::binary);
	/*	if (mapFile.is_open())
	{
		tileMap.clear();
		// >> ���� �о���� �� �ʱ�ȭ

		POINT pos = { 0,0 };
		TileMap temp;

		temp.pos = { 0,0,0,0 };
		temp.type = 0;

		// >> �÷��̾�
		mapFile.read((char*)&pos.x, sizeof(int));
		mapFile.read((char*)&pos.y, sizeof(int));

		pos.x = (pos.x / dKeyCode) - dKeyCode;
		pos.y = (pos.y / dKeyCode) - dKeyCode;

		temp.pos.left = pos.x - 8;
		temp.pos.top = pos.y - 8;
		temp.pos.right = pos.x + 8;
		temp.pos.bottom = pos.y + 8;
		temp.type = ePlayerResen;
		temp.showPos = SetShowType(temp.type);

		tileMap.push_back(temp);

		// >> �� ����
		while (!mapFile.eof())
		{
			mapFile.read((char*)&temp.type, sizeof(int));
			mapFile.read((char*)&temp.pos.left, sizeof(int));
			mapFile.read((char*)&temp.pos.top, sizeof(int));
			mapFile.read((char*)&temp.pos.right, sizeof(int));
			mapFile.read((char*)&temp.pos.bottom, sizeof(int));

			temp.type = (temp.type / dKeyCode) - dKeyCode;
			temp.pos.left = (temp.pos.left / dKeyCode) - dKeyCode;
			temp.pos.top = (temp.pos.top / dKeyCode) - dKeyCode;
			temp.pos.right = (temp.pos.right / dKeyCode) - dKeyCode;
			temp.pos.bottom = (temp.pos.bottom / dKeyCode) - dKeyCode;

			if (temp.type < 0)
				break;	// >> ���ѷ��� ó��

			temp.showPos = SetShowType(temp.type);
			tileMap.push_back(temp);
		}
	} */

	mapFile.close();
}

void CFileLoadManager::SaveMapData(string fileName)
{
	// >> todo : �Ľ�
	cout << " todo Something_saveMap " << endl;

	ofstream mapFile;
	mapFile.open(fileName.c_str(), ios::out | ios::binary);
	/*
	POINT playerPos;
	bool isPlayerIn = false;
	for (int i = 0; i < tileMap.size(); i++)
	{
		if (tileMap[i].type == ePlayerResen)
		{
			isPlayerIn = true;

			playerPos.x = (tileMap[i].pos.left + tileMap[i].pos.right) * 0.5;
			playerPos.y = (tileMap[i].pos.top + tileMap[i].pos.bottom) * 0.5;
		}
	}

	if (!isPlayerIn)
	{
		MessageBox(hWnd, L"�÷��̾� ��ġ�� �������� �ʽ��ϴ�.", L"���� ���� ����", MB_OKCANCEL);
		return;
	}

	mapFile.open(changeFile);

	// mapFile << playerPos.x << "\t" << playerPos.y << endl;
	playerPos.x = (playerPos.x + dKeyCode) * dKeyCode;
	playerPos.y = (playerPos.y + dKeyCode) * dKeyCode;

	mapFile.write((char*)&playerPos.x, sizeof(int));
	mapFile.write((char*)&playerPos.y, sizeof(int));

	TileMap tempMap;
	for (int i = 0; i < tileMap.size(); i++)
	{
		if (tileMap[i].type != ePlayerResen)
		{
			tempMap.type = (tileMap[i].type + dKeyCode) * dKeyCode;
			tempMap.pos.left = (tileMap[i].pos.left + dKeyCode) * dKeyCode;
			tempMap.pos.top = (tileMap[i].pos.top + dKeyCode) * dKeyCode;
			tempMap.pos.right = (tileMap[i].pos.right + dKeyCode) * dKeyCode;
			tempMap.pos.bottom = (tileMap[i].pos.bottom + dKeyCode) * dKeyCode;

			mapFile.write((char*)&tempMap.type, sizeof(int));
			mapFile.write((char*)&tempMap.pos.left, sizeof(int));
			mapFile.write((char*)&tempMap.pos.top, sizeof(int));
			mapFile.write((char*)&tempMap.pos.right, sizeof(int));
			mapFile.write((char*)&tempMap.pos.bottom, sizeof(int));
		}
		// mapFile << tileMap[i].type << "\t" << tileMap[i].pos.left << "\t" << tileMap[i].pos.top << "\t" << tileMap[i].pos.right << "\t" << tileMap[i].pos.bottom << endl;
	}

	mapFile.close(); 
	*/

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
