#include "stdafx.h"
#include "Door.h"

#define Inf -1

int CDoor::GetIndex()
{
	int index = Inf;
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
	m_isAnotherClick(false)
{
}

CDoor::~CDoor()
{
}

void CDoor::Setup(ST_MapData setData)
{
	CGimmick::Setup(setData);
}

void CDoor::Update()
{
	if ((m_isPick || m_isClick) && m_ObjectType == eG_Door)
	{
		int index = GetIndex();
		if (index == Inf)
			return;

		CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
		temp->SetPick(true);
		temp->SetClick(true);
		m_isPick = false;
		m_isClick = false;
	}
}

void CDoor::Render()
{
	// CGimmick::Render();

	IObject::Render_OBB_Box();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());

	if (m_pMesh == NULL)
		return;

	if (m_isAnotherClick)
	{
		SetShader(GetmatWorld());
		IObject::Render();
		m_isAnotherClick = false;
	}
	else if (g_pObjectManager->GetPickObjName() == m_strConditionName 
	 && m_strConditionName != "" 
	 && m_pShader)
	{
		// >> 조건 오브젝트가 선택되었을 경우
		SetShader(GetmatWorld());
		SetShader_ConditionColor();
		IObject::Render();
	}
	else if (!m_isPick && !m_isClick 
		|| !m_pShader)
	{
		// >> 오브젝트가 선택되지 않거나 셰이더가 없을 경우
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			else if (m_pTexture != NULL)
				g_pD3DDevice->SetTexture(0, m_pTexture);
			// >> 텍스처 매치 안되있을 때

			m_pMesh->DrawSubset(i);
		}
	}
	else
	{
		// >> 오브젝트가 선택되었을 경우

		int index = GetIndex();
		if (index == Inf)
			return;

		CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
		temp->SetIsAnotherClick(true);
		// >> 문은 2개의 오브젝트가 같이 보이게

		SetShader(GetmatWorld());
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}

void CDoor::SetAnotherScale(D3DXVECTOR3 set)
{
	SetDiffScale(set);

	int index = GetIndex();
	if (index == Inf)
		return;

	CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	// if (temp->GetObjType() == eG_Door)
		temp->SetDiffScale(set);
}

void CDoor::SetAnotherRotation(D3DXVECTOR3 set)
{
	// SetDiffRot(set);
	SetRotate(set);

	int index = GetIndex();
	if (index == Inf)
		return;

	CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	// if (temp->GetObjType() == eG_Door)
		temp->SetRotate(set);
}

void CDoor::SetAnotherTranslation(D3DXVECTOR3 set)
{
	SetTranslate(set);

	int index = GetIndex();
	if (index == Inf)return;

	CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	// if (temp->GetObjType() == eG_Door)
		temp->SetTranslate(set);
}

void CDoor::SetOpenCondition(int index)
{
	CGimmick::SetOpenCondition(index);

	int search = GetIndex();
	if (search == Inf)
		return;

	CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(search));
	if(temp->GetObjType() == eG_Door)
		temp->SetOpenCondition(index);
}

void CDoor::SetConditionName(string strName)
{
	CGimmick::SetConditionName(strName);

	int index = GetIndex();
	if (index == Inf)
		return;
	
	CDoor* temp = static_cast<CDoor*> (&g_pObjectManager->GetIObject(index));
	if (temp->GetObjType() == eG_Door)
		temp->SetConditionName(strName);
}

void CDoor::SetTexture(int index)
{
	CGimmick::SetTexture(index);

	int search = GetIndex();
	if (search == Inf)
		return;

	CDoor* temp = dynamic_cast<CDoor*> (&g_pObjectManager->GetIObject(search));
	//if (temp->GetObjType() == eG_Door)
		temp->SetTexture(index);
}
