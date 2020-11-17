#include "stdafx.h"
#include "Object.h"
#include "ObjectManager.h"

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

void CObjectManager::Update(CRay ray, D3DXCOLOR objectcolor)
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Update(ray);
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
