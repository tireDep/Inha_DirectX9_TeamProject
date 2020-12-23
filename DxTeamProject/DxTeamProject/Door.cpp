#include "stdafx.h"
#include "Door.h"

CDoor::CDoor()
	: m_fOpeningAngle(D3DX_PI / 2.0f)
	, IsOpen(false)
	, m_fRotAngle(0.0f)
	, m_fRotationSpeed(1.0f)
	, render(true)
{
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
	D3DXMatrixIdentity(&m_matRotGimmick);
	m_strName = string("Door") + to_string(m_nRefCount);
}

CDoor::~CDoor()
{
}

void CDoor::Setup(const ST_MapData & mapData)
{
	CGimmick::SetLoadData(mapData);
	m_fRotAngle = D3DXToRadian(m_vRotation.y);
	ResetPosition = mapData.vTranslate;
}

void CDoor::Update(float duration)
{
	if (m_ObjectType == eG_Door)
	{
		if (m_isCondition)
		{
			m_fRotAngle += m_fRotationSpeed * duration;
			if (m_fRotAngle >= m_fOpeningAngle + D3DXToRadian(m_vRotation.y))
			{
				m_fRotationSpeed = 0;
				m_fRotAngle = m_fOpeningAngle + D3DXToRadian(m_vRotation.y);
			}
			else
				m_fRotationSpeed = 1.0f;
		}
		else
		{
			m_fRotAngle -= m_fRotationSpeed * duration;
			if(m_fRotAngle <= D3DXToRadian(m_vRotation.y))
			{
				m_fRotationSpeed = 0;
				m_fRotAngle = D3DXToRadian(m_vRotation.y);
			}
			else
				m_fRotationSpeed = 1.0f;
		}

		D3DXMatrixRotationY(&m_matRotGimmick, m_fRotAngle);

		D3DXMATRIXA16 matS, matT;
		D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);

		m_matWorld = matS * m_matRotGimmick * matT;

		m_pOBB->Update(&m_matWorld);
	}
	else
	{
		if (m_isCondition)
		{
			//g_pObjectManager->RemoveObject(m_pOBB);
		}
		else
			m_pOBB->Update(&m_matWorld);
	}
}

void CDoor::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		if (m_ObjectType == eG_DoorFrame)
		{
			m_matWorld = m_matS * m_matR * m_matT;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		}
		else if(m_ObjectType == eG_Door)
		{
			m_matWorld = m_matS * m_matRotGimmick * m_matT;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		}
		if (m_pMesh == NULL)
			return;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			else
				g_pD3DDevice->SetTexture(0, m_pTexture);

			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
			m_pMesh->DrawSubset(i);
		}
		g_pD3DDevice->SetTexture(0, NULL);
	}
}