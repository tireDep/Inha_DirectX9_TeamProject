#include "stdafx.h"
#include "Door.h"

int CDoor::GetIndex()
{
	int index = 0;
	int size = g_pObjectManager->GetVecSize();
	for (int i = 0; i < size; i++)
	{
		if (g_pObjectManager->GetIObject(i).GetObjectName() == this->m_strObjName)
		{
			index = i;
			break;
		}
	}
#ifdef _DEBUG
	if (this->m_ObjectType == ObjectType::eG_DoorFrame)
		index += 1;
	else if (this->m_ObjectType == ObjectType::eG_Door)
		index -= 1;
#endif // _DEBUG

	return index;
}

CDoor::CDoor() :
	m_openCondition(OnOffCondition::eOrb)
{
	m_strConditionName = "";
}

CDoor::~CDoor()
{
}

void CDoor::Setup(ST_MapData setData)
{
	CGimmick::Setup(setData);
	m_strConditionName = "";
	// todo condition variable
}

void CDoor::Render()
{
	CGimmick::Render();
}

void CDoor::SetAnotherScale(D3DXVECTOR3 set)
{
	SetDiffScale(set);

	int index = GetIndex();
	if (index == 0)return;

	CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	temp->SetDiffScale(set);
}

void CDoor::SetAnotherRotation(D3DXVECTOR3 set)
{
	// SetDiffRot(set);
	SetRotate(set);

	int index = GetIndex();
	if (index == 0)return;

	CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	temp->SetRotate(set);
}

void CDoor::SetAnotherTranslation(D3DXVECTOR3 set)
{
	SetTranslate(set);

	int index = GetIndex();
	if (index == 0)return;

	CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	temp->SetTranslate(set);
}

void CDoor::SetOpenCondition(int index)
{
	if (index == 0)			m_openCondition = OnOffCondition::eOrb;
	else if (index == 1)	m_openCondition = OnOffCondition::eItem;
	else if (index == 2)	m_openCondition = OnOffCondition::eSwitch;

	int search = GetIndex();
	if (search == 0)return;

	CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(search));
	temp->SetOpenCondition(index);
}

void CDoor::SetConditionName(string strName)
{
	m_strConditionName = strName;

	int index = GetIndex();
	if (index == 0)return;

	CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	temp->SetConditionName(strName);
}

int CDoor::GetOpenConditionIndex()
{
	if (m_openCondition == OnOffCondition::eOrb)			return 0;
	else if (m_openCondition == OnOffCondition::eItem)		return 1;
	else if (m_openCondition == OnOffCondition::eSwitch);	return 2;
}

string CDoor::GetOpenConditionType()
{
	if (m_openCondition == OnOffCondition::eOrb)			return "Orb";
	else if (m_openCondition == OnOffCondition::eItem)		return "Item";
	else if (m_openCondition == OnOffCondition::eSwitch);	return "Switch";
}

string CDoor::GetConditionName()
{
	return m_strConditionName;
}
