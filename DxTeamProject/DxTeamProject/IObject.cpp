#include "stdafx.h"
#include "IObject.h"

//int IObject::m_nRefCnt = 0;

IObject::IObject() :
	m_strConditionName(""),
	m_isCondition(false),
	m_pOBB(NULL)
	//m_conditionOrbindex(-1),
//: m_pTexture(NULL),
	//m_pMesh(NULL),
	//m_numMtrls(0),
	//m_strObjName(""),
	//m_strFolder(""),
	//m_strTxtFile(""),
	//m_ObjectType(ObjectType::eNull),
	//m_vScale(0,0,0),
	//m_vRotate(0, 0, 0),
	//m_vTranslate(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
	g_pObjectManager->AddObject(this);
	m_strName = "Iobject" + to_string(m_nRefCount);
}

bool IObject::CheckIsGetColorOrb()
{
	// >> 태그와 맞는 색상 오브가 있는지 판별
	// >> 하나라도 존재 하지 않을 경우 false

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

//void IObject::CreateObject(const ST_MapData & mapData)
//{
//	switch (mapData.objType)
//	{
//	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
//	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
//	{
//		CTile* tile = new CTile;
//		tile->Setup(mapData);
//	}
//	break;
//
//	default:
//		CObject::CreateObject(mapData);
//		break;
//	}
//}
