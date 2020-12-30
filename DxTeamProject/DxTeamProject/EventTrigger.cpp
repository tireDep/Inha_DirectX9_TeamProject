#include "stdafx.h"
#include "EventTrigger.h"

CEventTrigger::CEventTrigger() :
	m_zoneType(ZoneType::eWinter),
	m_triggerType(TriggerType::eSave),
	player(false), 
	triggerpos(0,0,0)
{
}

CEventTrigger::~CEventTrigger()
{
}

void CEventTrigger::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;
	m_vScale = setData.vScale;
	m_vRotation = setData.vRotate;
	m_vTranslation = setData.vTranslate;

	if (setData.zoneIndex == 0)
		m_zoneType = ZoneType::eWinter;
	else if (setData.zoneIndex == 1)
		m_zoneType = ZoneType::eFall;
	else if (setData.zoneIndex == 2)
		m_zoneType = ZoneType::eZone;

	if (setData.triggerIndex == 0)
	{
		m_triggerType = TriggerType::eSave;
	}
	else if (setData.triggerIndex == 1)
	{
		m_triggerType = TriggerType::eZone;
	}

	m_vTranslation.y = 0.5f;
	D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);

	if (m_strTxtFile != "")
		g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(m_vRotation.x);
	v.y = D3DXToRadian(m_vRotation.y);
	v.z = D3DXToRadian(m_vRotation.z);

	D3DXMatrixRotationYawPitchRoll(&m_matR, v.y, v.x, v.z);

	D3DXMatrixTranslation(&m_matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	triggerpos = m_vTranslation;
	m_matWorld = m_matS * m_matR * m_matT;

	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	m_pOBB->Update(&m_matWorld);
}

void CEventTrigger::Update(float duration)
{

}

void CEventTrigger::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pMesh == NULL)
		return;

	g_pD3DDevice->SetTexture(0, NULL);

	if (player == true)
	{
		SafeRelease(m_pMesh);
		g_pObjectManager->RemoveObject(m_pOBB);
	}
}

string CEventTrigger::GetTriggerTypeString()
{
	if (m_triggerType == TriggerType::eSave)
		return "Save";
	else if (m_triggerType == TriggerType::eZone)
	{
		if (m_zoneType == ZoneType::eFall)
			return "Fall";

		else if (m_zoneType == ZoneType::eWinter)
			return "Winter";
	}
}
