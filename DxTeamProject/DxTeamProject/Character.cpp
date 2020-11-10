#include "stdafx.h"
#include "Character.h"
#include "OBB.h"

CCharacter::CCharacter()
	: m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
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
}

void CCharacter::ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam)
{
	// >> todo
	// - UI�� �������� �� �̵� ���� Ȯ�� �ʿ�
	// - �밢�� �̵� ���� Ȯ�� �ʿ�
	//   => �밢�� �̵��� �ӵ� ������
	//   => sa, sd �ݴ�� �۵���

	 switch (message)
	 {
	 case 'W':
	 	m_vPosition = DoMove(0.0f);
	 	break;
	 case 'S':
	 	m_vPosition = DoMove(D3DX_PI);
	 	break;
	 case 'A':
	 	m_vPosition = DoMove(-D3DX_PI / 2.0f);
	 	break;
	 case 'D':
	 	m_vPosition = DoMove(D3DX_PI / 2.0f);
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
	v.c = D3DCOLOR_XRGB(255, 0, 0); // ĳ���� �ĸ� ����
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : back 
	v.c = D3DCOLOR_XRGB(0, 0, 255); // ĳ���� ���� �Ķ�
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);

	// : top 
	v.c = D3DCOLOR_XRGB(127, 127, 127); // ĳ���� �Ѳ�(��ȭ)
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : left
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// : right 
	v.c = D3DCOLOR_XRGB(0, 0, 0);
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
	// if (m_vDirection != cameradirection)
		m_vDirection = cameradirection;
}

D3DXVECTOR3 CCharacter::DoMove(const float& radian)
{
	m_vDirection.y = 0;
	D3DXMatrixRotationY(&m_matRotY, radian);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &m_matRotY);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);

	D3DXVECTOR3 tempPos(0, 0, 0);
	D3DXVECTOR3 tempUp(0, 1, 0);
	D3DXMatrixLookAtLH(&m_matRotY, &tempPos, &m_vDirection, &tempUp);
	D3DXMatrixTranspose(&m_matRotY, &m_matRotY);

	return m_vPosition + (m_vDirection * 0.005f);
}

void CCharacter::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3 & CCharacter::GetPosition()
{
	return m_vPosition;
}

D3DXMATRIXA16 * CCharacter::GetTransform()
{
	return &m_matWorld;
}