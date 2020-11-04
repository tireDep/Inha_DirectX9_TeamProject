#include "stdafx.h"
#include "SkinnedMeshManager.h"
#include "SkinnedMesh.h"

CSkinnedMeshManager::CSkinnedMeshManager()
{
}


CSkinnedMeshManager::~CSkinnedMeshManager()
{
}

CSkinnedMesh * CSkinnedMeshManager::GetSkinnedMesh(char * szFolder, char * szFileName)
{
	string sFullPath(szFolder);
	sFullPath += string("/") + string(szFileName);

	if (m_mapSkinnedMesh.find(sFullPath) == m_mapSkinnedMesh.end())
	{
		CSkinnedMesh* pSkinnedMesh = new CSkinnedMesh();
		pSkinnedMesh->Load(szFolder, szFileName);
		m_mapSkinnedMesh[sFullPath] = pSkinnedMesh;
	}

	return m_mapSkinnedMesh[sFullPath];
}

void CSkinnedMeshManager::Destroy()
{
	for each(auto it in m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SafeDelete(it.second);
	}
}
