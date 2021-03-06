#include "stdafx.h"
#include "IObject.h"
#include "ObjectManager.h"
#include "ImguiClass.h"
#include "Ray.h"
#include "RotationBoard.h"
#include "Switch.h"
#include "Door.h"
#include "Switch.h"
#include "Background.h"

void CObjectManager::SetCopyObject(int index)
{
	m_vecObject[m_vecObject.size() - 1]->SetScale(m_vecObject[index]->GetScale());
	m_vecObject[m_vecObject.size() - 1]->SetRotate(m_vecObject[index]->GetRotate());
	m_vecObject[m_vecObject.size() - 1]->SetTranslate(m_vecObject[index]->GetTranslate());
}

void CObjectManager::SetReConditionName()
{
	map<string, string>::iterator it;

	for (int i = m_preVecObjSize; i < m_vecObject.size(); i++)
	{
		for (it = m_mapConditionName.begin(); it != m_mapConditionName.end(); it++)
		{
			if (m_vecObject[i]->GetConditionName() == it->first)
			{
				if (m_vecObject[i]->GetObjType() == ObjectType::eG_DoorFrame
					|| m_vecObject[i]->GetObjType() == ObjectType::eG_Door)
				{
					CDoor* temp = static_cast<CDoor*>(m_vecObject[i]);
					temp->SetConditionName(it->second);
				}
				else
					m_vecObject[i]->SetConditionName(it->second);
			}
		} // << : for_it

	} // << : for_i

	m_mapConditionName.clear();
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

void CObjectManager::RemoveCondition(string objectName)
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (objectName == m_vecObject[i]->GetObjectName())
			RemoveObject(m_vecObject[i]);
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
	// bool isSelect = false;
	// for (int i = 0; i < m_vecObject.size(); i++)
	// {
	// 	if (m_vecObject[i]->GetClick() == true)
	// 		isSelect = true;
	// }

	for (int i = 0; i < m_vecObject.size(); i++)
		m_vecObject[i]->Update(ray);

	// >> 피킹 오브젝트 판별
	// - 같은 선상에 있는 모든 오브젝트가 피킹 되기 때문에
	//   레이 위치와 가장 가까운 오브젝트 판별한 후 나머지 false
	
	int index = -1;

	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetPick() == true)
		{
			index = i;
			break;
		}
	}

	// if (index == -1 && !isSelect)
	// 	SetSelectAllFalse();

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

			if (m_vecObject[i]->GetConditionName() != "")
			{
				for (int j = 0; j < m_vecObject.size(); j++)
				{
					if (m_vecObject[i]->GetConditionName() == m_vecObject[j]->GetObjectName())
					{
						if (m_vecObject[j]->GetObjType() == eG_DoorFrame)
						{
							// >> 문은 삭제할 대상이 2개
							CDoor* temp = static_cast<CDoor*>(m_vecObject[j]);
							temp->SetConditionName("");
						}
						else
							m_vecObject[j]->SetConditionName("");
					}
				}
			}
			// >> 삭제하는 대상이 누군가의 조건일 경우, 조건 삭제

			// >>  문은 2개가 1세트

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
			{
				if (m_vecObject[j]->GetConditionName() != "")
				{
					// >> 이름이 변경될 파일에 조건 변수가 존재할 경우
					string preName = m_vecObject[j]->GetObjectName();

					m_vecObject[j]->SetObjectName(m_vecObject[j]->GetObjectName() + "(" + to_string(m_sameNum++) + ")");

					string nowName = m_vecObject[j]->GetObjectName();

					m_mapConditionName.insert(pair<string, string>(preName, nowName));
				}
				else
					m_vecObject[j]->SetObjectName(m_vecObject[j]->GetObjectName() + "(" + to_string(m_sameNum++) + ")");
			}

		} // >> : for_j

	} // >> : for_i

	if (m_mapConditionName.size() != 0)
		SetReConditionName();
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
			 || objType == ObjectType::eWTree || objType == ObjectType::eCTree
			 || objType == ObjectType::eFlower)
			{
				// >> 인덱스로 받아 오는 파일들은 인덱스 값 필요함
				string num = m_vecObject[i]->GetXFilePath();
				num = num[num.length() - 3];
				indexNum = atoi(num.c_str()) - 1;
			}

			else if (objType == ObjectType::eG_Door || objType == ObjectType::eG_DoorFrame)
			{
				objType = eG_DoorFrame;
			}


			IObject::CreateObject(objType, indexNum);
			break;
		} // << : if

	} // << : for

	if (objType != ObjectType::eNull)
	{
		SetCopyObject(index);

		// >> 복사한 물체 속성 받아옴
		switch (objType)
		{
		case eBox:	case eSphere:	case eCylinder:
			m_vecObject[m_vecObject.size() - 1]->SetColor(m_vecObject[index]->GetColor());
			break;

		case eCTree:
		case eUmbrella:
		{
			CBackground* temp = dynamic_cast<CBackground*> (&g_pObjectManager->GetIObject(m_vecObject.size() - 1));
			CBackground* temp2 = dynamic_cast<CBackground*> (&g_pObjectManager->GetIObject(index));

			temp->SetTexture(temp2->GetTextureIndex());
		}
			break;

		case eG_RotationBoard:
		{
			CRotationBoard* temp = dynamic_cast<CRotationBoard*> (&g_pObjectManager->GetIObject(m_vecObject.size() - 1));
			CRotationBoard* temp2 = dynamic_cast<CRotationBoard*> (&g_pObjectManager->GetIObject(index));

			temp->SetRotation_Axial(temp2->GetRotation_Axial());
			temp->SetRotationSpeed(temp2->GetRotationSpeed());
		}
		break;

		case eG_DoorFrame:	case eG_Door:
		{
			CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(m_vecObject.size() - 1));
			CDoor* temp2 = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(index));

			temp->SetAnotherScale(temp2->GetScale());
			temp->SetAnotherRotation(temp2->GetRotate());
			temp->SetAnotherTranslation(temp2->GetTranslate());
		}
		break;

		case eG_Switch:
		{
			CSwitch* temp = dynamic_cast<CSwitch*> (&g_pObjectManager->GetIObject(m_vecObject.size() - 1));
			CSwitch* temp2 = dynamic_cast<CSwitch*> (&g_pObjectManager->GetIObject(index));

			temp->SetTexture(temp2->GetTextureIndex());
		}
			break;

		} // << : switch

	} // << : if
	
}

string CObjectManager::GetPickObjName()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if (m_vecObject[i]->GetClick() == true || m_vecObject[i]->GetPick() == true)
			return m_vecObject[i]->GetObjectName();
	}

	return "";
}

void CObjectManager::SetPreVecSize(int set)
{
	m_preVecObjSize = set;
}

int CObjectManager::GetConditionIndex()
{
	int index = GetSelectIndex();
	string conditionName = m_vecObject[index]->GetConditionName();

	if (conditionName != "")
	{
		for (int i = 0; i < m_vecObject.size(); i++)
		{
			if (m_vecObject[i]->GetObjectName() == conditionName)
				return i;
		}
	}

	return -1;
}

D3DXVECTOR3 CObjectManager::GetHighestY(int index)
{
	// >> 해당 좌표(x, y)의 가장 높은 값 추출
	D3DXVECTOR3 checkPos(0, 0, 0);
	D3DXVECTOR3 pos = m_vecObject[index]->GetTranslate();
	float y = 0;
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		checkPos = m_vecObject[i]->GetTranslate();

		if (checkPos.x == pos.x && checkPos.z == pos.z)
			y = checkPos.y > pos.y ? checkPos.y : pos.y;
	}

	pos.y = y;
	return pos;
}

bool CObjectManager::GetIsAnotherPos(D3DXVECTOR3 pos)
{
	// >> 해당 위치에 오브젝트가 존재하는지 확인
	D3DXVECTOR3 result;
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		result = m_vecObject[i]->GetTranslate();
		if (pos.x == result.x
		 && pos.y == result.y 
		 && pos.z == result.z)
			return true;
	}
	return false;
}

