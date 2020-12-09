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
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Update(ray);

	// >> 피킹 오브젝트 판별
	// - 같은 선상에 있는 모든 오브젝트가 피킹 되기 때문에
	//   레이 위치와 가장 가까운 오브젝트 판별한 후 나머지 false
	int index = 0;
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetPick() == true)
		{
			index = i;
			break;
		}
	}

	D3DXVECTOR3 rayOrigin = ray->GetOrigin();
	for (int i = index + 1; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetPick() == true)
		{
			// >> 벡터 길이 계산
			float checkA = D3DXVec3Length( &(rayOrigin - m_vecObject[index]->GetTranslate()) );
			float checkB = D3DXVec3Length( &(rayOrigin - m_vecObject[i]->GetTranslate()) );

			if(checkA > checkB)
			{
				m_vecObject[index]->SetPick(false);
				index = i;
			}	
		} // << : if

	} // << : for
	// << 피킹 오브젝트 판별
}

void CObjectManager::Render()
{
	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Render();
}

void CObjectManager::RemoveClickedObj()
{
	int preIndex = 0;
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetClick())
		{
			preIndex = i - 1;
			RemoveObject(m_vecObject[i]);
		}
	}

	if (m_vecObject.size() == 0)
	{
		IObject::SetRefCnt(0);
		m_sameNum = 0;
		g_pFileLoadManager->SetIndexNumZero();
	}
	else
	{
		SetSelectAllFalse();
		if (preIndex == -1)
		{
			m_vecObject[0]->SetClick(true);
			m_vecObject[0]->SetPick(true);
		}
		else
		{
			m_vecObject[preIndex]->SetClick(true);
			m_vecObject[preIndex]->SetPick(true);
		}
		
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

void CObjectManager::SetSelectAllFalse()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->SetClick(false);
		m_vecObject[i]->SetPick(false);
	}
}

int CObjectManager::GetSelectIndex()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetClick() || m_vecObject[i]->GetPick())
			return i;
	}

	return -1;
}

void CObjectManager::CopyObject()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetPick())
		{
			SetSelectAllFalse();

			int indexNum = 0;
			ObjectType objType = m_vecObject[i]->GetObjType();

			if (objType == ObjectType::eATree || objType == ObjectType::eSTree
			 || objType == ObjectType::eWTree || objType == ObjectType::eCTree)
			{
				// >> 나무 파일들은 인덱스로 받아 오기 때문에 인덱스 값 필요함
				string num = m_vecObject[i]->GetXFilePath();
				num = num[num.length() - 3];
				indexNum = atoi(num.c_str()) - 1;
			}

			IObject::CreateObject(objType, indexNum);

			break;
		}
	}
}
