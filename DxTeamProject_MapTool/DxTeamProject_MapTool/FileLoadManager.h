#pragma once
#include "Singleton.h"

#define g_pFileLoadManager CFileLoadManager::GetInstance()

class CFileLoadManager : public CSingleton<CFileLoadManager>
{
private:
	bool CheckDataName(TCHAR* openFileName, string& realName);
	void ReadMapData(string fileName);
	void SaveMapData(string fileName);

public:
	void FileLoad_OpenMapData();
	void FileLoad_SaveMapData();
};

