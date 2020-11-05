#pragma once

#define g_pSkinnedMeshManager CSkinnedMeshManager::GetInstance()
class CSkinnedMesh;

class CSkinnedMeshManager
{
private:
	map<string, CSkinnedMesh*> m_mapSkinnedMesh;

public:
	Singletone(CSkinnedMeshManager);

	CSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFileName);

	void Destroy();
};

