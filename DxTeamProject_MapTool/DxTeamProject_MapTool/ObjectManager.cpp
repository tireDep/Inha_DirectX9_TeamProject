#include "stdafx.h"
#include "IObject.h"
#include "ObjectManager.h"
#include "ImguiClass.h"
#include "Ray.h"
#include "RotationBoard.h"
#include "Switch.h"
#include "Door.h"

void CObjectManager::SetCopyObject(int index)
{
	m_vecObject[m_vecObject.size() - 1]->SetScale(m_vecObject[index]->GetScale());
	m_vecObject[m_vecObject.size() - 1]->SetRotate(m_vecObject[index]->GetRotate());
	m_vecObject[m_vecObject.size() - 1]->SetTranslate(m_vecObject[index]->GetTranslate());
}

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
		m_vecObject[0]->Release(); // ������ �ϳ� ����

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

	// >> ��ŷ ������Ʈ �Ǻ�
	// - ���� ���� �ִ� ��� ������Ʈ�� ��ŷ �Ǳ� ������
	//   ���� ��ġ�� ���� ����� ������Ʈ �Ǻ��� �� ������ false
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
			// >> ���� ���� ���
			float checkA = D3DXVec3Length( &(rayOrigin - m_vecObject[index]->GetTranslate()) );
			float checkB = D3DXVec3Length( &(rayOrigin - m_vecObject[i]->GetTranslate()) );

			if(checkA > checkB)
			{
				m_vecObject[index]->SetPick(false);
				index = i;
			}	
		} // << : if

	} // << : for
	// << ��ŷ ������Ʈ �Ǻ�
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

			// >>  ���� 2���� 1��Ʈ
#ifdef _DEBUG
			if (m_vecObject[i]->GetObjType() == ObjectType::eG_DoorFrame)
			{
				RemoveObject(m_vecObject[i]);
				RemoveObject(m_vecObject[i]);
			}

			else if (m_vecObject[i]->GetObjType() == ObjectType::eG_Door)
			{
				RemoveObject(m_vecObject[i - 1]);
				RemoveObject(m_vecObject[i - 1]);
				preIndex -= 1;
			}

			else
				RemoveObject(m_vecObject[i]);
#else
			RemoveObject(m_vecObject[i]);
#endif // _DEBUG
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
	int index = 0;
	bool isCopy = false;
	ObjectType objType = ObjectType::eNull;

	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetPick())
		{
			index = i;
			SetSelectAllFalse();
			objType = m_vecObject[i]->GetObjType();

			int indexNum = 0;
			if (objType == ObjectType::eATree || objType == ObjectType::eSTree
			 || objType == ObjectType::eWTree || objType == ObjectType::eCTree )
#ifdef _DEBUG
				|| objType == ObjectType::eFlower)
#endif // _DEBUG
			{
				// >> �ε����� �޾� ���� ���ϵ��� �ε��� �� �ʿ���
				string num = m_vecObject[i]->GetXFilePath();
				num = num[num.length() - 3];
				indexNum = atoi(num.c_str()) - 1;
			}
#ifdef _DEBUG
			else if (objType == ObjectType::eG_Door || objType == ObjectType::eG_DoorFrame)
			{
				objType = eG_DoorFrame;
			}
#endif // _DEBUG

			IObject::CreateObject(objType, indexNum);
			break;
		} // << : if

	} // << : for

	if (objType != ObjectType::eNull)
	{
		SetCopyObject(index);

		// >> ������ ��ü �Ӽ� �޾ƿ�
		switch (objType)
		{
		case eBox:	case eSphere:	case eCylinder:
			m_vecObject[m_vecObject.size() - 1]->SetColor(m_vecObject[index]->GetColor());
			break;

		case eG_RotationBoard:
		{
			CRotationBoard* temp = dynamic_cast<CRotationBoard*> (&g_pObjectManager->GetIObject(m_vecObject.size() - 1));
			CRotationBoard* temp2 = dynamic_cast<CRotationBoard*> (&g_pObjectManager->GetIObject(index));

			temp->SetRotation_Axial(temp2->GetRotation_Axial());
			temp->SetRotationSpeed(temp2->GetRotationSpeed());
		}
		break;

#ifdef _DEBUG
		case eG_DoorFrame:	case eG_Door:
		{
			CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(m_vecObject.size() - 1));
			CDoor* temp2 = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
			temp->SetAnotherScale(temp->GetScale());
			temp->SetAnotherRotation(temp->GetRotate());
			temp->SetAnotherTranslation(temp->GetTranslate());
		}
		break;
#endif // _DEBUG

		} // << : switch

	} // << : if
	
}
