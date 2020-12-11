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

	if (this->m_ObjectType == ObjectType::eG_DoorFrame)
		index += 1;
	else if (this->m_ObjectType == ObjectType::eG_Door)
		index -= 1;

	return index;
}

CDoor::CDoor()
{
}

CDoor::~CDoor()
{
}

void CDoor::Setup(ST_MapData setData)
{
	CGimmick::Setup(setData);
	
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

	CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	temp->SetDiffScale(set);
}

void CDoor::SetAnotherRotation(D3DXVECTOR3 set)
{
	// SetDiffRot(set);
	SetRotate(set);

	int index = GetIndex();

	CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	temp->SetRotate(set);
}

void CDoor::SetAnotherTranslation(D3DXVECTOR3 set)
{
	SetTranslate(set);

	int index = GetIndex();

	CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	temp->SetTranslate(set);
}
