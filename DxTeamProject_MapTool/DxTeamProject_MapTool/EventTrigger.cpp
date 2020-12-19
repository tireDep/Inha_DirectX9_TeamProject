#include "stdafx.h"
#include "EventTrigger.h"

void CEventTrigger::SetMaterialColor(float r, float g, float b, float a)
{
	m_pMtrl.Ambient = D3DXCOLOR(r, g, b, a);
	m_pMtrl.Diffuse = D3DXCOLOR(r, g, b, a);
	m_pMtrl.Specular = D3DXCOLOR(r, g,  b, a);
}

CEventTrigger::CEventTrigger() :
	m_triggerType(TriggerType::eSave),
	m_zoneType(ZoneType::eWinter)
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
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

	if (setData.zoneIndex == 0)
		m_zoneType = ZoneType::eWinter;
	else if (setData.zoneIndex == 1)
		m_zoneType = ZoneType::eFall;
	
	if (setData.triggerIndex == 0)
	{
		m_triggerType = TriggerType::eSave;
		SetMaterialColor(0.5f, 0.0f, 0.5f, 1.0f);
	}
	else if (setData.triggerIndex == 1)
	{
		m_triggerType = TriggerType::eZone;
		
		if (m_zoneType == ZoneType::eWinter)
			SetMaterialColor(0.2f, 0.3f, 0.3f, 1.0f);
		else
			SetMaterialColor(0.3f, 0.3f, 0.0f, 1.0f);
	}

	m_vTranslate.y = 0.5f;
	D3DXCreateBox(g_pD3DDevice, m_vScale.x, m_vScale.y, m_vScale.z, &m_pMesh, NULL);

	IObject::Setup_OBB_Box();
}

void CEventTrigger::Render()
{
	IObject::Render_OBB_Box();

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());

	if (m_pMesh == NULL)
		return;

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	if (!m_isPick && !m_isClick || !m_pShader)
	{
		g_pD3DDevice->SetMaterial(&m_pMtrl);
		m_pMesh->DrawSubset(0);
	}
	else
	{
		SetShader(GetmatWorld());
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}

void CEventTrigger::SetTriggerIndex(int index)
{
	string tempName;
	if (index == 0)
	{
		m_triggerType = TriggerType::eSave;
		SetMaterialColor(0.5f, 0.0f, 0.5f, 1.0f);
		tempName = "EventTrigger_Save";
	}
	else if (index == 1)
	{
		m_triggerType = TriggerType::eZone;
		if (m_zoneType == ZoneType::eWinter)
			SetMaterialColor(0.2f, 0.3f, 0.3f, 1.0f);
		else
			SetMaterialColor(0.3f, 0.3f, 0.0f, 1.0f);
		tempName = "EventTrigger_Zone";
	}

	int search = 0;
	for (int i = 0; i < m_strObjName.length(); i++)
	{
		if (m_strObjName[i] >= 48 && m_strObjName[i] <= 57)
		{
			search = i;
			break;
		}
	}

	m_strObjName = tempName + m_strObjName.substr(search, m_strObjName.length());
}

int CEventTrigger::GetTriggerIndex()
{
	if (m_triggerType == TriggerType::eSave)
		return 0;
	else if (m_triggerType == TriggerType::eZone)
		return 1;
}

string CEventTrigger::GetTriggerType()
{
	if (m_triggerType == TriggerType::eSave)
		return "Save";
	else if (m_triggerType == TriggerType::eZone)
		return "Zone";
}

void CEventTrigger::SetZoneIndex(int index)
{
	if (index == 0)
		m_zoneType = ZoneType::eWinter;
	else if (index == 1)
		m_zoneType = ZoneType::eFall;

	if (m_zoneType == ZoneType::eWinter)
		SetMaterialColor(0.3f, 0.3f, 0.3f, 1.0f);
	else
		SetMaterialColor(0.3f, 0.3f, 0.0f, 1.0f);
}

int CEventTrigger::GetZoneIndex()
{
	if (m_zoneType == ZoneType::eWinter)
		return 0;
	else if (m_zoneType == ZoneType::eFall)
		return 1;
}
