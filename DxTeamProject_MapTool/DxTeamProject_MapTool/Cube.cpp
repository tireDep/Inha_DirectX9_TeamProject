#include "stdafx.h"
#include "Cube.h"

CCube::CCube() :
	m_vDirection(0, 0, 1),
	m_vPosition(0, 0.5f, 0),
	m_fRotY(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

CCube::~CCube()
{
}

void CCube::Setup()
{
	float fSzie = 0.5f;
	ST_PC_VERTEX v;
	// : front 
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(-fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);

	// : back 
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(-fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);

	// : left
	v.c = D3DCOLOR_XRGB(255, 255, 0);
	v.p = D3DXVECTOR3(-fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);

	// : right 
	v.c = D3DCOLOR_XRGB(0, 255, 255);
	v.p = D3DXVECTOR3(fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);

	// : top 
	v.c = D3DCOLOR_XRGB(150, 150, 150);
	v.p = D3DXVECTOR3(-fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, fSzie, -fSzie);
	m_vecVertex.push_back(v);

	// : bottom
	v.c = D3DCOLOR_XRGB(0, 0, 0);
	v.p = D3DXVECTOR3(-fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, -fSzie, -fSzie);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fSzie, -fSzie, fSzie);
	m_vecVertex.push_back(v);
}

void CCube::Update()
{
	float fSpeed = 0.001f;
	if (GetKeyState(VK_LEFT) & 0X8000)
	{
		m_fRotY -= fSpeed;
		// m_vPosition -= (D3DXVECTOR3(1, 0, 0) * fSpeed);
	}
	if (GetKeyState(VK_RIGHT) & 0X8000)
	{
		m_fRotY += fSpeed;
		// m_vPosition += (D3DXVECTOR3(1, 0, 0) * fSpeed);
	}

	if (GetKeyState(VK_UP) & 0X8000)
	{
		m_vPosition += (m_vDirection * fSpeed);
	}
	if (GetKeyState(VK_DOWN) & 0X8000)
	{
		m_vPosition -= (m_vDirection * fSpeed);
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;
}

void CCube::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3 & CCube::GetPosition()
{
	return m_vPosition;
}
