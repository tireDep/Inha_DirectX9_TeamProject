#include "stdafx.h"
#include "Character.h"
#include "OBB.h"

CCharacter::CCharacter()
	: m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
	, m_pOBB(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRotY);
	m_strName = "Character";
}

COBB * CCharacter::GetOBB()
{
	return m_pOBB;
}

void CCharacter::SetColor(D3DCOLOR c)
{
	for (int i = 12; i <= 17; i++)
		m_vecVertex[i].c = c;
	m_color = c;
}


void CCharacter::ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool pushA = false;
	static bool pushD = false;
	static bool pushW = false;
	static bool pushS = false;

	pushW = GetAsyncKeyState('W') & 0x8000 ? true : false;
	pushS = GetAsyncKeyState('S') & 0x8000 ? true : false;
	pushA = GetAsyncKeyState('A') & 0x8000 ? true : false;
	pushD = GetAsyncKeyState('D') & 0x8000 ? true : false;

	float speed = 0.0f;
	float rotation = 0.0f;

	switch (message)
	{
		case 'W':
			speed = 0.003f;
			rotation = 0.0f;
			if (pushA)
			{
				rotation = D3DX_PI / 4.0f * -1;
				speed = 0.0021f;
			}
			else if (pushD)
			{
				rotation = D3DX_PI / 4.0f;
				speed = 0.0021f;
			}
			DoRotation(rotation);
			DoMove(speed);
			break;
		case 'S':
			rotation = D3DX_PI;
			speed = 0.003f;
			if (pushA)
			{
				rotation = D3DX_PI + D3DX_PI / 4.0f;
				speed = 0.0021f;
			}
			else if (pushD)
			{
				rotation = (D3DX_PI + D3DX_PI / 4.0f) * -1;
				speed = 0.0021f;
			}
			DoRotation(rotation);
			DoMove(speed);
			break;

		case 'A':
			rotation = -D3DX_PI / 2.0f;
			speed = 0.003f;
			if (pushW || pushS) 
			{ 
				rotation = 0; 
				speed = 0.0021f; 
			}
			DoRotation(rotation);
			DoMove(speed);
			break;
		case 'D':
			rotation = D3DX_PI / 2.0f;
			speed = 0.003f;
			if (pushW || pushS)
			{
				rotation = 0;
				speed = 0.0021f;
			}			
			DoRotation(rotation);
			DoMove(speed);
			break;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = m_matRotY * matT;
}

string CCharacter::GetName()
{
	return m_strName;
}

CCharacter::~CCharacter()
{
}

void CCharacter::Setup()
{
	ST_PC_VERTEX v;
	float cubeSize = 0.5f;

	// : front
	v.c = D3DCOLOR_XRGB(255, 0, 0); // Ä³¸¯ÅÍ ÈÄ¸é »¡°­
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : back 
	v.c = D3DCOLOR_XRGB(0, 0, 255); // Ä³¸¯ÅÍ Á¤¸é ÆÄ¶û
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);

	// : top 
	v.c = D3DCOLOR_XRGB(127, 127, 127); // Ä³¸¯ÅÍ ¶Ñ²±(º¯È­)
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : left
	v.c = D3DCOLOR_XRGB(255, 255, 255); // Ä³¸¯ÅÍ ¿Þ¸é(Èò)
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : right 
	v.c = D3DCOLOR_XRGB(0, 0, 0); // Ä³¸¯ÅÍ ¿À¸¥¸é(Èæ)
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);

	// : bottom
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);

	m_pOBB = new COBB;
	m_pOBB->SetupCube(m_vecVertex[0], m_vecVertex[11]);
}

void CCharacter::Update(D3DXVECTOR3 cameradirection)
{
	m_vDirection = cameradirection;

	if (GetKeyState('1') & 0X8000) // »¡
		 SetColor(D3DCOLOR_XRGB(255, 0, 0));

	if (GetKeyState('2') & 0X8000) // ÃÊ·Ï
		SetColor(D3DCOLOR_XRGB(0, 255, 0));

	if (GetKeyState('3') & 0X8000) //ÆÄ¶û
		SetColor(D3DCOLOR_XRGB(0, 0, 255));

	if (GetKeyState('4') & 0X8000) //Èò»ö
		SetColor(D3DCOLOR_XRGB(255, 255, 255));

	if (GetKeyState('5') & 0X8000) //³ë¶õ
		SetColor(D3DCOLOR_XRGB(255, 255, 0));

	if (GetKeyState('6') & 0X8000) //°ËÁ¤
		SetColor(D3DCOLOR_XRGB(0, 0, 0));

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = m_matRotY * matT;

	if (m_pOBB)
		m_pOBB->Update(&m_matWorld);
}

void CCharacter::DoRotation(const float & radian)
{
	m_vDirection.y = 0;
	D3DXMatrixRotationY(&m_matRotY, radian);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &m_matRotY);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);

	D3DXVECTOR3 tempPos(0, 0, 0);
	D3DXVECTOR3 tempUp(0, 1, 0);
	D3DXMatrixLookAtLH(&m_matRotY, &tempPos, &m_vDirection, &tempUp);
	D3DXMatrixTranspose(&m_matRotY, &m_matRotY);
}

void CCharacter::DoMove(const float& velocity)
{
	m_vPosition = m_vPosition + (m_vDirection * velocity);
}

void CCharacter::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	 m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3 & CCharacter::GetPosition()
{
	return m_vPosition;
}

D3DXMATRIXA16 * CCharacter::GetTransform()
{
	return &m_matWorld;
}

D3DCOLOR CCharacter::GetColor()
{
	return m_color;
}