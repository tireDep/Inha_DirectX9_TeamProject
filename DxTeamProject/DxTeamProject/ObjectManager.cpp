#include "stdafx.h"
#include "Object.h"
#include "ObjectManager.h"
#include "CHeight.h"
CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

void CObjectManager::AddObject(CObject * pObject)
{
	m_vecObject.push_back(pObject);
}

void CObjectManager::RemoveObject(CObject * pObject)
{
	vector<CObject*>::iterator it;
	for (it = m_vecObject.begin(); it != m_vecObject.end();)
	{
		if (*it == pObject)
		{
			CObject* temp = *it;
			it = m_vecObject.erase(it);
			delete temp;
			return;
		}
		else
			it++;
	}
}

void CObjectManager::Destroy()
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Release();
}

void CObjectManager::Update(float duration, CHeight* pMap)
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Update(duration , pMap);
}

void CObjectManager::Update(CRay ray, D3DXCOLOR& objectcolor)
{
	vector<bool> vecIsPick;
	vector<D3DXVECTOR3> vecVPos;
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Update(ray, objectcolor, vecIsPick, vecVPos);
	}
	Update_PickCheck(vecIsPick, vecVPos);
}

void CObjectManager::Update()
{
	for (int hittee = 0; hittee < m_vecObject.size(); hittee++)
	{
		for (int hitter = 0; hitter < m_vecObject.size(); hitter++)
		{
			if (hittee >= hitter)
				continue;
			m_vecObject[hittee]->CollisionOtherObject(m_vecObject[hitter]);
		}
	}
}

void CObjectManager::Render()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Render();
	}
}

vector<CObject*> CObjectManager::GetVecObject()
{
	return m_vecObject;
}

void CObjectManager::Update_PickCheck(const vector<bool>& vecIsPick, const vector<D3DXVECTOR3>& vecVPos)
{
	int index = 0;
	for (int i = 1; i < m_vecObject.size(); i++)
	{
		if (vecIsPick[i] == false)
			continue;
		else
		{
			if (vecVPos[index].x >= vecVPos[i].x || vecVPos[index].y >= vecVPos[i].y || vecVPos[index].z >= vecVPos[i].z)
			{
				m_vecObject[index]->SetPickState(false);
				index = i;
			}
		} // >> : else
	} // >> : for
}