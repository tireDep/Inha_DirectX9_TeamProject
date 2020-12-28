#include "stdafx.h"
#include "IObject.h"

IObject::IObject() :
	m_grayTxt(NULL),
	m_strConditionName(""),
	m_isCondition(false),
	m_pOBB(NULL)
{
	ResetPosition = D3DXVECTOR3(0, 0, 0);
	PresentPosition = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixIdentity(&m_matWorld);
	g_pObjectManager->AddObject(this);
	m_strName = "Iobject" + to_string(m_nRefCount);
}

bool IObject::CheckIsGetColorOrb()
{
	// >> �±׿� �´� ���� ���갡 �ִ��� �Ǻ�
	// >> �ϳ��� ���� ���� ���� ��� false
	for (int i = 0; i < m_vecColorTag.size(); i++)
	{
		if (!g_pGameManager->GetIsHasOrb(m_vecColorTag[i]))
			return false;
	}
	return true;
}

IObject::~IObject()
{
	SafeDelete(m_pOBB);
}

void IObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	//IObject::m_nRefCnt -= 1;
}

void IObject::ReceiveEvent(ST_EVENT eventMsg)
{
	if (m_strConditionName == "")
		return;

	if (eventMsg.eventType == EventType::eConditionChange)
	{
		if (m_strConditionName == eventMsg.conditionName)
			m_isCondition = !eventMsg.isCondition;
	}
}