#include "stdafx.h"
#include "SpotLight.h"

SpotLight::SpotLight() :
	m_vRotation(0.0f , 0.0f, 0.0f)
{
	SetUp();
}

SpotLight::~SpotLight()
{

}

void SpotLight::SetUp()
{
	ZeroMemory(&m_SpotLight, sizeof(D3DLIGHT9));
	m_SpotLight.Type = D3DLIGHT_SPOT;
	m_SpotLight.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.0f, 1.0f);
	m_SpotLight.Specular = D3DXCOLOR(0.0f, 0.7f, 0.0f, 1.0f);
	m_SpotLight.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.0f, 1.0f);

	m_SpotLight.Position = D3DXVECTOR3(-5, 5, -5);

	D3DXVECTOR3 dir(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&dir, &dir);
	m_SpotLight.Direction = dir;

	m_SpotLight.Range = 20.0f;
	m_SpotLight.Falloff = 1.0f;

	m_SpotLight.Attenuation0 = 0.045f;
	m_SpotLight.Attenuation1 = 0.045f;
	m_SpotLight.Attenuation2 = 0.045f;

	m_SpotLight.Phi = D3DX_PI / 2.0f;
	m_SpotLight.Theta = D3DX_PI / 4.0f;

	g_pD3DDevice->SetLight(1, &m_SpotLight);
	g_pD3DDevice->LightEnable(1, true);

	// >> lightBox
	ST_PC_VERTEX v;
	float x, y, z;
	x = -5.0f; y = 5.0f; z = -5.0f;
	float addNum = 0.25;
	// : front 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x - addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x - addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x - addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);

	// : back 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x - addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x - addNum, y + addNum, z + addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x - addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z + addNum);
	m_vecVertex.push_back(v);

	// : left
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x - addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x - addNum, y + addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x - addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x - addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x - addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x - addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);

	// : right 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x + addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z + addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x + addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);

	// : top 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x - addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + -0.25f, y + addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z + addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x - addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y + addNum, z - addNum);
	m_vecVertex.push_back(v);

	// : bottom
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(x - addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x - addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(x - addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y - addNum, z - addNum);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(x + addNum, y - addNum, z + addNum);
	m_vecVertex.push_back(v);
}

void SpotLight::Update()
{
	if (GetKeyState(VK_UP) & 0x8000)
		m_vRotation.x += 0.05f;
	if (GetKeyState(VK_DOWN) & 0x8000)
		m_vRotation.x -= 0.05f;

	if (GetKeyState(VK_LEFT) & 0x8000)
		m_vRotation.z += 0.05f;
	if (GetKeyState(VK_RIGHT) & 0x8000)
		m_vRotation.z -= 0.05f;

	if (GetKeyState(VK_ESCAPE) & 0x8000)
		m_vRotation = D3DXVECTOR3(0, 0, 0);	// Reset

	D3DXVECTOR3 dir(0, -1, 0);
	D3DXMATRIXA16 matRx, matRz;
	D3DXMatrixRotationZ(&matRz, m_vRotation.z);
	D3DXMatrixRotationX(&matRx, m_vRotation.x);

	D3DXMATRIXA16 matR = matRx * matRz;
	D3DXVec3TransformCoord(&dir, &dir, &matR);
	
	D3DXVec3Normalize(&dir, &dir);

	m_SpotLight.Direction = dir;

	g_pD3DDevice->SetLight(1, &m_SpotLight);
}

void SpotLight::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
