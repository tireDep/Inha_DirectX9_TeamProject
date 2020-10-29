#include "stdafx.h"
#include "Cube.h"
#include <time.h>

CCube::CCube() :
	m_vDirection(0, 0, 1),
	m_vPosition(0, 0, 0),
	m_fRotY(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);

	srand((unsigned)time(NULL));
}


CCube::~CCube()
{
}

void CCube::Setup()
{
	float cubeSize = 0.5f;
	ST_PC_VERTEX v;

	// front
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	// back
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	// left
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	// right
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	// top
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);
	m_vecVertex.push_back(v);

	// bottom
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);
	m_vecVertex.push_back(v);
}

void CCube::Update()
{
	float speed = 0.001f;
	if (GetKeyState('A') & 0x8000)
		m_fRotY -= speed;
	if (GetKeyState('D') & 0x8000)
		m_fRotY += speed;

	if (GetKeyState('W') & 0x8000)
		m_vPosition += (m_vDirection * speed);
	if (GetKeyState('S') & 0x8000)
		m_vPosition -= (m_vDirection * speed);
	// 이동

	RECT rc;	// 화면 사이즈 변경 x 라면 미리 구해놔도 상관 x
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;
}

void CCube::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3 & CCube::GetPosition()
{
	return m_vPosition;
}
