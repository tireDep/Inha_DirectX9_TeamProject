#include "stdafx.h"
#include "EventTrigger.h"

CEventTrigger::CEventTrigger()
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

	if (setData.triggerIndex == 0)
	{
		m_triggerType = TriggerType::eSave;
	}
	else if (setData.triggerIndex == 1)
	{
		m_triggerType = TriggerType::eZone;
	}

	m_vTranslation.y = 0.5f;
	D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);

	if (m_strTxtFile != "")
		g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXVECTOR3 v;
	v.x = D3DXToRadian(m_vRotation.x);
	v.y = D3DXToRadian(m_vRotation.y);
	v.z = D3DXToRadian(m_vRotation.z);

	D3DXMatrixRotationYawPitchRoll(&m_matR, v.y, v.x, v.z);

	D3DXMatrixTranslation(&m_matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
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
}

string CEventTrigger::GetTriggerTypeString()
{
	if (m_triggerType == TriggerType::eSave)
		return "Save";
	else if (m_triggerType == TriggerType::eZone)
		return "Zone";
}
