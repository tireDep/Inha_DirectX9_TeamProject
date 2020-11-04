#include "stdafx.h"
#include "PointLight.h"

PointLight::PointLight()
{
	SetUp();
}

PointLight::~PointLight()
{

}

void PointLight::SetUp()
{
	ZeroMemory(&m_PointLight, sizeof(D3DLIGHT9));

	m_PointLight.Type = D3DLIGHT_POINT;
	m_PointLight.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.2f, 1.0f);
	m_PointLight.Specular = D3DXCOLOR(0.0f, 0.0f, 0.2f, 1.0f) * 0.3f;
	m_PointLight.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.2f, 1.0f) * 0.6f;

	m_PointLight.Attenuation0 = 0.045f;
	m_PointLight.Attenuation1 = 0.045f;
	m_PointLight.Attenuation2 = 0.045f;
	// 빛의 세기가 약해지는 정도

	m_PointLight.Position = D3DXVECTOR3(5.0f, 2.0f, 5.0f);

	m_PointLight.Range = 5.0f;

	g_pD3DDevice->SetLight(2, &m_PointLight);
	g_pD3DDevice->LightEnable(2, true);

	// >> lightBox
	ST_PC_VERTEX v;
	float x, y, z;
	x = 5.0f; y = 2.0f; z = 5.0f;
	float addNum = 0.25;
	// : front 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x-addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x-addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x-addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);

	// : back 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x-addNum, y - addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x-addNum, y + addNum, z+addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x-addNum, y - addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y - addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z+addNum);
	m_vecVertex.push_back(v);

	// : left
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x-addNum, y - addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x-addNum, y + addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x-addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x-addNum, y - addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x-addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x-addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);

	// : right 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x+addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z+addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x+addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y - addNum, z+addNum);
	m_vecVertex.push_back(v);

	// : top 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x-addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+-0.25f, y + addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z+addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x-addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y + addNum, z-addNum);
	m_vecVertex.push_back(v);

	// : bottom
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x-addNum, y - addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x-addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x-addNum, y - addNum, z+addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y - addNum, z-addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x+addNum, y - addNum, z+0.25f);
	m_vecVertex.push_back(v);
}

void PointLight::Update()
{
	if (GetKeyState('1') & 0x8000)
		m_PointLight.Range += 0.05f;
	if (GetKeyState('2') & 0x8000)
		m_PointLight.Range = m_PointLight.Range - 0.05f < 0.00001f ? 0 : m_PointLight.Range - 0.05f;
	if (GetKeyState('3') & 0x8000)
		m_PointLight.Range = 5.0f;	// Reset

	g_pD3DDevice->SetLight(2, &m_PointLight);
}

void PointLight::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
