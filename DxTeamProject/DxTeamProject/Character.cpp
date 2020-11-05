#include "stdafx.h"
#include "Character.h"


CCharacter::CCharacter()
	: m_fRotY(0.0f)
	, m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


CCharacter::~CCharacter()
{
}

void CCharacter::Setup()
{
}

void CCharacter::Update()
{
	
	if (GetKeyState('A') & 0X8000)
	{
		m_fRotY -= 0.001f;
	}
	if (GetKeyState('D') & 0X8000)
	{
		m_fRotY += 0.001f;
	}


	D3DXVECTOR3 vPosition = m_vPosition;
	if (GetKeyState('W') & 0X8000)
	{
		vPosition = m_vPosition + (m_vDirection*0.001f);
	}
	if (GetKeyState('S') & 0X8000)
	{
		vPosition = m_vPosition - (m_vDirection*0.001f);
	}

	/*RECT rc;
	GetClientRect(g_hWnd, &rc);*/

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	m_vPosition = vPosition;
	D3DXMatrixTranslation(&matT,
		m_vPosition.x,
		m_vPosition.y,
		m_vPosition.z);

	m_matWorld = matR * matT;
}

void CCharacter::Render()
{

}

D3DXVECTOR3 & CCharacter::GetPosition()
{
	return m_vPosition;
}
