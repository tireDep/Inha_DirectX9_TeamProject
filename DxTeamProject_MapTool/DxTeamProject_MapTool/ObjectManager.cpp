#include "stdafx.h"
#include "IObject.h"
#include "ObjectManager.h"
#include "ImguiClass.h"
#include "Ray.h"

void CObjectManager::AddObject(IObject * pObject)
{
	m_vecObject.push_back(pObject);
}

void CObjectManager::RemoveObject(IObject * pObject)
{
	vector<IObject *>::iterator it;
	for (it = m_vecObject.begin(); it != m_vecObject.end();)
	{
		if (*it == pObject)
		{
			IObject* temp = *it;
			it = m_vecObject.erase(it);
			delete temp;
			m_sameNum--;
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

	if (m_vecObject.size() == 1)
		m_vecObject[0]->Release(); // 마지막 하나 삭제

	m_vecObject.clear();
	IObject::SetRefCnt(0);
	m_sameNum = 0;
	g_pFileLoadManager->SetIndexNumZero();
	CImguiClass::m_nowSelectindex = -1;
	CImguiClass::m_nowSelectindex = 0;
}

void CObjectManager::Update()
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Update();
}

void CObjectManager::Update(CRay * ray)
{
	// todo
	// 피킹 오브젝트 선택 판별
	// 카메라랑 가장 가까운 위치 선택?
	
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Update(ray);
}

void CObjectManager::Render()
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Render();
}

void CObjectManager::RemoveClickedObj()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetClick())
			RemoveObject(m_vecObject[i]);
	}

	if (m_vecObject.size() == 0)
	{
		IObject::SetRefCnt(0);
		m_sameNum = 0;
		g_pFileLoadManager->SetIndexNumZero();
	}
}

void CObjectManager::CheckSameName()
{
	if (m_vecObject.size() == 0)
		return;

	for (int i = 0; i < m_vecObject.size() - 1; i++)
	{
		for (int j = i + 1; j < m_vecObject.size(); j++)
		{
			if (m_vecObject[i]->GetObjectName() == m_vecObject[j]->GetObjectName())
				m_vecObject[j]->SetObjectName(m_vecObject[j]->GetObjectName() + "(" + to_string(m_sameNum++) + ")");
		}
	}
}

vector<IObject*> CObjectManager::GetVecObject()
{
	return m_vecObject;
}

IObject & CObjectManager::GetIObject(int index)
{
	return *m_vecObject[index];
}

int CObjectManager::GetVecSize()
{
	return m_vecObject.size();
}

void CObjectManager::SetSelectFalse()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->SetClick(false);
		m_vecObject[i]->SetPick(false);
	}
}
